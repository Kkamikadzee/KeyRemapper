#pragma once
#include <windows.h>
#include "../IKeyHandler.h"
#include "../IKeyEventReplacer.h"

namespace Kmk
{
    class KeyboardKeyEventReplacer : public IKeyEventReplacer
    {
    public:
        KeyboardKeyEventReplacer(IKeyHandler *keyHandler, DWORD replaceableKeyCode);

        ~KeyboardKeyEventReplacer() = default;

        bool Invoke(const WPARAM wParam, const LPARAM lParam) const override;

    private:
        DWORD _replaceableKeyCode;
    };
}