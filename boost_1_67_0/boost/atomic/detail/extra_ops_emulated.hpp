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
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
*/