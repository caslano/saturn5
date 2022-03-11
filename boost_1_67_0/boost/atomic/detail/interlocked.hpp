#ifndef BOOST_ATOMIC_DETAIL_INTERLOCKED_HPP
#define BOOST_ATOMIC_DETAIL_INTERLOCKED_HPP

//  Copyright (c) 2009 Helge Bahmann
//  Copyright (c) 2012 - 2014, 2017 Andrey Semashev
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_WIN32_WCE)

#if _WIN32_WCE >= 0x600

extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))

#else // _WIN32_WCE >= 0x600

extern "C" long __cdecl InterlockedCompareExchange( long*, long, long );
extern "C" long __cdecl InterlockedExchangeAdd( long*, long );
extern "C" long __cdecl InterlockedExchange( long*, long );

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) InterlockedExchange((long*)(dest), (long)(newval))

#endif // _WIN32_WCE >= 0x600

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE((long*)(dest), (long)(exchange), (long)(compare)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE((long*)(dest), (long)(exchange)))

#elif defined(_MSC_VER) && _MSC_VER >= 1310

#if _MSC_VER < 1400

extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE((long*)(dest), (long)(exchange), (long)(compare)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE((long*)(dest), (long)(exchange)))

#else // _MSC_VER < 1400

#include <intrin.h>

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedAnd)
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedXor)
#pragma intrinsic(_interlockedbittestandset)
#pragma intrinsic(_interlockedbittestandreset)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_AND(dest, arg) _InterlockedAnd((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR(dest, arg) _InterlockedOr((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR(dest, arg) _InterlockedXor((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTS(dest, arg) _interlockedbittestandset((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTR(dest, arg) _interlockedbittestandreset((long*)(dest), (long)(arg))

#if defined(_M_AMD64)
#if defined(BOOST_MSVC)
#pragma intrinsic(_interlockedbittestandset64)
#pragma intrinsic(_interlockedbittestandreset64)
#endif

#define BOOST_ATOMIC_INTERLOCKED_BTS64(dest, arg) _interlockedbittestandset64((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTR64(dest, arg) _interlockedbittestandreset64((__int64*)(dest), (__int64)(arg))
#endif // defined(_M_AMD64)

#if (defined(_M_IX86) && _M_IX86 >= 500) || defined(_M_AMD64) || defined(_M_IA64)
#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange64)
#endif
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(dest, exchange, compare) _InterlockedCompareExchange64((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#endif

#if _MSC_VER >= 1500 && defined(_M_AMD64)
#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange128)
#endif
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE128(dest, exchange, compare) _InterlockedCompareExchange128((__int64*)(dest), ((const __int64*)(&exchange))[1], ((const __int64*)(&exchange))[0], (__int64*)(compare))
#endif

#if _MSC_VER >= 1600

// MSVC 2010 and later provide intrinsics for 8 and 16 bit integers.
// Note that for each bit count these macros must be either all defined or all not defined.
// Otherwise atomic<> operations will be implemented inconsistently.

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange8)
#pragma intrinsic(_InterlockedExchangeAdd8)
#pragma intrinsic(_InterlockedExchange8)
#pragma intrinsic(_InterlockedAnd8)
#pragma intrinsic(_InterlockedOr8)
#pragma intrinsic(_InterlockedXor8)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8(dest, exchange, compare) _InterlockedCompareExchange8((char*)(dest), (char)(exchange), (char)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8(dest, addend) _InterlockedExchangeAdd8((char*)(dest), (char)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE8(dest, newval) _InterlockedExchange8((char*)(dest), (char)(newval))
#define BOOST_ATOMIC_INTERLOCKED_AND8(dest, arg) _InterlockedAnd8((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR8(dest, arg) _InterlockedOr8((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR8(dest, arg) _InterlockedXor8((char*)(dest), (char)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_InterlockedExchangeAdd16)
#pragma intrinsic(_InterlockedExchange16)
#pragma intrinsic(_InterlockedAnd16)
#pragma intrinsic(_InterlockedOr16)
#pragma intrinsic(_InterlockedXor16)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16(dest, exchange, compare) _InterlockedCompareExchange16((short*)(dest), (short)(exchange), (short)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16(dest, addend) _InterlockedExchangeAdd16((short*)(dest), (short)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE16(dest, newval) _InterlockedExchange16((short*)(dest), (short)(newval))
#define BOOST_ATOMIC_INTERLOCKED_AND16(dest, arg) _InterlockedAnd16((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR16(dest, arg) _InterlockedOr16((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR16(dest, arg) _InterlockedXor16((short*)(dest), (short)(arg))

#endif // _MSC_VER >= 1600

#if defined(_M_AMD64) || defined(_M_IA64)

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedXor64)
#endif

#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, addend) _InterlockedExchangeAdd64((__int64*)(dest), (__int64)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(dest, newval) _InterlockedExchange64((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_AND64(dest, arg) _InterlockedAnd64((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR64(dest, arg) _InterlockedOr64((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR64(dest, arg) _InterlockedXor64((__int64*)(dest), (__int64)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchangePointer)
#pragma intrinsic(_InterlockedExchangePointer)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) _InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) _InterlockedExchangePointer((void**)(dest), (void*)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64((long*)(dest), byte_offset))

#elif defined(_M_IX86)

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)_InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) ((void*)_InterlockedExchange((long*)(dest), (long)(newval)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD((long*)(dest), byte_offset))

#endif

#if _MSC_VER >= 1700 && (defined(_M_ARM) || defined(_M_ARM64))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedXor64)
#endif

#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, addend) _InterlockedExchangeAdd64((__int64*)(dest), (__int64)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(dest, newval) _InterlockedExchange64((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_AND64(dest, arg) _InterlockedAnd64((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR64(dest, arg) _InterlockedOr64((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR64(dest, arg) _InterlockedXor64((__int64*)(dest), (__int64)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange8_nf)
#pragma intrinsic(_InterlockedCompareExchange8_acq)
#pragma intrinsic(_InterlockedCompareExchange8_rel)
#pragma intrinsic(_InterlockedCompareExchange16_nf)
#pragma intrinsic(_InterlockedCompareExchange16_acq)
#pragma intrinsic(_InterlockedCompareExchange16_rel)
#pragma intrinsic(_InterlockedCompareExchange_nf)
#pragma intrinsic(_InterlockedCompareExchange_acq)
#pragma intrinsic(_InterlockedCompareExchange_rel)
#pragma intrinsic(_InterlockedCompareExchange64)
#pragma intrinsic(_InterlockedCompareExchange64_nf)
#pragma intrinsic(_InterlockedCompareExchange64_acq)
#pragma intrinsic(_InterlockedCompareExchange64_rel)
#pragma intrinsic(_InterlockedCompareExchangePointer)
#pragma intrinsic(_InterlockedCompareExchangePointer_nf)
#pragma intrinsic(_InterlockedCompareExchangePointer_acq)
#pragma intrinsic(_InterlockedCompareExchangePointer_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_RELAXED(dest, exchange, compare) _InterlockedCompareExchange8_nf((char*)(dest), (char)(exchange), (char)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_ACQUIRE(dest, exchange, compare) _InterlockedCompareExchange8_acq((char*)(dest), (char)(exchange), (char)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_RELEASE(dest, exchange, compare) _InterlockedCompareExchange8_rel((char*)(dest), (char)(exchange), (char)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_RELAXED(dest, exchange, compare) _InterlockedCompareExchange16_nf((short*)(dest), (short)(exchange), (short)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_ACQUIRE(dest, exchange, compare) _InterlockedCompareExchange16_acq((short*)(dest), (short)(exchange), (short)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_RELEASE(dest, exchange, compare) _InterlockedCompareExchange16_rel((short*)(dest), (short)(exchange), (short)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_RELAXED(dest, exchange, compare) _InterlockedCompareExchange_nf((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_ACQUIRE(dest, exchange, compare) _InterlockedCompareExchange_acq((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_RELEASE(dest, exchange, compare) _InterlockedCompareExchange_rel((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(dest, exchange, compare) _InterlockedCompareExchange64((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_RELAXED(dest, exchange, compare) _InterlockedCompareExchange64_nf((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_ACQUIRE(dest, exchange, compare) _InterlockedCompareExchange64_acq((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_RELEASE(dest, exchange, compare) _InterlockedCompareExchange64_rel((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) _InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER_RELAXED(dest, exchange, compare) _InterlockedCompareExchangePointer_nf((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER_ACQUIRE(dest, exchange, compare) _InterlockedCompareExchangePointer_acq((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER_RELEASE(dest, exchange, compare) _InterlockedCompareExchangePointer_rel((void**)(dest), (void*)(exchange), (void*)(compare))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedExchangeAdd8_nf)
#pragma intrinsic(_InterlockedExchangeAdd8_acq)
#pragma intrinsic(_InterlockedExchangeAdd8_rel)
#pragma intrinsic(_InterlockedExchangeAdd16_nf)
#pragma intrinsic(_InterlockedExchangeAdd16_acq)
#pragma intrinsic(_InterlockedExchangeAdd16_rel)
#pragma intrinsic(_InterlockedExchangeAdd_nf)
#pragma intrinsic(_InterlockedExchangeAdd_acq)
#pragma intrinsic(_InterlockedExchangeAdd_rel)
#pragma intrinsic(_InterlockedExchangeAdd64_nf)
#pragma intrinsic(_InterlockedExchangeAdd64_acq)
#pragma intrinsic(_InterlockedExchangeAdd64_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_RELAXED(dest, addend) _InterlockedExchangeAdd8_nf((char*)(dest), (char)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_ACQUIRE(dest, addend) _InterlockedExchangeAdd8_acq((char*)(dest), (char)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_RELEASE(dest, addend) _InterlockedExchangeAdd8_rel((char*)(dest), (char)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_RELAXED(dest, addend) _InterlockedExchangeAdd16_nf((short*)(dest), (short)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_ACQUIRE(dest, addend) _InterlockedExchangeAdd16_acq((short*)(dest), (short)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_RELEASE(dest, addend) _InterlockedExchangeAdd16_rel((short*)(dest), (short)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELAXED(dest, addend) _InterlockedExchangeAdd_nf((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_ACQUIRE(dest, addend) _InterlockedExchangeAdd_acq((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELEASE(dest, addend) _InterlockedExchangeAdd_rel((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELAXED(dest, addend) _InterlockedExchangeAdd64_nf((__int64*)(dest), (__int64)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_ACQUIRE(dest, addend) _InterlockedExchangeAdd64_acq((__int64*)(dest), (__int64)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELEASE(dest, addend) _InterlockedExchangeAdd64_rel((__int64*)(dest), (__int64)(addend))

#if defined(_M_ARM64)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64((__int64*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_RELAXED(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELAXED((__int64*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_ACQUIRE(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_ACQUIRE((__int64*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_RELEASE(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELEASE((__int64*)(dest), byte_offset))
#else
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD((long*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_RELAXED(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELAXED((long*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_ACQUIRE(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_ACQUIRE((long*)(dest), byte_offset))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER_RELEASE(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELEASE((long*)(dest), byte_offset))
#endif

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedExchange8_nf)
#pragma intrinsic(_InterlockedExchange8_acq)
#pragma intrinsic(_InterlockedExchange16_nf)
#pragma intrinsic(_InterlockedExchange16_acq)
#pragma intrinsic(_InterlockedExchange_nf)
#pragma intrinsic(_InterlockedExchange_acq)
#pragma intrinsic(_InterlockedExchange64_nf)
#pragma intrinsic(_InterlockedExchange64_acq)
#pragma intrinsic(_InterlockedExchangePointer)
#pragma intrinsic(_InterlockedExchangePointer_nf)
#pragma intrinsic(_InterlockedExchangePointer_acq)
#if _MSC_VER >= 1800
#pragma intrinsic(_InterlockedExchange8_rel)
#pragma intrinsic(_InterlockedExchange16_rel)
#pragma intrinsic(_InterlockedExchange_rel)
#pragma intrinsic(_InterlockedExchange64_rel)
#pragma intrinsic(_InterlockedExchangePointer_rel)
#endif
#endif

#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_RELAXED(dest, newval) _InterlockedExchange8_nf((char*)(dest), (char)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_ACQUIRE(dest, newval) _InterlockedExchange8_acq((char*)(dest), (char)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_RELAXED(dest, newval) _InterlockedExchange16_nf((short*)(dest), (short)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_ACQUIRE(dest, newval) _InterlockedExchange16_acq((short*)(dest), (short)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_RELAXED(dest, newval) _InterlockedExchange_nf((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ACQUIRE(dest, newval) _InterlockedExchange_acq((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_RELAXED(dest, newval) _InterlockedExchange64_nf((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_ACQUIRE(dest, newval) _InterlockedExchange64_acq((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) _InterlockedExchangePointer((void**)(dest), (void*)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER_RELAXED(dest, newval) _InterlockedExchangePointer_nf((void**)(dest), (void*)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER_ACQUIRE(dest, newval) _InterlockedExchangePointer_acq((void**)(dest), (void*)(newval))

#if _MSC_VER >= 1800
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_RELEASE(dest, newval) _InterlockedExchange8_rel((char*)(dest), (char)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_RELEASE(dest, newval) _InterlockedExchange16_rel((short*)(dest), (short)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_RELEASE(dest, newval) _InterlockedExchange_rel((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_RELEASE(dest, newval) _InterlockedExchange64_rel((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER_RELEASE(dest, newval) _InterlockedExchangePointer_rel((void**)(dest), (void*)(newval))
#else
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_RELEASE(dest, newval) BOOST_ATOMIC_INTERLOCKED_EXCHANGE8(dest, newval)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_RELEASE(dest, newval) BOOST_ATOMIC_INTERLOCKED_EXCHANGE16(dest, newval)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_RELEASE(dest, newval) BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_RELEASE(dest, newval) BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(dest, newval)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER_RELEASE(dest, newval) BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval)
#endif

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedAnd8_nf)
#pragma intrinsic(_InterlockedAnd8_acq)
#pragma intrinsic(_InterlockedAnd8_rel)
#pragma intrinsic(_InterlockedAnd16_nf)
#pragma intrinsic(_InterlockedAnd16_acq)
#pragma intrinsic(_InterlockedAnd16_rel)
#pragma intrinsic(_InterlockedAnd_nf)
#pragma intrinsic(_InterlockedAnd_acq)
#pragma intrinsic(_InterlockedAnd_rel)
#pragma intrinsic(_InterlockedAnd64_nf)
#pragma intrinsic(_InterlockedAnd64_acq)
#pragma intrinsic(_InterlockedAnd64_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_AND8_RELAXED(dest, arg) _InterlockedAnd8_nf((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND8_ACQUIRE(dest, arg) _InterlockedAnd8_acq((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND8_RELEASE(dest, arg) _InterlockedAnd8_rel((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND16_RELAXED(dest, arg) _InterlockedAnd16_nf((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND16_ACQUIRE(dest, arg) _InterlockedAnd16_acq((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND16_RELEASE(dest, arg) _InterlockedAnd16_rel((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND_RELAXED(dest, arg) _InterlockedAnd_nf((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND_ACQUIRE(dest, arg) _InterlockedAnd_acq((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND_RELEASE(dest, arg) _InterlockedAnd_rel((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND64_RELAXED(dest, arg) _InterlockedAnd64_nf((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND64_ACQUIRE(dest, arg) _InterlockedAnd64_acq((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_AND64_RELEASE(dest, arg) _InterlockedAnd64_rel((__int64*)(dest), (__int64)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedOr8_nf)
#pragma intrinsic(_InterlockedOr8_acq)
#pragma intrinsic(_InterlockedOr8_rel)
#pragma intrinsic(_InterlockedOr16_nf)
#pragma intrinsic(_InterlockedOr16_acq)
#pragma intrinsic(_InterlockedOr16_rel)
#pragma intrinsic(_InterlockedOr_nf)
#pragma intrinsic(_InterlockedOr_acq)
#pragma intrinsic(_InterlockedOr_rel)
#pragma intrinsic(_InterlockedOr64_nf)
#pragma intrinsic(_InterlockedOr64_acq)
#pragma intrinsic(_InterlockedOr64_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_OR8_RELAXED(dest, arg) _InterlockedOr8_nf((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR8_ACQUIRE(dest, arg) _InterlockedOr8_acq((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR8_RELEASE(dest, arg) _InterlockedOr8_rel((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR16_RELAXED(dest, arg) _InterlockedOr16_nf((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR16_ACQUIRE(dest, arg) _InterlockedOr16_acq((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR16_RELEASE(dest, arg) _InterlockedOr16_rel((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR_RELAXED(dest, arg) _InterlockedOr_nf((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR_ACQUIRE(dest, arg) _InterlockedOr_acq((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR_RELEASE(dest, arg) _InterlockedOr_rel((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR64_RELAXED(dest, arg) _InterlockedOr64_nf((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR64_ACQUIRE(dest, arg) _InterlockedOr64_acq((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_OR64_RELEASE(dest, arg) _InterlockedOr64_rel((__int64*)(dest), (__int64)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedXor8_nf)
#pragma intrinsic(_InterlockedXor8_acq)
#pragma intrinsic(_InterlockedXor8_rel)
#pragma intrinsic(_InterlockedXor16_nf)
#pragma intrinsic(_InterlockedXor16_acq)
#pragma intrinsic(_InterlockedXor16_rel)
#pragma intrinsic(_InterlockedXor_nf)
#pragma intrinsic(_InterlockedXor_acq)
#pragma intrinsic(_InterlockedXor_rel)
#pragma intrinsic(_InterlockedXor64_nf)
#pragma intrinsic(_InterlockedXor64_acq)
#pragma intrinsic(_InterlockedXor64_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_XOR8_RELAXED(dest, arg) _InterlockedXor8_nf((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR8_ACQUIRE(dest, arg) _InterlockedXor8_acq((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR8_RELEASE(dest, arg) _InterlockedXor8_rel((char*)(dest), (char)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR16_RELAXED(dest, arg) _InterlockedXor16_nf((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR16_ACQUIRE(dest, arg) _InterlockedXor16_acq((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR16_RELEASE(dest, arg) _InterlockedXor16_rel((short*)(dest), (short)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR_RELAXED(dest, arg) _InterlockedXor_nf((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR_ACQUIRE(dest, arg) _InterlockedXor_acq((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR_RELEASE(dest, arg) _InterlockedXor_rel((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR64_RELAXED(dest, arg) _InterlockedXor64_nf((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR64_ACQUIRE(dest, arg) _InterlockedXor64_acq((__int64*)(dest), (__int64)(arg))
#define BOOST_ATOMIC_INTERLOCKED_XOR64_RELEASE(dest, arg) _InterlockedXor64_rel((__int64*)(dest), (__int64)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_interlockedbittestandset_nf)
#pragma intrinsic(_interlockedbittestandset_acq)
#pragma intrinsic(_interlockedbittestandset_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED(dest, arg) _interlockedbittestandset_nf((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE(dest, arg) _interlockedbittestandset_acq((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE(dest, arg) _interlockedbittestandset_rel((long*)(dest), (long)(arg))

#if defined(BOOST_MSVC)
#pragma intrinsic(_interlockedbittestandreset_nf)
#pragma intrinsic(_interlockedbittestandreset_acq)
#pragma intrinsic(_interlockedbittestandreset_rel)
#endif

#define BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED(dest, arg) _interlockedbittestandreset_nf((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE(dest, arg) _interlockedbittestandreset_acq((long*)(dest), (long)(arg))
#define BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE(dest, arg) _interlockedbittestandreset_rel((long*)(dest), (long)(arg))

#endif // _MSC_VER >= 1700 && defined(_M_ARM)

#endif // _MSC_VER < 1400

#else // defined(_MSC_VER) && _MSC_VER >= 1310

#if defined(BOOST_USE_WINDOWS_H)

#include <windows.h>

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) InterlockedExchangeAdd((long*)(dest), (long)(addend))

#if defined(_WIN64)

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(dest, exchange, compare) InterlockedCompareExchange64((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(dest, newval) InterlockedExchange64((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, addend) InterlockedExchangeAdd64((__int64*)(dest), (__int64)(addend))

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) InterlockedExchangePointer((void**)(dest), (void*)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, byte_offset))

#else // defined(_WIN64)

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, byte_offset))

#endif // defined(_WIN64)

#else // defined(BOOST_USE_WINDOWS_H)

#if defined(__MINGW64__)
#define BOOST_ATOMIC_INTERLOCKED_IMPORT
#else
#define BOOST_ATOMIC_INTERLOCKED_IMPORT __declspec(dllimport)
#endif

namespace boost {
namespace atomics {
namespace detail {

extern "C" {

BOOST_ATOMIC_INTERLOCKED_IMPORT long __stdcall InterlockedCompareExchange(long volatile*, long, long);
BOOST_ATOMIC_INTERLOCKED_IMPORT long __stdcall InterlockedExchange(long volatile*, long);
BOOST_ATOMIC_INTERLOCKED_IMPORT long __stdcall InterlockedExchangeAdd(long volatile*, long);

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) boost::atomics::detail::InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) boost::atomics::detail::InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) boost::atomics::detail::InterlockedExchangeAdd((long*)(dest), (long)(addend))

#if defined(_WIN64)

BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedCompareExchange64(__int64 volatile*, __int64, __int64);
BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedExchange64(__int64 volatile*, __int64);
BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedExchangeAdd64(__int64 volatile*, __int64);

BOOST_ATOMIC_INTERLOCKED_IMPORT void* __stdcall InterlockedCompareExchangePointer(void* volatile *, void*, void*);
BOOST_ATOMIC_INTERLOCKED_IMPORT void* __stdcall InterlockedExchangePointer(void* volatile *, void*);

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(dest, exchange, compare) boost::atomics::detail::InterlockedCompareExchange64((__int64*)(dest), (__int64)(exchange), (__int64)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(dest, newval) boost::atomics::detail::InterlockedExchange64((__int64*)(dest), (__int64)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, addend) boost::atomics::detail::InterlockedExchangeAdd64((__int64*)(dest), (__int64)(addend))

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) boost::atomics::detail::InterlockedCompareExchangePointer((void**)(dest), (void*)(exchange), (void*)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) boost::atomics::detail::InterlockedExchangePointer((void**)(dest), (void*)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(dest, byte_offset))

#else // defined(_WIN64)

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, newval) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_POINTER(dest, byte_offset) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, byte_offset))

#endif // defined(_WIN64)

} // extern "C"

} // namespace detail
} // namespace atomics
} // namespace boost

#undef BOOST_ATOMIC_INTERLOCKED_IMPORT

#endif // defined(BOOST_USE_WINDOWS_H)

#endif // defined(_MSC_VER)

#endif

/* interlocked.hpp
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
*/