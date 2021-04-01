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
VEy75L5qm2GKfgFGG+j+YiDSbjGOsbxKr0qc9zuCZdbstAM3awgvbrV0ETtnr45ph/fVJWb2Kpr0YOaJydxor+QMCFosuR6RcN8juGTRbPJ5IfkJWjLneQBK5YbpTRyi5sS5UjdTjJSY+iwtkkL5Ecd0jf/+Qk1l8GWh9Em4hbhoivYBL+UfjMCEsmzehmmZYZQEfPZBgBk6RIoBr2fK1V7VdLw52c87cEg8XRaEAKXHFIw6X25xEYz7lSD41i/6tvlMt+KFBDWlwK1PotHOwOGo/qBmA07kRxk2SPVBMNYioa52rxvxFKrXii0mbvinF49AbokVsZXHf+sMKnpsZWI3Ky8SzxTjxbhko9lyzi3tB1vbaRkHzH9+d2qfmBtU1sOpc2VjBJL7oeMw0U3fk8XwJltA8kB/KrF33mtdaq/VTR9MS5ZxaX4pYiIs1mLABOpUA4sBDGV1oP2DDbnCGw+0Suw3JpUlf/dVGoKnsnyvSDgiLbPwcyZJvUVtIN5kQt5eskP8RVbkrgfGMEMVqn+1czoO1Zj6W6HLeIzhBo7lJ4rUu6Nnr4k6fg==
*/