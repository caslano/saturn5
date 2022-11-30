/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_ops_cas_based.hpp
 *
 * This header contains CAS-based implementation of core atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPS_CAS_BASED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPS_CAS_BASED_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct core_operations_cas_based :
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

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPS_CAS_BASED_HPP_INCLUDED_

/* core_ops_cas_based.hpp
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
*/