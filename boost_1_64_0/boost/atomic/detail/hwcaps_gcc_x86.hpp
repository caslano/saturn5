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
jzo357t+haKRLR9R7lqGrJjWKmym8hQamamEv0FYklhHyR+J2FhnTRG8BDtuTdUM7xwd4h+8aexhn6rzWR/RTRKLMtZ7VwEvkhs5jkduz2CnCZNhF7DZGuXjUvPbpqb1uoglRvEQJFu9Kc/6emdSkGTpR31lR1LhlN2/vXbHv8mB0NbwQosTe9/Lw6hYMlb2nKtReXUXwKN85Ib9l4Um8+YcTbIWzNO/Q7R/7xQVDuGOe9HWdV4fvb20OS+fHXYcylInPR5vhRIMBSSHMe/uTA/hWUL46GWCLSnPucuLKOd7zY5cyFwoMH73/EbylfPyPaQouF9oCVHd0TEhbHw8ysY/gTSRztHWk2HnuM9a2reLfS11k6jneGAhfDR3tSacy4b4TvwkdX+piKhNeTJpdZx4+9hAuYIyVyxkCTeUTMTZe2OXyB78k8I7d//7ZwO1kX8lNKvynbNpa6EWNvvX8P8hIl3SBt/BHQ0PUJxFNO6WFVDYkMoNnFd/cbIDMoYd4Ba1HCdU1XM5Y843utvthCo9ouHBl3SdVEPRA4rJZNUoLueNUWKMj6OAtg==
*/