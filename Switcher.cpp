#pragma once
#include <Windows.h>
#include "KeyHandler.cpp"

class Switcher
{
private:
	DWORD _replaceableKeyCode;
	DWORD _replacementKeyCode;
	KeyHandler* _keyHandler;

public:
	Switcher(DWORD replaceableKeyCode, DWORD replacementKeyCode, KeyHandler *keyHandler)
	{
		_replaceableKeyCode = replaceableKeyCode;
		_replacementKeyCode = replacementKeyCode;
		_keyHandler = keyHandler;
	}

	bool ReplaceableKeyIsDowned(KBDLLHOOKSTRUCT* pkhs)
	{
		return (pkhs->vkCode == _replaceableKeyCode) && (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler));
	}

	void DowningKey()
	{
		_keyHandler->LowerKey(_replacementKeyCode);
	}
	
	bool ReplaceableKeyIsUpped(KBDLLHOOKSTRUCT* pkhs)
	{
		return (pkhs->vkCode == _replaceableKeyCode) && (pkhs->dwExtraInfo != static_cast<ULONG_PTR>(ExtraInfo::KeyHendler));
	}

	void UppingKey()
	{
		_keyHandler->RaiseKey(_replacementKeyCode);
	}
};