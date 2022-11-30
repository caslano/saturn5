// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_POSIX_ELF_INFO_HPP
#define BOOST_DLL_DETAIL_POSIX_ELF_INFO_HPP

#include <boost/dll/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <cstring>
#include <fstream>
#include <limits>
#include <vector>

#include <boost/cstdint.hpp>
#include <boost/throw_exception.hpp>

namespace boost { namespace dll { namespace detail {

template <class AddressOffsetT>
struct Elf_Ehdr_template {
  unsigned char     e_ident[16];    /* Magic number and other info */
  boost::uint16_t   e_type;         /* Object file type */
  boost::uint16_t   e_machine;      /* Architecture */
  boost::uint32_t   e_version;      /* Object file version */
  AddressOffsetT    e_entry;        /* Entry point virtual address */
  AddressOffsetT    e_phoff;        /* Program header table file offset */
  AddressOffsetT    e_shoff;        /* Section header table file offset */
  boost::uint32_t   e_flags;        /* Processor-specific flags */
  boost::uint16_t   e_ehsize;       /* ELF header size in bytes */
  boost::uint16_t   e_phentsize;    /* Program header table entry size */
  boost::uint16_t   e_phnum;        /* Program header table entry count */
  boost::uint16_t   e_shentsize;    /* Section header table entry size */
  boost::uint16_t   e_shnum;        /* Section header table entry count */
  boost::uint16_t   e_shstrndx;     /* Section header string table index */
};

typedef Elf_Ehdr_template<boost::uint32_t> Elf32_Ehdr_;
typedef Elf_Ehdr_template<boost::uint64_t> Elf64_Ehdr_;

template <class AddressOffsetT>
struct Elf_Shdr_template {
  boost::uint32_t   sh_name;        /* Section name (string tbl index) */
  boost::uint32_t   sh_type;        /* Section type */
  AddressOffsetT    sh_flags;       /* Section flags */
  AddressOffsetT    sh_addr;        /* Section virtual addr at execution */
  AddressOffsetT    sh_offset;      /* Section file offset */
  AddressOffsetT    sh_size;        /* Section size in bytes */
  boost::uint32_t   sh_link;        /* Link to another section */
  boost::uint32_t   sh_info;        /* Additional section information */
  AddressOffsetT    sh_addralign;   /* Section alignment */
  AddressOffsetT    sh_entsize;     /* Entry size if section holds table */
};

typedef Elf_Shdr_template<boost::uint32_t> Elf32_Shdr_;
typedef Elf_Shdr_template<boost::uint64_t> Elf64_Shdr_;

template <class AddressOffsetT>
struct Elf_Sym_template;

template <>
struct Elf_Sym_template<boost::uint32_t> {
  typedef boost::uint32_t AddressOffsetT;

  boost::uint32_t   st_name;    /* Symbol name (string tbl index) */
  AddressOffsetT    st_value;   /* Symbol value */
  AddressOffsetT    st_size;    /* Symbol size */
  unsigned char     st_info;    /* Symbol type and binding */
  unsigned char     st_other;   /* Symbol visibility */
  boost::uint16_t   st_shndx;   /* Section index */
};

template <>
struct Elf_Sym_template<boost::uint64_t> {
  typedef boost::uint64_t AddressOffsetT;

  boost::uint32_t   st_name;    /* Symbol name (string tbl index) */
  unsigned char     st_info;    /* Symbol type and binding */
  unsigned char     st_other;   /* Symbol visibility */
  boost::uint16_t   st_shndx;   /* Section index */
  AddressOffsetT    st_value;   /* Symbol value */
  AddressOffsetT    st_size;    /* Symbol size */
};


typedef Elf_Sym_template<boost::uint32_t> Elf32_Sym_;
typedef Elf_Sym_template<boost::uint64_t> Elf64_Sym_;

template <class AddressOffsetT>
class elf_info {
    typedef boost::dll::detail::Elf_Ehdr_template<AddressOffsetT>  header_t;
    typedef boost::dll::detail::Elf_Shdr_template<AddressOffsetT>  section_t;
    typedef boost::dll::detail::Elf_Sym_template<AddressOffsetT>   symbol_t;

    BOOST_STATIC_CONSTANT(boost::uint32_t, SHT_SYMTAB_ = 2);
    BOOST_STATIC_CONSTANT(boost::uint32_t, SHT_STRTAB_ = 3);
    BOOST_STATIC_CONSTANT(boost::uint32_t, SHT_DYNSYM_ = 11);

    BOOST_STATIC_CONSTANT(unsigned char, STB_LOCAL_ = 0);   /* Local symbol */
    BOOST_STATIC_CONSTANT(unsigned char, STB_GLOBAL_ = 1);  /* Global symbol */
    BOOST_STATIC_CONSTANT(unsigned char, STB_WEAK_ = 2);    /* Weak symbol */

    /* Symbol visibility specification encoded in the st_other field.  */
    BOOST_STATIC_CONSTANT(unsigned char, STV_DEFAULT_ = 0);      /* Default symbol visibility rules */
    BOOST_STATIC_CONSTANT(unsigned char, STV_INTERNAL_ = 1);     /* Processor specific hidden class */
    BOOST_STATIC_CONSTANT(unsigned char, STV_HIDDEN_ = 2);       /* Sym unavailable in other modules */
    BOOST_STATIC_CONSTANT(unsigned char, STV_PROTECTED_ = 3);    /* Not preemptible, not exported */

public:
    static bool parsing_supported(std::ifstream& fs) {
        const unsigned char magic_bytes[5] = { 
            0x7f, 'E', 'L', 'F', sizeof(boost::uint32_t) == sizeof(AddressOffsetT) ? 1 : 2
        };

        unsigned char ch;
        fs.seekg(0);
        for (std::size_t i = 0; i < sizeof(magic_bytes); ++i) {
            fs >> ch;
            if (ch != magic_bytes[i]) {
                return false;
            }
        }

        return true;
    }

    static std::vector<std::string> sections(std::ifstream& fs) {
        std::vector<std::string> ret;
        std::vector<char> names;
        sections_names_raw(fs, names);

        const char* name_begin = &names[0];
        const char* const name_end = name_begin + names.size();
        ret.reserve(header(fs).e_shnum);
        do {
            if (*name_begin) {
                ret.push_back(name_begin);
                name_begin += ret.back().size() + 1;
            } else {
                ++name_begin;
            }
        } while (name_begin != name_end);

        return ret;
    }

private:
    template <class Integer>
    static void checked_seekg(std::ifstream& fs, Integer pos) {
        /* TODO: use cmp_less, cmp_greater
        if ((std::numeric_limits<std::streamoff>::max)() < pos) {
            boost::throw_exception(std::runtime_error("Integral overflow while getting info from ELF file"));
        }
        if ((std::numeric_limits<std::streamoff>::min)() > pos){
            boost::throw_exception(std::runtime_error("Integral underflow while getting info from ELF file"));
        }
        */
        fs.seekg(static_cast<std::streamoff>(pos));
    }

    template <class T>
    static void read_raw(std::ifstream& fs, T& value, std::size_t size = sizeof(T)) {
        fs.read(reinterpret_cast<char*>(&value), size);
    }

    static header_t header(std::ifstream& fs) {
        header_t elf;

        fs.seekg(0);
        read_raw(fs, elf);

        return elf;
    }

    static void sections_names_raw(std::ifstream& fs, std::vector<char>& sections) {
        const header_t elf = header(fs);

        section_t section_names_section;
        checked_seekg(fs, elf.e_shoff + elf.e_shstrndx * sizeof(section_t));
        read_raw(fs, section_names_section);

        sections.resize(static_cast<std::size_t>(section_names_section.sh_size) + 1, '\0');
        checked_seekg(fs, section_names_section.sh_offset);
        read_raw(fs, sections[0], static_cast<std::size_t>(section_names_section.sh_size));
    }

    static void symbols_text(std::ifstream& fs, std::vector<symbol_t>& symbols, std::vector<char>& text) {
        std::vector<char> names;
        sections_names_raw(fs, names);
        symbols_text(fs, symbols, text, names);
    }

    static void symbols_text(std::ifstream& fs, std::vector<symbol_t>& symbols, std::vector<char>& text, const std::vector<char>& names) {
        const header_t elf = header(fs);
        checked_seekg(fs, elf.e_shoff);

        // ".dynsym" section may not have info on symbols that could be used while self loading an executable,
        // so we prefer ".symtab" section.
        AddressOffsetT symtab_size = 0;
        AddressOffsetT symtab_offset = 0;
        AddressOffsetT strtab_size = 0;
        AddressOffsetT strtab_offset = 0;

        AddressOffsetT dynsym_size = 0;
        AddressOffsetT dynsym_offset = 0;
        AddressOffsetT dynstr_size = 0;
        AddressOffsetT dynstr_offset = 0;

        for (std::size_t i = 0; i < elf.e_shnum; ++i) {
            section_t section;
            read_raw(fs, section);
            if (section.sh_name >= names.size()) {
                continue;
            }
            const char* name = &names[section.sh_name];

            if (section.sh_type == SHT_SYMTAB_ && !std::strcmp(name, ".symtab")) {
                symtab_size = section.sh_size;
                symtab_offset = section.sh_offset;
            } else if (section.sh_type == SHT_STRTAB_) {
                if (!std::strcmp(name, ".dynstr")) {
                    dynstr_size = section.sh_size;
                    dynstr_offset = section.sh_offset;
                } else if (!std::strcmp(name, ".strtab")) {
                    strtab_size = section.sh_size;
                    strtab_offset = section.sh_offset;
                }
            } else if (section.sh_type == SHT_DYNSYM_ && !std::strcmp(name, ".dynsym")) {
                dynsym_size = section.sh_size;
                dynsym_offset = section.sh_offset;
            }
        }

        if (!symtab_size || !strtab_size) {
            // ".symtab" stripped from the binary and we have to fallback to ".dynsym"
            symtab_size = dynsym_size;
            symtab_offset = dynsym_offset;
            strtab_size = dynstr_size;
            strtab_offset = dynstr_offset;
        }

        if (!symtab_size || !strtab_size) {
            return;
        }

        text.resize(static_cast<std::size_t>(strtab_size) + 1, '\0');
        checked_seekg(fs, strtab_offset);
        read_raw(fs, text[0], static_cast<std::size_t>(strtab_size));

        symbols.resize(static_cast<std::size_t>(symtab_size / sizeof(symbol_t)));
        checked_seekg(fs, symtab_offset);
        read_raw(fs, symbols[0], static_cast<std::size_t>(symtab_size - (symtab_size % sizeof(symbol_t))) );
    }

    static bool is_visible(const symbol_t& sym) BOOST_NOEXCEPT {
        const unsigned char visibility = (sym.st_other & 0x03);
        // `(sym.st_info >> 4) != STB_LOCAL_ && !!sym.st_size` check also workarounds the
        // GCC's issue https://sourceware.org/bugzilla/show_bug.cgi?id=13621
        return (visibility == STV_DEFAULT_ || visibility == STV_PROTECTED_)
                && (sym.st_info >> 4) != STB_LOCAL_ && !!sym.st_size;
    }

public:
    static std::vector<std::string> symbols(std::ifstream& fs) {
        std::vector<std::string> ret;

        std::vector<symbol_t> symbols;
        std::vector<char>   text;
        symbols_text(fs, symbols, text);

        ret.reserve(symbols.size());
        for (std::size_t i = 0; i < symbols.size(); ++i) {
            if (is_visible(symbols[i]) && symbols[i].st_name < text.size()) {
                ret.push_back(&text[symbols[i].st_name]);
                if (ret.back().empty()) {
                    ret.pop_back(); // Do not show empty names
                }
            }
        }

        return ret;
    }

    static std::vector<std::string> symbols(std::ifstream& fs, const char* section_name) {
        std::vector<std::string> ret;
        
        std::size_t index = 0;
        std::size_t ptrs_in_section_count = 0;

        std::vector<char> names;
        sections_names_raw(fs, names);

        const header_t elf = header(fs);

        for (; index < elf.e_shnum; ++index) {
            section_t section;
            checked_seekg(fs, elf.e_shoff + index * sizeof(section_t));
            read_raw(fs, section);

            if (!std::strcmp(&names.at(section.sh_name), section_name)) {
                if (!section.sh_entsize) {
                    section.sh_entsize = 1;
                }
                ptrs_in_section_count = static_cast<std::size_t>(section.sh_size / section.sh_entsize);
                break;
            }
        }

        std::vector<symbol_t> symbols;
        std::vector<char> text;
        symbols_text(fs, symbols, text, names);
    
        if (ptrs_in_section_count < symbols.size()) {
            ret.reserve(ptrs_in_section_count);
        } else {
            ret.reserve(symbols.size());
        }

        for (std::size_t i = 0; i < symbols.size(); ++i) {
            if (symbols[i].st_shndx == index && is_visible(symbols[i]) && symbols[i].st_name < text.size()) {
                ret.push_back(&text[symbols[i].st_name]);
                if (ret.back().empty()) {
                    ret.pop_back(); // Do not show empty names
                }
            }
        }

        return ret;
    }
};

typedef elf_info<boost::uint32_t> elf_info32;
typedef elf_info<boost::uint64_t> elf_info64;

}}} // namespace boost::dll::detail

#endif // BOOST_DLL_DETAIL_POSIX_ELF_INFO_HPP

/* elf_info.hpp
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
*/