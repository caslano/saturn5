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
unzse8CGQPG2GEUxOM3Olz9OfGd9vrcxbOO2cCu20Ycj8ZtiZ6IageY+fSEXmOEb7efXU5TWU4jPgmMzu8w3upsyNmcSG+n/W3mGEranntsC9daE4BJ9151w3JFLvYaQWrsnh6vEVH6w38F2P+Scd+R137iNnolHHupEYjv+z9F1RzWxrHEVIWgwESEUKVHwAle6SAtNpT2VchEFpAeQIi1I6IEIkSL1KhaUEooGkRoJRWpCCFjoXWoCKoFQgrRQEl7e+2d3zpzdObNnZ37lm2/OrCWToAYP69vB8XpQjak5NZ2jkNrZKl7tFXKUzIoZYknoxkqSy5+10gH7b6GKa9Hn9wSaf4J/mRvrf0EzP/n8PLhJhUr+UfoGXXFlfvax3MW4l+alr62LuFBFC7o1k2JBkWALgR0X6v2jzMPEVknnSP7du21OI/HVxBUMWy2SfNv7bcNj1XaPsdHnEnGJB+JxWgkH4Ny157ZumlP8Ro0L9/akhRuKV7V9b/MVCmBq4zxdS2BMRrv699luqm675uoDd4nVi8z9ube7MyLMUmRWArqYLaZDT/FThcnstuVw5DH5hIh4qLQ6o/Xj+ED7vtSfk0t/A9C7erWx6Zislnj/M7ut1PG5q4x4S2rH3AInIUaKFZtjw/vFGLGv9wU6UU7kUYuB2x/yfOPhAp1nozygCYLmiI5Y1kCP9etlohSQaTZUbb/149X68f7q
*/