#pragma once
#include "../IKeyHandler.h"

namespace Kmk
{
    class MouseKeyHandler : public IKeyHandler
    {
    public:
        MouseKeyHandler(DWORD eventKeyDown, DWORD eventKeyUp);
        ~MouseKeyHandler() = default;

        void KeyDown() override;
        void KeyUp() override;

    private:
        const DWORD _eventKeyDown, _eventKeyUp;
    };
}
