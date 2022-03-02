#include <windows.h>
#include "IKeyHandler.h"
#include "IKeyEventReplacer.h"
#include "Keyboard/KeyboardKeyEventReplacer.h"
#include "Enums.h"

namespace Kmk
{
    KeyboardKeyEventReplacer::KeyboardKeyEventReplacer(IKeyHandler *keyHandler, DWORD replaceableKeyCode)
        : IKeyEventReplacer(keyHandler), _replaceableKeyCode(replaceableKeyCode) {}

    bool KeyboardKeyEventReplacer::Invoke(const WPARAM wParam, const LPARAM lParam) const
    {
        auto pkhs = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

        if ((pkhs->vkCode == _replaceableKeyCode) && (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler)))
        {
            if (wParam == WM_KEYDOWN)
            {
                _keyHandler->KeyDown();
                return true;
            }
            else if (wParam == WM_KEYUP)
            {
                _keyHandler->KeyUp();
                return true;
            }
        }
        
        return false;
    }
}