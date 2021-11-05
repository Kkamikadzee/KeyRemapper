#pragma once
#include <windows.h>
#include "SwitchersStorage.h"

namespace KmkKeyRemapper
{
	class KeyRemapper {
	private:
		static SwitchersStorage* _storage;
		bool _isEnable;
		HHOOK _llHook;

		static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	public:
		KeyRemapper(SwitchersStorage* storage);

		~KeyRemapper();

		void SetStorage(SwitchersStorage* storage);

		void Activate();

		void Deactivate();
	};
}
