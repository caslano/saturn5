/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_sync.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if defined(__i386__) || defined(__x86_64__)
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>
#elif defined(__arm__)
#include <boost/atomic/detail/hwcaps_gcc_arm.hpp>
#elif defined(__POWERPC__) || defined(__PPC__)
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)\
    || defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_SYNC_HPP_INCLUDED_

/* caps_gcc_sync.hpp
Xaj15cyl53DmpJ3zvnaZMN977a3dtbduUmnMwXoC9pRlyHttpHaTTkuzXNXZZ+Lk3VamzZc7w+7mCzsFFmj7llYB9/+9inO6K9DupB3K1e6yrZ8jLeVwwJ6zmnyn7N2u2l2adeQ9Z7iXPWfkoZHjkRy4By2wbCR4PQ+VstFNysbuyf61h+rwZUPcdTBl40OtbxWybIww7rPMfsR3tf44K6hsGNk5f9X2UdZ5pE2oclH/d/bOBD6q4gzgb3dzkQOSEEJAUA4hIYCEcAXkCDdyhlNQJMQkSCSXyQYQUaCiUqUtVazU2oqKipa22GqL1lq01KLVelQrbbFqq61aWi1VoWqP//v229m3m12SVLS2fZPf5L/fXG9m3sy8N28usU9wlgvTDnctxw45nhZyMKZnWzmRZcG8v/xewunpGWP5nOXAlJVjYp/uacc9v9caaOYRWuVRy4FZt/aS+MvwfNvyRpYBs3byhfMD97bGSo55/98WN39qcc5ha+9/cMzhChlzsD64xt9+1r6BWTt2P1XdY/1Teh6sef+Sd1JRZ6DXe0LnufSEneBQmA2LYBf4OZW/rPItsCu8HZ4Cn4bd4PPwVPgi7AG9hN0TJsBeMBn2hv3h6bAU9oVSd3QdWB48CvvBd2E+PA4HwCSvrlODZ8B0OAgOhgVwPiyEK+EQ+Hm4CN4Mh8HbYBFM8gXkdGjLPeBI2AeOgZfAsfAyOA5eA4vhtXAC3AEnwhfgZPgynAbz4gLzKkfBGXAMnAW/B+fAh+AieNTin6VtKSzRe5CmzwOUnCOaBT8HO8MbYDG8EU6At8Cfw9s0v3fB38Ld8D14F/QR7t0wA34d9oLfgLnwOxqPbZbWYzg1VBaszRqPJRqPUo3HCjgQVml8Vml8LoKPwQaNl1/j1aTxuljjtQ7aF7tEy8N62BFeBnPgZpjlGLvaytjVHvRBdwzr/0bFoWs/xv5/WW2F/FtBDz7wBeCjfwO4zvENoEL3AFjvxQwugqsK6bPOl/7PvPGzJ5Xa1y6tLaup1D5uvTyLz29aEfoGoO4nIwf6sq+JPMgbOg+gsWpdpT6PjfsJZg38b0UuEvcXJcg67DLqp3m+vyT2I7zJen12YjN997fE7rQwv9WOvdi2LpA59+aZdrvIG1Rml8GF8r1C+s6ztV25Ttx81pNtnslNjZWlwTsR6qv+Va7dJ9Qnc6xr6Aw/EPu7VQ5dy7FP3jpL3WfAJ+S6PtN/fErkScQN2fg/Tlt/pRXM2yS9pu6PJ6pc3MXxjJsl+7Nl+UgTD+RU76bdKX0SvKntUvgXl2KHkYc598ffYIeh93OW+J9i0ZPV9weTNhPX6eKmr8rsoihyO57zszO66nU363V9m/6a0isl175mu4hrahnCnfjvr7LHOiJy7OtfL/ZZcr1gH7UpI6BXq7bfW0qsaMpzeabuhZcEZ3u8Zj4F5QtZyreYTYO9xU2wDI/MCNx36n5hQM5YEC4PiJCnRsjXRciPqjx0YEDOWRiSeW8y9XVbgiVqje5Xfx6st9+bF8l7s9TX6rqyCqm02Ify2jYwea3up5u87r7YlpOQg9/ezr/YX9loyiHuzb3OQv69yCXy/nydxIzun6O+pp0t907svb2knJ9vhb4xOcp/QyUUf9nwVQl3rifaO/ftEuZ55nvFTpHjJaz75TsW90yvUQKDZeJ3ncijzgGdmBkoEyuxOOH+iHGyPyJh8z1icaDfXdnQEOgfY0eeYi95KmZb4oL9a8k30zcm7ZiRdsfeD8QVM20/udcjJR20690C8hSVm7RsXKvyWpUfUnmhuk9bbPyHlZXDerDrcCz7wC5wNzdv5+JQWVnTUOWv1MISo6yo+4GmvX1SZNI=
*/