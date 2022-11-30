/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_ops_generic.hpp
 *
 * This header contains generic implementation of the floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/fp_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct fp_operations_generic :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type fetch_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
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
        return old_val;
    }

    static BOOST_FORCEINLINE value_type fetch_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
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
        return old_val;
    }
};

// Default fp_operations template definition will be used unless specialized for a specific platform
template< typename Base, typename Value, std::size_t Size >
struct fp_operations< Base, Value, Size, true > :
    public fp_operations_generic< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* fp_ops_generic.hpp
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
*/