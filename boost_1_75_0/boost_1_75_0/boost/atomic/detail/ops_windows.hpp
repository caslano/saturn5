/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_windows.hpp
 *
 * This header contains implementation of the \c operations template.
 *
 * This implementation is the most basic version for Windows. It should
 * work for any non-MSVC-like compilers as long as there are Interlocked WinAPI
 * functions available. This version is also used for WinCE.
 *
 * Notably, this implementation is not as efficient as other
 * versions based on compiler intrinsics.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_WINDOWS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_WINDOWS_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/ops_msvc_common.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct windows_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
        long tmp;
        BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&tmp, 0);
    }

    static BOOST_FORCEINLINE void fence_before(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }
};

template< std::size_t Size, bool Signed, typename Derived >
struct windows_operations :
    public windows_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Derived::exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return Derived::fetch_add(const_cast< storage_type volatile& >(storage), (storage_type)0, order);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        typedef typename boost::atomics::detail::make_signed< storage_type >::type signed_storage_type;
        return Derived::fetch_add(storage, static_cast< storage_type >(-static_cast< signed_storage_type >(v)), order);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return Derived::compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Derived::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

template< bool Signed >
struct operations< 4u, Signed > :
    public windows_operations< 4u, Signed, operations< 4u, Signed > >
{
    typedef windows_operations< 4u, Signed, operations< 4u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&storage, v));
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&storage, v));
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        base_type::fence_before(success_order);
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&storage, desired, previous));
        expected = old_val;
        // The success and failure fences are the same anyway
        base_type::fence_after(success_order);
        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_AND)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res & v, order, memory_order_relaxed)) {}
        return res;
#endif
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_OR)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res | v, order, memory_order_relaxed)) {}
        return res;
#endif
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_XOR)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res ^ v, order, memory_order_relaxed)) {}
        return res;
#endif
    }
};

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 1u, Signed >
{
};

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 2u, Signed >
{
};

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    if (order == memory_order_seq_cst)
        windows_operations_base::hardware_full_fence();
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_WINDOWS_HPP_INCLUDED_

/* ops_windows.hpp
2/HtQ2Lc0b3pD6iSnaUbo6NdZHXxK76h3yM43aJ8c0i0j56u/dQJbMHdLnMDgb/evlTOjuwUZHNnk+xuFHcmKE052GZeecGiZaXoFVFwZICcvlhMOpjZunEOOXLUDFhhzMpoQJolN0g5PI5RJUoE9tVHuQjfnhMM0d4RDFGN6lrRrfL5IJ94YvZsFKAgDxcOzyxknK/2eHDRgEP3mLjPXXqriKOq/mBS5lugao+lPtKSOR5qxm+xEgBJb/i9i/I2Osvvm9TBYsib9aMGGWxkVe1NSOp6MUAhN5Can7voWMIATish4QfooNXGNqxTtO5BL9f+ZU0qHJxxIvus1iAlO+Fl4C8UwEwFhTeiTkWM4KWip3aP4GUNAtCX3HI1JQStwaOS3FaRdD2/+HQS9ozoNYq2cDc37dYt12NGSDvGTo30r6QTEUmQ2a1rIBzr90IYrK/tVsWfvKJu1uuYTbFaB91JIE6nWvec4FjQxYJGzUJHCoLRFZFB22RnoPqIa/mrtSsJeipReI3QGB3KOSPSxT7D6KHTd2y6i0oPRLrJtfaECJMjON8RO4tpdn8mfHomeJQ84x9Ll2Kfo9S+hBE9iz7tccBv5cZ4Ap6epU9iPLZ9iqXFvgD/qF0u/kDFG7we52dmUhu43rcLQgbQYKP1mP5RSOHPU8A4v2yG956r2lh7CvaufvBcO/s8WPlsL8Qunal+m7VVH5c88JbT
*/