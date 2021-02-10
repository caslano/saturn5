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
 * \file   atomic/detail/caps_gcc_ppc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

/* caps_gcc_ppc.hpp
NNS0zffCiJdGZIjVa/IODQsP6GroypR6wPcqixfXrpGQXfRSw8Qs3YcRQrgSlluxqXU7pzcFxCV0j7tzwLciL8bXGCNvLK6alIup7LHe21FdnNwAh6pbLVzXXOiip8wadu8b2o0R37ASHiJsZbuKT46yKdCJzshuctCohOCI95hM71jlj5mEUJmpMqjr8YuoS6VhebCuhkDjOOSHtVLeybpN5QxbI9gVPUzgK+sh9o/MwVFH1Pjn/e7oOQll+16ndwQ4Mm3o/f3QS09w2ie/RtviVTs+GCAaZL6EY5Qgf6cXwNwChm6OnbPXQ7+2q7uloLJrbtFwUs2neagXNDQGl5lmN0DJ+Jz3yOsRjmEM604qM5d3g3mPCm22esSfj+OGb0nce4q6D1KEv3t6ijPl8Olpa9sf1jK9PMVnqN3MXsb4k96o8/kdq84v2fmi/zRIomM78HIdn7rjhDfazZM0vJaeEx8X2P8AUEsDBAoAAAAIAC1nSlJHA8V46gAAAJIBAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMveGF0dHIuZFVUBQABtkgkYI2QsW7DMAxEd33FfUDsD/CaJQUyFG2KjIVq0Y4AmTQkqrX/vpIKuOjWlby7d+RVeB6wWdVoLhTW
*/