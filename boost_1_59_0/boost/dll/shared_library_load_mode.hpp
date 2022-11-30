// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SHARED_LIBRARY_MODE_HPP
#define BOOST_DLL_SHARED_LIBRARY_MODE_HPP

#include <boost/dll/config.hpp>
#include <boost/predef/os.h>
#include <boost/predef/library/c.h>

#if BOOST_OS_WINDOWS
#   include <boost/winapi/dll.hpp>
#else
#   include <dlfcn.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

/// \file boost/dll/shared_library_load_mode.hpp
/// \brief Contains only the boost::dll::load_mode::type enum and operators related to it.

namespace boost { namespace dll { namespace load_mode {

/*! Library load modes.
*
* Each of system family provides own modes. Flags not supported by a particular platform will be silently ignored.
*
* For a detailed description of platform specific options see:
* <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ms684179(v=vs.85).aspx">Windows specific options</a>,
* <a href="http://pubs.opengroup.org/onlinepubs/000095399/functions/dlopen.html">POSIX specific options</a>.
*
*/

enum type {
#ifdef BOOST_DLL_DOXYGEN
    /*!
    * Default open mode. See the \b Default: comments below to find out the flags that are enabled by default.
    */
    default_mode,

    /*!
    * \b Platforms: Windows
    *
    * \b Default: disabled
    *
    * If this value is used, and the executable module is a DLL, the system does
    * not call DllMain for process and thread initialization and termination.
    * Also, the system does not load additional executable modules that are
    * referenced by the specified module.
    *
    * Note Do not use this value; it is provided only for backward compatibility.
    * If you are planning to access only data or resources in the DLL, use
    * LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE or LOAD_LIBRARY_AS_IMAGE_RESOURCE
    * or both.
    */
    dont_resolve_dll_references,

    /*!
    * \b Platforms: Windows
    *
    * \b Default: disabled
    *
    * If this value is used, the system does not check AppLocker rules or
    * apply Software Restriction Policies for the DLL.
    */
    load_ignore_code_authz_level,

    /*!
    * \b Platforms: Windows
    *
    * \b Default: disabled
    *
    * If this value is used and lpFileName specifies an absolute path,
    * the system uses the alternate file search strategy.
    *
    * This value cannot be combined with any LOAD_LIBRARY_SEARCH flag.
    */
    load_with_altered_search_path,

    /*!
    * \b Platforms: POSIX
    *
    * \b Default: enabled
    *
    * Relocations shall be performed at an implementation-defined time, ranging
    * from the time of the dlopen() call until the first reference to a given
    * symbol occurs.
    *
    * Specifying RTLD_LAZY should improve performance on implementations
    * supporting dynamic symbol binding as a process may not reference all of
    * the functions in any given object. And, for systems supporting dynamic
    * symbol resolution for normal process execution, this behavior mimics
    * the normal handling of process execution.
    */
    rtld_lazy,

    /*!
    * \b Platforms: POSIX
    *
    * \b Default: disabled
    *
    * All necessary relocations shall be performed when the object is first
    * loaded. This may waste some processing if relocations are performed for
    * functions that are never referenced. This behavior may be useful for
    * plugins that need to know as soon as an object is loaded that all
    * symbols referenced during execution are available.
    */
    rtld_now,

    /*!
    * \b Platforms: POSIX
    *
    * \b Default: disabled
    *
    * The object's symbols shall be made available for the relocation
    * processing of any other object. In addition, symbol lookup using
    * dlopen(0, mode) and an associated dlsym() allows objects loaded
    * with this mode to be searched.
    */
    rtld_global,

    /*!
    * \b Platforms: POSIX
    *
    * \b Default: enabled
    *
    * The object's symbols shall not be made available for the relocation
    * processing of any other object.
    *
    * This is a default Windows behavior that can not be changed.
    */
    rtld_local,

    /*!
    * \b Platforms: POSIX (requires glibc >= 2.3.4)
    *
    * \b Default: disabled
    *
    * The object will use its own symbols in preference to global symbols
    * with the same name contained in libraries that have already been loaded.
    * This flag is not specified in POSIX.1-2001.
    */
    rtld_deepbind,

    /*!
    * \b Platforms: Windows, POSIX
    *
    * \b Default: disabled
    *
    * Append a platform specific extension and prefix to shared library filename before trying to load it.
    * If load attempt fails, try to load with exactly specified name.
    *
    * \b Example:
    * \code
    * // Opens `./my_plugins/plugin1.dll` on Windows, `./my_plugins/libplugin1.so` on Linux, `./my_plugins/libplugin1.dylib` on MacOS.
    * // If that fails, loads `./my_plugins/plugin1`
    * boost::dll::shared_library lib("./my_plugins/plugin1", load_mode::append_decorations);
    * \endcode
    */
    append_decorations,
    /*!
    * \b Platforms: Windows, POSIX
    *
    * \b Default: disabled
    *
    * Allow loading from system folders if path to library contains no parent path.
    */
    search_system_folders
#elif BOOST_OS_WINDOWS
    default_mode                          = 0,
    dont_resolve_dll_references           = boost::winapi::DONT_RESOLVE_DLL_REFERENCES_,
    load_ignore_code_authz_level          = boost::winapi::LOAD_IGNORE_CODE_AUTHZ_LEVEL_,
    load_with_altered_search_path         = boost::winapi::LOAD_WITH_ALTERED_SEARCH_PATH_,
    rtld_lazy                             = 0,
    rtld_now                              = 0,
    rtld_global                           = 0,
    rtld_local                            = 0,
    rtld_deepbind                         = 0,
    append_decorations                    = 0x00800000,
    search_system_folders                 = (append_decorations << 1)
#else
    default_mode                          = 0,
    dont_resolve_dll_references           = 0,
    load_ignore_code_authz_level          = 0,
    load_with_altered_search_path         = 0,
    rtld_lazy                             = RTLD_LAZY,
    rtld_now                              = RTLD_NOW,
    rtld_global                           = RTLD_GLOBAL,
    rtld_local                            = RTLD_LOCAL,

#if BOOST_LIB_C_GNU < BOOST_VERSION_NUMBER(2,3,4)
    rtld_deepbind                         = 0,
#else
    rtld_deepbind                         = RTLD_DEEPBIND,
#endif

    append_decorations                    = 0x00800000,
    search_system_folders                 = (append_decorations << 1)
#endif
};


/// Free operators for load_mode::type flag manipulation.
BOOST_CONSTEXPR inline type operator|(type left, type right) BOOST_NOEXCEPT {
    return static_cast<type>(
        static_cast<unsigned int>(left) | static_cast<unsigned int>(right)
    );
}
BOOST_CXX14_CONSTEXPR inline type& operator|=(type& left, type right) BOOST_NOEXCEPT {
    left = left | right;
    return left;
}

BOOST_CONSTEXPR inline type operator&(type left, type right) BOOST_NOEXCEPT {
    return static_cast<type>(
        static_cast<unsigned int>(left) & static_cast<unsigned int>(right)
    );
}
BOOST_CXX14_CONSTEXPR inline type& operator&=(type& left, type right) BOOST_NOEXCEPT {
    left = left & right;
    return left;
}

BOOST_CONSTEXPR inline type operator^(type left, type right) BOOST_NOEXCEPT {
    return static_cast<type>(
        static_cast<unsigned int>(left) ^ static_cast<unsigned int>(right)
    );
}
BOOST_CXX14_CONSTEXPR inline type& operator^=(type& left, type right) BOOST_NOEXCEPT {
    left = left ^ right;
    return left;
}

BOOST_CONSTEXPR inline type operator~(type left) BOOST_NOEXCEPT {
    return static_cast<type>(
        ~static_cast<unsigned int>(left)
    );
}

}}} // boost::dll::load_mode

#endif // BOOST_DLL_SHARED_LIBRARY_MODE_HPP

/* shared_library_load_mode.hpp
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
*/