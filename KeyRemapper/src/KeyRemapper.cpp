#include <stdexcept>
#include <windows.h>
#include "SwitchersStorage.h"
#include "KeyRemapper.h"

namespace KmkKeyRemapper
{
	SwitchersStorage *KeyRemapper::_storage = nullptr;

	LRESULT CALLBACK KeyRemapper::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		// TODO: Убрать c-style кастинг
		KBDLLHOOKSTRUCT *pkhs = (KBDLLHOOKSTRUCT *)lParam;

		if (auto downedKey = _storage->GetDownedKey(pkhs, wParam))
		{
			downedKey->DowningKey();
			return 1;
		}

		if (auto uppedKey = _storage->GetUppedKey(pkhs, wParam))
		{
			uppedKey->UppingKey();
			return 1;
		}

		return CallNextHookEx(0, nCode, wParam, lParam);
	}

	KeyRemapper::KeyRemapper(SwitchersStorage *storage)
	{
		_storage = storage;
		_isEnable = false;
		_llHook = nullptr;
	}

	KeyRemapper::~KeyRemapper()
	{
		delete _storage;
	}

	void KeyRemapper::SetStorage(SwitchersStorage *storage)
	{
		if (_isEnable)
		{
			Deactivate();
			_storage = storage;
			Activate();
		}
		else
		{
			_storage = storage;
		}
	}

	void KeyRemapper::Activate()
	{
		if (_storage == nullptr)
		{
			throw std::runtime_error("SwitcherStorage has been null.");
		}
		else if (!_isEnable)
		{
			_llHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
			_isEnable = true;
		}
	}

	void KeyRemapper::Deactivate()
	{
		if (_isEnable)
		{
			UnhookWindowsHookEx(_llHook);
			_isEnable = false;
		}
	}

}