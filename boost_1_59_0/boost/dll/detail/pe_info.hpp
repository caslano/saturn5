// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
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
#include <string> // for std::getline
#include <vector>

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
        static const unsigned int IMAGE_DIRECTORY_ENTRY_EXPORT_ = 0;
        const std::size_t exp_virtual_address = h.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT_].VirtualAddress;
        exports_t exports;

        if (exp_virtual_address == 0) {
            // The virtual address can be 0 in case there are no exported symbols
            std::memset(&exports, 0, sizeof(exports));
            return exports;
        }

        const std::size_t real_offset = get_file_offset(fs, exp_virtual_address, h);
        BOOST_ASSERT(real_offset);

        fs.seekg(real_offset);
        read_raw(fs, exports);

        return exports;
    }

    static std::size_t get_file_offset(std::ifstream& fs, std::size_t virtual_address, const header_t& h) {
        BOOST_ASSERT(virtual_address);

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

        if (exported_symbols == 0) {
            return ret;
        }

        const std::size_t fixed_names_addr = get_file_offset(fs, exprt.AddressOfNames, h);

        ret.reserve(exported_symbols);
        boost::dll::detail::DWORD_ name_offset;
        std::string symbol_name;
        for (std::size_t i = 0;i < exported_symbols;++i) {
            fs.seekg(fixed_names_addr + i * sizeof(name_offset));
            read_raw(fs, name_offset);
            fs.seekg(get_file_offset(fs, name_offset, h));
            std::getline(fs, symbol_name, '\0');
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
            std::getline(fs, symbol_name, '\0');
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
tpa69uJQzm2GHMedUZKqZu8ct801VQbmFnxNXMvSVmYV0JtHA2Q2rV0o3y5o5XV4/+sxqW9Gkfv4+gmTUu8WTUcJiiaVCATGJHUlRmfTGYZnz1lPyS3GBXzet5dd5znOt+0nR/tPJyxNlm4ORnu3crUidnsk1lNZLA62OZ8PtDyCLW0SPifVF8hK+IhHG8Iv0FGJszULLDJQJkgmOHueMKE2CdCMN/QXIDckLA4uaD9GmhB5M5qgX5DqUF4T/wYC+ODK5IfZyl4gC1WBVdCHXJrmBFWB7WdTtIepDiM6I3W1qWPeJNs8pyAO1ANg3x0xpFOqMmadGc3vIsznc/T+k3xkVSatayTo5ZJqLRP2c3ft/r0afmhfQIUOPCAfIkht1TheMadvwMbGybr94zQDHDLNtqwYIm+pcVjS3w1aGS0jnioFX0v/tF7YnXZ9Y+FOpuQCBdguyIvR+QefyeKYXWgMrHUsGrROWFten40XRGxR7lNkjTrhPtinT8b8/a9oC+KsoTRFf36tGRKD95CkL0IY1sHZd48id+dX+ARQEyA2GCfhTMmLhlN3OZ+EOBXSYhRxoGKWHygHQEDpIFntmeZTiLHEz3AR3iHGjQEzq95/INHDae2qvOGDiFU6QpP5Kanl+9ajn5RJKJVStaHFnbkKWw4V77tk1cLVr0OHJ41fm4fMBFH+8/nMxs07NxY4LtydX0CV4RdJEcc/u/bjoPuBlVFSU8GMw8u/5lFcyV9tmtNtPOWHqiFX8IGSjV0DdLAumaOq/jqv7eamyd2UPQc88au5uDinrqDs6c+KLpj91J545TxUJT+KlEdjujZOCIR9cX9Dehlgb5KYTqPp5OqMxyw8B93isCQld8CKLPsqsdnNLS73YPvVNDaRdTTP7mCsHH2ADw5IT9YDVkSvutg/M0TbAggGno6nIrBbIKVaZiQpIbI6uB3oWATVkMOZ7/Y0BlDYvjNvZGO49g0iNrseCsbg2jXKxjMaPEq/S9xvsimg4NxX1nS7JuzBm2FPTZz4haLmVS9qMyvBWV1fVrV+Krc50CJbH1739bTXzcGuXMPhxKjXEPY/mt/exY+mpLeIZ+Iu9jhsZ4hOZD0HKwzua0Qh6PGOg/skKQ0qqR7rXpuvZyU81z4qkxlZNf98j5BXr5Gfc/J5TTfBoG8AO+69v4P2cB6WIOCJvzSzvKX8vUgrimlHZA17tzMnEkYsjm92OxrQIIwctTpab6V334+QY8LoKZv0CN85B6YA2GvndJIsl6p3aMvvukIpvllK19LUCYZWYTnnioUS8UEuW1CtsTXTprsseK/iMPiQQZoEoz7h0zXLroJHIJpJEIhNKeQHSrjvdw72tmr1x4AqjIiUeGtFqdT+NeAJTMC9iJbwZFfH7RsK0nmYSpDWYFw6hzmrN7woQC8C5mI/FJvWJT+dDqN6LsWuBTqpYfTFE5Z2viKMyZaEVmZvhgBVT1fJjpsSuLigEY+SciUGhBhL4zE8a3zimEReogidAQ3WuCOwkSLitcPev3ua52Zeklq17haO8snKCmdn7uwJOV8E8YLDJrVrhGlpy4SzUT00mH778sASkhjuecPNgaLZIYEbY953hPgCGoTGRpNfU67wsCZ8Lj+ApjNtCMdTwgjMuskk4qVz2iwEt3N7CNyI3M0MoA449ILFTwKK7JvgOdxHn/0YFtty/DCAQV0HmqHRXDA35kaD8BNyCN7DDTSBiEPymeYedcN/dsKc8XHBTtENbcQcuJ/KmAKr9YBqb7BAqSdjQkFf5z4SoVvehmFHc+xzNPD2i7T/W24UTsbGvGPv9DjRhbjNhB0V94MV5VZo7qH4gbu1SBx14HWBd/b7IScf6WY9/KQ/N+duPzckXBBkZUbC9cF+dy4cCoz1W+9X8a40GvVzAkLJpJU3WMHnIbd2mRvd7Gi7z725pHzCGcoMzG27N6WuplgHTruLeuRKIxfZKy/jkiv5jGM47ldP0xlZWPySLZlT1WG4sXXG8tV7rPzQFL65TDLXon3vlKiQkd6RO/cyFF6ja4JuuFSjde6SVtZ5j66pbWyYVtXka1viOVv8+EnUAlab8y7JVP4DgFJmk21h//8f6np7oIi21t1mXHieMDLnTJMACnmQuJDB40Hm86Ao6AHqiOIJGoKKwkZkpYNTUDPH8oAIk7RDUZRLru6cXN66K6qLrr4Aj6BHT6q6PGARS4nodb5vUgNN8J65vMio4/R+hb/NTb/l6OftVVxe1l7WVtbWXjI3uKuzdbWuH0IvWemjNGnvBv64Ab2ZW8q6j4AsmZ+h7YM3TFNRLxDLRjXU6AAlqOSLoO2rra4K3xLGtKKcnhjuVoOlZCeDmH5Tu8tH62iGXnjE1FxSOCjxrBSEfMehqRcMlWzKZulO3G9pZ4e6mTPJ02lOuLSp1P3TTClUdeDXdVvd+ze2tcAp/0KHXcU0e7ov4ZLOia9+tW30OTvZNqwfWycdg0ujaC96ViJylzT9YqPU7WO1GuTqqaHxZValKTwKPMq9ahi2h+M/X7QTQkkkQiZUAZbemowDsSMRl0119i8Jr2QeYiUV0Pakt9Wklw3khxdm/65+9N6Vtx3sAaE0b5nVN2MxjbqOnD4/5URj21LqBGcJn9q9Q2t+t5RqonQoX2jEAX15M/Xw0ouq+VXi1Dr+Xrtq4duXJTfaM06Z5i5rzKFP7dR7aJzk8XKRILEvzUSrywX3jRjqxapxG5mky6dweyt2X/CeiISQhLiYoDhVftkvVM5sUAzzyHvXXwlTvMdjkI5DoFFbtZBXNvVYCZfOHR0e31ZyU6ibdSudmYNEOjGlcbfkxPTjy//0eMgnbZyXuSnQJzZu6p5b9Nfzn7Gf/RF35huA22j4w/e8cGVWqitY+DPUevax+FjNTkwaCWpPd2sJF2v8gQp0TlRxqO5pg6leqeAnv0tRdax3fyCf7Hx8An9lxofqjWJ8xdeNWO9CDcqJ9pPRB0UYsCw7rV6SLd3tDsntQjHthhbEqrcjQF5we2ZfPHut8za8HVxz3wLsiIatmbDQgIP5rc/5SLlthsE7+6O408E3k5RUEfD8DJwhStjq6yJNSTVF6K4ZEr5faX9KrfGxAofElkH6q2x4aeIX2ODfut0Qy5dy5lNRWv6W/OA5hNQSpCXXAjqmI/HMb7KZCwcuPiNX89RDuFskdjEtTl/fyzvSJ3WJm570wOkc5kTg/mBCahQN7SK6hiITy3laIZL99Ij7fiJf2JBBQe/x0UEzSVFvvYaObfbFnBoRv5JJF4yNIC487sTQUdVmjcWFgiuPncIc8bU05vm0roUe/Mz2Xrx5lnG1eXa4bSh3+cvIbHU/NqT2nHDpV94sfQg4FoLs6OKClWFZYbUFf/dd5UOjuwSWiZRn3XzBSxHyqK+3zra7A4K9iI8xrU8VqC0zW3njkEUQ4/QztkqPdNDpjlpTHHt7qb/+I22NbviEK0VsaREr/IlsxTfr6byCfcRXGtOUYC0fjG6AmgQyvxfaLloFRA+DtvJApqAYVfj65+3lhZszPi3CG2s3I5ofIZ4fs0FEbbAZcMv4Rld8KwKKX3CI1Pa2AsNUt3lp6LOLFxNDren36CrZkejTpBYiV6bzfubWemx1ysHEo66QywczBeYRV/LorG0Gce6ezfaD0/IR678zrqx/E4xPejhbf9xTv3wx/Kmv8kM/zEdfX4dv7m42e1gj2+w1whf4zpFnLJMIW7NFCHfO1doN2Mrw+7xxChCgkStiXZBZPOYKqkG5+Zf5fAqUmbtsbOUzx7sfKnV5PDBe+fr3IuKDcnYW6Ff3FSMlnbqbNN3gOSrcvHJ9TcOISikJZaqUj8f7Waw3aN0E8hNYOt4jHGw8J88k5NI9DONFH/dK60KVRbRTdSglT8Jd5xp+aWrANHUrd/0ZhXjN+mw7EISXSN5L30Ubfan3fmBfsQ2pv64JB3/BB9faqSeYAEf4I697Wm+7T0o3zo+ba6mnDZSZuKzy/2hn5tMdZZ7SbD/CvEx8Pv/ZYLVVddfEzyWGxZLvrrO/rXquBK13U+WS/9oLen9rStS6cRqvHJJ5fTM6OYCnoib3Vp/sa8I9CBVRcbfoULF1r+RkBgFmSGIkmEFKMAOlM5rHmaYOTDFNPcoMevxlzE2xLP3TX+LL2FK9BUb56jZetrP0fEYEW2KZSD/CC9gzYOAbm2kG/LeyVrZyphZVUidzZqoSzHfr4jNbuQHBfZnUvudB/zYmZ0p1hh+OsunjuelUDYq6rvP+xJDlgvMk1PHxFBh7pbH26dB3lzjgsWQGgkHZfaIbeHtyMCl1wPKk7d69J2fsiy0xRykKysRpVKyBd0K3vR2YL+pRFRuPwlWqmWACMnVMveujBofZCzPzDOVJMqTok3nA3yeexuGHB84dQlCCi/Z9bi1c3L4kvVua3vtLLFyfk1l0FPZMFK5m5On2prU0fxv5cxZgoY/WBH44d1ey3GU91LDrNf37dnaQpjFI6/ta75EFBov7BfemyOuUmI23SjeiO7pfBh7HdANFoNfV8EIxy1m5pYaWeeRuToPzxaO33Fh99W+H08M4hWu7sqpfsvMSqrj9p9bpxs5lId2GR+sz6YdyU8pJ/9K9EhDBv19effqO7s1hxZpaenKA65DKdUlNFcqGTrWh41vqI6b1wTOQhMeMTX5zKun1MymmGNcv/BJYErZYyWuWE6o4Z3JpFN7TrFnwpxjTSvOFI3vTA8dpC9V46zQAu2Nm53RZzKDH6sU7CueC4bUJtGGntCUypi3UHWMPMXFvrOrdNv4o/q5hV2rU1x/VnnrBD+4q22T5IvCb84eQuJcfaCb0R+kZCBszAjVIipdpXIV39vlwKzsUVepgRg4jaRCBxRpOJ+YgKZnpRgqC/jfNSIcw9DzmOyndjKbk2ENK0i+8a/igrStK36kKrg19tIVOfmA2YHBKccHlUR2vS/xGBT/mFVmaIsoca+S5MPnXIiryZkgZ4Qycxw7wFPQPlFwJY066gZU+ZXaQVOqA6Jwo9hpE1V3B9UHG07NU6jioLkBvoKk0M+OJWuwV6miD+tfzlSf1mrWlBDybJ3jWA0x7qIERJM70CsafcBkN7vimkDOO6bKnGjb10I9j+oF3pZkInzVnk8DrNlb1TYHzwrBADn6ES3cyT9D2OH5BNi81djhKnYmBHrzMo7n8JF6s/NyVxqGzkivV/w6nJwIMCPzw95ERN1dmYURpwKlocCk6VgUqRoUBlvXVroIG/Ew96sRAQzvEk6m2YaNOKOs06WaAkLLRNi5+Au4SEUpu+DMkEv0CmalD3wR7rWeb3zJikybrh6tj271hWJgDjMZpiLhdOMtEp3f9xfnpLv7zidEAn2917PeUXEq7NcWMSlQQE72aI+eDPwhxr17ws/VAf7SW8tWxLrFuedGlI0ZHOwlenvmUcnc28+dkAK0a/d2p1An11Ltm5I2sN609YM0YajcdUHN19V7OquWF3gQune/kw9F7fLtmimWd9s/fodka7wcag0p1gSpBa5A7lpWiGU2E3Jf1gGsQNiQ2BB7JjnRbbl3kHeQAbpAf+Zbkm/qgNqW9t5gIfM8IjnN3I7Ju7mM6EljfpbR2gFH0iUJB/bYwAzxbMPKa7VQeq6DsdUW1ZljSEF+uu6R3HuKnuu5AEFN4dY7n3+eg3HmCT9pqy5rJsjp5rE/Zpm7ftukVxoddS5mzz1elerMyfkp322nPZtCnoy45g9zJfgholTmpfSybGc3r6h2qGU3c3RcTGzTn54AYxtBKaV/E1hFWT2LNy3RwkGVxpE52zPV0T9YuAzyTGqwCJA4Jj4hHen3KPYQhtyHqSB1Bd1J9qgOkIZYh9QGikBhHXj1Kre5Q8yuyIcfJJ+aPLuzRv8upuORuz++LopycLjn8FB/yTMEhy8ayTQJ22CW43PN2g0hvgMPagXbmTUI7XIvBP1BPzy4Bv1q3/DxdW7zYcIV4Psm9m09uFB12MbKnpqGfhjm4o7k4yW4708ezMYQ649OvMQqYmOsN5sEgW32gLX/y+hwZg2C1I/NWdaRh7tx+N47AGwkgbXOgrXBIG3Pk9V15A+7U/tXM/lclIG1toK0pSBt0pHU30vobeQNv3sAa3sCbD5BWduT1WfJ6XAmDraT+V31IG/3/aOUMtmw3D31dwp3o/NbozFA5BKrf3chYDBejmyep33TMzUf2iNoJwDyR2QAILPfTQKX5r66zny6jz9gFPBYYIfxhB+PnyKn9xdj7muKo3pMd8frabhS4jsIbf+3FbGZLhBNLNGAc7Ygliq4d0LWdgLQJAmmpA2l5A2m5A2P7nuu/7z/skP7sPv4unvbrOW9ftbZy6KwzjQ1LNErNH5K8OsXIvbJvrourHI10uJtNhXSo/qCnfewe0z+gHpng3f/+9kKWRpNS70hsBHt5CRtyDaYAfTH+izydBVODqkE995OH0YJ1wBtx3xkj9GE64Y+998UF4AJ4nBcl3Pnk/1wh1AX8kVrPBOMCdWCdEF798Uzoxl0SmBIUCYQFGgX/CXDFSV/DSHCPEyYAE9AHswRugzfiFOOYUEkQjgOTxxifHvjbPB7F05t+9uLJ5AFtXfim9zKEXnwQnIzI/CFc/yn082VfiA/K/BFEX9ylMfzcCJV6ezPp4k0+y63PwWlDDoMBAXP18GRcwFrK2NMaeHGP9yln/FIOzwXhfXHctwmMCn/6Asvog//jjbnAtpGZC/WF1nHAkdiD1AaXgBvHI1+iD5gOcWmTkrEH44Vxgz02nK8D7MAHGaX16gy+IFYtzQO+AP+YCK0Bv5YP4oU04cQZAz1Tgn9wD3IR8KDLHrJLUEFAfcwGOwTkBDk7CHqqDj26DqqfM+jr8mb8kU1wTDBT9S/l/zf0/ER4tCe/lhP3p1/mDfoEq4/ovTPTeDbsiqrvHFB85AAQjvFOhErCzGfbTzK/F4QFtVP3iAjh8jI59s4INk7+jgg2XkYwj0qdF9hPHOyEAtJJcAKNcM6XQi+YL62+36EYOAZ0ggLhAjipTjDPS/EHxAn8CDveRrAX2I+hFdhQ9miP4GGitp+hfxHRd4vwZ578x04Th5164J/tB/F25Rf5U3qRNdrfiE1e62v3Uee+99rQXQydJ/LFoXFENgrXL4ECbTa0Hb02IpxQa/fX0VOB/6Qaa9qbijndNkf+VWvC3kRK0EIQs4up0niRvwe3VbLNBvhs5YbMwGiCpg3whbV3XJQHqtPkb+vOvP5z9ev61+m/03er/1b3tfa/It1jU11YAcz4h+r0G/E4ZsIQwZfAL9Sj9NBerm0MIbof3Qda2t/js1OcVC/viVhmuwYuesNbl+s+vxjPS67/F0brmXrfm85qG/Rf36hbR3T6XcfINHr7lIT7Ij2FvA6tPuhZhLPOUS0tNvnDBr2Pf29zs4eC40T+vwGOC3BjSZwu3N7MBj9EjD7dofXXn3x9be2ec/a2VYMYYl4StgnI1ow1Jh2OYPI1+8PpCY7VLpD3YN+AeG0lzyJO+7F0+9fQM/EuR4cvZTvI3vThoiOsdbQESgEswV0AX1p8YPaJUS8UnMrDzks4s2tjVPC8pqQPni2Cifqj7izG8V73vkTpUNKyFwnldYl+HjbWm+zK+tDiOgJf6tBb
*/