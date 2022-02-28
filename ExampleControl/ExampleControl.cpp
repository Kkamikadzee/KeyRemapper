#include <windows.h>
#include <iostream>
#include <map>
#include <KeyHandler.h>
#include <ExtraInfo.h>
#include <SwitchersStorage.h>
#include <SwitchersStorageCreator.h>
#include <KeyRemapper.h>

using namespace Kmk;

static SwitchersStorage *storage1;
static SwitchersStorage *storage2;
static KeyRemapper *remapper;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pkhs = (KBDLLHOOKSTRUCT *)lParam;

	if (wParam == WM_KEYDOWN)
	{
		switch (pkhs->vkCode)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_F1:
			remapper->Activate();
			break;
		case VK_F2:
			remapper->SetStorage(storage1);
			break;
		case VK_F3:
			remapper->SetStorage(storage2);
			break;
		case VK_F4:
			remapper->Deactivate();
			break;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

int main()
{
	std::map<char, char> pairsReplacableKeyAndReplacementKey;
	pairsReplacableKeyAndReplacementKey['w'] = 's';
	pairsReplacableKeyAndReplacementKey['s'] = 'w';

	storage1 = (new SwitchersStorageCreator())->Create(pairsReplacableKeyAndReplacementKey);

	pairsReplacableKeyAndReplacementKey.clear();
	pairsReplacableKeyAndReplacementKey['a'] = 'd';
	pairsReplacableKeyAndReplacementKey['d'] = 'a';

	storage2 = (new SwitchersStorageCreator())->Create(pairsReplacableKeyAndReplacementKey);

	remapper = new KeyRemapper(storage1);

	HHOOK g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	UnhookWindowsHookEx(g_hHook);
	return 0;
}