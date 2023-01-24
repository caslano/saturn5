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
WE2AYuFoKXwA3gxF+AduejmUdfrun1SzLEpn3AjRJu0XAFeyBeZAbYI/Fs/Jn+RjFcB42lSbCz9lejG/+osCb9WYMqae5ZFWd5YU7tO8F8R5fogT4dCm7al7WSWV1PORnqbMgtvk4J1B5Igqh001Do8NxZX7h+1xf77FfX3Rc5TG7RtTCp2zO13HJ1x2VU44Qy1YmSoPMYMz0TPNnpDZhdtzg/a6F+ZzE6tDuasz5l9JMAf+Qx6AfjaQzPaTy7T54qxtwrHMH4fEDlz+sHRx04OSp6QeEKZ09KQ7LELzuiXg6RE2mvpWRSkuJia6Yzr1BQRwCpMtQJri3SZbscJqmxlNlL31b7QzJHMXu7dOCVD0lSA/Kdz1ZCSfT5cm0IkvVYnjaJqb51iuLiFwpUAORstTn76q6bGM6lE8htTu5FJEMu7TPZ67+2D2izyxrJtkyn415HllyMysO6XkFZCoVWs/NU8+P/IJM6icW7S8ULd4b3VqPsMlYM2hMrXUcXmXg7+xbUHEzFL2ReqAu7gfhOQqnpVxZnAQ/qw/+kRswO5q8BfSGfQz2Ibga2xDbfWA7X/5sY3agfh24xsIaTfK0p1gA7n4SZAzllp8QvvHRslBOItp2HAX84X+A1HzkfDwjbEkcbF+oQrDCx9UjMuPnocw6Z0RFGpZJHj2N80J8G/FRTbj7IrRronS542khCZKe1qbdvkS6hjWzxKX
*/