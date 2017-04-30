#ifndef __GXTBUILD_H
#define __GXTBUILD_H

#include <string>
#include <map>
#include <memory>

enum eGXTVersion
{
	GXT_III,	// Unsupported
	GXT_VC,
	GXT_SA
};

class GXTTableBase
{
public:
	std::wstring			szPath;
	std::string				Content;

	GXTTableBase(std::wstring szFilePath)
		: szPath(std::move(szFilePath))
	{}

	virtual ~GXTTableBase()
	{}

public:
	virtual bool	InsertEntry( const std::string& entryName, uint32_t offset ) = 0;
	virtual size_t	GetNumEntries() = 0;
	virtual size_t	GetFormattedContentSize() = 0;
	virtual size_t	GetEntrySize() = 0;
	virtual void	WriteOutEntries( std::ostream& stream ) = 0;
	virtual void	WriteOutContent( std::ostream& stream ) = 0;
	virtual void	PushFormattedChar( int character ) = 0;
};

struct EntryName
{
	char						cName[8];

	EntryName(const char* pName)
	{
		memset(cName, 0, sizeof(cName));
		strncpy( cName, pName, _countof(cName) );
	}

	EntryName(const wchar_t* pName)
	{
		memset(cName, 0, sizeof(cName));
		wcstombs( cName, pName, _countof(cName) );
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

namespace VC
{
	class GXTTable : public GXTTableBase
	{
	public:
		GXTTable( std::wstring szFilePath )
			: GXTTableBase( std::move(szFilePath) )
		{}

		virtual size_t	GetNumEntries() override
		{
			return Entries.size();
		}

		virtual size_t GetFormattedContentSize() override
		{
			return FormattedContent.size() * sizeof(character_t);
		}

		virtual size_t GetEntrySize() override
		{
			return GXT_ENTRY_NAME_LEN + sizeof(uint32_t);
		}
	
		virtual bool	InsertEntry( const std::string& entryName, uint32_t offset ) override;
		virtual void	WriteOutEntries( std::ostream& stream ) override;
		virtual void	WriteOutContent( std::ostream& stream ) override;
		virtual void	PushFormattedChar( int character ) override;

	private:
		typedef uint16_t character_t;
		static const size_t		GXT_ENTRY_NAME_LEN = 8;

		std::map<std::string, uint32_t>	Entries;
		std::basic_string<character_t>	FormattedContent;
	};
};

namespace SA
{
	class GXTTable : public GXTTableBase
	{
	public:
		GXTTable( std:: wstring szFilePath )
			: GXTTableBase( std::move(szFilePath) )
		{}

		virtual size_t	GetNumEntries() override
		{
			return Entries.size();
		}

		virtual size_t GetFormattedContentSize() override
		{
			return FormattedContent.size() * sizeof(character_t);
		}

		virtual size_t GetEntrySize() override
		{
			return sizeof(uint32_t) + sizeof(uint32_t);
		}

		virtual bool	InsertEntry( const std::string& entryName, uint32_t offset ) override;
		virtual void	WriteOutEntries( std::ostream& stream ) override;
		virtual void	WriteOutContent( std::ostream& stream ) override;
		virtual void	PushFormattedChar( int character ) override;

	private:
		typedef uint8_t character_t;

		std::map<uint32_t, uint32_t>	Entries;
		std::basic_string<character_t>	FormattedContent;
	};
};

typedef std::map<EntryName, std::unique_ptr<GXTTableBase>, bool(*)(const EntryName&,const EntryName&)>	tableMap_t;

#endif