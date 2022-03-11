// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_WINDOWS_PE_INFO_HPP
#define BOOST_DLL_DETAIL_WINDOWS_PE_INFO_HPP

#include <boost/dll/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <cstring>
#include <fstream>

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>

namespace boost { namespace dll { namespace detail {

// reference:
// http://www.joachim-bauch.de/tutorials/loading-a-dll-from-memory/
// http://msdn.microsoft.com/en-us/magazine/ms809762.aspx
// http://msdn.microsoft.com/en-us/magazine/cc301808.aspx
//

// Basic Windows typedefs. We can not use <boost/winapi/basic_types.hpp> header
// because that header must be included only on Windows platform
typedef unsigned char BYTE_;
typedef unsigned short WORD_;
typedef boost::uint32_t DWORD_;
typedef boost::int32_t LONG_;
typedef boost::uint32_t ULONG_;
typedef boost::int64_t LONGLONG_;
typedef boost::uint64_t ULONGLONG_;

struct IMAGE_DOS_HEADER_ { // 32/64 independent header
    boost::dll::detail::WORD_   e_magic;        // Magic number
    boost::dll::detail::WORD_   e_cblp;         // Bytes on last page of file
    boost::dll::detail::WORD_   e_cp;           // Pages in file
    boost::dll::detail::WORD_   e_crlc;         // Relocations
    boost::dll::detail::WORD_   e_cparhdr;      // Size of header in paragraphs
    boost::dll::detail::WORD_   e_minalloc;     // Minimum extra paragraphs needed
    boost::dll::detail::WORD_   e_maxalloc;     // Maximum extra paragraphs needed
    boost::dll::detail::WORD_   e_ss;           // Initial (relative) SS value
    boost::dll::detail::WORD_   e_sp;           // Initial SP value
    boost::dll::detail::WORD_   e_csum;         // Checksum
    boost::dll::detail::WORD_   e_ip;           // Initial IP value
    boost::dll::detail::WORD_   e_cs;           // Initial (relative) CS value
    boost::dll::detail::WORD_   e_lfarlc;       // File address of relocation table
    boost::dll::detail::WORD_   e_ovno;         // Overlay number
    boost::dll::detail::WORD_   e_res[4];       // Reserved words
    boost::dll::detail::WORD_   e_oemid;        // OEM identifier (for e_oeminfo)
    boost::dll::detail::WORD_   e_oeminfo;      // OEM information; e_oemid specific
    boost::dll::detail::WORD_   e_res2[10];     // Reserved words
    boost::dll::detail::LONG_   e_lfanew;       // File address of new exe header
};

struct IMAGE_FILE_HEADER_ { // 32/64 independent header
    boost::dll::detail::WORD_   Machine;
    boost::dll::detail::WORD_   NumberOfSections;
    boost::dll::detail::DWORD_  TimeDateStamp;
    boost::dll::detail::DWORD_  PointerToSymbolTable;
    boost::dll::detail::DWORD_  NumberOfSymbols;
    boost::dll::detail::WORD_   SizeOfOptionalHeader;
    boost::dll::detail::WORD_   Characteristics;
};

struct IMAGE_DATA_DIRECTORY_ { // 32/64 independent header
    boost::dll::detail::DWORD_  VirtualAddress;
    boost::dll::detail::DWORD_  Size;
};

struct IMAGE_EXPORT_DIRECTORY_ { // 32/64 independent header
    boost::dll::detail::DWORD_  Characteristics;
    boost::dll::detail::DWORD_  TimeDateStamp;
    boost::dll::detail::WORD_   MajorVersion;
    boost::dll::detail::WORD_   MinorVersion;
    boost::dll::detail::DWORD_  Name;
    boost::dll::detail::DWORD_  Base;
    boost::dll::detail::DWORD_  NumberOfFunctions;
    boost::dll::detail::DWORD_  NumberOfNames;
    boost::dll::detail::DWORD_  AddressOfFunctions;
    boost::dll::detail::DWORD_  AddressOfNames;
    boost::dll::detail::DWORD_  AddressOfNameOrdinals;
};

struct IMAGE_SECTION_HEADER_ { // 32/64 independent header
    static const std::size_t    IMAGE_SIZEOF_SHORT_NAME_ = 8;

    boost::dll::detail::BYTE_   Name[IMAGE_SIZEOF_SHORT_NAME_];
    union {
        boost::dll::detail::DWORD_   PhysicalAddress;
        boost::dll::detail::DWORD_   VirtualSize;
    } Misc;
    boost::dll::detail::DWORD_  VirtualAddress;
    boost::dll::detail::DWORD_  SizeOfRawData;
    boost::dll::detail::DWORD_  PointerToRawData;
    boost::dll::detail::DWORD_  PointerToRelocations;
    boost::dll::detail::DWORD_  PointerToLinenumbers;
    boost::dll::detail::WORD_   NumberOfRelocations;
    boost::dll::detail::WORD_   NumberOfLinenumbers;
    boost::dll::detail::DWORD_  Characteristics;
};


template <class AddressOffsetT>
struct IMAGE_OPTIONAL_HEADER_template {
    static const std::size_t IMAGE_NUMBEROF_DIRECTORY_ENTRIES_ = 16;

    boost::dll::detail::WORD_   Magic;
    boost::dll::detail::BYTE_   MajorLinkerVersion;
    boost::dll::detail::BYTE_   MinorLinkerVersion;
    boost::dll::detail::DWORD_  SizeOfCode;
    boost::dll::detail::DWORD_  SizeOfInitializedData;
    boost::dll::detail::DWORD_  SizeOfUninitializedData;
    boost::dll::detail::DWORD_  AddressOfEntryPoint;
    union {
        boost::dll::detail::DWORD_   BaseOfCode;
        unsigned char padding_[sizeof(AddressOffsetT) == 8 ? 4 : 8]; // in x64 version BaseOfData does not exist
    } BaseOfCode_and_BaseOfData;

    AddressOffsetT              ImageBase;
    boost::dll::detail::DWORD_  SectionAlignment;
    boost::dll::detail::DWORD_  FileAlignment;
    boost::dll::detail::WORD_   MajorOperatingSystemVersion;
    boost::dll::detail::WORD_   MinorOperatingSystemVersion;
    boost::dll::detail::WORD_   MajorImageVersion;
    boost::dll::detail::WORD_   MinorImageVersion;
    boost::dll::detail::WORD_   MajorSubsystemVersion;
    boost::dll::detail::WORD_   MinorSubsystemVersion;
    boost::dll::detail::DWORD_  Win32VersionValue;
    boost::dll::detail::DWORD_  SizeOfImage;
    boost::dll::detail::DWORD_  SizeOfHeaders;
    boost::dll::detail::DWORD_  CheckSum;
    boost::dll::detail::WORD_   Subsystem;
    boost::dll::detail::WORD_   DllCharacteristics;
    AddressOffsetT              SizeOfStackReserve;
    AddressOffsetT              SizeOfStackCommit;
    AddressOffsetT              SizeOfHeapReserve;
    AddressOffsetT              SizeOfHeapCommit;
    boost::dll::detail::DWORD_  LoaderFlags;
    boost::dll::detail::DWORD_  NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY_       DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES_];
};

typedef IMAGE_OPTIONAL_HEADER_template<boost::dll::detail::DWORD_>      IMAGE_OPTIONAL_HEADER32_;
typedef IMAGE_OPTIONAL_HEADER_template<boost::dll::detail::ULONGLONG_>  IMAGE_OPTIONAL_HEADER64_;

template <class AddressOffsetT>
struct IMAGE_NT_HEADERS_template {
    boost::dll::detail::DWORD_                      Signature;
    IMAGE_FILE_HEADER_                              FileHeader;
    IMAGE_OPTIONAL_HEADER_template<AddressOffsetT>  OptionalHeader;
};

typedef IMAGE_NT_HEADERS_template<boost::dll::detail::DWORD_>      IMAGE_NT_HEADERS32_;
typedef IMAGE_NT_HEADERS_template<boost::dll::detail::ULONGLONG_>  IMAGE_NT_HEADERS64_;


template <class AddressOffsetT>
class pe_info {
    typedef IMAGE_NT_HEADERS_template<AddressOffsetT>   header_t;
    typedef IMAGE_EXPORT_DIRECTORY_                     exports_t;
    typedef IMAGE_SECTION_HEADER_                       section_t;
    typedef IMAGE_DOS_HEADER_                           dos_t;

    template <class T>
    static void read_raw(std::ifstream& fs, T& value, std::size_t size = sizeof(T)) {
        fs.read(reinterpret_cast<char*>(&value), size);
    }

public:
    static bool parsing_supported(std::ifstream& fs) {
        dos_t dos;
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&dos), sizeof(dos));

        // 'MZ' and 'ZM' according to Wikipedia
        if (dos.e_magic != 0x4D5A && dos.e_magic != 0x5A4D) {
            return false;
        }

        header_t h;
        fs.seekg(dos.e_lfanew);
        fs.read(reinterpret_cast<char*>(&h), sizeof(h));

        return h.Signature == 0x00004550 // 'PE00'
                && h.OptionalHeader.Magic == (sizeof(boost::uint32_t) == sizeof(AddressOffsetT) ? 0x10B : 0x20B);
    }

private:
    static header_t header(std::ifstream& fs) {
        header_t h;

        dos_t dos;
        fs.seekg(0);
        read_raw(fs, dos);

        fs.seekg(dos.e_lfanew);
        read_raw(fs, h);

        return h;
    }
    
    static exports_t exports(std::ifstream& fs, const header_t& h) {
        exports_t exports;

        static const unsigned int IMAGE_DIRECTORY_ENTRY_EXPORT_ = 0;
        const std::size_t exp_virtual_address = h.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT_].VirtualAddress;

        const std::size_t real_offset = get_file_offset(fs, exp_virtual_address, h);
        BOOST_ASSERT(real_offset);

        fs.seekg(real_offset);
        read_raw(fs, exports);

        return exports;
    }

    static std::size_t get_file_offset(std::ifstream& fs, std::size_t virtual_address, const header_t& h) {
        section_t image_section_header;
        
        {   // fs.seekg to the beginning on section headers
            dos_t dos;
            fs.seekg(0);
            read_raw(fs, dos);
            fs.seekg(dos.e_lfanew + sizeof(header_t));
        }

        for (std::size_t i = 0;i < h.FileHeader.NumberOfSections;++i) {
            read_raw(fs, image_section_header);
            if (virtual_address >= image_section_header.VirtualAddress 
                && virtual_address < image_section_header.VirtualAddress + image_section_header.SizeOfRawData) 
            {
                return image_section_header.PointerToRawData + virtual_address - image_section_header.VirtualAddress;
            }
        }

        return 0;
    }

public:
    static std::vector<std::string> sections(std::ifstream& fs) {
        std::vector<std::string> ret;

        const header_t h = header(fs);
        ret.reserve(h.FileHeader.NumberOfSections);

        // get names, e.g: .text .rdata .data .rsrc .reloc
        section_t image_section_header;
        char name_helper[section_t::IMAGE_SIZEOF_SHORT_NAME_ + 1];
        std::memset(name_helper, 0, sizeof(name_helper));
        for (std::size_t i = 0;i < h.FileHeader.NumberOfSections;++i) {
            // There is no terminating null character if the string is exactly eight characters long
            read_raw(fs, image_section_header);
            std::memcpy(name_helper, image_section_header.Name, section_t::IMAGE_SIZEOF_SHORT_NAME_);
            
            if (name_helper[0] != '/') {
                ret.push_back(name_helper);
            } else {
                // For longer names, image_section_header.Name contains a slash (/) followed by ASCII representation of a decimal number.
                // this number is an offset into the string table.
                // TODO: fixme
                ret.push_back(name_helper);
            }
        }

        return ret;
    }

    static std::vector<std::string> symbols(std::ifstream& fs) {
        std::vector<std::string> ret;

        const header_t h = header(fs);
        const exports_t exprt = exports(fs, h);
        const std::size_t exported_symbols = exprt.NumberOfNames;
        const std::size_t fixed_names_addr = get_file_offset(fs, exprt.AddressOfNames, h);

        ret.reserve(exported_symbols);
        boost::dll::detail::DWORD_ name_offset;
        std::string symbol_name;
        for (std::size_t i = 0;i < exported_symbols;++i) {
            fs.seekg(fixed_names_addr + i * sizeof(name_offset));
            read_raw(fs, name_offset);
            fs.seekg(get_file_offset(fs, name_offset, h));
            getline(fs, symbol_name, '\0');
            ret.push_back(symbol_name);
        }

        return ret;
    }

    static std::vector<std::string> symbols(std::ifstream& fs, const char* section_name) {
        std::vector<std::string> ret;

        const header_t h = header(fs);
        
        std::size_t section_begin_addr = 0;
        std::size_t section_end_addr = 0;
        
        {   // getting address range for the section
            section_t image_section_header;
            char name_helper[section_t::IMAGE_SIZEOF_SHORT_NAME_ + 1];
            std::memset(name_helper, 0, sizeof(name_helper));
            for (std::size_t i = 0;i < h.FileHeader.NumberOfSections;++i) {
                // There is no terminating null character if the string is exactly eight characters long
                read_raw(fs, image_section_header);
                std::memcpy(name_helper, image_section_header.Name, section_t::IMAGE_SIZEOF_SHORT_NAME_);
                if (!std::strcmp(section_name, name_helper)) {
                    section_begin_addr = image_section_header.PointerToRawData;
                    section_end_addr = section_begin_addr + image_section_header.SizeOfRawData;
                }
            }
            
            // returning empty result if section was not found
            if(section_begin_addr == 0 || section_end_addr == 0)
                return ret;
        }

        const exports_t exprt = exports(fs, h);
        const std::size_t exported_symbols = exprt.NumberOfFunctions;
        const std::size_t fixed_names_addr = get_file_offset(fs, exprt.AddressOfNames, h);
        const std::size_t fixed_ordinals_addr = get_file_offset(fs, exprt.AddressOfNameOrdinals, h);
        const std::size_t fixed_functions_addr = get_file_offset(fs, exprt.AddressOfFunctions, h);

        ret.reserve(exported_symbols);
        boost::dll::detail::DWORD_ ptr;
        boost::dll::detail::WORD_ ordinal;
        std::string symbol_name;
        for (std::size_t i = 0;i < exported_symbols;++i) {
            // getting ordinal
            fs.seekg(fixed_ordinals_addr + i * sizeof(ordinal));
            read_raw(fs, ordinal);

            // getting function addr
            fs.seekg(fixed_functions_addr + ordinal * sizeof(ptr));
            read_raw(fs, ptr);
            ptr = static_cast<boost::dll::detail::DWORD_>( get_file_offset(fs, ptr, h) );

            if (ptr >= section_end_addr || ptr < section_begin_addr) {
                continue;
            }

            fs.seekg(fixed_names_addr + i * sizeof(ptr));
            read_raw(fs, ptr);
            fs.seekg(get_file_offset(fs, ptr, h));
            getline(fs, symbol_name, '\0');
            ret.push_back(symbol_name);
        }

        return ret;
    }
    
    // a test method to get dependents modules,
    // who my plugin imports (1st level only)
    /*
    e.g. for myself I get:
      KERNEL32.dll
      MSVCP110D.dll
      boost_system-vc-mt-gd-1_56.dll
      MSVCR110D.dll
    */
    /*
    static std::vector<std::string> depend_of(boost::dll::fs::error_code &ec) BOOST_NOEXCEPT {
        std::vector<std::string> ret;

        IMAGE_DOS_HEADER* image_dos_header = (IMAGE_DOS_HEADER*)native();
        if(!image_dos_header) {
            // ERROR_BAD_EXE_FORMAT 
            ec = boost::dll::fs::make_error_code(
                 boost::dll::fs::errc::executable_format_error
                 );

            return ret;
        }

        IMAGE_OPTIONAL_HEADER* image_optional_header = (IMAGE_OPTIONAL_HEADER*)((boost::dll::detail::BYTE_*)native() + image_dos_header->e_lfanew + 24);
        if(!image_optional_header) {
            // ERROR_BAD_EXE_FORMAT 
            ec = boost::dll::fs::make_error_code(
                 boost::dll::fs::errc::executable_format_error
                 );

            return ret;
        }

        IMAGE_IMPORT_DESCRIPTOR* image_import_descriptor =  (IMAGE_IMPORT_DESCRIPTOR*)((boost::dll::detail::BYTE_*)native() + image_optional_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
        if(!image_import_descriptor) {
            // ERROR_BAD_EXE_FORMAT 
            ec = boost::dll::fs::make_error_code(
                 boost::dll::fs::errc::executable_format_error
                 );

            return ret;
        }

        while(image_import_descriptor->FirstThunk) {
           std::string module_name = reinterpret_cast<char*>((boost::dll::detail::BYTE_*)native() + image_import_descriptor->Name);

           if(module_name.size()) {
              ret.push_back(module_name);
           }
                
           image_import_descriptor++;
        }

        return ret;
    }
*/
};

typedef pe_info<boost::dll::detail::DWORD_>      pe_info32;
typedef pe_info<boost::dll::detail::ULONGLONG_>  pe_info64;

}}} // namespace boost::dll::detail

#endif // BOOST_DLL_DETAIL_WINDOWS_PE_INFO_HPP

/* pe_info.hpp
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
*/