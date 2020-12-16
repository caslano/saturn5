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
NvarWec33n61pHlT7FfDE8l+Fds/T1Bc0emjufKv7QwAu2alHodeXCm2RzRicvTPfpjRzo2EZVfjTIJU5y9rJrKx7/+xWLFRy5yM7F3ftijlo25WyC6B4CFT+aYo6+KRE/nyTpYsvDsW7mxM4XvgXr7Bn+17rVtPNl1GldckE3HhT4asf3Dt833S0S6BU/NUL6DK+ag3FKfl0AQGzKAuMO9o6gKU7bEsse+RKfr7mGOxX8A+ISf3hx4/RPAtZZmHSz7HKeRBV1lCOy3qBIiir99bi8bx7TOe2fJrae+6/KI+N8/oc51MjCocaGaUWxs211mZ1WeAzqxRJwlmZRCzOtdl1mgvJhibWCUONnfUGNPOoRiz5ZB9w5gcO1dZj2TxUAyETjxcd4UCpkJYYYlTQ0JC5N6FRBii4Y/mOu3xjZAQDa8fhM25dVYdoVUUuq8j04bgP8+RbYRnIMwbw+NhY3iaWCdsdBp7w8u/pnVCfluxTshqq9YJhK4XXeJDMUB191Ild7an9rS4AxhzRK5cwuZIcyfwpZTa9Pz+lCVc6lTEFxP6Tuz0le/jy+vHzUFPNIoI94OcetoAK8oZpFAqxK4OoE16uZxkKieVLCgqtBoSacg3w/80G/Pi3yPR2JWZdCZVhtJeAmomOEs3ExcUTONu8fphlIP45NGIvbA90HG1njWPevjy9tSYdKeb9NYhLha/J2k4DkEc9TB/4xmm+aoQdNmL2qQ6Vh0Krurh3xT49zzA38G/jvDdArqBI5F/zsT99HPxV1y8/Ej4f9se1ff/MulScfuMuupTF02r69IO4g2d7/t2TVGNtKMtNT1Zf/NTKT2ou+SIAlaHwsmogFHYne2M74Vp26KNvblrp3/172mjf7Ud0Hj9K9PRFP2r/I8Ux6v1z38nEEHyFArpCc1xEguXutTcc1yaaQK8Jig1NHkC7Rg5ER4q9xlaUbJ7/GwsOVagwvVoaaajuA3FTwFH+zK+JcRrc92xv0SgFag8/B+edHYE6SCJROOHY8JzlPT13H035mVvYpgLN67gbIfIsZ7OMG0BzVKdFHKMPYHKmpkE6wY3F92ilSA6WSBbFVCud9LD16q5g7DHZcti6J5aOqrwZCsGQZ8PE6BE4EcElrrAvkU7ClrliOdoWBfZa2zfSytpgSzZGewbD3bfmw8V+arhG3jjpnOwGcL4WYBfOG2xGw9ZeHN5Azw3KUs9mh/67Qqvg9MgelkvJ/IOVWFZrQJOlG/sJ+YT7eOzkIq/dSYeTgAPmhaN77KdEdT4MkStPPd4YeNOi+0LsfTlbi50m2P2Vrf5T/xsx9dFPdT4Srfol3fy8Ho71TS83GfI4WU/rLKO5WHVH1AQR+/uBJ/a0CA3ivYjSD6O4RtDXYW7CKc095ENNP++WyCs+z79aQzbHhGj21gHTZ0x4ZlUYR0LpjRp+KoPVAFeo7o51zZGdVwlCNIMQUBfE2rpjnluhQuEQrTN+c93cESS1VDEnz5qabM0QSw+aai9ZhpqshiHWdxksLjJ7msoPrh7MtZ2lCmx6CyRo+eMuqOn4w4xei5jEarSDnfXSbv9R5G2h0wrSk4Iv/e7acCthUT0NSuBvID/Nw64xq4f3ulus3649BAedAhOyzbmtNK6B0tv8kxe7jIWD+M/pcXDuHSxeBiczosH7kqmnsyAVwfStB4HlPF3urkn8ncmpoml6maFvj5ZrjNONGSBTz+dekTsvE+pvL86NTlS3N5OhogFSKR5UJ1JwKWI0c/rKWSAKmSGXkhJG2qBc9ysDow0EdGNNhjokNBO/QhokprjIq7I24p5WNX62wHnajAlxiZ0QW9J6Dbz0mjG95Fo7FzXylyUtp8=
*/