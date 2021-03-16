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
 * \file   atomic/detail/caps_msvc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

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

#endif // BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

/* caps_msvc_arm.hpp
kfk7K3d2gueLp6zi8oQsKH8vixjWe4djq0TW+EjVRcbCVsoslXnzCGWRi7FiHnoNthQqIxkzxQYFMsNAyK1jc1GW/bgbMwRag4v1wNJWKx1sXbxcDwYXs3SJx1k7pkF3Xr2ktV2PhgYjfIAQgxgilimyOgFjoD8WVaPCcmGmIDkYHJ0Omo5Icc0Mpl02nmZZhp6YS5ZhGLPerMxmqVSBiYJXnmXk1cKqhBtgXjJzcn4W05+mSsVGWDgW7dELyWI=
*/