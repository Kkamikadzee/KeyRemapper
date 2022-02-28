#pragma once
#include <windows.h>
#include "ILowLevelProcObserver.h"

namespace Kmk
{
    class ILowLevelProcSubject
    {
    public:
        virtual ~ILowLevelProcSubject() = default;

        virtual void Attach(const ILowLevelProcObserver *) = 0;
        virtual void Detach(const ILowLevelProcObserver *) = 0;
        virtual void Notify(const WPARAM, const LPARAM) = 0;
    };
}