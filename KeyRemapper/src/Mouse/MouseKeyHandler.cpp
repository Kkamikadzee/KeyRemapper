#include <Windows.h>
#include "Emuns.h"
#include "Mouse/MouseKeyHandler.h"

namespace Kmk
{
	MouseKeyHandler::MouseKeyHandler(DWORD eventKeyDown, DWORD eventKeyUp) : IKeyHandler(), _eventKeyDown(eventKeyDown), _eventKeyUp(eventKeyUp)
	{
		// Set up a generic mouse event.
		_input.type = INPUT_MOUSE;
		_input.mi.time = 0;
		_input.mi.dwExtraInfo = static_cast<ULONG_PTR>(ExtraInfo::KeyHendler);
	}

	void MouseKeyHandler::KeyDown()
	{
		_input.mi.dwFlags = _eventKeyDown;
		SendInput(1, &_input, sizeof(INPUT));
	}

	void MouseKeyHandler::KeyUp()
	{
		_input.mi.dwFlags = _eventKeyUp;
		SendInput(1, &_input, sizeof(INPUT));
	}
}