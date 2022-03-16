#include <windows.h>
#include <vector>
#include <forward_list>
#include <mutex>
#include <exception>
#include <functional>
#include "ILowLevelProcObserver.h"
#include "ILowLevelProcSubject.h"
#include "KeyRemapper.h"

namespace Kmk
{
    KeyRemapper *KeyRemapper::_instance = nullptr;
    std::mutex KeyRemapper::_instanceMutex;

    KeyRemapper *KeyRemapper::GetInstance(ILowLevelProcSubject *keyboardSubject,
                                          std::vector<std::forward_list<ILowLevelProcObserver *>> &keyboardObserversSets,
                                          ILowLevelProcSubject *mouseSubject,
                                          std::vector<std::forward_list<ILowLevelProcObserver *>> &mouseObserversSets)
    {
        if (_instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(_instanceMutex);
            if (_instance == nullptr)
            {
                _instance = new KeyRemapper(keyboardSubject, keyboardObserversSets, mouseSubject, mouseObserversSets);
            }
        }

        return _instance;
    }

    void KeyRemapper::DestructInstance()
    {
        if (_instance != nullptr)
        {
            std::lock_guard<std::mutex> lock(_instanceMutex);
            delete _instance;
            _instance = nullptr;
        }
    }

    KeyRemapper::KeyRemapper(ILowLevelProcSubject *keyboardSubject,
                             std::vector<std::forward_list<ILowLevelProcObserver *>> &keyboardObserversSets,
                             ILowLevelProcSubject *mouseSubject,
                             std::vector<std::forward_list<ILowLevelProcObserver *>> &mouseObserversSets)
        : _keyboardSubject(keyboardSubject), _keyboardObserversSets(std::move(keyboardObserversSets)),
          _mouseSubject(mouseSubject), _mouseObserversSets(std::move(mouseObserversSets)),
          _keyboardLlHook(), _mouseLlHook(),
          _activeObserversSet(0), _isActive(false), _subjectsMutex()
    {
    }

    KeyRemapper::~KeyRemapper()
    {
        Deactivate();

        delete _keyboardSubject;
        delete _mouseSubject;

        EraseObserversSets(_keyboardObserversSets);
        EraseObserversSets(_mouseObserversSets);
    }

    void KeyRemapper::Activate(const std::size_t setIndex)
    {
        if (_isActive)
        {
            Deactivate();
        }

        if (_keyboardObserversSets.size() != _mouseObserversSets.size())
        {
            throw std::runtime_error("Size keyboard sets and mouse sets not equals.");
        }

        std::lock_guard<std::mutex> lock(_subjectsMutex);
        AttachRangeToSubject(_keyboardObserversSets[setIndex].begin(), _keyboardObserversSets[setIndex].end(), _keyboardSubject);
        AttachRangeToSubject(_mouseObserversSets[setIndex].begin(), _mouseObserversSets[setIndex].end(), _mouseSubject);

        _keyboardLlHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyRemapper::LowLevelKeyboardProc, nullptr, 0);
        _mouseLlHook = SetWindowsHookEx(WH_MOUSE_LL, KeyRemapper::LowLevelMouseProc, nullptr, 0);

        _activeObserversSet = setIndex;
        _isActive = true;
    }

    void KeyRemapper::Deactivate()
    {
        if (_isActive)
        {
            std::lock_guard<std::mutex> lock(_subjectsMutex);
            if (_isActive)
            {
                UnhookWindowsHookEx(_keyboardLlHook);
                UnhookWindowsHookEx(_mouseLlHook);

                DetachRange(_keyboardObserversSets[_activeObserversSet].begin(), _keyboardObserversSets[_activeObserversSet].end());
                DetachRange(_mouseObserversSets[_activeObserversSet].begin(), _mouseObserversSets[_activeObserversSet].end());

                _isActive = false;
            }
        }
    }

    LRESULT CALLBACK KeyRemapper::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        auto instance = KeyRemapper::TryGetInstance();
        if (instance != nullptr)
        {
            if(instance->_keyboardSubject->Notify(wParam, lParam))
            {
                return 1;
            }
        }

        return CallNextHookEx(0, nCode, wParam, lParam);
    }

    LRESULT CALLBACK KeyRemapper::LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        auto instance = KeyRemapper::TryGetInstance();
        if (instance != nullptr)
        {
            instance->_mouseSubject->Notify(wParam, lParam);
        }

        return CallNextHookEx(0, nCode, wParam, lParam);
    }

    void EraseObserversSets(std::vector<std::forward_list<ILowLevelProcObserver *>> &observersSets)
    {
        for (auto list : observersSets)
        {
            for (auto element: list)
            {
                delete element;
            }
        }
        observersSets.clear();
    }

    void AttachRangeToSubject(std::forward_list<ILowLevelProcObserver *>::iterator begin,
                              std::forward_list<ILowLevelProcObserver *>::iterator end,
                              ILowLevelProcSubject *subject)
    {
        for (auto currentPtr = begin; currentPtr != end; ++currentPtr)
        {
            subject->Attach(*currentPtr);
        }
    }

    void DetachRange(std::forward_list<ILowLevelProcObserver *>::iterator begin,
                     std::forward_list<ILowLevelProcObserver *>::iterator end)
    {
        for (auto currentPtr = begin; currentPtr != end; ++currentPtr)
        {
            (*currentPtr)->Detach();
        }
    }
}
