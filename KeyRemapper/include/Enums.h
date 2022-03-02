#pragma once
#include <windows.h>

namespace Kmk
{
	enum class ExtraInfo : ULONG_PTR
	{
		Zero = 0l,
		KeyHendler = 8956l
	};

	enum class MouseButton
	{
		Left = 0,
		Right = 1
	};

	const int GetKeyDownCodeByMouseButton(const MouseButton key);
	const int GetKeyUpCodeByMouseButton(const MouseButton key);
	const int GetKeyDownEventByMouseButton(const MouseButton key);
	const int GetKeyUpEventByMouseButton(const MouseButton key);
}
