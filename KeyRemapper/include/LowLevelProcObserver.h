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
        ~LowLevelProcObserver() = default;

        void Update(const WPARAM wParam, const LPARAM lParam);
        void Detach();

    private:
        const IKeyEventReplacer *_keyReplacer;
        ILowLevelProcSubject *_subject;
    };
}
