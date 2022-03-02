#include <windows.h>
#include "IKeyHandler.h"
#include "IKeyEventReplacer.h"
#include "Mouse/MouseKeyEventReplacer.h"
#include "Enums.h"

namespace Kmk
{
    MouseKeyEventReplacer::MouseKeyEventReplacer(IKeyHandler *keyHandler, const MouseButton replaceableKey)
        : IKeyEventReplacer(keyHandler),
          _keyDownCode(GetKeyDownCodeByMouseButton(replaceableKey)),
          _keyUpCode(GetKeyUpCodeByMouseButton(replaceableKey)) {}

    bool MouseKeyEventReplacer::Invoke(const WPARAM wParam, const LPARAM lParam) const
    {
        auto pmhs = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

        if (pmhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
        {
            if (wParam == _keyDownCode)
            {
                _keyHandler->KeyDown();
                return true;
            }
            else if (wParam == _keyUpCode)
            {
                _keyHandler->KeyUp();
                return true;
            }
        }

        return false;
    }
}