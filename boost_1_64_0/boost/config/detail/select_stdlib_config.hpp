//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

// locate which std lib we are using and define BOOST_STDLIB_CONFIG as needed:

// First, check if __has_include is available and <version> include can be located,
// otherwise include <cstddef> to determine if some version of STLport is in use as the std lib
// (do not rely on this header being included since users can short-circuit this header 
//  if they know whose std lib they are using.)
#if defined(__cplusplus) && defined(__has_include)
#  if __has_include(<version>)
// It should be safe to include `<version>` when it is present without checking
// the actual C++ language version as it consists solely of macro definitions.
// [version.syn] p1: The header <version> supplies implementation-dependent
// information about the C++ standard library (e.g., version number and release date).
#    include <version>
#  else
#    include <cstddef>
#  endif
#elif defined(__cplusplus)
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
// STLPort library; this _must_ come first, otherwise since
// STLport typically sits on top of some other library, we
// can end up detecting that first rather than STLport:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/stlport.hpp"

#else

// If our std lib was not some version of STLport, and has not otherwise
// been detected, then include <utility> as it is about 
// the smallest of the std lib headers that includes real C++ stuff.
// Some std libs do not include their C++-related macros in <cstddef> 
// so this additional include makes sure we get those definitions.
// Note: do not rely on this header being included since users can short-circuit this 
// #include if they know whose std lib they are using.
#if !defined(__LIBCOMO__) && !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)\
   && !defined(_LIBCPP_VERSION) && !defined(__GLIBCPP__) && !defined(__GLIBCXX__)\
   && !defined(__STL_CONFIG_H) && !defined(__MSL_CPP__) && !defined(__IBMCPP__)\
   && !defined(MSIPL_COMPILE_H) && !defined(_YVALS) && !defined(_CPPLIB_VER)
#include <utility>
#endif

#if defined(__LIBCOMO__)
// Comeau STL:
#define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcomo.hpp"

#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/roguewave.hpp"

#elif defined(_LIBCPP_VERSION)
// libc++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libstdcpp3.hpp"

#elif defined(__STL_CONFIG_H)
// generic SGI STL
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/sgi.hpp"

#elif defined(__MSL_CPP__)
// MSL standard lib:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/msl.hpp"

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
// IBM z/OS XL C/C++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/xlcpp_zos.hpp"

#elif defined(__IBMCPP__)
// take the default VACPP std lib
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/vacpp.hpp"

#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/modena.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (this has to appear after any possible replacement libraries):
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/dinkumware.hpp"

#elif defined (BOOST_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the library:
#  error "Unknown standard library - please configure and report the results to boost.org"

#endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "boost/config/stdlib/stlport.hpp"
#  include "boost/config/stdlib/libcomo.hpp"
#  include "boost/config/stdlib/roguewave.hpp"
#  include "boost/config/stdlib/libcpp.hpp"
#  include "boost/config/stdlib/libstdcpp3.hpp"
#  include "boost/config/stdlib/sgi.hpp"
#  include "boost/config/stdlib/msl.hpp"
#  include "boost/config/stdlib/xlcpp_zos.hpp"
#  include "boost/config/stdlib/vacpp.hpp"
#  include "boost/config/stdlib/modena.hpp"
#  include "boost/config/stdlib/dinkumware.hpp"
#endif


/* select_stdlib_config.hpp
ud93gkGXYYjIXEP6qsV8gO5iJNaG+s87X6lNvB0ZrKGrhE5nQt8qgikO2PA3kZO/dAvz51jzYBrj0yU946qcX3+iGHvVFoJxfRDUkcvrWs6hh5Ad9drDCngGvOAv2L1jRKomsUMclcAaNam/hd4tP3+M98HwUA1GyAm//jta2wbe+6QIsKb5zqti6cvUz4ccidfl767TXy9M9eNyT9lG/P4p5xYMRj2uCKme1eREUsM39ZVfJV/kWXTe7h711JL9Tv9GJaYrbpAEsyB7j0Qt3d0SW/TKwLgw03lSgA5fhXD08lYiuKZhaldymrNfCsTQYStfeL6QVu9N4f09Ks4CN7An6e66sDuFVCYodAdRWkogKD8vaDczi4hrPpalHf417TW3G/GnDzOPRh+mV187s1GfQCkdqAA+TCp/4Al+TEF/4ahBsD5AOcUQMiyXYm4Bs1p0aRJ5Ts7KXRRnACveavh6QYE4KizPRAGJe+76lRQ+G7g6bUZyF71rVBlxrgDZ3XpxR071r33ELuGUxfwkIjxUtnWeJ4ei81Zgg71J9cK1iMY59UDaUMt5Cg==
*/