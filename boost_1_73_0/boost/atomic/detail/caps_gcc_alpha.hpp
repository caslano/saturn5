/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_alpha.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

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

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

/* caps_gcc_alpha.hpp
7txTm0O3IyhqW5kkdi4w7Rfl7i46couz0XFpvWN0aaj4UktQdMfECNN52jMfA6Lq+y1h0Eep+gLOJZYdHc6JpZjWpcCdR4y9r+mJuPM1RVafVBPlBYU7S4Ccik3cubdz1j/Anb9pUX30XGe2wp0lgjuLgTuZ3JOAO693CS4DaE8Md3J+JODPj9n/6jTL2aqQaDHqWUIkymI2GPtfsRK+o5BoCS+9K9kMDvW3/7XNzPlaE4lO
*/