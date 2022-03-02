#pragma once
#include <windows.h>
#include "../IKeyHandler.h"
#include "../IKeyEventReplacer.h"
#include "../Enums.h"

namespace Kmk
{
    class MouseKeyEventReplacer : public IKeyEventReplacer
    {
    public:
        MouseKeyEventReplacer(IKeyHandler *keyHandler, const MouseButton replaceableKey);

        ~MouseKeyEventReplacer() = default;

        bool Invoke(const WPARAM wParam, const LPARAM lParam) const override;

    private:
        int _keyDownCode;
        int _keyUpCode;
    };
}