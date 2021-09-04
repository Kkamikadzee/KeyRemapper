#include <windows.h>
#include <iostream>
#include "KeyHandler.cpp"
#include "ExtraInfo.cpp"

static KeyHandler* keyHandler = new KeyHandler();

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* pkhs = (KBDLLHOOKSTRUCT*)lParam;

	//std::cout << "vkCode \t" << (unsigned short)pkhs->vkCode << "\t" << pkhs->vkCode << std::endl;
	//std::cout << "dwExtraInfo \t" << (unsigned long)pkhs->dwExtraInfo << "\t" << pkhs->dwExtraInfo << std::endl;

	if (pkhs->vkCode != VK_ESCAPE &&
		pkhs->vkCode != static_cast<DWORD>(KeyCode::KeyW) &&
		pkhs->vkCode != static_cast<DWORD>(KeyCode::KeyS))
	{
		return CallNextHookEx(0, nCode, wParam, lParam);
	}

	if (wParam == WM_KEYDOWN)
	{
		if (pkhs->vkCode == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}

		if (pkhs->vkCode == static_cast<DWORD>(KeyCode::KeyW))
		{
			if (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
			{
				keyHandler->LowerKey(static_cast<DWORD>(KeyCode::KeyS));
				return 1;
			}
		}

		if (pkhs->vkCode == static_cast<DWORD>(KeyCode::KeyS))
		{
			if (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
			{
				keyHandler->LowerKey(static_cast<DWORD>(KeyCode::KeyW));
				return 1;
			}
		}
	}
	else if (wParam == WM_KEYUP)
	{
		if (pkhs->vkCode == static_cast<DWORD>(KeyCode::KeyW))
		{
			if (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
			{
				keyHandler->RaiseKey(static_cast<DWORD>(KeyCode::KeyS));
				return 1;
			}
		}

		if (pkhs->vkCode == static_cast<DWORD>(KeyCode::KeyS))
		{
			if (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler))
			{
				keyHandler->RaiseKey(static_cast<DWORD>(KeyCode::KeyW));
				return 1;
			}
		}

	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

int main()
{
	HHOOK g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	UnhookWindowsHookEx(g_hHook);
	return 0;
}