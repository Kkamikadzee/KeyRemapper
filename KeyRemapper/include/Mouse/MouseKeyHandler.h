#pragma once
#include "../Enums.h"
#include "../IKeyHandler.h"

namespace Kmk
{
    class MouseKeyHandler : public IKeyHandler
    {
    public:
        MouseKeyHandler(const MouseButton replaceableKey);
        ~MouseKeyHandler() = default;

        void KeyDown() override;
        void KeyUp() override;

    private:
        const DWORD _eventKeyDown, _eventKeyUp;
    };
}
