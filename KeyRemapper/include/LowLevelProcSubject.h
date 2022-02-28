#pragma once
#include <windows.h>
#include <list>
#include "ILowLevelProcObserver.h"
#include "ILowLevelProcSubject.h"

namespace Kmk
{
    class LowLevelProcSubject : public ILowLevelProcSubject
    {
    public:
        LowLevelProcSubject() = default;
        ~LowLevelProcSubject() = default;

        void Attach(ILowLevelProcObserver *observer);
        void Detach(ILowLevelProcObserver *observer);
        void Notify(const WPARAM wParam, const LPARAM lParam);

    private:
        std::list<ILowLevelProcObserver *> _observers;
    };
}