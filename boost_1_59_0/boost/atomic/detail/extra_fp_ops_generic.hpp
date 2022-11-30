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
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_GCC) && BOOST_GCC >= 60000
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
struct extra_fp_negate_generic :
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
struct extra_fp_negate_generic< Base, Value, Size, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    //! The mask with only one sign bit set to 1
    static BOOST_CONSTEXPR_OR_CONST storage_type sign_mask = static_cast< storage_type >(1u) << (atomics::detail::value_size_of< value_type >::value * 8u - 1u);

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
struct extra_fp_operations_generic :
    public extra_fp_negate_generic< Base, Value, Size >
{
    typedef extra_fp_negate_generic< Base, Value, Size > base_type;
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
    public extra_fp_operations_generic< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && BOOST_GCC >= 60000
#pragma GCC diagnostic pop
#endif

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* extra_fp_ops_generic.hpp
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
*/