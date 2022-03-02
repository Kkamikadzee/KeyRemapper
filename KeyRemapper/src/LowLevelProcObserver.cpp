#include <windows.h>
#include "ILowLevelProcSubject.h"
#include "LowLevelProcObserver.h"
#include "IKeyHandler.h"

namespace Kmk
{
    LowLevelProcObserver::LowLevelProcObserver(
        ILowLevelProcSubject *subject,
        const IKeyEventReplacer *keyReplacer)
        : _subject(subject), _keyReplacer(keyReplacer)
    {
    }

    bool LowLevelProcObserver::Update(const WPARAM wParam, const LPARAM lParam)
    {
        return _keyReplacer->Invoke(wParam, lParam);
    }

    void LowLevelProcObserver::Detach()
    {
        _subject->Detach(this);
    }
}
