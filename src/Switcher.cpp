#include <Windows.h>
#include "../include/KeyHandler.h"
#include "../include/ExtraInfo.h"
#include "../include/Switcher.h"

using namespace KmkKeyRemapper;

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

inline bool Switcher::ReplaceableKeyIsDownedOrUpped(KBDLLHOOKSTRUCT* pkhs)
{
	return (pkhs->vkCode == _replaceableKeyCode) && (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler));
}

inline void Switcher::DowningKey()
{
	_keyHandler->LowerKey(_replacementKeyCode);
}

inline void Switcher::UppingKey()
{
	_keyHandler->RaiseKey(_replacementKeyCode);
}