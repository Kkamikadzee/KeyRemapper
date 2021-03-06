#pragma once
#include <windows.h>
#include "IKeyHandler.h"

namespace Kmk
{
    class IKeyEventReplacer
    {
    public:
        explicit IKeyEventReplacer(IKeyHandler *keyHandler) : _keyHandler(keyHandler) {}
        IKeyEventReplacer(const IKeyEventReplacer &orig) = delete;
        virtual ~IKeyEventReplacer()
        {
            delete _keyHandler;
        }

        IKeyEventReplacer &operator=(IKeyEventReplacer &orig) = delete;

        virtual bool Invoke(const WPARAM wParam, const LPARAM lParam) const = 0;

    protected:
        IKeyHandler *_keyHandler;
    };
}