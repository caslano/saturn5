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
#include <boost/atomic/capabilities.hpp>

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
template< typename Base, std::size_t Size, bool Signed, bool = Base::full_cas_based >
struct generic_extra_operations :
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
struct generic_extra_operations< Base, Size, Signed, true > :
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
    public generic_extra_operations< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_

/* extra_ops_generic.hpp
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
*/