#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <KeyRemapper.h>
#include <KeyRemapperCreator.h>

using namespace Kmk;

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
			remapper->Activate(0);
			break;
		case VK_F2:
			remapper->Activate(1);
			break;
		case VK_F3:
			remapper->Activate(2);
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
	std::vector<std::map<std::string, std::string>> replacePairs{
		{{"w", "s"}},
		{{"LMB", "w"}, {"w", "LMB"}, {"LALT", "A"}},
		{{"w", "s"},
		 {"s", "w"},
		 {"a", "d"},
		 {"d", "a"}}};

	KeyRemapperCreator krc;
	remapper = krc.Create(replacePairs);

	HHOOK g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	UnhookWindowsHookEx(g_hHook);
	KeyRemapper::DestructInstance();
	return 0;
}