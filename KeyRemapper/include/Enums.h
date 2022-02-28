#pragma once
#include <Windows.h>

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
}
