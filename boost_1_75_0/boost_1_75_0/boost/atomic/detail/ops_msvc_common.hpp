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
5+/awVarb/yl+y46hnaM/fploinSDUb9G0iXRj/r8A7Ui0m0/D0VZzCj/46vDorLM/mqai+6U1he2o3JitleecCoGMLuTH7QkYJoVuhhmwmZKII5asI7hgYZM6Uq2z8HeetALMIu9Hj0d5vaYLae4BOyhp1n3V9B0eCfe/ibUXLhv1/MUMnKUkfQcPCC1SwnfYbhJr+/CydepupLUFk/5ezLHjq0LUOj9yxGGn9jToSodrJOxuFZttjLrzhfd+M9hxjFj81aFt2rB+IBRUIoBJ9L7oUuzn7r1VISm+UvBBSGdgfjgm+iO845e6K3GWfznBh4ShkeSo2tRz1qkuK2GfzMghlnYtld7t0tB79dTbi28ZgNi7ltyudlJ3fuGeoR1lw2Pi1RwF7fe2AJawR3OFU6fSxheKjt3LPVm/TQgrQC39fyDgDVD2vbyMI+8Wr5MX6BKZjmN39342z5XjZZsi9uKH9kz7+PUk7yGosGPReTIPR3WiFOJdav0DwMgTD84VWczMi0ml4/7Fjf7lX7YvkPRJpiuYV9nnnSnjgVRQo39KRFevs67dIJ2kSJZK7H6EPO/lRXl4m+ep2A0v6FgaZWbuf8FpdYov7gBePbaFFD5Wx7Dgm5gBF5oGf0l2vO3OK9Azn/mE8NrIpbTBupaJJsTMlM6XWsGUWyCMYzDJmZp14fIad91OVC0KRA/1zcE0U+nW/m4D6fo97s
*/