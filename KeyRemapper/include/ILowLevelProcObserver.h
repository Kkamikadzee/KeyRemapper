#pragma once
#include <windows.h>

namespace Kmk
{
    class ILowLevelProcObserver
    {
    public:
        virtual ~ILowLevelProcObserver() = default;

        virtual void Update(const WPARAM, const LPARAM) = 0;
        virtual void Detach() = 0;
    };
}
