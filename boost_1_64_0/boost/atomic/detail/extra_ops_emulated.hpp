/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable: 4146)
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra operations
template< typename Base, std::size_t Size, bool Signed >
struct emulated_extra_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(-old_val);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(-s);
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val += v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val -= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val &= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val |= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val ^= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(~old_val);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(~s);
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!add(storage, v, order);
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!sub(storage, v, order);
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_and(storage, v, order);
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_or(storage, v, order);
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, Size, Signed, false > :
    public emulated_extra_operations< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

/* extra_ops_emulated.hpp
4ARNh8nwKTgFvgjz4StwKtwPp8F34HT4CTwFfgpnwbb2d3rYHs7RcG6ydN0KfEnTIRlu0HAe0j0Ch2Ev+CWcCL+Ck2EzlQ8YgPKdDy6EIVgBY+BaGAuvVPvXwUbwFhgP74eN4aOwCXxM7T0NE+CfVK/hZc2Hf3gTNd+lwF6QuEp4M+Bk2EfD21HDm6Xh7aTh7azh7aLh7aPh7abh7a7h7aHh7anh7aPh7a3hRa/5TNdKwCUe+WwT9jLgZi0nd8Eh8FdwHNyi4b8fzoH3wiLVf6j1xz71/2L1vynEjvy2ano8ArPgo5ouv1N/f6/p8kc4Gz4GC+E2OA8+ARfAp2Gl2vsQXmLpN274B31uc4fMy7l2foOFsDucB/vAYngSPBtOh/M135fApXAJXAnPhRfCpfAquAjeBMvhg7ACPgmrNDwHLP22C2dreUtXmYWWyk1qBx+HXeAT8Dj4DJwC/winwvdgAdwO58GdcBXcBa+Cf4U3wOfhZjV/CL4Cd8HX4atwP3wNvgHfVP0B1b+v+k/gm/Br+BYMBKjnYGv4KuwA98KT4D44Ab5n9ubot0D9JrnetTfnC33vX8Js+JXmK1tu5kjVj4Mh9BPUXPMr39j882ueVVPfjYA94CiYC8dAlDVe64fJcA6cCItUr3L99LtRzXew9S65fskqZysVdodpsD8cDEdC4iDh7qH1T094Juyjz8mBZ8Nh8FzYCy5X8xVqfgXsB6+Bg+C1sC28HraDN8L28NcwEz4DO8KX4FC4R/05CDtD6ib0Jv302wzx9Ei/S0n3ZHiZlvufaHm8Ag6A6/Q9rYVj4eVwvJpru63fPLj2aLfv0/r6ftgZPgh7w61Q2yX9ZiDfLWq1S42CNe6bwiyYAHvBFDgRtoKTYRacDZvDQtgCzoNJcAFsAythOjwXtoVXwfbwGnV/E8yEt8KOcLOaq9xRnXenD6LhdModnarxnAGz4CnaPs3T/Ddf80cJnA1Ph2fBOXARPAtW6v0L4Ex4KZyl+aNE02uppXPXcJeGIwGWajh+oOVsuZaz8+EweAE8Ha7Q9uYSOB+uglXwQrgOXgyv1fu/hD+C20Wv5dzML8v8tDzffs5IyI9w1PRDKmAHWAVHwCVaHs/V+C/TeJ+n5aJa67Ut8DK4UuWyroIb4A+1HFwEb4EXwwfhGrgd/hi+Ai/XdLobfqL+BQPkXxgHr4RpcB3sAa/W+sy2TxzE/hR4LZwOfwGL4XWwEt4AL1H7l6v99fBmuAHeAu+At8Gtau9RtbcDboYHYDV8V81VPq/OsVLXo9a75PN20XLQDQ6EfeDJ8Dg4BuZoeegLT4f94ffgQFgCB8FFMBcugYPhhfAEuBqeCNfCk+CVsAe8Go6Gv4Bj4HVwEtwEx8G74Hi4Rc2NvLoUf/l8Q5zy6lo1TI5fTquGyefLb6C98gbaW+uwN99l73WnvL8G2tsZbc9f3l899g59y3tPd7/6n91/OpIJhFkov32oMXu/nb2oOXtr70c98lqMtZxnu/elrr0g9K3uTZ3Dsw9yfR/++u1RfeaC0L98n+ple6P3qsasCH2r+1Xv3Ht0e1bvu+1b2re6IvRv27saMyHW6oXKRy1HbURtR+1DxUzkHiofVY7agHoEtRv1BSpzUqyVh5qLWonaiHoEtR+VMBm3qHxUFWo9aitq9+Tv9sd+9/vu993vu993v+9+3/bv37b/v6ispOpbkv/XOtsya2Tjdb+8nCMD28Kn+zK22dXCCnjuK2adr+W7F1vdtTRr4z4SfbOgfcL4z1ByJrU8EY/s45R1f9AsGP9X2+5nsqf4Kjk8diFnm0fWFvWX+78NTNR9UplxMqrh0OrwvhH4vG2ntfiZz90=
*/