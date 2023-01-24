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
BbbEQaBqG9Q+pfrIwJNsbuRsSkVkeRZK7djvWYwFNXR2DaU7Euom/uGuptqitOUmiZpEe2Oupj/8qzdyeFQMKmVN2oLYTaV2pBsTdjWEU+p2WIKrTTZPvB/AaceMV3m28sIk/XEs5tTl5seaSHvzAlUL3lOLWOrlTSCeubeALsDBCD8jtbWxswaiMK3WyJY7V2Mdzx0ypaYL/HcBk/GRHVL2XFrzcs0vewsGOxZ6U3U7It2x8zXetkiO5iENv5St2TdtYr7wTjTdKqr7vTtF80+zsxLLqnoRwI8vss/Tl4VbvF7JnUGPO8S+hEexqocARXgnc3BNQhXMMkP5I9rMzBvq5/tqf06hOb1vs66wP27ZRISGPHEnjL0pqUYaGQMzpSzaZLcWxmT0fiUhhMYOK7FOGVuTSKzYs/0RW0M50w2/NwV+j/Ey+645eKDvH22wTcJPT+3mAyjgtOc9ViLdnpv8p+MyL/351jNzt2K8D17MczV885Bqjh3Gnm4EOtOvu0zq/cOvyx1/Ia7ePXToC8XOef/uNzAsDZRzHNPBtXiLxfLKmZRvuWHKU9T3dv12eiR/1hwIb915QdxKd1Ab6WXYOgmAGsm9Khfe3BOE2md88SW5CvmG2FfoSIvs3rWgugoQkNv8JjJaikiL6GuNus6tZqGyuE5HxNHkIhGKGskugKtBq8dcd7K0k7Jxc/TLiPQ9PpDbZNoZD/1A
*/