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

    bool LowLevelProcSubject::Notify(const WPARAM wParam, const LPARAM lParam)
    {
        for (auto observerPtr = _observers.begin(); observerPtr != _observers.end(); ++observerPtr)
        {
            if((*observerPtr)->Update(wParam, lParam))
            {
                return true;
            }
        }

        return false;
    }
}