#include <windows.h>
#include <list>
#include "ILowLevelProcObserver.h"
#include "LowLevelProcSubject.h"

namespace Kmk
{
    void LowLevelProcSubject::Attach(ILowLevelProcObserver *observer)
    {
        _observers.push_back(observer);
    }

    void LowLevelProcSubject::Detach(ILowLevelProcObserver *observer)
    {
        _observers.remove(observer);
    }

    void LowLevelProcSubject::Notify(const WPARAM wParam, const LPARAM lParam)
    {
        for (auto observerPtr = _observers.begin(); observerPtr != _observers.end(); ++observerPtr)
        {
            (*observerPtr)->Update(wParam, lParam);
        }
    }
}