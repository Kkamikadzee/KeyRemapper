#include <Windows.h>
#include "ExtraInfo.h"
#include "KeyHandler.h"

namespace KmkKeyRemapper
{
	void KeyHandler::LowerKey(DWORD key)
	{
		// Set up a generic keyboard event.
		_input.type = INPUT_KEYBOARD;
		_input.ki.wScan = 0; // hardware scan code for key
		_input.ki.time = 0;
		_input.ki.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);

		// Press the key
		_input.ki.wVk = key;   // virtual-key code
		_input.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &_input, sizeof(INPUT));
	}

	void KeyHandler::RaiseKey(DWORD key)
	{
		// Set up a generic keyboard event.
		_input.type = INPUT_KEYBOARD;
		_input.ki.wScan = 0; // hardware scan code for key
		_input.ki.time = 0;
		_input.ki.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);

		// Release the key
		_input.ki.wVk = key;				 // virtual-key code
		_input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		SendInput(1, &_input, sizeof(INPUT));
	}
}