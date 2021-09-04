#pragma once
#include <list>
#include <Windows.h>
#include "Switcher.cpp"

class SwitcherStorage 
{
private:
	Switcher** _keySwitchers;
	UINT _countSwitchers;
public:
	SwitcherStorage(Switcher** keySwitchersArray, UINT countSwitchers)
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
				if (_keySwitchers[i]->ReplaceableKeyIsDowned)
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
				if (_keySwitchers[i]->ReplaceableKeyIsUpped)
				{
					return _keySwitchers[i];
				}
			}
		}
	}
};