//  boost/chrono/config.hpp  -------------------------------------------------//

//  Copyright Beman Dawes 2003, 2006, 2008
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Copyright (c) Microsoft Corporation 2014

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CONFIG_HPP
#define BOOST_CHRONO_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/predef.h>

#if !defined BOOST_CHRONO_VERSION
#define BOOST_CHRONO_VERSION 1
#else
#if BOOST_CHRONO_VERSION!=1  && BOOST_CHRONO_VERSION!=2
#error "BOOST_CHRONO_VERSION must be 1 or 2"
#endif
#endif

#if defined(BOOST_CHRONO_SOURCE) && !defined(BOOST_USE_WINDOWS_H)
#define BOOST_USE_WINDOWS_H
#endif

#if ! defined BOOST_CHRONO_PROVIDES_DATE_IO_FOR_SYSTEM_CLOCK_TIME_POINT \
    && ! defined BOOST_CHRONO_DONT_PROVIDE_DATE_IO_FOR_SYSTEM_CLOCK_TIME_POINT

# define BOOST_CHRONO_PROVIDES_DATE_IO_FOR_SYSTEM_CLOCK_TIME_POINT

#endif

//  BOOST_CHRONO_POSIX_API, BOOST_CHRONO_MAC_API, or BOOST_CHRONO_WINDOWS_API
//  can be defined by the user to specify which API should be used

#if defined(BOOST_CHRONO_WINDOWS_API)
# warning Boost.Chrono will use the Windows API
#elif defined(BOOST_CHRONO_MAC_API)
# warning Boost.Chrono will use the Mac API
#elif defined(BOOST_CHRONO_POSIX_API)
# warning Boost.Chrono will use the POSIX API
#endif

# if defined( BOOST_CHRONO_WINDOWS_API ) && defined( BOOST_CHRONO_POSIX_API )
#   error both BOOST_CHRONO_WINDOWS_API and BOOST_CHRONO_POSIX_API are defined
# elif defined( BOOST_CHRONO_WINDOWS_API ) && defined( BOOST_CHRONO_MAC_API )
#   error both BOOST_CHRONO_WINDOWS_API and BOOST_CHRONO_MAC_API are defined
# elif defined( BOOST_CHRONO_MAC_API ) && defined( BOOST_CHRONO_POSIX_API )
#   error both BOOST_CHRONO_MAC_API and BOOST_CHRONO_POSIX_API are defined
# elif !defined( BOOST_CHRONO_WINDOWS_API ) && !defined( BOOST_CHRONO_MAC_API ) && !defined( BOOST_CHRONO_POSIX_API )
#   if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
#     define BOOST_CHRONO_WINDOWS_API
#   elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#     define BOOST_CHRONO_MAC_API
#   else
#     define BOOST_CHRONO_POSIX_API
#   endif
# endif

# if defined( BOOST_CHRONO_WINDOWS_API )
#   ifndef UNDER_CE
#     define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   endif
#   define BOOST_CHRONO_HAS_CLOCK_STEADY
#   if BOOST_PLAT_WINDOWS_DESKTOP
#     define BOOST_CHRONO_HAS_THREAD_CLOCK
#   endif
#   define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
# endif

# if defined( BOOST_CHRONO_MAC_API )
#   define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   define BOOST_CHRONO_HAS_CLOCK_STEADY
#   define BOOST_CHRONO_HAS_THREAD_CLOCK
#   define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
# endif

# if defined( BOOST_CHRONO_POSIX_API )
#   define BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   include <time.h>  //to check for CLOCK_REALTIME and CLOCK_MONOTONIC and _POSIX_THREAD_CPUTIME
#   if defined(CLOCK_MONOTONIC)
#      define BOOST_CHRONO_HAS_CLOCK_STEADY
#   endif
#   if defined(_POSIX_THREAD_CPUTIME) && !defined(BOOST_DISABLE_THREADS)
#     define BOOST_CHRONO_HAS_THREAD_CLOCK
#     define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
#   endif
#   if defined(CLOCK_THREAD_CPUTIME_ID) && !defined(BOOST_DISABLE_THREADS)
#     define BOOST_CHRONO_HAS_THREAD_CLOCK
#     define BOOST_CHRONO_THREAD_CLOCK_IS_STEADY true
#   endif
#   if defined(sun) || defined(__sun)
#     undef BOOST_CHRONO_HAS_THREAD_CLOCK
#     undef BOOST_CHRONO_THREAD_CLOCK_IS_STEADY
#   endif
#   if (defined(__HP_aCC) || defined(__GNUC__)) && defined(__hpux)
#     undef BOOST_CHRONO_HAS_THREAD_CLOCK
#     undef BOOST_CHRONO_THREAD_CLOCK_IS_STEADY
#   endif
#   if defined(__VXWORKS__)
#     undef BOOST_CHRONO_HAS_PROCESS_CLOCKS
#   endif
# endif

#if defined(BOOST_CHRONO_THREAD_DISABLED) && defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#undef BOOST_CHRONO_HAS_THREAD_CLOCK
#undef BOOST_CHRONO_THREAD_CLOCK_IS_STEADY
#endif

// unicode support  ------------------------------//

#if defined(BOOST_NO_CXX11_UNICODE_LITERALS) || defined(BOOST_NO_CXX11_CHAR16_T) || defined(BOOST_NO_CXX11_CHAR32_T)
//~ #define BOOST_CHRONO_HAS_UNICODE_SUPPORT
#else
#define BOOST_CHRONO_HAS_UNICODE_SUPPORT 1
#endif

#ifndef BOOST_CHRONO_LIB_CONSTEXPR
#if defined( BOOST_NO_CXX11_NUMERIC_LIMITS )
#define BOOST_CHRONO_LIB_CONSTEXPR
#elif defined(_LIBCPP_VERSION) &&  !defined(_LIBCPP_CONSTEXPR)
  #define BOOST_CHRONO_LIB_CONSTEXPR
#else
  #define BOOST_CHRONO_LIB_CONSTEXPR BOOST_CONSTEXPR
#endif
#endif

#if defined( BOOST_NO_CXX11_NUMERIC_LIMITS )
#  define BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW throw()
#else
#ifdef BOOST_NO_CXX11_NOEXCEPT
#  define BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW throw()
#else
#  define BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW noexcept
#endif
#endif

#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING \
 && defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
#error "BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING && BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING defined"
#endif

#if defined BOOST_CHRONO_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0 \
 && defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#error "BOOST_CHRONO_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0 && BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0 defined"
#endif

#if ! defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING \
 && ! defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
#define BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#endif

#if (BOOST_CHRONO_VERSION == 2)
#if ! defined BOOST_CHRONO_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0 \
 && ! defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#define BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#endif
#endif

#ifdef BOOST_CHRONO_HEADER_ONLY
#define BOOST_CHRONO_INLINE inline
#define BOOST_CHRONO_STATIC inline
#define BOOST_CHRONO_DECL

#else
#define BOOST_CHRONO_INLINE
#define BOOST_CHRONO_STATIC static

//  enable dynamic linking on Windows  ---------------------------------------//

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_CHRONO_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CHRONO_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_CHRONO_SOURCE
# define BOOST_CHRONO_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_CHRONO_DECL BOOST_SYMBOL_IMPORT
#endif  // BOOST_CHRONO_SOURCE
#endif  // DYN_LINK
//
// if BOOST_CHRONO_DECL isn't defined yet define it now:
#ifndef BOOST_CHRONO_DECL
#define BOOST_CHRONO_DECL
#endif



//  enable automatic library variant selection  ------------------------------//

#if !defined(BOOST_CHRONO_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_CHRONO_NO_LIB)
//
// Set the name of our library; this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_chrono
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CHRONO_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled
#endif // BOOST_CHRONO_HEADER_ONLY
#endif // BOOST_CHRONO_CONFIG_HPP


/* config.hpp
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
*/