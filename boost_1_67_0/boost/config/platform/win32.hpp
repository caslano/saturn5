//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Bill Kempf 2001. 
//  (C) Copyright Aleksey Gurtovoy 2003. 
//  (C) Copyright Rene Rivera 2005.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Win32 specific config options:

#define BOOST_PLATFORM "Win32"

//  Get the information about the MinGW runtime, i.e. __MINGW32_*VERSION.
#if defined(__MINGW32__)
#  include <_mingw.h>
#endif

#if defined(__GNUC__) && !defined(BOOST_NO_SWPRINTF)
#  define BOOST_NO_SWPRINTF
#endif

//  Default defines for BOOST_SYMBOL_EXPORT and BOOST_SYMBOL_IMPORT
//  If a compiler doesn't support __declspec(dllexport)/__declspec(dllimport),
//  its boost/config/compiler/ file must define BOOST_SYMBOL_EXPORT and
//  BOOST_SYMBOL_IMPORT
#ifndef BOOST_SYMBOL_EXPORT
#  define BOOST_HAS_DECLSPEC
#  define BOOST_SYMBOL_EXPORT __declspec(dllexport)
#  define BOOST_SYMBOL_IMPORT __declspec(dllimport)
#endif

#if defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
#  define BOOST_HAS_STDINT_H
#  ifndef __STDC_LIMIT_MACROS
#     define __STDC_LIMIT_MACROS
#  endif
#  define BOOST_HAS_DIRENT_H
#  define BOOST_HAS_UNISTD_H
#endif

#if defined(__MINGW32__) && (__GNUC__ >= 4)
// Mingw has these functions but there are persistent problems
// with calls to these crashing, so disable for now:
//#  define BOOST_HAS_EXPM1
//#  define BOOST_HAS_LOG1P
#  define BOOST_HAS_GETTIMEOFDAY
#endif
//
// Win32 will normally be using native Win32 threads,
// but there is a pthread library avaliable as an option,
// we used to disable this when BOOST_DISABLE_WIN32 was 
// defined but no longer - this should allow some
// files to be compiled in strict mode - while maintaining
// a consistent setting of BOOST_HAS_THREADS across
// all translation units (needed for shared_ptr etc).
//

#ifndef BOOST_HAS_PTHREADS
#  define BOOST_HAS_WINTHREADS
#endif

//
// WinCE configuration:
//
#if defined(_WIN32_WCE) || defined(UNDER_CE)
#  define BOOST_NO_ANSI_APIS
// Windows CE does not have a conforming signature for swprintf
#  define BOOST_NO_SWPRINTF
#else
#  define BOOST_HAS_GETSYSTEMTIMEASFILETIME
#  define BOOST_HAS_THREADEX
#  define BOOST_HAS_GETSYSTEMTIMEASFILETIME
#endif

//
// Windows Runtime
//
#if defined(WINAPI_FAMILY) && \
  (WINAPI_FAMILY == WINAPI_FAMILY_APP || WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#  define BOOST_NO_ANSI_APIS
#endif

#ifndef BOOST_DISABLE_WIN32
// WEK: Added
#define BOOST_HAS_FTIME
#define BOOST_WINDOWS 1

#endif

/* win32.hpp
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
*/