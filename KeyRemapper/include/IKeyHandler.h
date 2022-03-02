#pragma once
#include <windows.h>

namespace Kmk
{
	class IKeyHandler
	{
	public:
		IKeyHandler() : _input() {}
		virtual ~IKeyHandler() = default;

		virtual void KeyUp() = 0;
		virtual void KeyDown() = 0;

	protected:
		INPUT _input;
	};
}