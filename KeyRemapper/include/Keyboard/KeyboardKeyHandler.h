#pragma once
#include "../IKeyHandler.h"

namespace Kmk
{
    class KeyboardKeyHandler : public IKeyHandler
    {
    public:
        KeyboardKeyHandler(DWORD key);
        ~KeyboardKeyHandler() = default;

        void KeyDown() override;
        void KeyUp() override;
    };
}
