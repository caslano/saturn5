/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_emulated.hpp
 *
 * This header contains lock pool-based implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/lock_pool.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool = Alignment >= storage_traits< Size >::native_alignment >
struct base_emulated_operations
{
    typedef typename storage_traits< Size >::type storage_type;
};

template< std::size_t Size, std::size_t Alignment >
struct base_emulated_operations< Size, Alignment, false >
{
    typedef buffer_storage< Size, Alignment > storage_type;
};

template< std::size_t Size, std::size_t Alignment, bool Signed >
struct emulated_operations :
    public base_emulated_operations< Size, Alignment >
{
    typedef base_emulated_operations< Size, Alignment > base_type;

    // Define storage_type to have alignment not greater than Alignment. This will allow operations to work with value_types
    // that possibly have weaker alignment requirements than storage_traits< Size >::type would. This is important for atomic_ref<>.
    // atomic<> will allow higher alignment requirement than its value_type.
    // Note that storage_type should be an integral type, if possible, so that arithmetic and bitwise operations are possible.
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = Alignment >= storage_traits< Size >::alignment ? storage_traits< Size >::alignment : Alignment;

    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;

    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = false;

    typedef lock_pool::scoped_lock< storage_alignment > scoped_lock;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        scoped_lock lock(&storage);
        const_cast< storage_type& >(storage) = v;
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        scoped_lock lock(&storage);
        return const_cast< storage_type const& >(storage);
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s += v;
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s -= v;
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = v;
        return old_val;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        // Note: This function is the exact copy of compare_exchange_strong. The reason we're not just forwarding the call
        // is that MSVC-12 ICEs in this case.
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s &= v;
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s |= v;
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s ^= v;
        return old_val;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

template< std::size_t Size, bool Signed >
struct operations :
    public emulated_operations< Size, storage_traits< Size >::alignment, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_EMULATED_HPP_INCLUDED_

/* ops_emulated.hpp
CO5tnBP3rc2Jmypz4tZ/tnj2/a0/zRvZ95Ynf114xd/ZDy/o3G+xN2XToi6vjvzowUH3tl4yoTT+HDf/OXT/fXPfjnSOm/9cuSOfGxjee0r6YbQOW+rZe2pyZI8q+k3iy/Uwcii1r4OPXH/3nlz12NfXJVfQQPtq6pHLccntqcfdji652gbad6Ce+DvRJWfVIzfUHc/1uDvaJbe3nnCMcr+PFQ2zr6AeuSx3PK+I726mS25LA+3b00C5gysalg5yqhr23gqqGhYvNVUN819tVcP8d6CB/kutrt9/VmLdXMXyTUFrE8qZs1gL96IOobIuYp8w1HyUdy7jRu7tRNU3p/F5nvvNa9x913/f3MZN2YH/6PzG+PvIIXvXf888x8/u+nL7yR3MDsicx5S76+Y99rn7f3/uY8rZ3/z8x7fJQykXB60+qMmoctRmVC3qedRnqPaXBK1RqGLURtQO1OOol1GfoTI2s98caiZqLWorajfq5c2Ncycbr8ar8frPXN/i+H9x8dcw/u+MS+e7xqUf1/X/2do34dzc6fT5nenuSy8uEf8UrmDlX7x1/2oGG/z339PnuBR/vz0jY/owXut2+D6M8LrG633OpPLulaZnUum92HXBB3Tc+l09T3wf6k4sr4yKDxnmryxaeGahzkqQMAdk3S/vKBInaq6/6E9Ff6PoHxL5G+v6RvGOxpGR72P2KNwm+h9Hnw92VGQPvuvkeYnGX9h8Tytd9+QLlcved+yPnhZtxwDLnKV/jZh5QPRlxo48kb8h35y1ac4BvF2e32mlm7M4NRZce/p9LjJjSFPd9F60X/J4v8nID9T98v6GWkd8DFL9YMg9effihXrOpu9a7joXT98x74J3zLtwrf8kvrlHfOs913po4lT3snPfGxCdNp5J1M369MyyfqjdeG57uTttSLIoqq4qjZwvb/qKyceRtKHmOvme2z3JPM828f6A6HuYdb/H5Dlx1vC1zXV9yPjB5I/os/PcfZb7tVr1uoQVPeoBx5IlMWGtPKa4qKoo/plQmIk+ay1T9M9Yx/D/fpTnvElztltHkXvE6oW/dqLCaeZYV5q5F3NDNR64x9mXDUsz9y3xpJnYs8fMe8/S8cazMNAFFsKHkc2p8ImLkoqFGh3ucm5BiSwdN+dUq9l+os9CP1X0m3RvS07SXoqeGMqxAvHKU7WjjylbJot+Stz9TDPhBJEZZWt5oXb0dO1boHtg6rsaJ8/Hi/xJRj7PFTaz32b0md0VrjOzLZ8zs1U23yMbdbaYnkVt9ib1yFaiD++hakkcO3taWmat/F0im8sazgSxc1pYzorIPC0yKUg0MWc5/lbu3cFJ3jl6z/M+vOejano9te6d2kNJp81d6XQEHInbr1HY/gtz76EOotZzb6jzLO/I0m7lUpN2vd80TWda5vl8/wos/71CZ5r9IuT9i+x8I6vvWGVLzX19l9yr9JzZ6c4/L2v+WaT7SsxF/RxZq9Kdf6orPCWnxPNjkXJTvyNQzE1j3aytZYzahUQmcZ+I9rNUiVMpI89PO3y8hsuAx1xlpLs83KbzAeZpGGagfoFsjU8YtER0nSdGOnH5/woxc6I12OX/mjj+H3qE/tezxY7xlmGHdFz/SlQWagPqScfCZb7+N6WYNwzqXzXXzuSZdqJfxbfd9i+vjBnqA1q36Sb6hdQGQn51QnNWcUeRW2p10PM9S41dHc1eH59pXI1uQB6KiasjzC+Ne0R8++NhG2Q8LO1vnVff9fDwnQP77/nplIftoY17RHyVPSKGWNregtk+ewRcpnsEbIFp8HLYWvWYh9pWgO+q+ZZwo2svhf6wDRwOs+Bs2BbOg+1gCWwP18IO0DHbEV4=
*/