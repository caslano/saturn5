/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_operations_emulated.hpp
 *
 * This header contains lock pool-based implementation of the core atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPERATIONS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPERATIONS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_operations_emulated_fwd.hpp>
#include <boost/atomic/detail/lock_pool.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool = Alignment >= storage_traits< Size >::native_alignment >
struct core_operations_emulated_base
{
    typedef typename storage_traits< Size >::type storage_type;
};

template< std::size_t Size, std::size_t Alignment >
struct core_operations_emulated_base< Size, Alignment, false >
{
    typedef buffer_storage< Size, Alignment > storage_type;
};

//! Emulated implementation of core atomic operations
template< std::size_t Size, std::size_t Alignment, bool Signed, bool Interprocess >
struct core_operations_emulated :
    public core_operations_emulated_base< Size, Alignment >
{
    typedef core_operations_emulated_base< Size, Alignment > base_type;

    // Define storage_type to have alignment not greater than Alignment. This will allow operations to work with value_types
    // that possibly have weaker alignment requirements than storage_traits< Size >::type would. This is important for atomic_ref<>.
    // atomic<> will allow higher alignment requirement than its value_type.
    // Note that storage_type should be an integral type, if possible, so that arithmetic and bitwise operations are possible.
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = Alignment >= storage_traits< Size >::alignment ? storage_traits< Size >::alignment : Alignment;

    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;

    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = false;

    typedef lock_pool::scoped_lock< storage_alignment > scoped_lock;

    static void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        scoped_lock lock(&storage);
        const_cast< storage_type& >(storage) = v;
    }

    static storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        scoped_lock lock(&storage);
        return const_cast< storage_type const& >(storage);
    }

    static storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s += v;
        return old_val;
    }

    static storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s -= v;
        return old_val;
    }

    static storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = v;
        return old_val;
    }

    static bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        // Note: This function is the exact copy of compare_exchange_strong. The reason we're not just forwarding the call
        // is that MSVC-12 ICEs in this case.
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        const bool res = old_val == expected;
        if (res)
            s = desired;
        expected = old_val;

        return res;
    }

    static storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s &= v;
        return old_val;
    }

    static storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s |= v;
        return old_val;
    }

    static storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s ^= v;
        return old_val;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        store(storage, (storage_type)0, order);
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPERATIONS_EMULATED_HPP_INCLUDED_

/* core_operations_emulated.hpp
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
*/