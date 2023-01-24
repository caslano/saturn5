/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/int_sizes.hpp
 *
 * This header defines macros for testing buitin integer type sizes
 */

#ifndef BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// GCC and compatible compilers define internal macros with builtin type traits
#if defined(__SIZEOF_SHORT__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT __SIZEOF_SHORT__
#endif
#if defined(__SIZEOF_INT__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT __SIZEOF_INT__
#endif
#if defined(__SIZEOF_LONG__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG __SIZEOF_LONG__
#endif
#if defined(__SIZEOF_LONG_LONG__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG __SIZEOF_LONG_LONG__
#endif
#if defined(__SIZEOF_WCHAR_T__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T __SIZEOF_WCHAR_T__
#endif
#if defined(__SIZEOF_POINTER__)
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER __SIZEOF_POINTER__
#elif defined(_MSC_VER)
#if defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_IA64)
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER 8
#else
#define BOOST_ATOMIC_DETAIL_SIZEOF_POINTER 4
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LLONG)

// Try to deduce sizes from limits
#include <limits.h>
#include <boost/cstdint.hpp>

#if (USHRT_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 1
#elif (USHRT_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 2
#elif (USHRT_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 4
#elif (USHRT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_SHORT 8
#endif

#if (UINT_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 1
#elif (UINT_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 2
#elif (UINT_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 4
#elif (UINT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_INT 8
#endif

#if (ULONG_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 1
#elif (ULONG_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 2
#elif (ULONG_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 4
#elif (ULONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LONG 8
#endif

#if defined(__hpux) // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 8
#else

// The list of the non-standard macros (the ones except ULLONG_MAX) is taken from cstdint.hpp
#if defined(ULLONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULLONG_MAX
#elif defined(ULONG_LONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULONG_LONG_MAX
#elif defined(ULONGLONG_MAX)
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX ULONGLONG_MAX
#elif defined(_LLONG_MAX) // strangely enough, this one seems to be holding the limit for the unsigned integer
#define BOOST_ATOMIC_DETAIL_ULLONG_MAX _LLONG_MAX
#endif

#if (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 1
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 2
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 4
#elif (BOOST_ATOMIC_DETAIL_ULLONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_LLONG 8
#endif

#endif // defined(__hpux)

#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T)

#include <wchar.h>
#include <boost/cstdint.hpp>

#if defined(_MSC_VER) && (_MSC_VER <= 1310 || defined(UNDER_CE) && _MSC_VER <= 1500)
// MSVC 7.1 and MSVC 8 (arm) define WCHAR_MAX to a value not suitable for constant expressions
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xff || (WCHAR_MAX + 0) == 0x7f
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 1
#elif (WCHAR_MAX + 0) == 0xffff || (WCHAR_MAX + 0) == 0x7fff
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xffffffff || (WCHAR_MAX + 0) == 0x7fffffff
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 4
#elif (WCHAR_MAX + 0) == UINT64_C(0xffffffffffffffff) || (WCHAR_MAX + 0) == INT64_C(0x7fffffffffffffff)
#define BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T 8
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(BOOST_ATOMIC_DETAIL_SIZEOF_LLONG) ||\
    !defined(BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T)
#error Boost.Atomic: Failed to determine builtin integer sizes, the target platform is not supported. Please, report to the developers (patches are welcome).
#endif

#endif // BOOST_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_

/* int_sizes.hpp
A4nej0s4udfijTOiaO1qrR7jhK8tcCFgsxCsbgczLnsK+m6eXA7Lr66IRWYR7Dw+7X4+7WrXr7iYOHfXykGOvdOdAMKNUWq8Z0Rsf6tzq3I6QuH/YH3A4/tIIp3kDNOCRdPPH/HACD+s3+4/MFXtul6VOK3fwqemjh9G8No6cq/UkBYlQ+NqvsrNpc/cCIavzzSPfw4jR39/GcI7gkeHgbPfoXj+zuKNhXvHXP7nCTXDf2PxgoJ/jyXN3az/Rt2dj/VNnLRlyIGedxzqeY/vvj8S4HErNn8xumdVXDhuVaK6D1qpw4z5ae9pGNJ6w90oXmokeB4ApunBASlf3q+pWch/YhDEzvJ7E4NjadGJ8YqcAZeYqdf5MAXgWZ/PVWv0XrqrUdjXdiczBTksbAsdBd1BZmrVuF0aiLTseDgDKs/yK7w000gr1CgCSKuAH4BAkB09TPqZjUaGKBuRiAk1/gZev6j61UaOGPp6znj/rEFldQYJCMBmaePqV1nBs8lnNdOAjIR/FNHSOKk3jc0ii7Mun4ZWHMyNwXQpfwy6LtT9RXPtayDxVWXcnz0vHKzuuIg+c6ZVryEDxk18R42/QLG9neUTb2oztbrCTM4iuVhnaBcdF6NmhdVWCmtfanankjysGZ9lob87KXkwRDio9nn0HCp1c6kLj5rOuyng3qox8nBuCCEbVyb/BE3vRJbHO8DQO8EyjzvmKnpq
*/