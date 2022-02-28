#include <windows.h>
#include "ILowLevelProcSubject.h"
#include "LowLevelProcObserver.h"
#include "IKeyHandler.h"

namespace Kmk
{
    LowLevelProcObserver::LowLevelProcObserver(
        ILowLevelProcSubject *subject,
        const IKeyEventReplacer *keyHandler)
        : _subject(subject), _keyReplacer(keyHandler)
    {
    }

    void LowLevelProcObserver::Update(const WPARAM wParam, const LPARAM lParam)
    {
        _keyReplacer->Invoke(wParam, lParam);
    }

    void LowLevelProcObserver::Detach()
    {
        _subject->Detach(this);
    }
}
