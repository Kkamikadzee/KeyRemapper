#include <windows.h>
#include <stdexcept>
#include "Enums.h"

namespace Kmk
{
    const int GetKeyDownCodeByMouseButton(const MouseButton key)
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

    const int GetKeyUpCodeByMouseButton(const MouseButton key)
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

    const int GetKeyDownEventByMouseButton(const MouseButton key)
    {
        switch (key)
        {
        case MouseButton::Left:
            return MOUSEEVENTF_LEFTDOWN;
        case MouseButton::Right:
            return MOUSEEVENTF_RIGHTDOWN;
        default:
            throw std::runtime_error("Unknown mouse button.");
        }
    }

    const int GetKeyUpEventByMouseButton(const MouseButton key)
    {
        switch (key)
        {
        case MouseButton::Left:
            return MOUSEEVENTF_LEFTUP;
        case MouseButton::Right:
            return MOUSEEVENTF_RIGHTUP;
        default:
            throw std::runtime_error("Unknown mouse button.");
        }
    }
}