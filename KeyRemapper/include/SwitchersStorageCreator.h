#pragma once
#include <vector>
#include <map>
#include <Windows.h>
#include "KeyHandler.h"
#include "Switcher.h"
#include "SwitchersStorage.h"

namespace KmkKeyRemapper
{
	class SwitchersStorageCreator
	{
	private:
		std::vector<Switcher *> *AddSwitcherIntoVector(std::vector<Switcher *> *switchers, DWORD replaceableKeyCode, DWORD replacementKeyCode);

	public:
		SwitchersStorageCreator();

		SwitchersStorage *Create(std::map<char, char> pairsReplacableKeyAndReplacementKey);
	};
}
