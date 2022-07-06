#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>

const std::vector RustKeys{
"Unknown",
"mouse0",
"mouse1",
"VK_CANCEL",
"mouse2",
"mouse3",
"mouse4",
"Unknown",
"back",
"tab",
"Unknown",
"Unknown",
"VK_CLEAR",
"return",
"Unknown",
"Unknown",
"leftshift",
"leftcontrol",
"menu",
"VK_PAUSE",
"VK_CAPITAL",
"VK_KANA",
"Unknown",
"VK_JUNJA",
"VK_FINAL",
"VK_KANJI",
"Unknown",
"escape",
"VK_CONVERT",
"VK_NONCONVERT",
"VK_ACCEPT",
"VK_MODECHANGE",
"space",
"VK_PRIOR",
"VK_NEXT",
"end",
"home",
"left",
"up",
"right",
"down",
"VK_SELECT",
"VK_PRINT",
"VK_EXECUTE",
"VK_SNAPSHOT",
"VK_INSERT",
"VK_DELETE",
"VK_HELP",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"a",
"b",
"c",
"d",
"e",
"f",
"g",
"h",
"i",
"j",
"k",
"l",
"m",
"n",
"o",
"p",
"q",
"r",
"s",
"t",
"u",
"v",
"w",
"x",
"y",
"z",
"VK_LWIN",
"VK_RWIN",
"VK_APPS",
"Unknown",
"VK_SLEEP",
"keypad0",
"keypad1",
"keypad2",
"keypad3",
"keypad4",
"keypad5",
"keypad6",
"keypad7",
"keypad8",
"keypad9",
"VK_MULTIPLY",
"VK_ADD",
"VK_SEPARATOR",
"VK_SUBTRACT",
"VK_DECIMAL",
"VK_DIVIDE",
"f1",
"f2",
"f3",
"f4",
"f5",
"f6",
"f7",
"f8",
"f9",
"f10",
"f11",
"f12",
"f13",
"f14",
"f15",
"f16",
"f17",
"f18",
"f19",
"f20",
"f21",
"f22",
"f23",
"f24",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"VK_NUMLOCK",
"VK_SCROLL",
"VK_OEM_NEC_EQUAL",
"VK_OEM_FJ_MASSHOU",
"VK_OEM_FJ_TOUROKU",
"VK_OEM_FJ_LOYA",
"VK_OEM_FJ_ROYA",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"leftshift",
"rightshift",
"leftcontrol",
"rightcontrol",
"VK_LMENU",
"VK_RMENU"
};

std::string GetRustInstallationPath() {
	LONG   lResult;
	HKEY   hKey;
	char   value[64];
	DWORD  value_length = 64;
	DWORD  dwType = REG_SZ;

	lResult = RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Steam App 252490"), &hKey);
	RegQueryValueExA(hKey, "InstallLocation", NULL, &dwType, (LPBYTE)&value, &value_length);

	RegCloseKey(hKey);

	return value;
}

std::string ClientCfgExtractor(std::string file_name, std::string search_string)
{
	std::string line;
	std::ifstream myfile(file_name);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find(search_string) != std::string::npos)
			{
				std::string::size_type pos = line.find("\"");
				std::string::size_type pos2 = line.find("\"", pos + 1);
				return line.substr(pos + 1, pos2 - pos - 1);
			}
		}
		myfile.close();
	}
	return "";
}

std::string KeysCfgExtractor(std::string file_name, std::string search_string)
{
	std::string line;
	std::ifstream myfile(file_name);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find(search_string) != std::string::npos)
			{
				std::string::size_type pos = line.find(" ");
				std::string::size_type pos2 = line.find(" ", pos + 1);
				return line.substr(pos + 1, pos2 - pos - 1);
			}
		}
		myfile.close();
	}
	return "";
}

int RustKeyToVirtualKey(const char* rust_key)
{
	for (int virtual_key = 0; virtual_key < RustKeys.size(); virtual_key++)
	{
		std::string this_key = RustKeys[virtual_key];

		if (this_key == std::string(rust_key))
		{
			return virtual_key;
		}
	}
}

int main()
{
	std::string clientCfgPath = GetRustInstallationPath() + "\\cfg\\client.cfg";
	std::string keysCfgPath = GetRustInstallationPath() + "\\cfg\\keys.cfg";
	
	std::cout << "Sensitivity  | " << ClientCfgExtractor(clientCfgPath, "input.sensitivity") << std::endl;
	std::cout << "ADS          | " << ClientCfgExtractor(clientCfgPath, "input.ads_sensitivity") << std::endl;
	std::cout << "Fov:         | " << ClientCfgExtractor(clientCfgPath, "graphics.fov") << std::endl;
	
	std::cout << std::endl;
	
	std::cout << "Attack       | " << KeysCfgExtractor(keysCfgPath, "+attack") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+attack").c_str()) << std::endl;
	std::cout << "Scope        | " << KeysCfgExtractor(keysCfgPath, "+attack2") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+attack2").c_str()) << std::endl;
	std::cout << "Duck         | " << KeysCfgExtractor(keysCfgPath, "+duck") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+duck").c_str()) << std::endl;
	std::cout << "Forward      | " << KeysCfgExtractor(keysCfgPath, "+forward") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+forward").c_str()) << std::endl;
	std::cout << "Backward     | " << KeysCfgExtractor(keysCfgPath, "+backward") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+backward").c_str()) << std::endl;
	std::cout << "Left         | " << KeysCfgExtractor(keysCfgPath, "+left") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+left").c_str()) << std::endl;
	std::cout << "Right        | " << KeysCfgExtractor(keysCfgPath, "+right") << " -> " << RustKeyToVirtualKey(KeysCfgExtractor(keysCfgPath, "+right").c_str()) << std::endl;
}
