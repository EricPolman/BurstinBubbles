#pragma once
class SettingHelper
{
public:
	SettingHelper(void);
	~SettingHelper(void);
	
	static int g_iWindowHeight, g_iWindowWidth;
	static std::string GetRootPath(void);
	static std::string g_sRootPath;
};

