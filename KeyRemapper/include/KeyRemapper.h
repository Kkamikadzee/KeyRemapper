#pragma once
#include <windows.h>
#include <vector>
#include <forward_list>
#include <mutex>
#include "ILowLevelProcObserver.h"
#include "ILowLevelProcSubject.h"

namespace Kmk
{
    class KeyRemapper
    {
    public:
        static KeyRemapper *GetInstance(ILowLevelProcSubject *keyboardSubject,
                                        std::vector<std::forward_list<ILowLevelProcObserver *>> &keyboardObserversSets,
                                        ILowLevelProcSubject *mouseSubject,
                                        std::vector<std::forward_list<ILowLevelProcObserver *>> &mouseObserversSets);
        static KeyRemapper *TryGetInstance();
        static void DestructInstance();

        KeyRemapper(const KeyRemapper &orig) = delete;
        ~KeyRemapper();

        KeyRemapper operator=(KeyRemapper &orig) = delete;

        void Activate(const std::size_t setIndex = 0);
        void Deactivate();

    protected:
        KeyRemapper(ILowLevelProcSubject *keyboardSubject,
                    std::vector<std::forward_list<ILowLevelProcObserver *>> &keyboardObserversSets,
                    ILowLevelProcSubject *mouseSubject,
                    std::vector<std::forward_list<ILowLevelProcObserver *>> &mouseObserversSets);

    private:
        static KeyRemapper *_instance;
        static std::mutex _instanceMutex;

        bool _isActive;
        std::size_t _activeObserversSet;

        std::mutex _subjectsMutex;

        ILowLevelProcSubject *_keyboardSubject;
        std::vector<std::forward_list<ILowLevelProcObserver *>> _keyboardObserversSets;

        ILowLevelProcSubject *_mouseSubject;
        std::vector<std::forward_list<ILowLevelProcObserver *>> _mouseObserversSets;

        HHOOK _keyboardLlHook;
        HHOOK _mouseLlHook;

        static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    };

    void EraseObserversSets(std::vector<std::forward_list<ILowLevelProcObserver *>> &observersSets);
    void AttachRangeToSubject(std::forward_list<ILowLevelProcObserver *>::iterator begin,
                              std::forward_list<ILowLevelProcObserver *>::iterator end,
                              ILowLevelProcSubject *subject);
    void DetachRange(std::forward_list<ILowLevelProcObserver *>::iterator begin,
                     std::forward_list<ILowLevelProcObserver *>::iterator end);

    inline KeyRemapper *KeyRemapper::TryGetInstance()
    {
        return _instance;
    }
}
