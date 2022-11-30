#ifndef BOOST_DETAIL_INTERLOCKED_HPP_INCLUDED
#define BOOST_DETAIL_INTERLOCKED_HPP_INCLUDED

//
//  boost/detail/interlocked.hpp
//
//  Copyright 2005 Peter Dimov
//  Copyright 2018, 2019 Andrey Semashev
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// BOOST_INTERLOCKED_HAS_INTRIN_H

// VC9 has intrin.h, but it collides with <utility>
#if defined( BOOST_MSVC ) && BOOST_MSVC >= 1600

# define BOOST_INTERLOCKED_HAS_INTRIN_H

// Unlike __MINGW64__, __MINGW64_VERSION_MAJOR is defined by MinGW-w64 for both 32 and 64-bit targets.
#elif defined( __MINGW64_VERSION_MAJOR )

// MinGW-w64 provides intrin.h for both 32 and 64-bit targets.
# define BOOST_INTERLOCKED_HAS_INTRIN_H

#elif defined( __CYGWIN__ )

// Cygwin and Cygwin64 provide intrin.h. On Cygwin64 we have to use intrin.h because it's an LP64 target,
// where long is 64-bit and therefore _Interlocked* functions have different signatures.
# define BOOST_INTERLOCKED_HAS_INTRIN_H

// Intel C++ on Windows on VC10+ stdlib
#elif defined( BOOST_INTEL_WIN ) && defined( _CPPLIB_VER ) && _CPPLIB_VER >= 520

# define BOOST_INTERLOCKED_HAS_INTRIN_H

// clang-cl on Windows on VC10+ stdlib
#elif defined( __clang__ ) && defined( _MSC_VER ) && defined( _CPPLIB_VER ) && _CPPLIB_VER >= 520

# define BOOST_INTERLOCKED_HAS_INTRIN_H

#endif

#if !defined(__LP64__)
#define BOOST_INTERLOCKED_LONG32 long
#else
#define BOOST_INTERLOCKED_LONG32 int
#endif

#if defined( BOOST_USE_WINDOWS_H )

# include <windows.h>

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
    InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
# define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
    InterlockedExchangePointer((void**)(dest), (void*)(exchange))

#elif defined( BOOST_USE_INTRIN_H ) || defined( BOOST_INTERLOCKED_HAS_INTRIN_H )

#include <intrin.h>

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    _InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    _InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    _InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    _InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    _InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))

// Note: Though MSVC-12 defines _InterlockedCompareExchangePointer and _InterlockedExchangePointer in intrin.h, the latter
//       is actually broken as it conflicts with winnt.h from Windows SDK 8.1.
# if (defined(_MSC_VER) && _MSC_VER >= 1900) || \
  (defined(_M_IA64) || defined(_M_AMD64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_ARM64))

#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
     _InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
     _InterlockedExchangePointer((void**)(dest), (void*)(exchange))

# else

#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
    ((void*)BOOST_INTERLOCKED_COMPARE_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare)))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
    ((void*)BOOST_INTERLOCKED_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange)))

# endif

#elif defined(_WIN32_WCE)

#if _WIN32_WCE >= 0x600

extern "C" BOOST_INTERLOCKED_LONG32 __cdecl _InterlockedIncrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl _InterlockedDecrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl _InterlockedCompareExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl _InterlockedExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl _InterlockedExchangeAdd( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    _InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    _InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    _InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    _InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    _InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))

#else // _WIN32_WCE >= 0x600

// under Windows CE we still have old-style Interlocked* functions

extern "C" BOOST_INTERLOCKED_LONG32 __cdecl InterlockedIncrement( BOOST_INTERLOCKED_LONG32 * );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl InterlockedDecrement( BOOST_INTERLOCKED_LONG32 * );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl InterlockedCompareExchange( BOOST_INTERLOCKED_LONG32 *, BOOST_INTERLOCKED_LONG32, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl InterlockedExchange( BOOST_INTERLOCKED_LONG32 *, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 __cdecl InterlockedExchangeAdd( BOOST_INTERLOCKED_LONG32 *, BOOST_INTERLOCKED_LONG32 );

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))

#endif // _WIN32_WCE >= 0x600

# define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
    ((void*)BOOST_INTERLOCKED_COMPARE_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare)))
# define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
    ((void*)BOOST_INTERLOCKED_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange)))

#elif defined( BOOST_MSVC ) || defined( BOOST_INTEL_WIN )

# if defined( __CLRCALL_PURE_OR_CDECL )
#  define BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL __CLRCALL_PURE_OR_CDECL
# else
#  define BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL __cdecl
# endif

extern "C" BOOST_INTERLOCKED_LONG32 BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedIncrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_LONG32 BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedDecrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_LONG32 BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedCompareExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_LONG32 BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedExchangeAdd( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );

# if defined( BOOST_MSVC ) && BOOST_MSVC >= 1310
#  pragma intrinsic( _InterlockedIncrement )
#  pragma intrinsic( _InterlockedDecrement )
#  pragma intrinsic( _InterlockedCompareExchange )
#  pragma intrinsic( _InterlockedExchange )
#  pragma intrinsic( _InterlockedExchangeAdd )
# endif

# if defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM64)

extern "C" void* BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedCompareExchangePointer( void* volatile *, void*, void* );
extern "C" void* BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL _InterlockedExchangePointer( void* volatile *, void* );

#  if defined( BOOST_MSVC ) && BOOST_MSVC >= 1310
#   pragma intrinsic( _InterlockedCompareExchangePointer )
#   pragma intrinsic( _InterlockedExchangePointer )
#  endif

#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
     _InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
     _InterlockedExchangePointer((void**)(dest), (void*)(exchange))

# else

#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
    ((void*)BOOST_INTERLOCKED_COMPARE_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare)))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
    ((void*)BOOST_INTERLOCKED_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange)))

# endif

# undef BOOST_INTERLOCKED_CLRCALL_PURE_OR_CDECL

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    _InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    _InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    _InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    _InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    _InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))

#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ )

#define BOOST_INTERLOCKED_IMPORT __declspec(dllimport)

namespace boost
{

namespace detail
{

extern "C" BOOST_INTERLOCKED_IMPORT BOOST_INTERLOCKED_LONG32 __stdcall InterlockedIncrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_IMPORT BOOST_INTERLOCKED_LONG32 __stdcall InterlockedDecrement( BOOST_INTERLOCKED_LONG32 volatile * );
extern "C" BOOST_INTERLOCKED_IMPORT BOOST_INTERLOCKED_LONG32 __stdcall InterlockedCompareExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_IMPORT BOOST_INTERLOCKED_LONG32 __stdcall InterlockedExchange( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );
extern "C" BOOST_INTERLOCKED_IMPORT BOOST_INTERLOCKED_LONG32 __stdcall InterlockedExchangeAdd( BOOST_INTERLOCKED_LONG32 volatile *, BOOST_INTERLOCKED_LONG32 );

# if defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM64)
extern "C" BOOST_INTERLOCKED_IMPORT void* __stdcall InterlockedCompareExchangePointer( void* volatile *, void*, void* );
extern "C" BOOST_INTERLOCKED_IMPORT void* __stdcall InterlockedExchangePointer( void* volatile *, void* );
# endif

} // namespace detail

} // namespace boost

# define BOOST_INTERLOCKED_INCREMENT(dest) \
    ::boost::detail::InterlockedIncrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_DECREMENT(dest) \
    ::boost::detail::InterlockedDecrement((BOOST_INTERLOCKED_LONG32*)(dest))
# define BOOST_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) \
    ::boost::detail::InterlockedCompareExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange), (BOOST_INTERLOCKED_LONG32)(compare))
# define BOOST_INTERLOCKED_EXCHANGE(dest, exchange) \
    ::boost::detail::InterlockedExchange((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(exchange))
# define BOOST_INTERLOCKED_EXCHANGE_ADD(dest, add) \
    ::boost::detail::InterlockedExchangeAdd((BOOST_INTERLOCKED_LONG32*)(dest), (BOOST_INTERLOCKED_LONG32)(add))

# if defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM64)
#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
     ::boost::detail::InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
     ::boost::detail::InterlockedExchangePointer((void**)(dest), (void*)(exchange))
# else
#  define BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) \
    ((void*)BOOST_INTERLOCKED_COMPARE_EXCHANGE((BOOST_INTERLOCKED_LONG32 volatile*)(dest),(BOOST_INTERLOCKED_LONG32)(exchange),(BOOST_INTERLOCKED_LONG32)(compare)))
#  define BOOST_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) \
    ((void*)BOOST_INTERLOCKED_EXCHANGE((BOOST_INTERLOCKED_LONG32*)(dest),(BOOST_INTERLOCKED_LONG32)(exchange)))
# endif

#else

# error "Interlocked intrinsics not available"

#endif

#endif // #ifndef BOOST_DETAIL_INTERLOCKED_HPP_INCLUDED

/* interlocked.hpp
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
*/