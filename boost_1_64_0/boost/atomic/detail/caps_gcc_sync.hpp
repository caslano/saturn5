/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_sync.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if defined(__i386__) || defined(__x86_64__)
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>
#elif defined(__arm__)
#include <boost/atomic/detail/hwcaps_gcc_arm.hpp>
#elif defined(__POWERPC__) || defined(__PPC__)
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_

/* caps_gcc_sync.hpp
yr6pbVHDqxLj0i69ISjIGONZvATXhkqwkqMAvGJghDgO0C5mheggZr7M5DmVo01/Om9jg1a2QXBmbk8uMwTK9vJI13CmDZx/+D5giidKrrl6z4+f0fbzuPK8WghIMD7zE1wD8dImINq12zSCEfw4vCEDPDiSrFOrjvauEyzRW3JBjrqkffr6YNe7WL0kluVxv8oVpCRNM/214bGSDyVcpujRw8GmLvHf32U2/JhloONmz4/E5vdjjCp1397ZnzHUf7l8PuWY70EesH5o6TSRRrQTNC6Xmsf8bMQDAMEk9kH6GyFvVGuZN82wDV8S3+g0HuGA7rsVTwuxMVIld109CGgidbEP78t6WDQXocc96utLu1KBeoJ6EzeFsPGPiajBWuQsq+fWWpKj1a+fDDF82yE1BxdH9rI58FiUm60poaUzyARneTn3kLsorkBH95sp1rDGTVS5UM/wRzwQzg8pbey1JCZlT36p42HTT7KCuNwjAZqZm+fxRzKVtzRC2ar4QheAvZKhzW7CBPR0w9xoPWrHf0Be3hz6wRt5023BqElBk1mkTv7MbMEQxg==
*/