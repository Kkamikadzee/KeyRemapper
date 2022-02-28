#include <windows.h>
#include "Emuns.h"
#include "Keyboard/KeyboardKeyHandler.h"

namespace Kmk
{
	KeyboardKeyHandler::KeyboardKeyHandler(DWORD key) : IKeyHandler()
	{
		// Set up a generic keyboard event.
		_input.type = INPUT_KEYBOARD;
		_input.ki.wScan = 0; // hardware scan code for key
		_input.ki.time = 0;
		_input.ki.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);

		// Press the key
		_input.ki.wVk = key; // virtual-key code
	}

	void KeyboardKeyHandler::KeyDown()
	{
		_input.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &_input, sizeof(INPUT));
	}

	void KeyboardKeyHandler::KeyUp()
	{
		_input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		SendInput(1, &_input, sizeof(INPUT));
	}
}