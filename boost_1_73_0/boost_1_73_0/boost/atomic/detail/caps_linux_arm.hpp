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
hbvtD3q+N+kNhr2JD4PzLq6c988mO4SGxwm99p444M0cD9H9UlPjoru8iJh2aaRcP4HwYAnv7RJ+bWqT8dtz55eg08wdrdP2jEW3XMZN8u3xJxxA/dxNuCXZ5pKaYw/VbPID6GNK7QnXdqTtx03vJMsojv4cj3IF7Xd43CERek5l4SvXJdgKnBUe9ljG2k0ytsN48XIzDIN9E/2PTQrOA2Tlaifb+Nu4We0MLW9U7STNVrH32PGA58EGkCyz/4zjk28IwAtymc7VeEy1Y6Xe4kitBkVBfCmxOgm/x7EQiYwhho3/JcxoXNAWzlmU2A547WXsq0KNTEi62KM2MxFuIqFybKrTdhqcBiewtO8erur00tE5xZ+TzROXd3RMxD3aIxt14g4PggCGyvD1biwkdjsG9zcv1JqUCs/7jkou3NxVkhhcqFs7GK223Z47eHBIOTZmcGDPeK3eX90P40EvbHkfXRBb/MF3gr7jjm2PvqPNJkt+9zyAZ1tHVLezeA7wwfnsAWQlUU2OOovzUkZWYa8Bdwj0vEu1dIC3Eu/E/JGd3vZ+NUP34lXnBnxFXhQ8J3Hn/k+PTeeKSHvBqrUN79xJlgFFmFavrdYvRrOiTbMQ7GSQcYX4ZSfeqAn6C7QVvhYxGgP1NYh2FagC
*/