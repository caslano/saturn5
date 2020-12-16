/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_msvc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_M_IX86) && _M_IX86 >= 500
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if !defined(BOOST_ATOMIC_NO_CMPXCHG16B)
#if defined(__clang__) && (defined(_M_AMD64) || defined(__x86_64__)) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#elif _MSC_VER >= 1500 && defined(_M_AMD64)
#define BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif
#endif

#if defined(_MSC_VER) && (defined(_M_AMD64) || (defined(_M_IX86) && defined(_M_IX86_FP) && _M_IX86_FP >= 2))
// Use mfence only if SSE2 is available
#define BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE 1
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2

#if defined(_M_AMD64) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif

#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_MSVC_X86_HPP_INCLUDED_

/* caps_msvc_x86.hpp
veMcSsr8+TNlboTV4rrsDhLuhxrubJ2TcZbOySieGHPNopmPcWlWcM1fy+e8OdchbvcFLBbpNefq+r29E0+8DrEr6xAt/NbbmrxJSUvplzKAVYj58dHiJOsKWzNP5AyN1z5dZ92fitoHtofPc52S0WZdYfS9IfR8vKvE3Ts+XQOr/kosWz4b+ZWxtnyBFbD3WMuKbZm42/bIl46z5Qewv7n5umyucTrcIGF+6DP7S4icL2Eu4hrrRH7UkymyxyqWa470JlrzPe3NnhOkwuw3YeKpcjBe3S3cSz21pI4GzpPMQ8rUuFnU8dKqirWWhpUBqyQNXklTtn1vx9jyn705Xq+VbPxVifsa4ttZ4jfMG7K7UOxqsZsqdjtVJpUSrzlyfdoUFEWkrLqUVsWcT5ltwqEY1db5AzUec12DmiPxyfR1II7pngZPezEnbE1zJvncA3fdxF2pL4WQHetZVwfTmmP8lDjStUrs6oj7FRL3pSoH3aaJ2+s7Sp6K3Uzc3ib5f7+vvTlzsbypwbFu9u9if4o1jzJue83KCKynriSDB3RmDRWsRa9U1neh/OLmtCi6JifkLjsDbc2nTGBnV8KE8L1IfgTTJN5J4q63cWeeB2ad7AN2fuGqaxR35vmg9aJY3F5EqS2WdmNHC+eDlpjzQeMzZkp8rNOZ4iZrxPdG2S9gn3O/ADXbb/YwoeyrWR6kfGMm5duc90rZwsyUrbAzNJemWqKG8um7l3I8YfSYZNqIFvc2Ebe0MJl6/yeL3CH+rjhPrP0Y1M8gK1PrzRyR4+NviovDLOgnsIOGpe3FUDhd3CXH2+GsNNce5jhfluuUlldWVVtmb4jvi5vrPdkiU8Kn2HKcb7f1Hc8V3r5R24ViJA3TtAvOfRR+P9kOY5zvBW+h5azrmVrXz5Zr/My7zDtK63vwuokx63tJcL+LbhbKT900Z942q5O29+MSXkJ4G9Hor2rgJN666tAZxQslrpUqe6znRW6v5w9r/Wwotc9K1XYnIu1y6zDTdv8d8T/Y94w331n/xX429lslvw/GjY/rJc+4BxOpI8nUU0pcqjc/NSE+NT5Fz9n9Gm1AX9MGBOry+qwAK7Ve+3NpqdDbslpuD7RNiHBjwjX2hGXajKXUt1+jkfmtZsoT1H/TVhyW/BjeYtuzVdylShuxrYU2YqWjjfhgmqONQO5zlpF5Easx7QZ184TtRjZm+42Z1i11Wxyl7Shp3nbIe+gE3O3Xd+KqBl7gtbwF91ui/OLHLr/aBpmzpU05k/0FpM5j/sssS+RSlScXhrdRT2gb5de9PS7U96uNZzbbH8Hsz5GYKVr3R2h5fw7n9ZanBSwS1EE8+lnC2Ds9dL2VawJb1LTX8u+xyv1rQ22iuk2Q+sQ77oneYafr/iDijrDIJ8KKOH+7oH3Asc/hsaEb9yE8TmvrGmK20+rWp3EKuOsd0TbPiHBHpFt8/9a4R5Y/8dvblL/w9/S4DpaoLvrOnK77J20bb9LD645zB6WY6VI/XWI+a9Te7IvS2Ip9UVq7z5EzTYc0TV01TRnBfcJCaWr1nlABP11jpkntP7Y0BevCLr3zp2qaOqGfzSWMUB+ixb2aAm5PjZkWtTdpaWhDWhLSW5+WnfKfNHi0zOkZ9k+H7o/usRN7z5e7JwT2gYr1bnuq2G+N+d6eqc/uCeJuHSF5reGkO9WK+Q6sz0PzLOTZ1fr9yvI17UMzAxY56DTVz2aR9kD7EWiTifPTmNFPWICs90/d4DP29XpMd94TwiD/CUPb+Vemm3berGMo9rZ9H5Do+6q0fT1E9HUJsfZVibXvSaz1CrH2YYm1jiHW/iwn74z3I7Ke44J+DcP2VPV57c7NX00=
*/