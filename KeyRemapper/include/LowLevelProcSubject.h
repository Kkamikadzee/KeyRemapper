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
        LowLevelProcSubject(const LowLevelProcSubject &orig) = delete;
        ~LowLevelProcSubject() = default;

        LowLevelProcSubject operator=(LowLevelProcSubject &orig) = delete;

        void Attach(ILowLevelProcObserver *observer) override;
        void Detach(ILowLevelProcObserver *observer) override;
        bool Notify(const WPARAM wParam, const LPARAM lParam) override;

    private:
        std::list<ILowLevelProcObserver *> _observers;
    };
}