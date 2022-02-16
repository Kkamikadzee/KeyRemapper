#include <Windows.h>
#include "KeyHandler.h"
#include "ExtraInfo.h"
#include "Switcher.h"

namespace KmkKeyRemapper
{
	Switcher::Switcher(DWORD replaceableKeyCode, DWORD replacementKeyCode, KeyHandler *keyHandler)
	{
		_replaceableKeyCode = replaceableKeyCode;
		_replacementKeyCode = replacementKeyCode;
		_keyHandler = keyHandler;
	}

	Switcher::~Switcher()
	{
		delete _keyHandler;
	}

	bool Switcher::ReplaceableKeyIsDownedOrUpped(KBDLLHOOKSTRUCT *pkhs)
	{
		return (pkhs->vkCode == _replaceableKeyCode) && (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler));
	}

	void Switcher::DowningKey()
	{
		_keyHandler->LowerKey(_replacementKeyCode);
	}

	void Switcher::UppingKey()
	{
		_keyHandler->RaiseKey(_replacementKeyCode);
	}
}