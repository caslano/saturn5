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
LxZ8ofAJ9yqAb0DYMIZK8/SGqVPem1JQqXB9e4k7WOFuggpdcoFIap6MQTd4Fry3skHERpQdZcwa9+qDg4NnOoeJ27+Zv0MeZCpferzOvwNc5x7lOg9zlloOE9JzrcrIxoKBPBq9n8mj2WB6/RHJ0Gbpp43Q9p7qsVpTWeWwObaKmbVMDLD4B1BjIZGERmXRwW440g/qMW4IwLhypfisEXuRSJ54AN5eUfTezMcCDl5bjDw6NWPek87/VIVHsQB1olP6TnNbf8S0PWdgdmG1rMvbT6JsLTaawgxFpiqeOrF+sbOFh70wU1p2uHzZUZR/faWrPmp1jSQrpW7mRzxs/AFQSwMECgAAAAgALWdKUpEqM7CYDgAAjBwAACcACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2NhY2VydGlubWVtLmNVVAUAAbZIJGDNWVmT2ziSfvevwNQ+bFWpbN3XtLtjeUqUeJM6tzcUFAkeEkVSJChKGvd/H4C6ytPucMXEPKwcLoqJzC8PJBJAqvr6n/t8Aq/gp59V+X+FP/hZSqhpvIE2+jH3avUNXP5hqd/x82dKquAh8m31An4u8g08lyKrq5av5Ptq9TNFvxPbyJ8qkfx9Rb5iChYjkkycnNLA8xF4Zl5Avd/v
*/