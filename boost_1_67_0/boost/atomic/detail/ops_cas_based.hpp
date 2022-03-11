/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_cas_based.hpp
 *
 * This header contains CAS-based implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct cas_based_exchange :
    public Base
{
    typedef typename Base::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, v, order, memory_order_relaxed)) {}
        return old_val;
    }
};

template< typename Base >
struct cas_based_operations :
    public Base
{
    typedef typename Base::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val + v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val - v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val & v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val | v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val ^ v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Base::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        Base::store(storage, (storage_type)0, order);
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_

/* ops_cas_based.hpp
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
*/