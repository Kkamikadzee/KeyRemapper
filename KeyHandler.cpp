#pragma once
#include <Windows.h>
#include "ExtraInfo.cpp"

class KeyHandler
{
private:
	INPUT _input;
public:
	void LowerKey(DWORD key)
	{
		// Set up a generic keyboard event.
		_input.type = INPUT_KEYBOARD;
		_input.ki.wScan = 0; // hardware scan code for key
		_input.ki.time = 0;
		_input.ki.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);

		// Press the key
		_input.ki.wVk = key; // virtual-key code
		_input.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &_input, sizeof(INPUT));
	}

	void RaiseKey(DWORD key)
	{
		// Set up a generic keyboard event.
		_input.type = INPUT_KEYBOARD;
		_input.ki.wScan = 0; // hardware scan code for key
		_input.ki.time = 0;
		_input.ki.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);

		// Release the key
		_input.ki.wVk = key; // virtual-key code
		_input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		SendInput(1, &_input, sizeof(INPUT));
	}
};