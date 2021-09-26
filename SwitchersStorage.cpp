#pragma once
#include <Windows.h>
#include "Switcher.cpp"

class SwitchersStorage 
{
private:
	Switcher** _keySwitchers;
	UINT _countSwitchers;
public:
	SwitchersStorage(Switcher** keySwitchersArray, UINT countSwitchers)
	{
		_keySwitchers = keySwitchersArray;
		_countSwitchers = countSwitchers;
	}

	Switcher* GetDownedKey(KBDLLHOOKSTRUCT* pkhs, WPARAM wParam)
	{
		if (wParam == WM_KEYDOWN)
		{
			for (int i = 0; i < _countSwitchers; i++)
			{
				if (_keySwitchers[i]->ReplaceableKeyIsDowned(pkhs))
				{
					return _keySwitchers[i];
				}
			}
		}
	}

	Switcher* GetUppedKey(KBDLLHOOKSTRUCT* pkhs, WPARAM wParam)
	{
		if (wParam == WM_KEYUP)
		{
			for (int i = 0; i < _countSwitchers; i++)
			{
				if (_keySwitchers[i]->ReplaceableKeyIsUpped(pkhs))
				{
					return _keySwitchers[i];
				}
			}
		}
	}
};