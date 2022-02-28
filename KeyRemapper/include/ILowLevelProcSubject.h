#pragma once
#include <windows.h>
#include "ILowLevelProcObserver.h"

namespace Kmk
{
    class ILowLevelProcSubject
    {
    public:
        virtual ~ILowLevelProcSubject() = default;

        virtual void Attach(ILowLevelProcObserver *observer) = 0;
        virtual void Detach(ILowLevelProcObserver *observer) = 0;
        virtual void Notify(const WPARAM wParam, const LPARAM lParam) = 0;
    };
}