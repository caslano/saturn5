/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_extra_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
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

template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, false > :
    public emulated_extra_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

/* extra_fp_ops_emulated.hpp
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
*/