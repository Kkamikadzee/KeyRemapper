#include <vector>
#include <map>
#include <Windows.h>
#include "KeyHandler.h"
#include "Switcher.h"
#include "SwitchersStorage.h"
#include "SwitchersStorageCreator.h"

namespace KmkKeyRemapper
{
	std::vector<Switcher *> *SwitchersStorageCreator::AddSwitcherIntoVector(std::vector<Switcher *> *switchers, DWORD replaceableKeyCode, DWORD replacementKeyCode)
	{
		KeyHandler *keyHandler = new KeyHandler();
		Switcher *switcher = new Switcher(replaceableKeyCode, replacementKeyCode, keyHandler);
		switchers->push_back(switcher);
		return switchers;
	}

	SwitchersStorageCreator::SwitchersStorageCreator() {}

	SwitchersStorage *SwitchersStorageCreator::Create(std::map<char, char> pairsReplacableKeyAndReplacementKey)
	{
		std::vector<Switcher *> *switchersLikeVector = new std::vector<Switcher *>();
		for (auto &pair : pairsReplacableKeyAndReplacementKey)
		{
			AddSwitcherIntoVector(switchersLikeVector, VkKeyScan(pair.first), VkKeyScan(pair.second));
		}

		Switcher **switchersLikeArray = new Switcher *[switchersLikeVector->size()];
		std::copy(switchersLikeVector->begin(), switchersLikeVector->end(), switchersLikeArray);

		SwitchersStorage *storage = new SwitchersStorage(switchersLikeArray, switchersLikeVector->size());

		delete switchersLikeVector;

		return storage;
	}
}