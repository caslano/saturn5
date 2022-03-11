// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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
                getline(fs, symbol_name, '\0');
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