#pragma once
#include <Windows.h>
#include "Switcher.h"

namespace KmkKeyRemapper
{
	class SwitchersStorage
	{
	private:
		Switcher** _keySwitchers;
		UINT _countSwitchers;
	public:
		SwitchersStorage(Switcher** keySwitchersArray, UINT countSwitchers);

		~SwitchersStorage();

		Switcher* GetDownedKey(KBDLLHOOKSTRUCT* pkhs, WPARAM wParam);

		Switcher* GetUppedKey(KBDLLHOOKSTRUCT* pkhs, WPARAM wParam);
	};
}
