/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2014-2018, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/platform.hpp
 *
 * This header defines macros for the target platform detection
 */

#ifndef BOOST_ATOMIC_DETAIL_PLATFORM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_PLATFORM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__) && defined(__arm__)

// Newer gcc versions define __ARM_ARCH. Older ones don't, so we have to deduce ARM arch version from a bunch of version-specific macros.
#if defined(__ARM_ARCH)
#define BOOST_ATOMIC_DETAIL_ARM_ARCH __ARM_ARCH
#elif defined(__ARM_ARCH_8A__)
#define BOOST_ATOMIC_DETAIL_ARM_ARCH 8
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) ||\
    defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) ||\
    defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7S__)
#define BOOST_ATOMIC_DETAIL_ARM_ARCH 7
#elif defined(__ARM_ARCH_6__)  || defined(__ARM_ARCH_6J__) ||\
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) ||\
    defined(__ARM_ARCH_6ZK__)
#define BOOST_ATOMIC_DETAIL_ARM_ARCH 6
#else
// We are not interested in older versions - they don't support atomic ops
#define BOOST_ATOMIC_DETAIL_ARM_ARCH 0
#endif

#endif // defined(__GNUC__) && defined(__arm__)

#if !defined(BOOST_ATOMIC_FORCE_FALLBACK)

// Determine the target platform.
// The target platform describes the compiler and target architecture. It can be used by more generic backends, such as the ones
// based on compiler intrinsics, to implement specialized operations in a non-generic way.

#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_x86
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_x86

#elif defined(__GNUC__) && defined(__aarch64__)

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_aarch64
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_aarch64

#elif defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH >= 6)

#if (BOOST_ATOMIC_DETAIL_ARM_ARCH >= 8)
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_aarch32
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_aarch32
#else
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_arm
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_arm
#endif

#elif defined(__GNUC__) && (defined(__POWERPC__) || defined(__PPC__))

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_ppc
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_ppc

#elif (defined(__GNUC__) || defined(__SUNPRO_CC)) && (defined(__sparcv8plus) || defined(__sparc_v9__))

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_sparc

#elif defined(__GNUC__) && defined(__alpha__)

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND gcc_alpha

#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND msvc_x86

#elif defined(_MSC_VER) && _MSC_VER >= 1700 && (defined(_M_ARM) || defined(_M_ARM64))

#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND msvc_arm

#endif

// Compiler-based backends

// IBM XL C++ Compiler has to be checked before GCC/Clang as it pretends to be one but does not support __atomic* intrinsics.
// It does support GCC inline assembler though.
#if !(defined(__ibmxl__) || defined(__IBMCPP__)) &&\
    ((defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 407)) ||\
        (defined(BOOST_CLANG) && ((__clang_major__ * 100 + __clang_minor__) >= 302))) &&\
    (\
        (__GCC_ATOMIC_BOOL_LOCK_FREE == 2) ||\
        (__GCC_ATOMIC_CHAR_LOCK_FREE == 2) ||\
        (__GCC_ATOMIC_SHORT_LOCK_FREE == 2) ||\
        (__GCC_ATOMIC_INT_LOCK_FREE == 2) ||\
        (__GCC_ATOMIC_LONG_LOCK_FREE == 2) ||\
        (__GCC_ATOMIC_LLONG_LOCK_FREE == 2)\
    )

#define BOOST_ATOMIC_DETAIL_CORE_BACKEND gcc_atomic

// GCC __sync* instrinsics backend is less efficient than asm-based backends, so use it only when nothing better is available.
#elif !defined(BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND) &&\
    defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 401) &&\
    (\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)\
    )

#define BOOST_ATOMIC_DETAIL_CORE_BACKEND gcc_sync

#endif

// OS-based backends

#if !defined(BOOST_ATOMIC_DETAIL_CORE_BACKEND) && !defined(BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND)

#if defined(__linux__) && defined(__arm__)

#define BOOST_ATOMIC_DETAIL_CORE_BACKEND linux_arm

#elif defined(BOOST_WINDOWS) || defined(_WIN32_CE)

#define BOOST_ATOMIC_DETAIL_CORE_BACKEND windows

#endif

#endif // !defined(BOOST_ATOMIC_DETAIL_CORE_BACKEND)

// Waiting and notifying operations backends
#if defined(BOOST_WINDOWS)

#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND windows

#else // defined(BOOST_WINDOWS)

#include <boost/atomic/detail/futex.hpp>

#if defined(BOOST_ATOMIC_DETAIL_HAS_FUTEX)
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND futex
#elif defined(__APPLE__)
#if !defined(BOOST_ATOMIC_NO_DARWIN_ULOCK) && (\
    (defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 101200) || \
    (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) && __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 100000) || \
    (defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__) && __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ >= 100000) || \
    (defined(__ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__) && __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ >= 30000))
// Darwin 16+ supports ulock API
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND darwin_ulock
#endif // __ENVIRONMENT_*_VERSION_MIN_REQUIRED__
#elif defined(__FreeBSD__)
#include <sys/param.h>
// FreeBSD prior to 7.0 had _umtx_op with a different signature
#if defined(__FreeBSD_version) && __FreeBSD_version >= 700000
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND freebsd_umtx
#endif // defined(__FreeBSD_version) && __FreeBSD_version >= 700000
#elif defined(__DragonFly__)
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND dragonfly_umtx
#endif

#endif // defined(BOOST_WINDOWS)

#endif // !defined(BOOST_ATOMIC_FORCE_FALLBACK)

#if !defined(BOOST_ATOMIC_DETAIL_FP_BACKEND)
#define BOOST_ATOMIC_DETAIL_FP_BACKEND generic
#define BOOST_ATOMIC_DETAIL_FP_BACKEND_GENERIC
#endif

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_BACKEND)
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND generic
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_GENERIC
#endif

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND)
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND generic
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_GENERIC
#endif

#if !defined(BOOST_ATOMIC_DETAIL_WAIT_BACKEND)
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND generic
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND_GENERIC
#endif

#if defined(BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND)
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_CORE_ARCH_BACKEND).hpp>
#endif
#if defined(BOOST_ATOMIC_DETAIL_CORE_BACKEND)
#define BOOST_ATOMIC_DETAIL_CORE_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_CORE_BACKEND).hpp>
#endif
#define BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_FP_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_EXTRA_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_WAIT_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_WAIT_BACKEND).hpp>

#endif // BOOST_ATOMIC_DETAIL_PLATFORM_HPP_INCLUDED_

/* platform.hpp
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
*/