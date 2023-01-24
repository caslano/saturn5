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
5U+OKuBlss/yQUj7FEs+2vE7ExXxlEX6BB/qjfMkP+iJGojx/LhWe+p2qXQjUHQgrpWSL+r5W681RUoL/Iwq9bsmrKNCNmYGzkDxN0/yz+D+yvyU+fiBZyceAcCi89IZ1CqajBQvNq9ceUW5m94asTmLaP/AKjOAJVlvqiUrUkcvffFdgkoeh3rAp7A6mndWXH6XFuIkcSyzuE9JCncLs06bOWl6mMZJ4KoA4fbCgvJNlVAyVvKjqWUQy2qQcBZJATiOJMr19oeFGwmSGWrYCebltf/HkBP0VWizE3aM2M/904iTPaIObKKg6NPE/AgMnyPKhymmYfJTq/hBrj3dG/sXRv4fO1KGn6QfsAE/hcLyB5tvZF8w+ZGZBogXQgzD6G88vXLzBXam8RFovtKwUAMDp8U/zFm/VAj6FMf2YMwv36Ji4OYmOm6QcSPSAV4d8mNi8TERAqyCxOnO7GQHp8OsBoHyYxeObLd8IKDcfL/e2ze2VPOBlEfuw9JCitBKFkvr32Vj/MjkgIyqJ//zTp56/tGyKGDqJJl5ZZOedk2N2god/RqP1qjFAdwkQv8o9wcpv2WtEWSN8h/o7FSWhqaLRgnVLoyIu6DFSrUhTu7qHBWHULnYt4MoXW9mR8e+dZ6XhmC+c3Fr0Zey3xCHxbm0DzJ9fEVCBkVp0wE8PF8430IZBx2XL12fdGx9FlmAbyGHiMtvIQJnfWek
*/