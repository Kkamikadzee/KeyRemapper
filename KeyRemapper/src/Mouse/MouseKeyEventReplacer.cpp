#include <windows.h>
#include <stdexcept>
#include "IKeyHandler.h"
#include "IKeyEventReplacer.h"
#include "Mouse/MouseKeyEventReplacer.h"
#include "Emuns.h"

namespace Kmk
{
    MouseKeyEventReplacer::MouseKeyEventReplacer(IKeyHandler *keyHandler, MouseButton replaceableKey)
        : IKeyEventReplacer(keyHandler),
          _keyDownCode(MouseKeyEventReplacer::GetKeyDownCodeByMouseButton(replaceableKey)),
          _keyUpCode(MouseKeyEventReplacer::GetKeyUpCodeByMouseButton(replaceableKey)) {}

    void MouseKeyEventReplacer::Invoke(const WPARAM wParam, const LPARAM lParam) const
    {
        auto pmhs = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

        if (pmhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
        {
            if (wParam == _keyDownCode)
            {
                _keyHandler->KeyDown();
            }
            else if (wParam == _keyUpCode)
            {
                _keyHandler->KeyUp();
            }
        }
    }

    int MouseKeyEventReplacer::GetKeyDownCodeByMouseButton(MouseButton key)
    {
        switch (key)
        {
        case MouseButton::Left:
            return WM_LBUTTONDOWN;
        case MouseButton::Right:
            return WM_RBUTTONDOWN;
        default:
            throw std::runtime_error("Unknown mouse button.");
        }
    }

    int MouseKeyEventReplacer::GetKeyUpCodeByMouseButton(MouseButton key)
    {
        switch (key)
        {
        case MouseButton::Left:
            return WM_LBUTTONUP;
        case MouseButton::Right:
            return WM_RBUTTONUP;
        default:
            throw std::runtime_error("Unknown mouse button.");
        }
    }
}