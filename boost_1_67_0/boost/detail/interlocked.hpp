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