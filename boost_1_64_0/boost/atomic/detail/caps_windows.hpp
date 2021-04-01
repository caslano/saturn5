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
hQkQiG6FO9fcVwyXBnxIB36oaRnmBZ+tKkBlAuLDw7B0E4g2wqf6BmBisGDBMMkDRR9xxWNrh5eVcnSLRvQ94vxYtU/Qhmgbe9oQsF+Yf7cI5Yz0z4qM42WAHTRgINIRv6eyHK9jTofYMFc81GFeI1GLs/pKpYKLwk6UaYxyBNKbJhKiPez6V6mfwkGjQr7P5RHEkfMflrNtJO+rv9wVWau7XzfEGArosEDF+E2Mtyig0T+CkCRQUD5n8jIEY2VOdlSJgmRFzVZc7bmgVYfbZb8H9vup6xEmMQ9HgKNDedvrJcftrqU2HCW3ugoMgEd7vSBKM4ckPE2nuYiVKBlhxC+cAxSVMWxKU4RsXjjA8RpFQAulNrrXIxsg2uC6E5mzh3PA1IX0nsyw2WkyAuzi3vTu5aMT1YwTx+UypFIHb7rnoLvooq46to9cMBFSSVyUk1sb9tGz0gJ55sjRg5fPohvCLCEkbZ6rKd3SKUjVWV3D4pek1dazXFGT7i5O5ZGUd7BGp3/tEt8zsncrR6bZIGJnbu9+PGjf9TVmcRBtaf/B7TnDVT3syQrvYg==
*/