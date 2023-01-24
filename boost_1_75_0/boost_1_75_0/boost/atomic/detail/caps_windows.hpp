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
u2BQpXfQtPiktCaXGso1T5Tkhe/3JbyGGi05TKpJsoj58Cidady5baU4X/HUiqu3h8g/zYqQ3bSC+lsyvKs+4Pqcqf/D07Arg4SQF9UqPlPQIlqCwoMfDVHcVA+IclWHlJ0r2Mlr5PlaJGjbq2Imj9pvom2WDLTYuHRy2F632Wn6s61zTLex2NXrNh630gRqAyG12HusVdtny/DQYVWeNf9Wq8NdP4hvlfDeZ1jeIxGfaxFyf7NKbi9rXdk4fwwjqzWQPgi1vy9b1Bhha00Uhqd/ytrTWn1xUWf2YoY4nvLRNo0sqnP2lNC2rjRQP1m8mBkACM9bcX1gcmqzyPRz/CqgRYETRsPkdJTq6L4SLjZ4UUbF9IYIMA1GSq59mZwSE8Ll184w1FVrDfw2I6zv9QG1yu70uhQy76i3WAPLdJ55s2uX2mY1dGxCoAj7lCaYC1Fz/8G5XQVFoh1hAF78stjiDguLXGBxt8Hd3d3d3R2Cu7u7u8OyuLs7g8PA4DKRhyQPqaQqVafqVL/0+/d3dx/DRabyom6itjS6eKfa7robQqXnkPme0WkMY4fANxYMw2zbFOXJoffzotyHRkkJ5W6BM2SJn9iN7Orsl26cXdYEPeIt8xZthEocn6LUDun1vCVgJbl1FJf8mCMPckY/xYzdgXclmMe3OMLBcfHLBQQ0FHV9V6wT3r8QmXfwGmtOXLAH30p+jT4Ow9hp
*/