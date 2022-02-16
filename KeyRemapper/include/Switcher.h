#pragma once
#include <Windows.h>
#include "KeyHandler.h"

namespace KmkKeyRemapper
{
	class Switcher
	{
	private:
		DWORD _replaceableKeyCode;
		DWORD _replacementKeyCode;
		KeyHandler *_keyHandler;

	public:
		Switcher(DWORD replaceableKeyCode, DWORD replacementKeyCode, KeyHandler *keyHandler);

		~Switcher();

		bool ReplaceableKeyIsDownedOrUpped(KBDLLHOOKSTRUCT *pkhs);

		void DowningKey();

		void UppingKey();
	};
}