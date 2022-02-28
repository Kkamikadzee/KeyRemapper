#pragma once
#include <windows.h>

namespace Kmk
{
    class ILowLevelProcObserver
    {
    public:
        virtual ~ILowLevelProcObserver() = default;

        virtual void Update(const WPARAM wParam, const LPARAM lParam) = 0;
        virtual void Detach() = 0;
    };
}
