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
BZ7Dy6OXRz6cCSUxhZlDtUCz9OEkKld+TcTtbc/iqQ/oQKS9jap5Ii1YHbuVMAj0nMoQlcUIhIUIbWjkgl6kApcgxDJFGE4vPo0n73xYJTJMWMlaF2ATXaQRJOIGwWCI8qbSkQvjQMckTsojaR0pLJzUqke2ERyazLIONi9Sq0HcCJmKBRkSDhLncvu63w8Lk5L3/UiHth/W4fcSl20j+UROZGINOnfgNBQWfWBOHzIdyZjvBAgt5sUilTbxd96QKRX1tQGLacq6SE6irdxGmG3g8ZkNcvJYOr5ZrSybWiU6u8NIOLKWuDCKDBEOxBRpgtmHQkVoSuYy8trEBtMS4NbU7PyNQCtyBg4GMxjPDmAhrLQ+fBjPf59ezeHD4PJyMJl/gulbGEw+sbI/xpMzSr0kYwbwNjdoybgBmeWpxGhj88dd/U7/EE7ORrPhKZs/0yuVahFRhtS6jNJyTVFxiDTF1K8LzIqMkEkMitIlOOnXKvqdzhOpwrSIEE7QGKV7yeneknVRKhf314xUy2otJuBjQmjy88vOE4AtT0EpclHJg4rqZE+ci66qPKJ2rBNOhlQayjoIE2HgkEj2r7/hDXztABzUtbparXqZDI3m3PVCnR34+2Sd0/7ShQmxp83yLo1Fl1ovqQgeyDFt
*/