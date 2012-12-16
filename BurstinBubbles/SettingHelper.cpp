#include "StdAfx.h"
#include "SettingHelper.h"

std::string SettingHelper::g_sRootPath = "";

SettingHelper::SettingHelper(void)
{
}


SettingHelper::~SettingHelper(void)
{
}


std::string SettingHelper::GetRootPath(void)
{
	char CurrentPath[_MAX_PATH];
	GetModuleFileNameA(NULL, CurrentPath, _MAX_PATH);
	std::string::size_type pos = std::string( CurrentPath ).find_last_of( "\\/" );
	g_sRootPath = std::string( CurrentPath ).substr( 0, pos);
    return g_sRootPath;
}