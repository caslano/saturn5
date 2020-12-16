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
PZlV7e7KL82PtkqjWEbvyTbSAvN0UCtCsZiL93+U5luIxzSL69XweAVplsU6yMLirlbtNJDilurgIYs7UKX0FIpboYN2zG7XPf0XtXOlyF0Yzx3c4c2sYlYVs4da6DUArbawFCgDy35o5JHmR4tSLGTtFkCLVixk7QY/hVjI+swUasHf1hFmRhvK7EOLNs2ledHqMCu0dNwNilsl9uHC/vzfyJKUHxqvj34zCs2Vyv5eeyOLNDdaNsVC/obYi7Y6ImgHoBeUm3n1hDTTOjy3MvvhTN9SdP7coIM+oJgvcVARafaN4nsuYV3zl9JIM28S4yeMxg/NqmJ2tCwaxd4cOnaWzlmblf3RQRgATY0xGjoXoD3QKDb6wupv6Jj+Rew3hWVN/2KNNNgq7nEK63Zn4090DkllBzouzUHn5FRWvcebBtIsaFHMls5JX1WaFa0os0vNm+6S5kwVt7JdfDc6z6NFKxZyvnanirOXctH6xYMWqZi4byr6E60Js4uNaw2g/Dw66MxMu6b/DKoPrTWz4dmaK+fdX3WwgFnV7wrvkOZDa8usXMJ3e6hftulgFzPPpSenqT+36+AFs5lpxmWRZt+hgz3cMlRoSOO+U9y3EZZ3zoHm1C9oA5ntHJNnPLVll1gPCnPVy9OXxgGNj3u/zfvOUb+g1WGW3HtbR2mwWwcWZlPjD7+l+tCGahRrVMtzncZhrzhWhPHrkVXF7GEtEZxo84Udgnhos/nkE2nWfeJaLKxvfWNHaR60hxrFiu3TJEkzHdBBaVCsf7FhU6XZ0AoyW7ra0ZLagvYds5zPcyySZj4o5rywve+6b5VmQdOwthTY0P4SlXkIvztjphm1qTCVeVjcKxFmepKmWdC6gQdtmojzAsCUzePzSHMfwecLmO1fUNQQtKH47KRyTB+G7rCp0/i50uC4GAdhNA5oZrSqzBYWGVJQmgOtI7Ntp99eluZPZb8VfxYvzXZCB2OZ3Wy1n9oZQAvXFtPJcJYAFrTWwn6DzlBlc4X50txoWmZbWw3ZCyDevYEm/6biCCRA88WFJ1DcGR0cjQraUSgHiesergxaX3Bf1MEYEXcM6sIPmtOtpHkv4fepesVS1pSsQOuzv/B+iIg7DsMg4cuEgjRf7uBeRhe0E9i24hfWpwmaA8xP8TsiMbYnMQfnHFxACfM9w/kZrdiT5bGTpXn+xWdcMin2zYzThcjS6GFERsUiX49aR2UW0IfUN2p7tqvSnIX0MJTV1/OnfvRuUHtJPb0T9hSUgb73CuUK2hBwxenhtLDT0B029LuQiayUHtoxK1Z15hW5B4LSerqmnoEhsH7U1O3SLGjFIxR7tedmdQDx7r4yeliQLmhnIQ7fgfLPILrXVVcP0SLuHJSF7vWq0T1cb3097dXOwwCIONTDQO+laqQHV2TQLmAdncfPnEFrm2/19HdSPkiED3+sWkPHbUs91BRlXoQesGK45bmcg9bWerrG/Y51nN5Fv6cBbrQVwv6AJLh19PRXGedoo6d7a5dgJAQ+/K8dzetUVvJNjTzSAmglmLkm/3ZXmqVteHOgjWZ2Z+fjTdJM7fSwKoLVN8U3X5q9ox66gmLjk7unleZH0ysm9vZiP432VfTZZegFgWKbj0tzdNFDd2ZzJ6+bQsdRNz34tEG7AgmQPq77/aDF471DPX3ffxX6wa48VZtIs/bRg5nZ6JdVt0pzoLVltmbgAq00P1puZs8gezFppr56yMMse157K6ovleVY024P1YfWjNmHdl4/1YeWg1n+jd550qCf6Bdhe/peOUO599dDZWZb5vWJlGYbqIcEZhVS2meiHBIxd2bXLxXMTWU69DAcFDuV7806afbBeviGWXM=
*/