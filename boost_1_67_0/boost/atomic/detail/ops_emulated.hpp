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
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
*/