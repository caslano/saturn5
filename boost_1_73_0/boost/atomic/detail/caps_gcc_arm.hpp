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
46VPOxQ1Iq5QSLRYkGgJ978+AQ7dSxa2c3AfHGqGH7f9Ozi0U++FQ58T9PAzhUOLTRxaIjg0k2ZP+8ehg86MQ1UlK2M4dJDCoYOBQ/Fr4tBrEnFoZpwYPyMGTe+7d0Yp6r+GQC+W30vOhEA7/paIQI0eIk5jxygEWnwmBDpDIdC8++W7yLz/4xBoZm8EmtY/Ah2/OQGBdsYQaIaJQKdtiCHQzj0m+iy55ZDo05AE7E2uJ3s2
*/