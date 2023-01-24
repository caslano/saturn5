/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_arm.hpp
 *
 * This header defines hardware capabilities macros for ARM
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH+0) >= 6

#if BOOST_ATOMIC_DETAIL_ARM_ARCH > 6
// ARMv7 and later have dmb instruction
#define BOOST_ATOMIC_DETAIL_ARM_HAS_DMB 1
#endif

#if defined(__ARM_FEATURE_LDREX)

#if (__ARM_FEATURE_LDREX & 1)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB 1
#endif
#if (__ARM_FEATURE_LDREX & 2)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH 1
#endif
#if (__ARM_FEATURE_LDREX & 8)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD 1
#endif

#else // defined(__ARM_FEATURE_LDREX)

#if !(defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6Z__))

// ARMv6k and ARMv7 have 8 and 16-bit ldrex/strex variants, but at least GCC 4.7 fails to compile them. GCC 4.9 is known to work.
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB 1
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH 1
#endif

#if !(((defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6ZK__)) && defined(__thumb__)) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7M__))
// ARMv6k and ARMv7 except ARMv7-M have 64-bit ldrex/strex variants.
// Unfortunately, GCC (at least 4.7.3 on Ubuntu) does not allocate register pairs properly when targeting ARMv6k Thumb,
// which is required for ldrexd/strexd instructions, so we disable 64-bit support. When targeting ARMv6k ARM
// or ARMv7 (both ARM and Thumb 2) it works as expected.
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD 1
#endif

#endif // !(defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6Z__))

#endif // defined(__ARM_FEATURE_LDREX)

#endif // defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH+0) >= 6

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_

/* hwcaps_gcc_arm.hpp
izUFwue+KZBjUEG4dpLN/aFvFH6AybWOS/gnOroM8KUqulVAssIoltLk7F0B1sIP5RiZIFNBuVFXu6E55fEgPL2PSlPdYllRP55iKpPzhLwsRTeT87n9EO0tPKTqjdMMZkO8Lo4k5iWw/0MKujL2j+Lq+V5v3eXWowoFGdrXlADZWP5jmVwCdQz8JQ5AonSV1A+egnjz38zDmVcHgx25KJZdBKzKr6qu5TzsJXgma5QiCpSiq8UnKq5otKjVUYj369ftag47IdRKFP3PrFY/2BnE8aXMwHgbYqRqKGSclxI4O29GvO0GrBhVlIwlZ1bD3n9UUKfIDvmD6SwrQq3gfb6fGakpFDfpSTuzFcdUdbe0BD3e0lipgY33YM/R75UtKfIQYE782DIXcjG5MmQJpcmdDOeySJWI5sWTdX0EZRQoUmgAV5aFkcypiiLSsqXBkY/Icj7SwFLAtGQ+wPvsPJWzqE+VnMRtcv7Rwk+apfL8r5RdVVAbChYtvnjxAgVeixUvVgqBUNzdLbhLGigOCZQCpVhxh+IPKO4a3N09uENwD6zMzu7Mzs7s7Of9uPZ15py5Z+705O8fHpb70cCGe7KHfYbnncVo+LORQqwhzuLOFZuXYmS20jDyVeretw+pExQ0FQtzw/KL4xEECUdKKiGa9w2dKmGGGD+yk3u3ofzpUeF3CuArzzuR5qaVFQ1wP+3feDVgy87z/Ti1
*/