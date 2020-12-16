/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2014 Andrey Semashev
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

#define BOOST_ATOMIC_DETAIL_PLATFORM gcc_x86
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_x86

#elif defined(__GNUC__) && (defined(__POWERPC__) || defined(__PPC__))

#define BOOST_ATOMIC_DETAIL_PLATFORM gcc_ppc
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_ppc

#elif defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH+0) >= 6

#define BOOST_ATOMIC_DETAIL_PLATFORM gcc_arm
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND gcc_arm

#elif (defined(__GNUC__) || defined(__SUNPRO_CC)) && (defined(__sparcv8plus) || defined(__sparc_v9__))

#define BOOST_ATOMIC_DETAIL_PLATFORM gcc_sparc

#elif defined(__GNUC__) && defined(__alpha__)

#define BOOST_ATOMIC_DETAIL_PLATFORM gcc_alpha

#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))

#define BOOST_ATOMIC_DETAIL_PLATFORM msvc_x86

#elif defined(_MSC_VER) && _MSC_VER >= 1700 && (defined(_M_ARM) || defined(_M_ARM64))

#define BOOST_ATOMIC_DETAIL_PLATFORM msvc_arm

#endif

// Compiler-based backends

// IBM XL C++ Compiler has to be checked before GCC/Clang as it pretends to be one but does not support __atomic* intrinsics.
// It does support GCC inline assembler though.
#if !(defined(__ibmxl__) || defined(__IBMCPP__)) &&\
    ((defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 407)) ||\
        (defined(BOOST_CLANG) && ((__clang_major__ * 100 + __clang_minor__) >= 302))) &&\
    (\
        (__GCC_ATOMIC_BOOL_LOCK_FREE + 0) == 2 ||\
        (__GCC_ATOMIC_CHAR_LOCK_FREE + 0) == 2 ||\
        (__GCC_ATOMIC_SHORT_LOCK_FREE + 0) == 2 ||\
        (__GCC_ATOMIC_INT_LOCK_FREE + 0) == 2 ||\
        (__GCC_ATOMIC_LONG_LOCK_FREE + 0) == 2 ||\
        (__GCC_ATOMIC_LLONG_LOCK_FREE + 0) == 2\
    )

#define BOOST_ATOMIC_DETAIL_BACKEND gcc_atomic

#elif defined(BOOST_ATOMIC_DETAIL_PLATFORM)

#define BOOST_ATOMIC_DETAIL_BACKEND BOOST_ATOMIC_DETAIL_PLATFORM

#elif defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 401) &&\
    (\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) ||\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)\
    )

#define BOOST_ATOMIC_DETAIL_BACKEND gcc_sync

#endif

// OS-based backends

#if !defined(BOOST_ATOMIC_DETAIL_BACKEND)

#if defined(__linux__) && defined(__arm__)

#define BOOST_ATOMIC_DETAIL_BACKEND linux_arm

#elif defined(BOOST_WINDOWS) || defined(_WIN32_CE)

#define BOOST_ATOMIC_DETAIL_BACKEND windows

#endif

#endif // !defined(BOOST_ATOMIC_DETAIL_BACKEND)

#endif // !defined(BOOST_ATOMIC_FORCE_FALLBACK)

#if !defined(BOOST_ATOMIC_DETAIL_BACKEND)
#define BOOST_ATOMIC_DETAIL_BACKEND emulated
#define BOOST_ATOMIC_EMULATED
#endif

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

#define BOOST_ATOMIC_DETAIL_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_FP_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_EXTRA_BACKEND).hpp>
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_HEADER(prefix) <BOOST_JOIN(prefix, BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND).hpp>

#endif // BOOST_ATOMIC_DETAIL_PLATFORM_HPP_INCLUDED_

/* platform.hpp
e/aW+fm/Z2/VvbNR266sbvLqttqCnkE/obagwXsy+YzzVsg7zrcINfwtnlzXt3jMXkwOO9OsGPdnsuPOd+/7pO9OdxG5zPd8zD1H2UH8J/Og9IWwEzyEjCt3+dxzGMv6QLt6TXeq2b/kH+KvCUXGlZBjXBlu4p9s7tG+Ef9XEv+WXmb/UHNv+aWE7wrJ/YJJP9i9Z6gZp2okfGVok3WT3hNE0mSZcWvZd7Z/UuC+vb0sSWNs4qsTfPZ103vjDyTeQ6FnrOdN+kxX+o0Jrn3ddGz4XGUze7i50m1J8Hn/Q+8/tkq8uDi/fT8m/8MOSwxlMH4cbz2ox9GsyJ3PvHgPNJhgbEjPlPhLQ677CrNn6CgJPy0kfvS3XPI51G+fTXP/cKCk6WqeIW63/eiog9q0HiP+ZaHulLM/d1GloQSNG7k+uX77t5j345ISmdNrVdv/xi9sn9jVdL/tAm3m3pVzNje2u9Xi78CI3jzQLn69xOkufdpp9GmtzT6aZm8Fp9/sj4ktkNkj83ncq7SFVfDo7nV7hJQ0sEdItmM/zCe+q99PVSZ4+6k1HEuWvoA2p8eqOEa7qrfX5boE716X1HHnXpdyjHrr7uOok949RcxeIS478fRkf5v2iu9bxWzTTtyoNu2Lvm+1VzbtA7SsVZo6FXeguhS7X6wta+k5jm5xxtwC826aeVYyZdY05GTGTb3evRooX6ZrnJF+W8uX2dpbvpbErfYpX3HBeVOLy2fNIorjHq/hMoi9sJ5vvc/57IfkGr/zlc8WXbTy0UWNSxf3x1COiC5aGV3Uv1YrUrxlSyJu8m5v2UrKSwuDr5WmIae68arE1L/hjnBzb9WI8juvpY712j5LPPWvrI1Xprakz/SRad60WeVUwCCda5pUx/hWlD/f7KlYF27u2RohU901ce8DYp9j/7cD/5u+HThcbH2fn/lieOGLfSfOWvhw3Ovrlmft/3ag2gyLTe8IS35yH5EbJ+vQ8qzUIkS94O+nHX8/7vj7KcffT0T+Nra+Oq+p87cVbhtcS21w4RAZH9UG11IbXEttcOFl+t3BZfrdwRthV12rzYrXOTCdO7TPU2CJrYX8eqkNVW94KvwpHKM2j+NhBpykNo9nwmPUBvJnet5+8FdwALwGDoR3wJPgn+EguAUOV9vHCbA7nAj7wlz4MzjJPj88HU6AZ8DTYR4shmfBBbAIVsCz4SVwFlwOi+FdcB68F54H74fnw8fgBbAK/hy+AhfAavV/DSv49x38ha6ZXwK7wKtgV/gr2BMuhZnwGtgfXq9r69fBU9U/A94IC+HN8GJ4K7wGroTXw9/Cm+Dv4B3wbngfXAUfgffCJ9W/Ad4P31H/R+r/GI6En8NxcCccD3fDR2CIa/wojIePw0Pgk3AwfBoOh3+AOfAZWAJfgufB1+CV8A14F3wTvgnfgtvhYPgtHAL/AYfCH+Bm2J42+T7sBf8K+8AP4dFwLTwNPg8vglvt6wg/htfBT+AdcBtcBT+Fq/X4c/Az+BLcAf8MP4evwxq4Df4d/gB3wrbhWtvjg+FX8Ci4Dg6E6+Ep8BU4Gv4RjtfjZ8EqeDZ81tjI6nOXPhdXuGxkv1MbxO+1HYXURjQOngHj1YY+AVbAMLwEtoI3w4Pgo9JHc91ha/g2TIGb1eb+72pz/43a3LcN0c5he9gT5sM+cD7sC5fBTPgwPAo+AvvDbTAL7oanwpZx9HF2PnCk2qyPChnbHL2/lj6I/m/vbHPSLb331fsY+kT5u63mt9sRrzrGeDUxxkveHVu8zAbiFTbSlmP/d1z3f8d1T+0y/p9tMqrvxB4D12ll2BqCm4JbgFuBq8JtWbnvbS5+pPV/pmT2/vt/ndk=
*/