/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_ppc.hpp
 *
 * This header defines hardware capabilities macros for PowerPC
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__POWERPC__) || defined(__PPC__)

#if defined(_ARCH_PWR8)
// Power8 and later architectures have 8 and 16-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX
#endif

#if defined(__powerpc64__) || defined(__PPC64__)
// Power7 and later architectures in 64-bit mode have 64-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX
#if defined(_ARCH_PWR8)
// Power8 also has 128-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LQARX_STQCX
#endif
#endif

#endif // defined(__POWERPC__) || defined(__PPC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

/* hwcaps_gcc_ppc.hpp
iOHtmwImrFRF7zVPu7rZGXx8U8CWR4CCy6mQYyMhTgwyzkRM4+CQiiIUdlWiZv7OEV+mJ+TsoC/QMUAK+KW95Krfvu5S0KSMROPTuRr0hyN8/mGbNFDeSmeZzNV0lMny4aVIiOIwSs1yCWv6phE2tClg+qt0flVQp1CMU2VekjYEJ7TJ9XlJCu0ki3qVC1lBP8yQXfplcyb1IdemOuXQ6SwqvW76adPKXfTPmgjFCZOqBUvY0W3TX5nZXmp21TU5NlDW4TVIuJKhvw/bju7DJCgRKHjhnCcD6Gx5HBsrN7FnrQBaKjZc+j6kknwjgnTDApjCW/2QTX4fd0IOiu7POw70w9eiE8ppIiLr61qSiKB6mGSeMRv6QGHZFVbpALWYNWuxlIMAHzld3YgiZWdntc600AVlHDdF24DS/Hn8jZArONkE9rzcDLZNauxMo389bOmp2bcRk/1VypYcsZ1tCbLcF7Q7BpVl6g12ig0vVa0U03h0lC1C4fSZIhc2fDFKUKuf8SljcICXIyd/bf9IAXv9MtyyFCfiuQBoN0dN2iTSY/NBRUxN1TrOB9YcXtiftHgGu5NxoXe7sD/BSlXaXTwovFDaBl41ZdBC5s+V/Yc6Pt8OJzEd0slNAvfLlxT5eT5Dyz5e4TkXDrK3
*/