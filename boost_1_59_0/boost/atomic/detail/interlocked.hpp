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

extern "C" long __cdecl _InterlockedCompareExchange(long volatile*, long, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern "C" long __cdecl _InterlockedDecrement(long volatile*);

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) _InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) _InterlockedDecrement((long*)(dest))

#else // _WIN32_WCE >= 0x600

extern "C" long __cdecl InterlockedCompareExchange(long*, long, long);
extern "C" long __cdecl InterlockedExchangeAdd(long*, long);
extern "C" long __cdecl InterlockedExchange(long*, long);
extern "C" long __cdecl InterlockedIncrement(long*);
extern "C" long __cdecl InterlockedDecrement(long*);

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) InterlockedDecrement((long*)(dest))

#endif // _WIN32_WCE >= 0x600

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE((long*)(dest), (long)(exchange), (long)(compare)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE((long*)(dest), (long)(exchange)))

#elif defined(_MSC_VER) && _MSC_VER >= 1310

#if _MSC_VER < 1400

extern "C" long __cdecl _InterlockedCompareExchange(long volatile*, long, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern "C" long __cdecl _InterlockedDecrement(long volatile*);

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), exchange, compare)
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) _InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) _InterlockedDecrement((long*)(dest))

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest, exchange, compare) ((void*)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE((long*)(dest), (long)(exchange), (long)(compare)))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_POINTER(dest, exchange) ((void*)BOOST_ATOMIC_INTERLOCKED_EXCHANGE((long*)(dest), (long)(exchange)))

#else // _MSC_VER < 1400

#include <intrin.h>

#if defined(BOOST_MSVC)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedAnd)
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedXor)
#pragma intrinsic(_interlockedbittestandset)
#pragma intrinsic(_interlockedbittestandreset)
#endif

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) _InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) _InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) _InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) _InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) _InterlockedDecrement((long*)(dest))
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
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) InterlockedDecrement((long*)(dest))

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
BOOST_ATOMIC_INTERLOCKED_IMPORT long __stdcall InterlockedIncrement(long volatile*, long);
BOOST_ATOMIC_INTERLOCKED_IMPORT long __stdcall InterlockedDecrement(long volatile*, long);

#define BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(dest, exchange, compare) boost::atomics::detail::InterlockedCompareExchange((long*)(dest), (long)(exchange), (long)(compare))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE(dest, newval) boost::atomics::detail::InterlockedExchange((long*)(dest), (long)(newval))
#define BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(dest, addend) boost::atomics::detail::InterlockedExchangeAdd((long*)(dest), (long)(addend))
#define BOOST_ATOMIC_INTERLOCKED_INCREMENT(dest) boost::atomics::detail::InterlockedIncrement((long*)(dest))
#define BOOST_ATOMIC_INTERLOCKED_DECREMENT(dest) boost::atomics::detail::InterlockedDecrement((long*)(dest))

#if defined(_WIN64)

BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedCompareExchange64(__int64 volatile*, __int64, __int64);
BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedExchange64(__int64 volatile*, __int64);
BOOST_ATOMIC_INTERLOCKED_IMPORT __int64 __stdcall InterlockedExchangeAdd64(__int64 volatile*, __int64);

BOOST_ATOMIC_INTERLOCKED_IMPORT void* __stdcall InterlockedCompareExchangePointer(void* volatile*, void*, void*);
BOOST_ATOMIC_INTERLOCKED_IMPORT void* __stdcall InterlockedExchangePointer(void* volatile*, void*);

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