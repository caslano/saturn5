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
 * \file   atomic/fences.hpp
 *
 * This header contains definition of \c atomic_thread_fence and \c atomic_signal_fence functions.
 */

#ifndef BOOST_ATOMIC_FENCES_HPP_INCLUDED_
#define BOOST_ATOMIC_FENCES_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/operations.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace boost {

namespace atomics {

#if BOOST_ATOMIC_THREAD_FENCE > 0
BOOST_FORCEINLINE void atomic_thread_fence(memory_order order) BOOST_NOEXCEPT
{
    atomics::detail::thread_fence(order);
}
#else
BOOST_FORCEINLINE void atomic_thread_fence(memory_order) BOOST_NOEXCEPT
{
    atomics::detail::lock_pool::thread_fence();
}
#endif

#if BOOST_ATOMIC_SIGNAL_FENCE > 0
BOOST_FORCEINLINE void atomic_signal_fence(memory_order order) BOOST_NOEXCEPT
{
    atomics::detail::signal_fence(order);
}
#else
BOOST_FORCEINLINE void atomic_signal_fence(memory_order) BOOST_NOEXCEPT
{
    atomics::detail::lock_pool::signal_fence();
}
#endif

} // namespace atomics

using atomics::atomic_thread_fence;
using atomics::atomic_signal_fence;

} // namespace boost

#endif // BOOST_ATOMIC_FENCES_HPP_INCLUDED_

/* fences.hpp
p+8bYqKNStRX1Xse6/0mR6NCn2Hh7Je6CPyGIaYx3AtUTd5RcFmxmnygAjy9a2L4ZxB/sKGVA8GlLxOGfFYamHSXyaRfp5j0prsc2OeuBp+zDk/4VmHPMc6lH1JcuuxXy+CTX0/Yj0562uRzdwCSlv46tCqHwaP/zuTRq+foW4eY7PL6fnj0l2Q3+jFi+XJh1D1Tths8esWHZgnXsYRSB4xCmRx6ueLQr4nlXYIA1dv6lUM+
*/