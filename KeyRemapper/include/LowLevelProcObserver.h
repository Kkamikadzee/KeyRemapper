#pragma once
#include <windows.h>
#include "ILowLevelProcObserver.h"
#include "ILowLevelProcSubject.h"
#include "IKeyEventReplacer.h"

namespace Kmk
{
    class LowLevelProcObserver : public ILowLevelProcObserver
    {
    public:
        LowLevelProcObserver(ILowLevelProcSubject *subject, const IKeyEventReplacer *keyHandler);
        LowLevelProcObserver(LowLevelProcObserver &orig) = delete;
        ~LowLevelProcObserver() = default;

        ILowLevelProcObserver operator=(ILowLevelProcObserver &orig) = delete;

        void Update(const WPARAM wParam, const LPARAM lParam) override;
        void Detach() override;

    private:
        const IKeyEventReplacer *_keyReplacer;
        ILowLevelProcSubject *_subject;
    };
}
