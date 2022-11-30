// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_MACHO_INFO_HPP
#define BOOST_DLL_DETAIL_MACHO_INFO_HPP

#include <boost/dll/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <algorithm>
#include <fstream>
#include <string> // for std::getline
#include <vector>

#include <boost/cstdint.hpp>

namespace boost { namespace dll { namespace detail {

typedef int integer_t;
typedef int vm_prot_t;
typedef integer_t cpu_type_t;
typedef integer_t cpu_subtype_t;

template <class AddressOffsetT>
struct mach_header_template {
    boost::uint32_t     magic;
    cpu_type_t          cputype;
    cpu_subtype_t       cpusubtype;
    boost::uint32_t     filetype;
    boost::uint32_t     ncmds;
    boost::uint32_t     sizeofcmds;
    boost::uint32_t     flags[sizeof(AddressOffsetT) / sizeof(uint32_t)]; // Flags and reserved
};

typedef mach_header_template<boost::uint32_t> mach_header_32_;
typedef mach_header_template<boost::uint64_t> mach_header_64_;

struct load_command_ {
    boost::uint32_t        cmd;        /* type of command */
    boost::uint32_t        cmdsize;
};

struct load_command_types {
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SEGMENT_          = 0x1);   /* segment of this file to be mapped */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SYMTAB_           = 0x2);   /* link-edit stab symbol table info */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SYMSEG_           = 0x3);   /* link-edit gdb symbol table info (obsolete) */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_THREAD_           = 0x4);   /* thread */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_UNIXTHREAD_       = 0x5);   /* unix thread (includes a stack) */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_LOADFVMLIB_       = 0x6);   /* load a specified fixed VM shared library */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_IDFVMLIB_         = 0x7);   /* fixed VM shared library identification */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_IDENT_            = 0x8);   /* object identification info (obsolete) */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_FVMFILE_          = 0x9);   /* fixed VM file inclusion (internal use) */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_PREPAGE_          = 0xa);   /* prepage command (internal use) */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_DYSYMTAB_         = 0xb);   /* dynamic link-edit symbol table info */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_LOAD_DYLIB_       = 0xc);   /* load a dynamically linked shared library */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_ID_DYLIB_         = 0xd);   /* dynamically linked shared lib ident */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_LOAD_DYLINKER_    = 0xe);   /* load a dynamic linker */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_ID_DYLINKER_      = 0xf);   /* dynamic linker identification */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_PREBOUND_DYLIB_   = 0x10);  /* modules prebound for a dynamically linked shared library */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_ROUTINES_         = 0x11);  /* image routines */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SUB_FRAMEWORK_    = 0x12);  /* sub framework */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SUB_UMBRELLA_     = 0x13);  /* sub umbrella */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SUB_CLIENT_       = 0x14);  /* sub client */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SUB_LIBRARY_      = 0x15);  /* sub library */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_TWOLEVEL_HINTS_   = 0x16);  /* two-level namespace lookup hints */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_PREBIND_CKSUM_    = 0x17);  /* prebind checksum */
/*
 * After MacOS X 10.1 when a new load command is added that is required to be
 * understood by the dynamic linker for the image to execute properly the
 * LC_REQ_DYLD bit will be or'ed into the load command constant.  If the dynamic
 * linker sees such a load command it it does not understand will issue a
 * "unknown load command required for execution" error and refuse to use the
 * image.  Other load commands without this bit that are not understood will
 * simply be ignored.
 */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_REQ_DYLD_         = 0x80000000);

/*
 * load a dynamically linked shared library that is allowed to be missing
 * (all symbols are weak imported).
 */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_LOAD_WEAK_DYLIB_  = (0x18 | LC_REQ_DYLD_));

    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SEGMENT_64_       = 0x19);                    /* 64-bit segment of this file to be mapped */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_ROUTINES_64_      = 0x1a);                    /* 64-bit image routines */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_UUID_             = 0x1b);                    /* the uuid */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_RPATH_            = (0x1c | LC_REQ_DYLD_));   /* runpath additions */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_CODE_SIGNATURE_   = 0x1d);                    /* local of code signature */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_SEGMENT_SPLIT_INFO_= 0x1e);                   /* local of info to split segments */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_REEXPORT_DYLIB_   = (0x1f | LC_REQ_DYLD_));   /* load and re-export dylib */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_LAZY_LOAD_DYLIB_  = 0x20);                    /* delay load of dylib until first use */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_ENCRYPTION_INFO_  = 0x21);                    /* encrypted segment information */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_DYLD_INFO_        = 0x22);                    /* compressed dyld information */
    BOOST_STATIC_CONSTANT(boost::uint32_t, LC_DYLD_INFO_ONLY_   = (0x22|LC_REQ_DYLD_));     /* compressed dyld information only */
};

template <class AddressOffsetT>
struct segment_command_template {
    boost::uint32_t     cmd;            /* LC_SEGMENT_ */
    boost::uint32_t     cmdsize;        /* includes sizeof section structs */
    char                segname[16];    /* segment name */
    AddressOffsetT      vmaddr;         /* memory address of this segment */
    AddressOffsetT      vmsize;         /* memory size of this segment */
    AddressOffsetT      fileoff;        /* file offset of this segment */
    AddressOffsetT      filesize;       /* amount to map from the file */
    vm_prot_t           maxprot;        /* maximum VM protection */
    vm_prot_t           initprot;       /* initial VM protection */
    boost::uint32_t     nsects;         /* number of sections in segment */
    boost::uint32_t     flags;          /* flags */
};

typedef segment_command_template<boost::uint32_t> segment_command_32_;
typedef segment_command_template<boost::uint64_t> segment_command_64_;

template <class AddressOffsetT>
struct section_template {
    char                sectname[16];   /* name of this section */
    char                segname[16];    /* segment this section goes in */
    AddressOffsetT      addr;           /* memory address of this section */
    AddressOffsetT      size;           /* size in bytes of this section */
    boost::uint32_t     offset;         /* file offset of this section */
    boost::uint32_t     align;          /* section alignment (power of 2) */
    boost::uint32_t     reloff;         /* file offset of relocation entries */
    boost::uint32_t     nreloc;         /* number of relocation entries */
    boost::uint32_t     flags;          /* flags (section type and attributes)*/
    boost::uint32_t     reserved[1 + sizeof(AddressOffsetT) / sizeof(uint32_t)];
};

typedef section_template<boost::uint32_t> section_32_;
typedef section_template<boost::uint64_t> section_64_;

struct symtab_command_ {
    boost::uint32_t    cmd;        /* LC_SYMTAB_ */
    boost::uint32_t    cmdsize;    /* sizeof(struct symtab_command) */
    boost::uint32_t    symoff;     /* symbol table offset */
    boost::uint32_t    nsyms;      /* number of symbol table entries */
    boost::uint32_t    stroff;     /* string table offset */
    boost::uint32_t    strsize;    /* string table size in bytes */
};

template <class AddressOffsetT>
struct nlist_template {
    boost::uint32_t     n_strx;
    boost::uint8_t      n_type;
    boost::uint8_t      n_sect;
    boost::uint16_t     n_desc;
    AddressOffsetT      n_value;
};

typedef nlist_template<boost::uint32_t> nlist_32_;
typedef nlist_template<boost::uint64_t> nlist_64_;

template <class AddressOffsetT>
class macho_info {
    typedef boost::dll::detail::mach_header_template<AddressOffsetT>        header_t;
    typedef boost::dll::detail::load_command_                               load_command_t;
    typedef boost::dll::detail::segment_command_template<AddressOffsetT>    segment_t;
    typedef boost::dll::detail::section_template<AddressOffsetT>            section_t;
    typedef boost::dll::detail::symtab_command_                             symbol_header_t;
    typedef boost::dll::detail::nlist_template<AddressOffsetT>              nlist_t;

    BOOST_STATIC_CONSTANT(boost::uint32_t, SEGMENT_CMD_NUMBER = (sizeof(AddressOffsetT) > 4 ? load_command_types::LC_SEGMENT_64_ : load_command_types::LC_SEGMENT_));

public:
    static bool parsing_supported(std::ifstream& fs) {
        static const uint32_t magic_bytes = (sizeof(AddressOffsetT) <= sizeof(uint32_t) ? 0xfeedface : 0xfeedfacf);

        uint32_t magic;
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        return (magic_bytes == magic);
    }

private:
    template <class T>
    static void read_raw(std::ifstream& fs, T& value, std::size_t size = sizeof(T)) {
        fs.read(reinterpret_cast<char*>(&value), size);
    }

    template <class F>
    static void command_finder(std::ifstream& fs, uint32_t cmd_num, F callback_f) {
        const header_t h = header(fs);
        load_command_t command;
        fs.seekg(sizeof(header_t));
        for (std::size_t i = 0; i < h.ncmds; ++i) {
            const std::ifstream::pos_type pos = fs.tellg();
            read_raw(fs, command);
            if (command.cmd != cmd_num) {
                fs.seekg(pos + static_cast<std::ifstream::pos_type>(command.cmdsize));
                continue;
            }

            fs.seekg(pos);
            callback_f(fs);
            fs.seekg(pos + static_cast<std::ifstream::pos_type>(command.cmdsize));
        }
    }

    struct section_names_gather {
        std::vector<std::string>&       ret;

        void operator()(std::ifstream& fs) const {
            segment_t segment;
            read_raw(fs, segment);

            section_t section;
            ret.reserve(ret.size() + segment.nsects);
            for (std::size_t j = 0; j < segment.nsects; ++j) {
                read_raw(fs, section);
                // `segname` goes right after the `sectname`.
                // Forcing `sectname` to end on '\0'
                section.segname[0] = '\0';
                ret.push_back(section.sectname);
                if (ret.back().empty()) {
                    ret.pop_back(); // Do not show empty names
                }
            }
        }
    };

    struct symbol_names_gather {
        std::vector<std::string>&       ret;
        std::size_t                     section_index;

        void operator()(std::ifstream& fs) const {
            symbol_header_t symbh;
            read_raw(fs, symbh);
            ret.reserve(ret.size() + symbh.nsyms);

            nlist_t symbol;
            std::string symbol_name;
            for (std::size_t j = 0; j < symbh.nsyms; ++j) {
                fs.seekg(symbh.symoff + j * sizeof(nlist_t));
                read_raw(fs, symbol);
                if (!symbol.n_strx) {
                    continue; // Symbol has no name
                }

                if ((symbol.n_type & 0x0e) != 0xe || !symbol.n_sect) {
                    continue; // Symbol has no section
                }

                if (section_index && section_index != symbol.n_sect) {
                    continue; // Not in the required section
                }

                fs.seekg(symbh.stroff + symbol.n_strx);
                std::getline(fs, symbol_name, '\0');
                if (symbol_name.empty()) {
                    continue;
                }

                if (symbol_name[0] == '_') {
                    // Linker adds additional '_' symbol. Could not find official docs for that case.
                    ret.push_back(symbol_name.c_str() + 1);
                } else {
                    ret.push_back(symbol_name);
                }
            }
        }
    };

public:
    static std::vector<std::string> sections(std::ifstream& fs) {
        std::vector<std::string> ret;
        section_names_gather f = { ret };
        command_finder(fs, SEGMENT_CMD_NUMBER, f);
        return ret;
    }

private:
    static header_t header(std::ifstream& fs) {
        header_t h;

        fs.seekg(0);
        read_raw(fs, h);

        return h;
    }

public:
    static std::vector<std::string> symbols(std::ifstream& fs) {
        std::vector<std::string> ret;
        symbol_names_gather f = { ret, 0 };
        command_finder(fs, load_command_types::LC_SYMTAB_, f);
        return ret;
    }

    static std::vector<std::string> symbols(std::ifstream& fs, const char* section_name) {
        // Not very optimal solution
        std::vector<std::string> ret = sections(fs);
        std::vector<std::string>::iterator it = std::find(ret.begin(), ret.end(), section_name);
        if (it == ret.end()) {
            // No section with such name
            ret.clear();
            return ret;
        }

        // section indexes start from 1
        symbol_names_gather f = { ret, static_cast<std::size_t>(1 + (it - ret.begin())) };
        ret.clear();
        command_finder(fs, load_command_types::LC_SYMTAB_, f);
        return ret;
    }
};

typedef macho_info<boost::uint32_t> macho_info32;
typedef macho_info<boost::uint64_t> macho_info64;

}}} // namespace boost::dll::detail

#endif // BOOST_DLL_DETAIL_MACHO_INFO_HPP

/* macho_info.hpp
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
*/