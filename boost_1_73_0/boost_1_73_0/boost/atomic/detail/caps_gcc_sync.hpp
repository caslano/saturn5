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
BJ2oMo0hYXccCh5xcedgclYYUHNEQPxYaIOYpRFKBmieg+FFpisYcoKlWgG7YyJlMzTHDCTG5Pr14WFUFilGchirSB9GdSqCxGQ7UV2jNxlbgcoNGAWl5j6QvA+ZisWcrpgifJiXs1ToxF+7hQZlfKgK0DxNKzhUFVy7EDiEVbZ8koQcvReGLlpJTdaWicq2BDGtFdC8LCSaw7SgXKww8T6UMuaFlbeJqK1UWbYp/07J1r7HoCR6Ba1uCP2wBTOmhfbhY39yOfpzAh+7V1fd4eQaRhfQHV5XeO/7w3PkhkCrBfD7vOAavShAZHkqeLxl/Id2uhdMLoFq2o6UnIsFHEHr+AWMsIePO53TFrTOcBFOgyP8xW+bohmTJUsRIryEYfdDz9tcvGnDO+S6kHNVZIyYBmymSmQ/0ntGkrimDUtTu2hBwuvhaBz2Qy94u+XTJ+QQyujPVuq8F55d9ceT/mi4I+hhFfKUrfQes1RPa5UIs8+DwIKPLC560B9Dq92OWMs7r0EJYlaK1LSxFXNmEmKQ5UkXIo79NUMeYbfYHqtNIO910MBFO3CRynIkV0FilpCE3/i31punbKFbXshtEzdaVV5wEF0Muu/Cg6rRkP5cVlJCLix/yR62Ma56NTpgaQsuTbpya+i1kvYL
*/