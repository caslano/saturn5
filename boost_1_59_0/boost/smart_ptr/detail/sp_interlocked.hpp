#ifndef BOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/detail/sp_interlocked.hpp
//
//  Copyright 2005, 2014 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/config.hpp>

// BOOST_SP_HAS_INTRIN_H

// VC9 has intrin.h, but it collides with <utility>
#if defined( BOOST_MSVC ) && BOOST_MSVC >= 1600

# define BOOST_SP_HAS_INTRIN_H

// Unlike __MINGW64__, __MINGW64_VERSION_MAJOR is defined by MinGW-w64 for both 32 and 64-bit targets.
#elif defined( __MINGW64_VERSION_MAJOR )

// MinGW-w64 provides intrin.h for both 32 and 64-bit targets.
# define BOOST_SP_HAS_INTRIN_H

#elif defined( __LP64__ )

// We have to use intrin.h on Cygwin 64
# define BOOST_SP_HAS_INTRIN_H

// Intel C++ on Windows on VC10+ stdlib
#elif defined( BOOST_INTEL_WIN ) && defined( _CPPLIB_VER ) && _CPPLIB_VER >= 520

# define BOOST_SP_HAS_INTRIN_H

// clang-cl on Windows on VC10+ stdlib
#elif defined( __clang__ ) && defined( _MSC_VER ) && defined( _CPPLIB_VER ) && _CPPLIB_VER >= 520

# define BOOST_SP_HAS_INTRIN_H

#endif

#if defined( BOOST_USE_WINDOWS_H )

# include <windows.h>

# define BOOST_SP_INTERLOCKED_INCREMENT InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd

#elif defined( BOOST_USE_INTRIN_H ) || defined( BOOST_SP_HAS_INTRIN_H )

#include <intrin.h>

# define BOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#elif defined( _WIN32_WCE )

#if _WIN32_WCE >= 0x600

extern "C" long __cdecl _InterlockedIncrement( long volatile * );
extern "C" long __cdecl _InterlockedDecrement( long volatile * );
extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );

# define BOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#else

// under Windows CE we still have old-style Interlocked* functions

extern "C" long __cdecl InterlockedIncrement( long* );
extern "C" long __cdecl InterlockedDecrement( long* );
extern "C" long __cdecl InterlockedCompareExchange( long*, long, long );
extern "C" long __cdecl InterlockedExchange( long*, long );
extern "C" long __cdecl InterlockedExchangeAdd( long*, long );

# define BOOST_SP_INTERLOCKED_INCREMENT InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd

#endif

#elif defined( BOOST_MSVC ) || defined( BOOST_INTEL_WIN )

#if defined( __CLRCALL_PURE_OR_CDECL )

extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedIncrement( long volatile * );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedDecrement( long volatile * );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedExchange( long volatile *, long );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedExchangeAdd( long volatile *, long );

#else

extern "C" long __cdecl _InterlockedIncrement( long volatile * );
extern "C" long __cdecl _InterlockedDecrement( long volatile * );
extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );

# if defined( BOOST_MSVC ) && BOOST_MSVC == 1310
//From MSDN, Visual Studio .NET 2003 spedific: To declare one of the interlocked functions
//for use as an intrinsic, the function must be declared with the leading underscore and
//the new function must appear in a #pragma intrinsic statement.
#  pragma intrinsic( _InterlockedIncrement )
#  pragma intrinsic( _InterlockedDecrement )
#  pragma intrinsic( _InterlockedCompareExchange )
#  pragma intrinsic( _InterlockedExchange )
#  pragma intrinsic( _InterlockedExchangeAdd )
# endif

#endif

# define BOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )

namespace boost
{

namespace detail
{

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedCompareExchange( long volatile *, long, long );
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange( long volatile *, long );
extern "C" __declspec(dllimport) long __stdcall InterlockedExchangeAdd( long volatile *, long );

} // namespace detail

} // namespace boost

# define BOOST_SP_INTERLOCKED_INCREMENT ::boost::detail::InterlockedIncrement
# define BOOST_SP_INTERLOCKED_DECREMENT ::boost::detail::InterlockedDecrement
# define BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE ::boost::detail::InterlockedCompareExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE ::boost::detail::InterlockedExchange
# define BOOST_SP_INTERLOCKED_EXCHANGE_ADD ::boost::detail::InterlockedExchangeAdd

#else

# error "Interlocked intrinsics not available"

#endif

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED

/* sp_interlocked.hpp
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
*/