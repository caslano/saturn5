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
+PHKFEfoXWCS1C4123DutLYIeoV4KbpUqx4dGxEsPfkV8aRFV6b0if5uyW/8w55EZnTMdVOVDnLf5nqHo8KwA3qoIjTDgqjWpng9F/l8vFFxx5SWlheNz3G4vBktrt4Gej9gyOTRE4yWBTF2K3mJ1hI7MYbGqfOIGgf1aia4kpohzm9dv0ceJ5PwWSf8W8vN8NAvKSfUn2CGQQmgfLPsHVICKDE7UuYBpo9RVFRu+uAg4L5jOQ7NUP4g/h5GD6rRLmK26zMX8tYNTefUWN1WyH7lLYfD8gXQ/G/VBr4aHKttW2FUMikVm5+XI0V5aG5eoszhnbRLicEqfxj4IQLBKQQIwkGm7nwk2zELjWSqtP6jK2ZWVPLleCHNzfvucFKdTD6j1SP0AhaHE/SceY6D69NQ/FPPC+zvtmbEOPECx5I9ATse753AJ4lign3C1zEuUY3S1ZqXXoRmBufOcMrrqznFYpN4nFcMmkYGU6FJqgcfDKY2Z/Y54yCpYo9MjtVVEOLgKIwMlenFBWsjl+G7+nuYUg9WfRR7AH4Zqlxf6rCrOalkaHWOZv/FrxfqGyfEIi11d4kcpQElSZSTurcjLd6AMoU9W41fvLFnHeZmPwfnPPFQxYqe5LhgWnTJDxy52he8mTOTmlb6jYwxTWSwNLBOn+uj6MvNaOgatdnKG/PN1SeZEXNNWYnKVFFXA/TKqQd/d/Cc2k6wDTFf
*/