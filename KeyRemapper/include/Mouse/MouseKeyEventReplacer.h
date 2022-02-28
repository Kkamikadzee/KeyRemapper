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
        MouseKeyEventReplacer(IKeyHandler *keyHandler, MouseButton replaceableKey);

        ~MouseKeyEventReplacer() = default;

        void Invoke(const WPARAM wParam, const LPARAM lParam) const override;

    private:
        static int GetKeyDownCodeByMouseButton(MouseButton key);
        static int GetKeyUpCodeByMouseButton(MouseButton key);

    private:
        int _keyDownCode;
        int _keyUpCode;
    };
}