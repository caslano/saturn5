// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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