#pragma once
#include <windows.h>
#include "IKeyHandler.h"

namespace Kmk
{
    class IKeyEventReplacer
    {
    public:
        IKeyEventReplacer(IKeyHandler *keyHandler) : _keyHandler(keyHandler) {}
        IKeyEventReplacer(const IKeyEventReplacer &orig) = delete;
        virtual ~IKeyEventReplacer()
        {
            delete _keyHandler;
        }

        IKeyEventReplacer &operator=(IKeyEventReplacer &orig) = delete;

        virtual void Invoke(const WPARAM wParam, const LPARAM lParam) const = 0;

    protected:
        IKeyHandler *_keyHandler;
    };
}