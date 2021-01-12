/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2010 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_sparc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

/* caps_gcc_sparc.hpp
9l0Ay93DsuTQsLdoB0rbnl+f7irBI0pzUYKWbj+MSZfjCT+CPjD2N431LpMVKi3Yv+5oG4VTOFuJG76JMq219Y3k8IE7Uvet3rX8LzS8o/rhjYIWuua0F72H+h4MpFaivsxQ6lvGeuXutr/I+nLKAiILkgHYO5Y6Z0Xcv2Lh9mcAbt+V+zJrXtSKOrfl12d6sTCxzl4LB0PVGXMTH0pCZS3mPHW1iWhengx5udeooojNMbbH
*/