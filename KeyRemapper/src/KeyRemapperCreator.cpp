#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <forward_list>
#include <utility>
#include <cctype>
#include <sstream>
#include "Keyboard/KeyboardKeyEventReplacer.h"
#include "Keyboard/KeyboardKeyHandler.h"
#include "Mouse/MouseKeyEventReplacer.h"
#include "Mouse/MouseKeyHandler.h"
#include "Enums.h"
#include "KeyRemapper.h"
#include "LowLevelProcObserver.h"
#include "LowLevelProcSubject.h"
#include "KeyRemapperCreator.h"

namespace Kmk
{
    KeyRemapperCreator::KeyRemapperCreator() : _nameCodePairs()
    {
        FillMap();
    }

    KeyRemapper *KeyRemapperCreator::Create(const std::vector<std::map<std::string, std::string>> &pairsReplacableKeyAndReplacementKey) const
    {
        ILowLevelProcSubject *keyboardSubject = new LowLevelProcSubject;
        ILowLevelProcSubject *mouseSubject = new LowLevelProcSubject;

        std::vector<std::forward_list<ILowLevelProcObserver *>> keyboardObserversSets;
        std::vector<std::forward_list<ILowLevelProcObserver *>> mouseObserversSets;

        for (auto replacePairs : pairsReplacableKeyAndReplacementKey)
        {
            std::forward_list<ILowLevelProcObserver *> keyboardObserversSet;
            std::forward_list<ILowLevelProcObserver *> mouseObserversSet;
            for (auto replacePair = replacePairs.begin(); replacePair != replacePairs.end(); ++replacePair)
            {
                IKeyHandler *keyHandler;
                const IKeyEventReplacer *keyReplacer;
                {
                    MouseButton mb;
                    int keyCode;
                    if (TryConvertStringToMouseKeyCode(replacePair->second, mb))
                    {
                        keyHandler = new MouseKeyHandler(mb);
                    }
                    else if (TryConvertStringToCharKeyCode(replacePair->second, keyCode) || TryConvertStringToOthersKeyCode(replacePair->second, keyCode))
                    {
                        keyHandler = new KeyboardKeyHandler(keyCode);
                    }
                }
                {
                    MouseButton mb;
                    int keyCode;
                    if (TryConvertStringToMouseKeyCode(replacePair->first, mb))
                    {
                        keyReplacer = new MouseKeyEventReplacer(keyHandler, mb);

                        auto observer = new LowLevelProcObserver(keyboardSubject, keyReplacer);
                        mouseObserversSet.push_front(observer);
                    }
                    else if (TryConvertStringToCharKeyCode(replacePair->first, keyCode) || TryConvertStringToOthersKeyCode(replacePair->first, keyCode))
                    {
                        keyReplacer = new KeyboardKeyEventReplacer(keyHandler, keyCode);

                        auto observer = new LowLevelProcObserver(keyboardSubject, keyReplacer);
                        keyboardObserversSet.push_front(observer);
                    }
                }
            }

            keyboardObserversSets.push_back(std::move(keyboardObserversSet));
            mouseObserversSets.push_back(std::move(mouseObserversSet));
        }

        return KeyRemapper::GetInstance(keyboardSubject, keyboardObserversSets, mouseSubject, mouseObserversSets);
    }

    void KeyRemapperCreator::FillMap()
    {
        {
            std::stringstream keyName;
            // insert F1 - F24
            {
                for (int keyNumber = 1; keyNumber != 25; ++keyNumber)
                {
                    keyName << 'F' << keyNumber;
                    _nameCodePairs.insert({keyName.str(), VK_F1 + (keyNumber - 1)});
                    keyName.clear();
                }
            }

            // insert numeric keypad
            {
                for (int keyNumber = 0; keyNumber != 10; ++keyNumber)
                {
                    keyName << "NUMPAD" << keyNumber;
                    _nameCodePairs.insert({keyName.str(), VK_NUMPAD0 + keyNumber});
                    keyName.clear();
                }
            }
        }

        _nameCodePairs.insert({"TAB", VK_TAB});
        _nameCodePairs.insert({"CAPS", VK_CAPITAL});
        _nameCodePairs.insert({"LSHIFT", VK_LSHIFT});
        _nameCodePairs.insert({"RSHIFT", VK_RSHIFT});
        _nameCodePairs.insert({"LCTRL", VK_LCONTROL});
        _nameCodePairs.insert({"RCTRL", VK_RCONTROL});
        _nameCodePairs.insert({"LALT", VK_LMENU});
        _nameCodePairs.insert({"RALT", VK_RMENU});
        _nameCodePairs.insert({"SPACE", VK_SPACE});
        _nameCodePairs.insert({"ENTER", VK_RETURN});
        _nameCodePairs.insert({"BACKSPACE", VK_BACK});
        _nameCodePairs.insert({"LEFT", VK_LEFT});
        _nameCodePairs.insert({"UP", VK_UP});
        _nameCodePairs.insert({"RIGHT", VK_RIGHT});
        _nameCodePairs.insert({"DOWN", VK_DOWN});
        _nameCodePairs.insert({"PAGE_UP", VK_PRIOR});
        _nameCodePairs.insert({"PAGE_DOWN", VK_NEXT});
        _nameCodePairs.insert({"END", VK_END});
        _nameCodePairs.insert({"HOME", VK_HOME});
        _nameCodePairs.insert({"INSERT", VK_INSERT});
        _nameCodePairs.insert({"DELETE", VK_DELETE});
    }

    bool KeyRemapperCreator::TryConvertStringToMouseKeyCode(const std::string &keyCode, MouseButton &resultKey) const
    {
        if (keyCode == "LMB")
        {
            resultKey = MouseButton::Left;
            return true;
        }

        if (keyCode == "RMB")
        {
            resultKey = MouseButton::Right;
            return true;
        }

        return false;
    }

    bool KeyRemapperCreator::TryConvertStringToCharKeyCode(const std::string &keyCode, int &resultKeyCode) const
    {
        if (keyCode.size() != 1)
        {
            return false;
        }

        resultKeyCode = VkKeyScan(keyCode[0]);
        return true;
    }

    bool KeyRemapperCreator::TryConvertStringToOthersKeyCode(const std::string &keyCode, int &resultKeyCode) const
    {
        auto searchResult = _nameCodePairs.find(keyCode);
        if (searchResult == _nameCodePairs.end())
        {
            return false;
        }

        resultKeyCode = searchResult->second;
        return true;
    }
}