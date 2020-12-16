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
wWnEsbDor4b2nzuFPn7lS1Iff5AGOlvcrReIL5kGjxlQ/B4DINHct8EHKUcwQOMzlJLH10Oy7oJF8mikuKa312dDf8xOavadNPCP/AwD/zAM/Fo58E3YZUjVDqgnwC97ifg4io1B39ekOcseApKHQB4xAjn0OAMyTQVSvoFwzEWTNJyo+COTKyUPELRGCG2OEVoxQHNHgmD2LI4r1oXl/IcFyllQgHqTQO1D/c/jRlCZAOojJueGur/1ae9F8/vbrqXDRdpRlqbookt9qUJD6da+XcunWERgK5W+l0MgdD4mdDIRnUeN6Dy+nqEzRCqr87Tbo3UHmu1/gyLjtgDnO1TOF+Y12l1vUPfzcR/i3f+W2tuPCqjHjO31hPb+gRoqEOzKwPBG6CrucqDtAsKoJhglCGOjEcZPjzEYK0VEWHT89BBH/EK1hmCth4y1XoRaYMEEEiW4fEJl9MQoIy9M7atvU2ziHuh3guRASOuMkAoBUlM7+9kVfg7YDPSpp9KH+jPldQufq2jSzm04CoCfNAJuDoDhsCYG2UmqzMRN+gVVPNWfhPU3GOt/+CirP48v1wWExJoFulI8meqeh3XXG+uuZXUDkrsSubbVqd29BtvG+s2o/vfVUP8JY/08qO+EZcQuzekemMtsS17YotiWjJyFq3c2fy8UL5E+2YeXSNr/XUPq/uGmCjAAB8uNEqvQzSIzpMsZe2exrqfuSePZ8gfJDw/q/n8PM16CKURMfuVTFkzOQd7+qsWF5wCCvfsI8rkRdgaDHRgE+4o0IMH9RIjDuEwLTy6hi8vTpj4NtnOV0HQZsPaQOUL7jbJgl9ncC4ptmEVniJMs7W8nPKdosrhRxnVPoffisd20Uz21XD0tkFBwvuaAm2E0sZWRJnC9zinNSpVh6R4vwdX81MLJKaiuwPvPbWK/f6JC7vdzVRd7jzBd1BLx+QPSb6yh5S/qe7n8rtPtH9DWMHA5d7lzwcnck1XugFKwYQijSa2GDbMA+BAB3PodSnpGgO0AoOgtchVfGfbtxpVhxamvDJbxJB59lsTj+xZCqPX9SlwJ5KN3X+bScjjvH3BQQxBUpQJluoAS8vz/rHr+nx/Wefqbrabz9Kuildr5AQFsIAAKnrue4BDCqj+J6mvdK8z9vXOmFRzz1OlI9ekk0X6dOklIj75MnExRMIvT7r9X9xqX6f6LxUrBZl/x/kThEwOWw0rG4Y8tMmT4XuGGToaWLYk/c76R/Hm/bv/2wBk76OaEvE9q+IzumaVEpRUHKy9aLEHs80Aa6EPeZEuJdqKIKwJPob0Ht4TX3g3U3lhob/V+3l44608u2v9vUe+DLcx+ZHw2eQTTPShY60e+xtZvWspav3VO7Y435vZ3bD699guo/R+WsPbLX6q9/dD3hV0IE+23beK4WBbVCKADxbNhPuTIoEN0sIx86Gital7z/DzwNLVy7zbz/Mws5POzdnyRcvMIknxUYRGTTcVem685nqV9biqlZsM1WZPCJCytOrZ5A/V1P20bdZ2bK+PMB1mQX4J6BCGKlLjieCR501874cOkz4ZNRJ9Chj/aVsltd9BChT6h1z9ev3tQ/eduD5u+FP+KQwrAihiSB0bsIh4IY31HqAeeUpTq5tiTKQRY+u72YoJ3oGOgAy9gL2yK3xSXMqe27nFWJprtzTVhvX1iud6kIv/rmLkQMwezdnO0BbyKuOlzY0jgajKOvp2rSJLULK+qQePKGrfixJjO09KVtEyelglp4voVgEK/ZyEkEwJuHYF0EwLpCgKZprxM7rSpmnN7oNEQ2qWALuiFY2B+mh/LUJnLNuLQqEui13CCEKI49nEc2ZHLNHW2KyZr7Z9B4Y8=
*/