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
g0dwBf2Af8nlAs9FFszGQuYW6oqduKWbUxGKMJp8tdp2w4TLXIoW4k6fNFHolbeKCm0FrHE6YKEo6anPv3id369IZRYcKrb0njENUh57WKjQG9A62ed4XGvq+GDPv9S5eLYcRYMjqLlL+RmyAV1mH3LIMy3fbZwB5eb8ngBtzngIPzM4cPjslj44xwv1i87Bl6YY2kQawHV/zO2wmYY/P6eVgxatWU8DCls0EsUJRffYEEybltURHEbHvILVrJCrHIl7M8Z7jehE4oVDpXiw2y7osnQxqh4IGEPSNYijOcWJLiPoY1Gft9zEfYzvJz8ARu+c6IlM69iNMkoHZm0Oq64MBimzZFbb+FTx7Pqlxsol5Jgjvd5x23+h4JOYY0JlqyCs603uM1WeTybLTe4RpPeReRZwvaiCj5MhTpZ1bEtHieW9zYa05cZyWjFjlvxjF+fLrkpkD9SPCuYS+gLDRG8RvRZHL4/0Ixt98S6au8oQPUTVjO/EscudqpE8FdCtzFq9flwP0kTRHlWlJ/4jGY/EDMuxClAN3bdLk5/Pck6jUddG875HaXZDWTxdBXCz546nONSkltSRlnxrH97PK/7f+AwPmKsUVpV+RyFIkaHqHv02RiqjSxOeLYtGfdAIWAKkfqUi2Jc4nd7UPTTj9wa5jA9bb6YYeigj3hpnN90a4y4KXxtjW5O+Ow7sCWSOCd/GOW8zwhBGcDX3
*/