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
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
*/