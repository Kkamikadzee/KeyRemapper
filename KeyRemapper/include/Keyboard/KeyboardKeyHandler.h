#pragma once
#include "../IKeyHandler.h"

namespace Kmk
{
    class KeyboardKeyHandler : public IKeyHandler
    {
    public:
        explicit KeyboardKeyHandler(DWORD key);
        ~KeyboardKeyHandler() = default;

        void KeyDown() override;
        void KeyUp() override;
    };
}
