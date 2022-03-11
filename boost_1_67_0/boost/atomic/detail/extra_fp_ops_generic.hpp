/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_ops_generic.hpp
 *
 * This header contains generic implementation of the extra floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/is_iec559.hpp>
#include <boost/atomic/detail/type_traits/is_integral.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_GCC) && (BOOST_GCC+0) >= 60000
#pragma GCC diagnostic push
// ignoring attributes on template argument X - this warning is because we need to pass storage_type as a template argument; no problem in this case
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Negate implementation
template<
    typename Base,
    typename Value,
    std::size_t Size
#if defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)
    , bool = atomics::detail::is_iec559< Value >::value && atomics::detail::is_integral< typename Base::storage_type >::value
#endif
>
struct generic_extra_fp_negate :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = -old_val;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return old_val;
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = -old_val;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }
};

#if defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)

//! Negate implementation for IEEE 754 / IEC 559 floating point types. We leverage the fact that the sign bit is the most significant bit in the value.
template< typename Base, typename Value, std::size_t Size >
struct generic_extra_fp_negate< Base, Value, Size, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    //! The mask with only one sign bit set to 1
    static BOOST_CONSTEXPR_OR_CONST storage_type sign_mask = static_cast< storage_type >(1u) << (atomics::detail::value_sizeof< value_type >::value * 8u - 1u);

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(base_type::fetch_xor(storage, sign_mask, order));
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(base_type::bitwise_xor(storage, sign_mask, order));
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::opaque_xor(storage, sign_mask, order);
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct generic_extra_fp_operations :
    public generic_extra_fp_negate< Base, Value, Size >
{
    typedef generic_extra_fp_negate< Base, Value, Size > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val + v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE value_type sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val - v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }
};

// Default extra_fp_operations template definition will be used unless specialized for a specific platform
template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, true > :
    public generic_extra_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && (BOOST_GCC+0) >= 60000
#pragma GCC diagnostic pop
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* extra_fp_ops_generic.hpp
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
*/