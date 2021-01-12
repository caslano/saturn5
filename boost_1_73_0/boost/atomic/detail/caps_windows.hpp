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
 * \file   atomic/detail/caps_windows.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_

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

#endif // BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_

/* caps_windows.hpp
QKGGVzSViCtyVXXsORMT+nysAvvjhjq0D3N74vYFaAyoa4K2L24ZWDsO28CzEX9G+FUnFNHKhXJVVD1/j8+nobJ5h2fN3XiGdWF7u7Ta3lbzeZ8c1P3Kr+Oo82sgYQdWUGxZqa/8vsxgyvayI9OtpAntcAbwZQRHHGPap0FPE/uwVZRQ/Z20q4Gvqizj92vbHVy4FxwxYMbEqw63cLAp+8LuYGxDUe/YducHAhnaaaEh3gvD
*/