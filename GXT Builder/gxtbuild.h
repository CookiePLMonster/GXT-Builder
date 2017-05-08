#ifndef __GXTBUILD_H
#define __GXTBUILD_H

#include <string>
#include <map>
#include <memory>
#include <strsafe.h>

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
	static const size_t		GXT_TABLE_NAME_LEN = 8;

	char						cName[GXT_TABLE_NAME_LEN];

	EntryName(const char* pName)
	{
		StringCchCopyNExA( cName, _countof(cName), pName, GXT_TABLE_NAME_LEN, nullptr, nullptr, STRSAFE_FILL_BEHIND_NULL );
	}

	EntryName(const wchar_t* pName)
	{
		size_t numConverted = 0;
		wcstombs_s( &numConverted, cName, pName, _countof(cName) );
		std::fill( std::begin(cName)+numConverted, std::end(cName), 0 ); 
	}
};

typedef std::map<EntryName, std::unique_ptr<GXTTableBase>, bool(*)(const EntryName&,const EntryName&)>	tableMap_t;

class GXTFileBase
{
public:
	static std::unique_ptr<GXTFileBase> InstantiateBuilder( eGXTVersion version );

	void ProduceGXTFile( const std::wstring& szLangName, const tableMap_t& TablesMap );

private:
	virtual uint32_t WriteOutHeader( std::ostream& stream ) const = 0;
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
		typedef uint16_t character_t;

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
		static const size_t		GXT_ENTRY_NAME_LEN = 8;

		std::map<std::string, uint32_t>	Entries;
		std::basic_string<character_t>	FormattedContent;
	};

	class GXTFile : public GXTFileBase
	{
	private:
		virtual uint32_t WriteOutHeader( std::ostream& ) const override
		{
			// No header
			return 0;
		}
	};
};

namespace SA
{
	class GXTTable : public GXTTableBase
	{
	public:
		typedef uint8_t character_t;

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
		std::map<uint32_t, uint32_t>	Entries;
		std::basic_string<character_t>	FormattedContent;
	};

	class GXTFile : public GXTFileBase
	{
	private:
		virtual uint32_t WriteOutHeader( std::ostream& stream ) const override
		{
			const char		header[] = { 0x04, 0x00, sizeof(GXTTable::character_t) * 8, 0x00 };	// 0x080004
			stream.write(header, sizeof(header));
			return sizeof(header);
		}
	};
};

#endif