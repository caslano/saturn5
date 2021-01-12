/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014, 2019 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_msvc_common.hpp
 *
 * This header contains common tools for MSVC implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Define compiler barriers
#if defined(__INTEL_COMPILER)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __memory_barrier()
#elif defined(__clang__)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __atomic_signal_fence(__ATOMIC_SEQ_CST)
#elif defined(_MSC_VER) && !defined(_WIN32_WCE)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() _ReadWriteBarrier()
#endif

#ifndef BOOST_ATOMIC_DETAIL_COMPILER_BARRIER
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER()
#endif

#endif // BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

/* ops_msvc_common.hpp
UDVpb6vFqomzPV2I1W5lEpD1Q+ZVpIGO4GEyKAh6m4mi0fV45WbprPnz5hsvojKt2Yb/+mTyKgziEYeMkP8RWP3NpAbwSYrVI6JN8CE4T1Qe8NRYBaUANZUUIx+b5nrmcoy+/xY29wua6s0O9AX1eIlMnXKrgW9m2jXmc6351Bx2WxDCpPUxRHWPZHcOhsrytkF3csYa+yyr9qh3vQHntbFcc56d1iSdpybVVuUgpwis0V8T
*/