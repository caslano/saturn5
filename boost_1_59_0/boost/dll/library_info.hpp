// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_LIBRARY_INFO_HPP
#define BOOST_DLL_LIBRARY_INFO_HPP

#include <boost/dll/config.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/predef/os.h>
#include <boost/predef/architecture.h>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <fstream>

#include <boost/dll/detail/pe_info.hpp>
#include <boost/dll/detail/elf_info.hpp>
#include <boost/dll/detail/macho_info.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

/// \file boost/dll/library_info.hpp
/// \brief Contains only the boost::dll::library_info class that is capable of
/// extracting different information from binaries.

namespace boost { namespace dll {

/*!
* \brief Class that is capable of extracting different information from a library or binary file.
* Currently understands ELF, MACH-O and PE formats on all the platforms.
*/
class library_info: private boost::noncopyable {
private:
    std::ifstream f_;

    enum {
        fmt_elf_info32,
        fmt_elf_info64,
        fmt_pe_info32,
        fmt_pe_info64,
        fmt_macho_info32,
        fmt_macho_info64
    } fmt_;

    /// @cond
    inline static void throw_if_in_32bit_impl(boost::true_type /* is_32bit_platform */) {
        boost::throw_exception(std::runtime_error("Not native format: 64bit binary"));
    }

    inline static void throw_if_in_32bit_impl(boost::false_type /* is_32bit_platform */) BOOST_NOEXCEPT {}


    inline static void throw_if_in_32bit() {
        throw_if_in_32bit_impl( boost::integral_constant<bool, (sizeof(void*) == 4)>() );
    }

    static void throw_if_in_windows() {
#if BOOST_OS_WINDOWS
        boost::throw_exception(std::runtime_error("Not native format: not a PE binary"));
#endif
    }

    static void throw_if_in_linux() {
#if !BOOST_OS_WINDOWS && !BOOST_OS_MACOS && !BOOST_OS_IOS
        boost::throw_exception(std::runtime_error("Not native format: not an ELF binary"));
#endif
    }

    static void throw_if_in_macos() {
#if BOOST_OS_MACOS || BOOST_OS_IOS
        boost::throw_exception(std::runtime_error("Not native format: not an Mach-O binary"));
#endif
    }

    void init(bool throw_if_not_native) {
        if (boost::dll::detail::elf_info32::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_windows(); throw_if_in_macos(); }

            fmt_ = fmt_elf_info32;
        } else if (boost::dll::detail::elf_info64::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_windows(); throw_if_in_macos(); throw_if_in_32bit(); }

            fmt_ = fmt_elf_info64;
        } else if (boost::dll::detail::pe_info32::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_linux(); throw_if_in_macos(); }

            fmt_ = fmt_pe_info32;
        } else if (boost::dll::detail::pe_info64::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_linux(); throw_if_in_macos(); throw_if_in_32bit(); }

            fmt_ = fmt_pe_info64;
        } else if (boost::dll::detail::macho_info32::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_linux(); throw_if_in_windows(); }

            fmt_ = fmt_macho_info32;
        } else if (boost::dll::detail::macho_info64::parsing_supported(f_)) {
            if (throw_if_not_native) { throw_if_in_linux(); throw_if_in_windows(); throw_if_in_32bit(); }

            fmt_ = fmt_macho_info64;
        } else {
            boost::throw_exception(std::runtime_error("Unsupported binary format"));
        }
    }
    /// @endcond

public:
    /*!
    * Opens file with specified path and prepares for information extraction.
    * \param library_path Path to the binary file from which the info must be extracted.
    * \param throw_if_not_native_format Throw an exception if this file format is not
    * supported by OS.
    */
    explicit library_info(const boost::dll::fs::path& library_path, bool throw_if_not_native_format = true)
        : f_(
        #ifdef BOOST_DLL_USE_STD_FS
            library_path,
        //  Copied from boost/filesystem/fstream.hpp
        #elif defined(BOOST_WINDOWS_API)  && (!defined(_CPPLIB_VER) || _CPPLIB_VER < 405 || defined(_STLPORT_VERSION))
            // !Dinkumware || early Dinkumware || STLPort masquerading as Dinkumware
            library_path.string().c_str(),  // use narrow, since wide not available
        #else  // use the native c_str, which will be narrow on POSIX, wide on Windows
            library_path.c_str(),
        #endif
            std::ios_base::in | std::ios_base::binary
        )
    {
        f_.exceptions(
            std::ios_base::failbit
            | std::ifstream::badbit
            | std::ifstream::eofbit
        );

        init(throw_if_not_native_format);
    }

    /*!
    * \return List of sections that exist in binary file.
    */
    std::vector<std::string> sections() {
        switch (fmt_) {
        case fmt_elf_info32:   return boost::dll::detail::elf_info32::sections(f_);
        case fmt_elf_info64:   return boost::dll::detail::elf_info64::sections(f_);
        case fmt_pe_info32:    return boost::dll::detail::pe_info32::sections(f_);
        case fmt_pe_info64:    return boost::dll::detail::pe_info64::sections(f_);
        case fmt_macho_info32: return boost::dll::detail::macho_info32::sections(f_);
        case fmt_macho_info64: return boost::dll::detail::macho_info64::sections(f_);
        };
        BOOST_ASSERT(false);
        BOOST_UNREACHABLE_RETURN(std::vector<std::string>())
    }

    /*!
    * \return List of all the exportable symbols from all the sections that exist in binary file.
    */
    std::vector<std::string> symbols() {
        switch (fmt_) {
        case fmt_elf_info32:   return boost::dll::detail::elf_info32::symbols(f_);
        case fmt_elf_info64:   return boost::dll::detail::elf_info64::symbols(f_);
        case fmt_pe_info32:    return boost::dll::detail::pe_info32::symbols(f_);
        case fmt_pe_info64:    return boost::dll::detail::pe_info64::symbols(f_);
        case fmt_macho_info32: return boost::dll::detail::macho_info32::symbols(f_);
        case fmt_macho_info64: return boost::dll::detail::macho_info64::symbols(f_);
        };
        BOOST_ASSERT(false);
        BOOST_UNREACHABLE_RETURN(std::vector<std::string>())
    }

    /*!
    * \param section_name Name of the section from which symbol names must be returned.
    * \return List of symbols from the specified section.
    */
    std::vector<std::string> symbols(const char* section_name) {
        switch (fmt_) {
        case fmt_elf_info32:   return boost::dll::detail::elf_info32::symbols(f_, section_name);
        case fmt_elf_info64:   return boost::dll::detail::elf_info64::symbols(f_, section_name);
        case fmt_pe_info32:    return boost::dll::detail::pe_info32::symbols(f_, section_name);
        case fmt_pe_info64:    return boost::dll::detail::pe_info64::symbols(f_, section_name);
        case fmt_macho_info32: return boost::dll::detail::macho_info32::symbols(f_, section_name);
        case fmt_macho_info64: return boost::dll::detail::macho_info64::symbols(f_, section_name);
        };
        BOOST_ASSERT(false);
        BOOST_UNREACHABLE_RETURN(std::vector<std::string>())
    }


    //! \overload std::vector<std::string> symbols(const char* section_name)
    std::vector<std::string> symbols(const std::string& section_name) {
        switch (fmt_) {
        case fmt_elf_info32:   return boost::dll::detail::elf_info32::symbols(f_, section_name.c_str());
        case fmt_elf_info64:   return boost::dll::detail::elf_info64::symbols(f_, section_name.c_str());
        case fmt_pe_info32:    return boost::dll::detail::pe_info32::symbols(f_, section_name.c_str());
        case fmt_pe_info64:    return boost::dll::detail::pe_info64::symbols(f_, section_name.c_str());
        case fmt_macho_info32: return boost::dll::detail::macho_info32::symbols(f_, section_name.c_str());
        case fmt_macho_info64: return boost::dll::detail::macho_info64::symbols(f_, section_name.c_str());
        };
        BOOST_ASSERT(false);
        BOOST_UNREACHABLE_RETURN(std::vector<std::string>())
    }
};

}} // namespace boost::dll
#endif // BOOST_DLL_LIBRARY_INFO_HPP

/* library_info.hpp
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
*/