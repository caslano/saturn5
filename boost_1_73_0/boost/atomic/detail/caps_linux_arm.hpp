/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009, 2011 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * Linux-specific code by Phil Endecott
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_linux_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_

/* caps_linux_arm.hpp
sQjlL4Nj3GGVqMkOdRPAhslu2tsDpx8/QibvFvVqpg/f6oC5J83abmaQEM9qm5d+9+t9qk97uET6yiauVkUhqNbKLyiSeTE85hetdC8dE2/NTb/9aGuahsWbJPsqIJ6VlbCiYzDP2kXVw3H2lqKOJce1Y7AgnKOyu7Ya+XkwrMry9wAVen3X/VxOGpwNK10Y6sGaUz4g+3afvvshpeDkXNiwwLGg3WEXj55tq9552JJ4fnGD
*/