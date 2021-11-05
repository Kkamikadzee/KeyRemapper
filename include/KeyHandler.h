#pragma once
#include <Windows.h>

namespace KmkKeyRemapper
{
	class KeyHandler
	{
	private:
		INPUT _input;
	public:
		void LowerKey(DWORD key);

		void RaiseKey(DWORD key);
	};
}