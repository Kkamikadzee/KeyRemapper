#pragma once
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <forward_list>
#include "Keyboard/KeyboardKeyEventReplacer.h"
#include "Keyboard/KeyboardKeyHandler.h"
#include "Mouse/MouseKeyEventReplacer.h"
#include "Mouse/MouseKeyHandler.h"
#include "Enums.h"
#include "KeyRemapper.h"
#include "LowLevelProcObserver.h"
#include "LowLevelProcSubject.h"

namespace Kmk
{
    class KeyRemapperCreator
    {
    public:
        KeyRemapperCreator();

        KeyRemapper *Create(const std::vector<std::map<std::string, std::string>> &pairsReplacableKeyAndReplacementKey) const;

    private:
        std::map<const std::string, const int> _nameCodePairs;

        void FillMap();

        bool TryConvertStringToMouseKeyCode(const std::string &keyCode, MouseButton &resultKey) const;
        bool TryConvertStringToCharKeyCode(const std::string &keyCode, int &resultKeyCode) const;
        bool TryConvertStringToOthersKeyCode(const std::string &keyCode, int &resultKeyCode) const;
    };
}