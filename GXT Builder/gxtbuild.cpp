#include "gxtbuild.h"

static const uint32_t crc32table[256] =
{
    0x00000000UL, 0x77073096UL, 0xee0e612cUL, 0x990951baUL, 0x076dc419UL,
    0x706af48fUL, 0xe963a535UL, 0x9e6495a3UL, 0x0edb8832UL, 0x79dcb8a4UL,
    0xe0d5e91eUL, 0x97d2d988UL, 0x09b64c2bUL, 0x7eb17cbdUL, 0xe7b82d07UL,
    0x90bf1d91UL, 0x1db71064UL, 0x6ab020f2UL, 0xf3b97148UL, 0x84be41deUL,
    0x1adad47dUL, 0x6ddde4ebUL, 0xf4d4b551UL, 0x83d385c7UL, 0x136c9856UL,
    0x646ba8c0UL, 0xfd62f97aUL, 0x8a65c9ecUL, 0x14015c4fUL, 0x63066cd9UL,
    0xfa0f3d63UL, 0x8d080df5UL, 0x3b6e20c8UL, 0x4c69105eUL, 0xd56041e4UL,
    0xa2677172UL, 0x3c03e4d1UL, 0x4b04d447UL, 0xd20d85fdUL, 0xa50ab56bUL,
    0x35b5a8faUL, 0x42b2986cUL, 0xdbbbc9d6UL, 0xacbcf940UL, 0x32d86ce3UL,
    0x45df5c75UL, 0xdcd60dcfUL, 0xabd13d59UL, 0x26d930acUL, 0x51de003aUL,
    0xc8d75180UL, 0xbfd06116UL, 0x21b4f4b5UL, 0x56b3c423UL, 0xcfba9599UL,
    0xb8bda50fUL, 0x2802b89eUL, 0x5f058808UL, 0xc60cd9b2UL, 0xb10be924UL,
    0x2f6f7c87UL, 0x58684c11UL, 0xc1611dabUL, 0xb6662d3dUL, 0x76dc4190UL,
    0x01db7106UL, 0x98d220bcUL, 0xefd5102aUL, 0x71b18589UL, 0x06b6b51fUL,
    0x9fbfe4a5UL, 0xe8b8d433UL, 0x7807c9a2UL, 0x0f00f934UL, 0x9609a88eUL,
    0xe10e9818UL, 0x7f6a0dbbUL, 0x086d3d2dUL, 0x91646c97UL, 0xe6635c01UL,
    0x6b6b51f4UL, 0x1c6c6162UL, 0x856530d8UL, 0xf262004eUL, 0x6c0695edUL,
    0x1b01a57bUL, 0x8208f4c1UL, 0xf50fc457UL, 0x65b0d9c6UL, 0x12b7e950UL,
    0x8bbeb8eaUL, 0xfcb9887cUL, 0x62dd1ddfUL, 0x15da2d49UL, 0x8cd37cf3UL,
    0xfbd44c65UL, 0x4db26158UL, 0x3ab551ceUL, 0xa3bc0074UL, 0xd4bb30e2UL,
    0x4adfa541UL, 0x3dd895d7UL, 0xa4d1c46dUL, 0xd3d6f4fbUL, 0x4369e96aUL,
    0x346ed9fcUL, 0xad678846UL, 0xda60b8d0UL, 0x44042d73UL, 0x33031de5UL,
    0xaa0a4c5fUL, 0xdd0d7cc9UL, 0x5005713cUL, 0x270241aaUL, 0xbe0b1010UL,
    0xc90c2086UL, 0x5768b525UL, 0x206f85b3UL, 0xb966d409UL, 0xce61e49fUL,
    0x5edef90eUL, 0x29d9c998UL, 0xb0d09822UL, 0xc7d7a8b4UL, 0x59b33d17UL,
    0x2eb40d81UL, 0xb7bd5c3bUL, 0xc0ba6cadUL, 0xedb88320UL, 0x9abfb3b6UL,
    0x03b6e20cUL, 0x74b1d29aUL, 0xead54739UL, 0x9dd277afUL, 0x04db2615UL,
    0x73dc1683UL, 0xe3630b12UL, 0x94643b84UL, 0x0d6d6a3eUL, 0x7a6a5aa8UL,
    0xe40ecf0bUL, 0x9309ff9dUL, 0x0a00ae27UL, 0x7d079eb1UL, 0xf00f9344UL,
    0x8708a3d2UL, 0x1e01f268UL, 0x6906c2feUL, 0xf762575dUL, 0x806567cbUL,
    0x196c3671UL, 0x6e6b06e7UL, 0xfed41b76UL, 0x89d32be0UL, 0x10da7a5aUL,
    0x67dd4accUL, 0xf9b9df6fUL, 0x8ebeeff9UL, 0x17b7be43UL, 0x60b08ed5UL,
    0xd6d6a3e8UL, 0xa1d1937eUL, 0x38d8c2c4UL, 0x4fdff252UL, 0xd1bb67f1UL,
    0xa6bc5767UL, 0x3fb506ddUL, 0x48b2364bUL, 0xd80d2bdaUL, 0xaf0a1b4cUL,
    0x36034af6UL, 0x41047a60UL, 0xdf60efc3UL, 0xa867df55UL, 0x316e8eefUL,
    0x4669be79UL, 0xcb61b38cUL, 0xbc66831aUL, 0x256fd2a0UL, 0x5268e236UL,
    0xcc0c7795UL, 0xbb0b4703UL, 0x220216b9UL, 0x5505262fUL, 0xc5ba3bbeUL,
    0xb2bd0b28UL, 0x2bb45a92UL, 0x5cb36a04UL, 0xc2d7ffa7UL, 0xb5d0cf31UL,
    0x2cd99e8bUL, 0x5bdeae1dUL, 0x9b64c2b0UL, 0xec63f226UL, 0x756aa39cUL,
    0x026d930aUL, 0x9c0906a9UL, 0xeb0e363fUL, 0x72076785UL, 0x05005713UL,
    0x95bf4a82UL, 0xe2b87a14UL, 0x7bb12baeUL, 0x0cb61b38UL, 0x92d28e9bUL,
    0xe5d5be0dUL, 0x7cdcefb7UL, 0x0bdbdf21UL, 0x86d3d2d4UL, 0xf1d4e242UL,
    0x68ddb3f8UL, 0x1fda836eUL, 0x81be16cdUL, 0xf6b9265bUL, 0x6fb077e1UL,
    0x18b74777UL, 0x88085ae6UL, 0xff0f6a70UL, 0x66063bcaUL, 0x11010b5cUL,
    0x8f659effUL, 0xf862ae69UL, 0x616bffd3UL, 0x166ccf45UL, 0xa00ae278UL,
    0xd70dd2eeUL, 0x4e048354UL, 0x3903b3c2UL, 0xa7672661UL, 0xd06016f7UL,
    0x4969474dUL, 0x3e6e77dbUL, 0xaed16a4aUL, 0xd9d65adcUL, 0x40df0b66UL,
    0x37d83bf0UL, 0xa9bcae53UL, 0xdebb9ec5UL, 0x47b2cf7fUL, 0x30b5ffe9UL,
    0xbdbdf21cUL, 0xcabac28aUL, 0x53b39330UL, 0x24b4a3a6UL, 0xbad03605UL,
    0xcdd70693UL, 0x54de5729UL, 0x23d967bfUL, 0xb3667a2eUL, 0xc4614ab8UL,
    0x5d681b02UL, 0x2a6f2b94UL, 0xb40bbe37UL, 0xc30c8ea1UL, 0x5a05df1bUL,
    0x2d02ef8dUL
};

// Hashes a string
uint32_t crc32FromString(const char *Str)
{
  uint32_t hash = 0xFFFFFFFF;
  while(*Str)
    hash = crc32table[(hash ^ *Str++)&0xFF] ^ (hash >> 8);
  return hash;
}

// Hashes a string as it is in upper case
uint32_t crc32FromUpcaseString(const char* Str)
{
	uint32_t hash = 0xFFFFFFFF;
	while(*Str)
		hash = crc32table[(hash^toupper(*Str++))&0xFF]^(hash >> 8);
	return hash;
}

// Continues hashing, takes a hash (to be continued) and a string (to be hashed)
uint32_t crc32Continue(uint32_t hash, const char* Str)
{
  while(*Str)
    hash = crc32table[(hash ^ *Str++)&0xFF] ^ (hash >> 8);
  return hash;
}


namespace VC
{
	bool GXTTable::InsertEntry( const std::string& entryName, size_t offset )
	{
		return Entries.insert( std::make_pair( entryName, offset * 2 ) ).second != false;
	}

	void GXTTable::WriteOutEntries( std::ostream& stream )
	{
		for ( auto& it : Entries )
		{
			stream.write(reinterpret_cast<const char*>(&it.second), sizeof( it.second ) );
			stream.write( it.first.c_str(), GXT_ENTRY_NAME_LEN );
		}
	}

	void GXTTable::WriteOutContent( std::ostream& stream )
	{
		stream.write( reinterpret_cast<const char*>( FormattedContent.c_str() ), FormattedContent.size() );
	}

	void GXTTable::PushFormattedChar( int character )
	{
		FormattedContent.push_back( static_cast<uint16_t>( character ) );
	}
};

namespace SA
{
	bool GXTTable::InsertEntry( const std::string& entryName, size_t offset )
	{
		uint32_t entryHash = crc32FromUpcaseString( entryName.c_str() );
		return Entries.insert( std::make_pair( entryHash, offset ) ).second != false;
	}

	void GXTTable::WriteOutEntries( std::ostream& stream )
	{
		for ( auto& it : Entries )
		{
			stream.write(reinterpret_cast<const char*>(&it.second), sizeof( it.second ) );
			stream.write(reinterpret_cast<const char*>(&it.first), sizeof( it.first ) );
		}
	}

	void GXTTable::WriteOutContent( std::ostream& stream )
	{
		stream.write( reinterpret_cast<const char*>( FormattedContent.c_str() ), FormattedContent.size() );
	}

	void GXTTable::PushFormattedChar( int character )
	{
		FormattedContent.push_back( static_cast<uint8_t>( character ) );
	}
};


static bool compTable(const EntryName& lhs, const EntryName& rhs)
{
	if ( !strncmp(lhs.cName, "MAIN", 8) )
		return true;

	if ( !strncmp(rhs.cName, "MAIN", 8) )
		return false;

	return strncmp(lhs.cName, rhs.cName, 8) < 0;
}

static bool MakeSureFileIsValid(ifstream& file)
{
	istreambuf_iterator<char> it(file.rdbuf());
	istreambuf_iterator<char> eos;
	if ( !utf8::is_valid(it, eos) )
		return false;

	file.seekg(0, ios_base::beg);

	// Skip BOM (if exists)
	// starts_with_bom advances the pointer all the time, so we have to call seekg anyway
	file.seekg(utf8::starts_with_bom(it, eos) ? 3 : 0, ios_base::beg);
	return true;
}

void ParseCharacterMap(const string& szFileName, wchar_t* pCharacterMap)
{
	ifstream		CharMapFile(szFileName, ifstream::in);

	if ( CharMapFile.is_open() && MakeSureFileIsValid(CharMapFile) )
	{
		for ( int i = 0; i < 14; ++i )
		{
			string					FileLine;

			getline(CharMapFile, FileLine);

			utf8::iterator<string::iterator> utf8It(FileLine.begin(), FileLine.begin(), FileLine.end());

			for ( int j = 0; j < 16; ++j )
			{
				pCharacterMap[i*16+j] = static_cast<wchar_t>(*utf8It);

				// Skip the tabulation too
				if ( j < 15 )
				{
					utf8It++;
					utf8It++;
				}
			}
		}

		CharMapFile.close();
	}
	else
		throw szFileName;
}

void ParseINI( const wstring& szName, tableMap_t& TableMap, wchar_t* pCharacterMap, eGXTVersion fileVersion )
{
	ifstream		InputINI(szName + L".ini", ifstream::in);

	if ( InputINI.is_open() && MakeSureFileIsValid(InputINI) )
	{
		// Parse it
		bool		bThisLineIsCharMap = true;
		string		FileLine;
		while ( getline(InputINI, FileLine) )
		{
			if ( !FileLine.empty() && FileLine[0] != ';' )
			{
				if ( !bThisLineIsCharMap )
				{
					std::unique_ptr<GXTTableBase>	Table;
					switch ( fileVersion )
					{
					case GXT_VC:
						Table = std::make_unique<VC::GXTTable>( FileLine ); 
						break;
					case GXT_SA:
						Table = std::make_unique<SA::GXTTable>( FileLine ); 
						break;
					}			

					// Extract name
					const char*		pName = strrchr(FileLine.c_str(),'\\');
					if ( pName )
						++pName;
					else
						pName = FileLine.c_str();

					TableMap.insert( make_pair(pName, move(Table)) );

					wcout << L"Registered '" << pName << L"' GXT table\n";
				}
				else
				{
					bThisLineIsCharMap = false;
					ParseCharacterMap(FileLine, pCharacterMap);

					wcout << L"Character map parsed\n";
				}
			}
		}

		InputINI.close();
	}
	else
		wcerr << L"Could not open " << szName << L".ini!\n";
}

void LoadFileContent(const wchar_t* pFileName, tableMap_t::iterator& TableIt, map<uint32_t,VersionControlMap>& MasterMap, const forward_list<ofstream*>& SlaveStreams, ofstream& LogFile, bool bMasterBuilding)
{
	ifstream		InputFile(pFileName, ifstream::in);

	if ( InputFile.is_open() )
	{
		wcout << L"Reading entries from " << pFileName << L"...\n";

		if ( !MakeSureFileIsValid(InputFile) )
		{
			wcerr << L"ERROR: File " << pFileName << " contains invalid UTF-8 characters!\n";
			return;
		}

		string		FileLine;
		while ( getline(InputFile, FileLine) )
		{
			if ( !FileLine.empty() && FileLine[0] != '#' )
			{
				// Extract entry name
				string		EntryName(FileLine.begin(), FileLine.begin()+FileLine.find('\t'));
				string		EntryContent(FileLine.begin()+FileLine.find('\t')+1, FileLine.end());
				uint32_t	nEntryHash = crc32FromUpcaseString(EntryName.c_str());

				// Push entry into table map
				if ( TableIt->second->InsertEntry( EntryName, utf8::distance( TableIt->second->Content.begin(), TableIt->second->Content.end() ) ) )
				{
					TableIt->second->Content.append(EntryContent);
					TableIt->second->Content.push_back('\0');

					// Hash it and perform checks
					if ( bMasterBuilding )
					{
						auto		ThisEntryIt = MasterMap.find(nEntryHash);
						uint32_t	nTextHash = crc32FromString(EntryContent.c_str());
						if ( ThisEntryIt == MasterMap.end() )
						{
							// New entry, add it!
							VersionControlMap		VersionCtrlEntry(nTextHash);
							MasterMap.insert(make_pair(nEntryHash, VersionCtrlEntry));

							// Notify about it in slave lang changes file
							for ( auto it = SlaveStreams.cbegin(); it != SlaveStreams.cend(); it++ )
							{
								(**it) << EntryName << " - ADDED to table " << TableIt->first.cName << endl;
							}
						}
						else
						{
							ThisEntryIt->second.bLinked = true;
							if ( nTextHash != ThisEntryIt->second.TextHash )
							{
								// Modified entry!
								// Notify about it in slave lang changes file
								for ( auto it = SlaveStreams.cbegin(); it != SlaveStreams.cend(); it++ )
								{
									(**it) << EntryName << " - MODIFIED in table " << TableIt->first.cName << endl;
								}

								ThisEntryIt->second.TextHash = nTextHash;
							}
						}
					}
				}
				else
				{
					if ( LogFile.is_open() )
					{
						wstring		WideFileName(pFileName);
						LogFile << "Entry " << EntryName << " duplicated in " << string(WideFileName.begin(), WideFileName.end()) << " file!\n";
					}
				}
			}
		}

		InputFile.close();
	}
	else
		throw pFileName;
}

void ReadTextFiles(tableMap_t& TableMap, map<uint32_t,VersionControlMap>& MasterMap, const forward_list<ofstream*>& SlaveStreams, ofstream& LogFile, bool bMasterBuilding)
{
	for ( tableMap_t::iterator it = TableMap.begin(); it != TableMap.end(); it++ )
	{
		// Prepare a path
		char		szTextsPath[MAX_PATH];
		wchar_t		szWidePath[MAX_PATH];
		wchar_t		szSavedPath[MAX_PATH];

		strncpy(szTextsPath, it->second->szPath.c_str(), MAX_PATH);
		mbstowcs(szWidePath, szTextsPath, MAX_PATH);

		GetCurrentDirectory(MAX_PATH, szSavedPath);
		SetCurrentDirectory(szWidePath);


		// Iterate through a directory
		WIN32_FIND_DATA		findData;
		HANDLE				hFoundFiles = FindFirstFile(L"*.txt", &findData);

		if ( hFoundFiles != INVALID_HANDLE_VALUE )
		{
			do
				LoadFileContent(findData.cFileName, it, MasterMap, SlaveStreams, LogFile, bMasterBuilding);
			while ( FindNextFile(hFoundFiles, &findData) );

			FindClose(hFoundFiles);
		}
		else
			throw szWidePath;

		SetCurrentDirectory(szSavedPath);
	}

}

#include <cassert>

void ApplyCharacterMap(tableMap_t& TablesMap, const wchar_t* pCharacterMap)
{
	for ( auto it = TablesMap.begin(); it != TablesMap.end(); it++ )
	{
		auto	endIt = utf8::iterator<string::iterator>(it->second->Content.end(), it->second->Content.begin(),  it->second->Content.end());
		for ( auto strIt = utf8::iterator<string::iterator>(it->second->Content.begin(), it->second->Content.begin(), it->second->Content.end()); strIt != endIt; strIt++ )
		{
			bool	bFound = false;
			if ( *strIt == '\0' )
			{
				it->second->PushFormattedChar('\0');
				continue;
			}
			for ( int i = 0; i < CHARACTER_MAP_SIZE; ++i )
			{
				if ( *strIt == pCharacterMap[i] )
				{
					it->second->PushFormattedChar( i + 32 );
					bFound = true;
					break;
				}
			}

			if ( !bFound )
				throw *strIt;
		}

	}
}

// NOTE: Some GXT editors seem to use a different structure (offset differences), but this structure
// matches original San Andreas GXT structure more!
void ProduceGXTFile( const wstring& szLangName, const tableMap_t& TablesMap, eGXTVersion fileVersion )
{
	ofstream	OutputFile(szLangName + L".gxt", ofstream::binary);
	if ( OutputFile.is_open() )
	{
		// Header (SA only)
		if ( fileVersion == GXT_SA )
		{
			const char		header[] = { 0x04, 0x00, 0x08, 0x00 };	// 0x080004
			OutputFile.write(header, sizeof(header));
		}

		// Write TABL section
		{
			DWORD			dwCurrentOffset = fileVersion == GXT_SA ? 12 : 8;
			const char		header[] = { 'T', 'A', 'B', 'L' };
			OutputFile.write(header, sizeof(header));

			const DWORD		dwBlockSize = TablesMap.size() * 12;
			OutputFile.write(reinterpret_cast<const char*>(&dwBlockSize), sizeof(dwBlockSize));

			dwCurrentOffset += dwBlockSize;

			bool			bItsNotMain = false;
			for ( auto it = TablesMap.cbegin(); it != TablesMap.cend(); it++ )
			{
				OutputFile.write(it->first.cName, 8);
				OutputFile.write(reinterpret_cast<const char*>(&dwCurrentOffset), sizeof(dwCurrentOffset));
				dwCurrentOffset += 16 + (bItsNotMain * 8) + (it->second->GetNumEntries() * it->second->GetEntrySize()) + it->second->GetFormattedContentSize();

				// Align to 4 bytes
				dwCurrentOffset = (dwCurrentOffset + 4 - 1) & ~(4 - 1);

				bItsNotMain = true;
			}
		}

		// Write TKEY and TDAT sections
		bool			bItsNotMain = false;
		for ( tableMap_t::const_iterator it = TablesMap.cbegin(); it != TablesMap.cend(); it++ )
		{
			if ( bItsNotMain )
				OutputFile.write(it->first.cName, 8);
			else
				bItsNotMain = true;

			{
				const char		header[] = { 'T', 'K', 'E', 'Y' };
				OutputFile.write(header, sizeof(header));
				const DWORD		dwBlockSize = it->second->GetNumEntries() * it->second->GetEntrySize();
				OutputFile.write(reinterpret_cast<const char*>(&dwBlockSize), sizeof(dwBlockSize));

				// Write TKEY entries
				it->second->WriteOutEntries( OutputFile );
			}

			{
				const char		header[] = { 'T', 'D', 'A', 'T' };
				OutputFile.write(header, sizeof(header));
				const size_t	dwBlockSize = it->second->GetFormattedContentSize();;
				OutputFile.write(reinterpret_cast<const char*>(&dwBlockSize), sizeof(dwBlockSize));

				it->second->WriteOutContent( OutputFile );
			}

			// Align to 4 bytes
			if ( OutputFile.tellp() % 4 )
				OutputFile.seekp(4 - (OutputFile.tellp() % 4), ios_base::cur);
		}

		wcout << L"Finished building " << szLangName << L".gxt!\n";
		OutputFile.close();
	}
	else
		throw szLangName;
}

void ProduceStats(ofstream& LogFile, const wstring& szLangName, const tableMap_t& TablesMap)
{
	if ( LogFile.is_open() )
	{
		time_t			currentTime;
		size_t			numEntries = 0;

		time(&currentTime);

		LogFile << "\nBuilding finished at " << ctime(&currentTime) << "GXT contains " << TablesMap.size() << " tables:\n";

		for ( auto it = TablesMap.cbegin(); it != TablesMap.cend(); ++it )
		{
			size_t			numTheseEntries = it->second->GetNumEntries();
			LogFile << "\t- " << it->first.cName << " - " << numTheseEntries << " entries\n";
			numEntries += numTheseEntries;
		}

		LogFile << '\n' << numEntries << " entries total.";
		wcout << szLangName << L"_build.log generated.\n";
	}
}

void ReadMasterTable(const wstring& szMasterLangName, map<uint32_t,VersionControlMap>& MasterMap)
{
	string								szNarrowLangName(szMasterLangName.begin(), szMasterLangName.end());
	wchar_t								wcHashText[MAX_PATH];

	swprintf(wcHashText, MAX_PATH, L"cache\\%X", crc32FromString(szNarrowLangName.c_str()));

	ifstream	CacheFile(wcHashText, ifstream::binary);
	if ( CacheFile.is_open() )
	{
		for ( ;; )
		{
			pair<uint32_t, VersionControlMap>	OneEntry;
			OneEntry.second.bLinked = false;
			CacheFile.read(reinterpret_cast<char*>(&OneEntry), 8);
			if ( CacheFile.eof() )
				break;
			MasterMap.insert(OneEntry);
		}
		CacheFile.close();
	}
}

void ProduceMasterCache(const wstring& szMasterLangName, map<uint32_t,VersionControlMap>& MasterMap)
{
	string								szNarrowLangName(szMasterLangName.begin(), szMasterLangName.end());
	wchar_t								wcHashText[MAX_PATH];

	swprintf(wcHashText, MAX_PATH, L"cache\\%X", crc32FromString(szNarrowLangName.c_str()));

	ofstream	CacheFile(wcHashText, ofstream::binary);
	if ( CacheFile.is_open() )
	{
		for ( auto it = MasterMap.cbegin(); it != MasterMap.cend(); it++ )
		{
			if ( it->second.bLinked )
			{
				pair<uint32_t,VersionControlMap>		OneEntry = *it;
				CacheFile.write(reinterpret_cast<const char*>(&OneEntry), 8);
			}
		}
		CacheFile.close();
	}
}

bool ValidateSlaveLangUpToDate(const wstring& szLangName)
{
	ifstream	ChangesFile(szLangName + L"_changes.txt");
	if ( ChangesFile.is_open() )
	{
		string		FileLine;
		while ( getline(ChangesFile, FileLine) )
		{
			if ( !FileLine.empty() && FileLine[0] != '#' )
			{
				ChangesFile.close();
				return false;
			}
		}
		ChangesFile.close();
	}
	return true;
}

const wchar_t* GetFormatName( eGXTVersion version )
{
	switch ( version )
	{
	case GXT_VC:
		return L"GTA Vice City";
	case GXT_SA:
		return L"GTA San Andreas";
	}
	return L"Unsupported";
}

int wmain(int argc, wchar_t* argv[])
{
	wcout << L"GXT Builder v1.1\nMade by Silent for GTA VCS PC Edition\n\n";
	if ( argc >= 2 )
	{
				// A map of GXT tables
		wchar_t								wcCharacterMap[CHARACTER_MAP_SIZE];
		tableMap_t							TablesMap(compTable);
		map<uint32_t,VersionControlMap>		MasterCacheMap;
		forward_list<ofstream*>				SlaveStreamsList;
		wstring								LangName(argv[1]);
		ofstream							LogFile;

		// Parse commandline arguments
		eGXTVersion		fileVersion = GXT_SA;

		int	firstStream = 2;
		for ( int i = 2; i < argc; ++i )
		{
			if ( argv[i][0] == '-' )
			{
				wstring	tmp = argv[i];
				firstStream++;
				if ( tmp == L"-sa" )
					fileVersion = GXT_SA;
				else if ( tmp == L"-vc" )
					fileVersion = GXT_VC;
			}
			else
				break;
		}

		// Retrieve language name
		LangName = wstring(LangName.begin()+1+LangName.find_last_of('\\'), LangName.end()-4);

		wcout << L"Building a file from " << LangName << L".ini, please wait...\n";
		wcout << L"Used format: " << GetFormatName( fileVersion ) << L"\n";

		LogFile.open(LangName + L"_build.log");

		time_t			currentTime;

		time(&currentTime);
		LogFile << string(LangName.begin(), LangName.end()) << ".gxt building started at " << ctime(&currentTime);

		try
		{
			ParseINI( LangName, TablesMap, wcCharacterMap, fileVersion );
			if ( argc > firstStream )
			{
				// Open 'slave' streams
				for ( int i = firstStream; i < argc; ++i )
				{
					wstring			SlaveFileName = argv[i];
					SlaveFileName += L"_changes.txt";

					ofstream*		SlaveStream = new ofstream(SlaveFileName, ofstream::app);
					if ( SlaveStream->is_open() )
					{
						SlaveStream->put('\n');
						SlaveStreamsList.push_front(SlaveStream);
					}
				}
				ReadMasterTable(/*TablesMap,*/ LangName, MasterCacheMap);
			}
			else
			{
				if ( !ValidateSlaveLangUpToDate(LangName) )
				{
					wstring			Error(L"Error: This language isn't up to date - please check " + LangName + L"_changes.txt for the latest English language updates, apply them to this language translation files and try again.");
					wcerr << L"Error: Language file not updated to cover English updates!\n";
					MessageBox(nullptr, Error.c_str(), L"GXT Builder", MB_OK | MB_ICONWARNING);
					return 0;
				}
			}


			try
			{
				ReadTextFiles(TablesMap, MasterCacheMap, SlaveStreamsList, LogFile, argc > 2);
				ApplyCharacterMap(TablesMap, wcCharacterMap);
			}
			catch (uint32_t cChar)
			{
				wcerr << L"Error: Can't locate character \"" << static_cast<wchar_t>(cChar) << "\" (" << cChar << L") in a character map!\n";
				return -1;
			}
			catch (const wchar_t* pDir)
			{
				wcerr << L"Error: Directory " << pDir << L" not found or empty!\n";
				return -1;
			}

			ProduceGXTFile( LangName, TablesMap, fileVersion );
			if ( argc > 2 )
				ProduceMasterCache(LangName, MasterCacheMap);

			ProduceStats(LogFile, LangName, TablesMap);
		}
		catch (...)
		{
			wcerr << L"Unknown error occured!\n";
			return 1;
		}

		LogFile.close();
	}
	else
		wcerr << L"Input file not specified!\n";

	return 0;
}