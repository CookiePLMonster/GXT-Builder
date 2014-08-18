#ifndef __GXTBUILD_H
#define __GXTBUILD_H

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#define WINVER 0x0500
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <cstdint>
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <forward_list>
#include <shlwapi.h>
#include <ctime>
#include "utf8.h"

using namespace std;

#define CHARACTER_MAP_SIZE		224

struct GXTTable
{
	string						szPath;
	map<uint32_t, uint32_t>		Entries;
	string						Content;
	basic_string<uint8_t>		FormattedContent;

	GXTTable(const string& szFilePath)
		: szPath(szFilePath)
	{}
};

struct EntryName
{
	char						cName[8];

	EntryName(const char* pName)
	{
		memset(cName, 0, sizeof(cName));
		strncpy(cName, pName, 8);
	}
};

struct VersionControlMap
{
	uint32_t					TextHash;
	bool						bLinked;

	VersionControlMap(uint32_t hash = 0)
		: TextHash(hash), bLinked(true)
	{}
};

typedef std::map<EntryName, GXTTable, bool(*)(const EntryName&,const EntryName&)>	tableMap_t;

#endif