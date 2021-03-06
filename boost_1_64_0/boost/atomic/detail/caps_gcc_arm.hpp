/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * ARM Code by Phil Endecott, based on other architectures.
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_arm.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

/* caps_gcc_arm.hpp
BhkjxdWa8At3f8NdaKjD6yozeZBQ9xoSngK1P21kJ30fSbFkpYMefe/2EMTqP6LT0qX8BWqDJC4IfoRJKPSKZtwtFXSqNeLMa4RnyDFRVL2/ODueA3i/y+PG/NGRR0Pi7Dmhd5uOm0/o9ljgmOOVj4vBZWqUsO5W+Vxtjvdia/hXSQFP5YHgI9GTHLUj6PiCgu03p9FM9upiCAgYPL8D+A7pdTPNKSjmjhQkX84zUoSY3s64DO1nP+fLyUmq313w7NcWDWhoxbfEEQg4rh4Tv4r4Ec6/IWp/4ma6+fv+izwnpkcnEEkDUdJnLczNhNGiZ3889vzKBIWkJGU2hsn28yPgGSqNLSjVAqdIBSbYHzTAT5cVTayrtyVuhkIBLQnfMDzflSuNfDgK6nHfiDSlQDuZF/o399QMa92h352KZEX70ehbnblAhTeAXHullbq2qnp0hicc2I/uPxzWcgIzsVt+aetIjKCeH1GPdsLRL3zh753/SJW6pfRZ8QVHfGHDDHaWFarLKeJOP1aSir6xmxPRI80fr0nT3VD5zM4zU76K5rxl/f4KRZysqA==
*/