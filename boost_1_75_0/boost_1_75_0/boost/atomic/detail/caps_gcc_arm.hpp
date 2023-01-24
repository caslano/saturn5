/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * ARM Code by Phil Endecott, based on other architectures.
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_arm.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

/* caps_gcc_arm.hpp
/QBMqOCnHLlNj7Qa+OA2VRYsKh0esilbAYwqdLQbZR3TjD3/eS28qD7/UyAbTkW7qt3CAen3LgwFrKM49c5PXUo8gJq4Gjka+kRWkoWBzS2+7DYhggGboEUEU5KFhMIAg/3nQiVRqoH919D/80ysHZg0XM3ErY3tHC1dmViY2Vn+lcXcXd0c7VlF3d3cHB3E7SwZPa3NQHi2djlSzk/Nc/Ejf4NGZt5vR//O5Y5E3xmN75gd7tRkss4pabygcFc5MQlsrOfdyfSlcBY7PekOvztNbEMxOD+DtwGrbC0QpoXVwVQbqUYjWSKDUkEIJS7FWA+SkSUen74K2MllOomeU4MtubLp23L09LDw8LCw7O99H52zNfgYMpUNQOaxhkkZ6D6ToZmyMUXzqoIeQbm+LgNaF/N8Brz1y1yT0HQ43B/x6jSUcDBJVQhXiGeEMeMXwhsjDemFXlAEeFSNtl3ct/Tnf3kCRWBN4oLgGWGNcIMbN2sLjHTAsIAnAMarurp9kGK0gyfnFbCef/6j/ca1JuUcQSL7RxcpPHlGb86zQ8o+hQzGPgPqjbGAUtA3rxIViAeY6C00pCyxxCfgCSLYbP2zfZ75ldOsikkT4xfsZ9b1EU9aYXSz88d5tHH5NcN27CM6LxB/yP/4w/OKH3THd712635yjHta4AP9oUl6mkbwRZiub2sxlr9gIM7Jof+VcqyB8yEE0rvYtgsc
*/