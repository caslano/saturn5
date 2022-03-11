// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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