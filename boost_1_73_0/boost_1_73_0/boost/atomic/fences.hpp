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
tkLc5uB5fnMaJZnHm6uFB4+bUhG0i9F90rR4XJRQnfbH45PRj8FSYL1Sck0Sk04m9TicG9TvVeP2wWiQtHrMUTtXFIX74NBOf4T/comDpHttCxujoguMMKmgJRBfJXXUo12zS+QBAZevOh8Gc8S94jvaiM2LrQu9VpsS5ztCFovCmZT9FX2wACXOvgK1Xm6PlPGR8dgxS08uf8o03j1DVzWatXS/UEsDBAoAAAAIAC1nSlLuYe3DUwEAAEMCAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdXNlci1hZ2VudC5kVVQFAAG2SCRgTVBLbuMwDN3rFA9ZTYE4BzAGBYLZdIBZFEh6AMVhbKGSqFJ0Or59qdjozEoU+T58PE0s2uPo/nAee8yVpPMjZXVHsf/P7BM9uxeKpceJ8hVvDXFsiG0IZVjvTuJehZUHjrXHy/n86n55pZFl6RFSMR9vpEm1uK7rnDsVGsJtgU70v2pVCXlcVc3P3gZoepvNAWcG5YGvhEv0+b0iZNdAK3WPOovw3MjfTXwGnVCtioSPmZWQvLxXE5tCxUT+SoLBZ/hY2V2MR7qSmkjXbQiW7V+E/y7f3aKBcz049/uGhWeM4U4wMUpFF3gZ59SyWZiu+3dj/Njt
*/