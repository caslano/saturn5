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
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Emulated implementation of extra floating point operations
template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations_emulated :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static value_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static value_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static value_type add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static value_type sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        base_type::fetch_sub(storage, v, order);
    }
};

template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, false > :
    public extra_fp_operations_emulated< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

/* extra_fp_ops_emulated.hpp
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
*/