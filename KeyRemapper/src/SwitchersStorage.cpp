#include <Windows.h>
#include "Switcher.h"
#include "SwitchersStorage.h"

namespace KmkKeyRemapper
{
	SwitchersStorage::SwitchersStorage(Switcher **keySwitchersArray, UINT countSwitchers)
	{
		_keySwitchers = keySwitchersArray;
		_countSwitchers = countSwitchers;
	}

	SwitchersStorage::~SwitchersStorage()
	{
		for (UINT i = 0; i < _countSwitchers; i++)
		{
			delete _keySwitchers[i];
		}

		delete[] _keySwitchers;
	}

	Switcher *SwitchersStorage::GetDownedKey(KBDLLHOOKSTRUCT *pkhs, WPARAM wParam)
	{
		if (wParam == WM_KEYDOWN)
		{
			for (UINT i = 0; i < _countSwitchers; i++)
			{
				if (_keySwitchers[i]->ReplaceableKeyIsDownedOrUpped(pkhs))
				{
					return _keySwitchers[i];
				}
			}
		}

		return nullptr;
	}

	Switcher *SwitchersStorage::GetUppedKey(KBDLLHOOKSTRUCT *pkhs, WPARAM wParam)
	{
		if (wParam == WM_KEYUP)
		{
			for (UINT i = 0; i < _countSwitchers; i++)
			{
				if (_keySwitchers[i]->ReplaceableKeyIsDownedOrUpped(pkhs))
				{
					return _keySwitchers[i];
				}
			}
		}

		return nullptr;
	}
}