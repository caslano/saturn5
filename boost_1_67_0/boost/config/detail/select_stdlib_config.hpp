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
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
*/