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
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
*/