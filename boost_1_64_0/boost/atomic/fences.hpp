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
xfRHisIx+wXnHU3b4HpevrfyH8yNB4I/yVMYFpET0IuHYa0WF5rkrOh2dyMkobipO4zVLQts5ttDDTRbTBAwDwBXfuKM2Ml4Dobp0qfOGbhkRSb+eIhUrzJsDGI27ASDnSWKxeEaz1EU73Xhao+M4g3WUvs9qChuO0kI1sUmBHyKnEmtNXKTqbBM3DyCM0tXGK4j2VBaeiXs7uMvAlSWpKMHbZ1zcjirU7hkWlKtlowjEhC+y8zb8Ei2Ss8mwvpVGDWWrJRpf+/Cpv/wB/iTC1V1p9EEIJ9xM3/mWsy5rjMSBQORihW8I0nOCQUj6BbmWYhBP+EHwYnGC9aCMbFWNYvpeBUNqGO6xpRTzciT6QBPmGw7WdnJlTGb7bOIALBfx7RmwJwfop64irruBqjkvhoSwDHvai/aSqK/+ktGrILIVIlLAvDtFK8ED73mytkT5EoZ9Qq6qCY+8azbcigQgUj9v373itrtCTjDxxaQeRxEJ8tfylbV98fj88AcaPwEtBB8G9RuyYjtGPH2cq+ucOe39zhB0l+icr0ckj4dmUUvA7HNnQgwKTx2+w==
*/