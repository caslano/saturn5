/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations.hpp
 *
 * This header defines extra atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/extra_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(boost/atomic/detail/extra_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

/* extra_operations.hpp
G5OeD2+Y82G1Aje4RDjhoWL0JWRFWxy6m6s2ehJ0VNvVdTAfcij8S0UinEJBXXj+n95Vhj50Jp4YYh5Gx36PhgQaEjcFDyAXn9wENWC/K1oEAdpv62V3q/HQNNQW9sznWQzWJVJJxDK7VuAU/1ffMvUSJA7EcL02T93uIHtk3PY1icaM3WInsRHj5CcJ1YMBZkNYUVsD1r/2fg1oLyvyd05Bd0jYUBbetGwXumjzSFKslIo7
*/