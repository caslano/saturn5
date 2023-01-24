/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_x86.hpp
 *
 * This header defines hardware capabilities macros for x86
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

#if defined(__i386__) &&\
    (\
        defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) ||\
        defined(__i586__) || defined(__i686__) || defined(__SSE__)\
    )
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if defined(__x86_64__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif

#if defined(__x86_64__) || defined(__SSE2__)
// Use mfence only if SSE2 is available
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#else // defined(__GNUC__)

#if defined(__i386__) && !defined(BOOST_ATOMIC_NO_CMPXCHG8B)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if defined(__x86_64__) && !defined(BOOST_ATOMIC_NO_CMPXCHG16B)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif

#if !defined(BOOST_ATOMIC_NO_MFENCE)
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#endif // defined(__GNUC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_X86_HPP_INCLUDED_

/* hwcaps_gcc_x86.hpp
g/uWdIqLBHnwUw1HRHYIn0n2R7Kej6ONjPyc8zkFYfW5GVOvO4AUCPbYDquW7k9cdcGUVQ5RI7DWzw5tj6u1DDV1R/ZxPoxkg1aa3wsPVkjCeN7iUk1YhP/wGiclre/O0TWZtimcrrl7ctUyAeuOI1monlxc15G57MN6pwidmWCYolKBT3Vb6vMBaRHl0tz7udjjH1qEz4K68makV4U0GqGaHAatA/ivw69KsYVLhp+MilzCINPJ7jo7rasdRuHSznop1iWnSQj2+JWAsYTvsm6/CfUdasHtpkkzt0zj7UtzZ5UvZl887WC+Pp70MLE31BI40VnW3R4JttO7Yt1Xy9jXirQrdb2vxPYGyx2uHJyWqDkUmwaikhRrPwIEC55j1GYST/MB1Fa0JPpJMqYjmgssNbsi6TG1XuXv54jvRO7OP0z1ldwtlu9AF9tT9fmBQpaRwexatmSuJDEM5bxDxcpw0OgFTZusjAGd6WZCS/oTjmF0q9ssim3QcUR0H7GxR1xKdK5SQ7GI7TL4/DyiZ7mYTwFJy20Z5YS9hDTnPuryAz8kQ6zFGLQwakcM7Tagf/hVED1oBHEJnV/JoFwrCa+Xw9t0zr0ON+5EXOTe2AYNSD3VTRzhRLEqXV3l0N3RJNXTLDkL3J0IXS33bSfMmnYoSOIJ71XK2EUrSBH9SBYw/volj5/FP3jK8ShHpdztvr0AsXQpLnOJE/fH
*/