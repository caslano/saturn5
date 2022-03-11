// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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

#include <boost/cstdint.hpp>

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
            ret.push_back(name_begin);
            name_begin += ret.back().size() + 1;
        } while (name_begin != name_end);

        return ret;
    }

private:
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
        fs.seekg(elf.e_shoff + elf.e_shstrndx * sizeof(section_t));
        read_raw(fs, section_names_section);

        sections.resize(static_cast<std::size_t>(section_names_section.sh_size));
        fs.seekg(section_names_section.sh_offset);
        read_raw(fs, sections[0], static_cast<std::size_t>(section_names_section.sh_size));
    }

    static void symbols_text(std::ifstream& fs, std::vector<symbol_t>& symbols, std::vector<char>& text) {
        const header_t elf = header(fs);
        fs.seekg(elf.e_shoff);

        for (std::size_t i = 0; i < elf.e_shnum; ++i) {
            section_t section;
            read_raw(fs, section);

            if (section.sh_type == SHT_SYMTAB_) {
                symbols.resize(static_cast<std::size_t>(section.sh_size / sizeof(symbol_t)));

                const std::ifstream::pos_type pos = fs.tellg();
                fs.seekg(section.sh_offset);
                read_raw(fs, symbols[0], static_cast<std::size_t>(section.sh_size - (section.sh_size % sizeof(symbol_t))) );
                fs.seekg(pos);
            } else if (section.sh_type == SHT_STRTAB_) {
                text.resize(static_cast<std::size_t>(section.sh_size));

                const std::ifstream::pos_type pos = fs.tellg();
                fs.seekg(section.sh_offset);
                read_raw(fs, text[0], static_cast<std::size_t>(section.sh_size));
                fs.seekg(pos);
            }
        }
    }

    static bool is_visible(const symbol_t& sym) BOOST_NOEXCEPT {
        // `(sym.st_info >> 4) != STB_LOCAL_ && !!sym.st_size` check also workarounds the
        // GCC's issue https://sourceware.org/bugzilla/show_bug.cgi?id=13621
        return (sym.st_other & 0x03) == STV_DEFAULT_ && (sym.st_info >> 4) != STB_LOCAL_ && !!sym.st_size;
    }

public:
    static std::vector<std::string> symbols(std::ifstream& fs) {
        std::vector<std::string> ret;

        std::vector<symbol_t> symbols;
        std::vector<char>   text;
        symbols_text(fs, symbols, text);

        ret.reserve(symbols.size());
        for (std::size_t i = 0; i < symbols.size(); ++i) {
            if (is_visible(symbols[i])) {
                ret.push_back(&text[0] + symbols[i].st_name);
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
        {
            std::vector<char> names;
            sections_names_raw(fs, names);

            const header_t elf = header(fs);

            for (; index < elf.e_shnum; ++index) {
                section_t section;
                fs.seekg(elf.e_shoff + index * sizeof(section_t));
                read_raw(fs, section);
            
                if (!std::strcmp(&names[0] + section.sh_name, section_name)) {
                    if (!section.sh_entsize) {
                        section.sh_entsize = 1;
                    }
                    ptrs_in_section_count = static_cast<std::size_t>(section.sh_size / section.sh_entsize);
                    break;
                }
            }                        
        }

        std::vector<symbol_t> symbols;
        std::vector<char>   text;
        symbols_text(fs, symbols, text);
    
        if (ptrs_in_section_count < symbols.size()) {
            ret.reserve(ptrs_in_section_count);
        } else {
            ret.reserve(symbols.size());
        }

        for (std::size_t i = 0; i < symbols.size(); ++i) {
            if (symbols[i].st_shndx == index && is_visible(symbols[i])) {
                ret.push_back(&text[0] + symbols[i].st_name);
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