/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2015 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_generic.hpp
 *
 * This header contains generic implementation of the extra atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra operations
template< typename Base, std::size_t Size, bool Signed, bool = Base::full_cas_based >
struct extra_operations_generic :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!base_type::compare_exchange_weak(storage, old_val, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val)), order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_add(storage, v, order) + v;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_sub(storage, v, order) - v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_and(storage, v, order) & v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_or(storage, v, order) | v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, v, order) ^ v;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u)));
        return base_type::fetch_xor(storage, mask, order) ^ mask;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(add(storage, v, order));
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(sub(storage, v, order));
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
        return !!static_cast< emulated_storage_type >(bitwise_complement(storage, order));
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

//! Specialization for cases when the platform only natively supports CAS
template< typename Base, std::size_t Size, bool Signed >
struct extra_operations_generic< Base, Size, Signed, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!base_type::compare_exchange_weak(storage, old_val, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val)), order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val + v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val - v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val & v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val | v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val ^ v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return bitwise_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(add(storage, v, order));
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(sub(storage, v, order));
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
        return !!static_cast< emulated_storage_type >(bitwise_complement(storage, order));
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

// Default extra_operations template definition will be used unless specialized for a specific platform
template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, Size, Signed, true > :
    public extra_operations_generic< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_

/* extra_ops_generic.hpp
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
*/