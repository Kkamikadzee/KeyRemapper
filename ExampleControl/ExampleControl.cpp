#include <windows.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <KeyRemapper.h>
#include <KeyRemapperCreator.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::string pathToConfig = "config.json";
Kmk::KeyRemapper *remapper;

json GetConfig();
void PrintStartMessage();
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
	PrintStartMessage();

	auto configJson = GetConfig();
	auto replacePairs = configJson.get<std::vector<std::map<std::string, std::string>>>();

	remapper = Kmk::KeyRemapperCreator().Create(replacePairs);

	HHOOK g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	UnhookWindowsHookEx(g_hHook);
	Kmk::KeyRemapper::DestructInstance();
	return 0;
}

json GetConfig()
{
	std::ifstream fstream(pathToConfig.c_str());
	if (!fstream.good())
	{
		std::stringstream errorMessage;
		errorMessage << "File \"" << pathToConfig << "\" not found.";
		throw std::runtime_error(errorMessage.str());
	}

	json result;
	fstream >> result;

	return result;
}

void PrintStartMessage()
{
	std::stringstream ss;
	ss << "File config: \"" << pathToConfig << "\"." << std::endl;
	ss << "Press F1 to exit." << std::endl;
	ss << "Press F2 to deactivate." << std::endl;
	ss << "Press F3-F8 to activate corresponding replacement set." << std::endl;
	std::cout << ss.str();
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pkhs = (KBDLLHOOKSTRUCT *)lParam;

	if (wParam == WM_KEYDOWN)
	{
		switch (pkhs->vkCode)
		{
		case VK_F1:
			std::cout << "Bye bye..." << std::endl;
			PostQuitMessage(0);
			break;
		case VK_F2:
			remapper->Deactivate();
			std::cout << "Deactivated." << std::endl;
			break;
		default:
		{
			if (pkhs->vkCode >= VK_F3 && pkhs->vkCode <= VK_F8)
			{
				auto setNumber = pkhs->vkCode - VK_F3;
				remapper->Activate(setNumber);
				std::cout << "Activated set '" << setNumber << "'." << std::endl;
			}
		}
		break;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}