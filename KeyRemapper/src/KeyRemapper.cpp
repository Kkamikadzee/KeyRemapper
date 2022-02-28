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

    inline KeyRemapper *KeyRemapper::TryGetInstance()
    {
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
        Deativate();

        delete _keyboardSubject;
        delete _mouseSubject;

        EraseObserversSets(_keyboardObserversSets);
        EraseObserversSets(_mouseObserversSets);
    }

    void KeyRemapper::Activate(const std::size_t setIndex)
    {
        if (_isActive)
        {
            Deativate();
        }

        if (_keyboardObserversSets.size() != _mouseObserversSets.size())
        {
            throw std::runtime_error("Size keyboard sets and mouse sets not equals.");
        }

        if (_subjectsMutex.try_lock())
        {
            AttachRangeToSubject(_keyboardObserversSets[setIndex].begin(), _keyboardObserversSets[setIndex].end(), _keyboardSubject);
            AttachRangeToSubject(_mouseObserversSets[setIndex].begin(), _mouseObserversSets[setIndex].end(), _mouseSubject);

            _keyboardLlHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyRemapper::LowLevelKeyboardProc, nullptr, 0);
            _mouseLlHook = SetWindowsHookEx(WH_MOUSE_LL, KeyRemapper::LowLevelMouseProc, nullptr, 0);

            _activeObserversSet = setIndex;
            _isActive = true;

            _subjectsMutex.unlock();
        }
    }

    void KeyRemapper::Deativate()
    {
        if (_isActive)
        {
            UnhookWindowsHookEx(_keyboardLlHook);
            UnhookWindowsHookEx(_mouseLlHook);

            DetachRange(_keyboardObserversSets[_activeObserversSet].begin(), _keyboardObserversSets[_activeObserversSet].end());
            DetachRange(_mouseObserversSets[_activeObserversSet].begin(), _mouseObserversSets[_activeObserversSet].end());

            _isActive = false;
        }
    }

    LRESULT CALLBACK KeyRemapper::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        auto instance = KeyRemapper::TryGetInstance();
        if (instance != nullptr)
        {
            instance->_keyboardSubject->Notify(wParam, lParam);
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
        for (auto listPtr = observersSets.rbegin(); listPtr != observersSets.rend(); listPtr = observersSets.rbegin())
        {
            for (auto elementPtr = listPtr->begin(); elementPtr != listPtr->end(); elementPtr = listPtr->begin())
            {
                listPtr->pop_front();
                delete *elementPtr;
            }

            observersSets.pop_back();
        }
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
