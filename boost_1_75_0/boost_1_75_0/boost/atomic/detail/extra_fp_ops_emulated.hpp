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
NGXFT/pvhSpgptyyWUVGvzQAAj+XTIB0/AKmKwkBKJ3rFHlhcS6acb6ZK1CvrH4eu+svix/R4Pa51JuF3cVJMBqY/xXwEfgZ9Rn2idJ3KPfq0CUFEekvhJR6nLVjvgrvQBbLGyH9tleQrZk3gXwYkh8Pdg9Skx4GLb4HMmkG762t8TUNjyF6K/57jY8h4jYB3OZXP5RsSPFbHrOBtR8nVa27vjp/vnMuQG4fE1Xf5KZZ8ydkqHdskh51rMMOEEmiHMVBog6f7/Enn+diTt1+tDo6VfSr6tYeNtWt0HapXDCkXAjUX0g/YN/Gyq1+nG+INrZFS7eQNEWNVDC3aE9X8heqWa+vFcrbULfmsmUdPs5aLW8kY7bJp/CKBBSdNXSAAWbZG1566/eOx19qlK9ZPTYCaPldcjlzDJy2igZUkD05cd6JM19YliFo5/TcLhVgvnPv0Q83DanOM1pHe5esurP52R+AWlreDNoPcWUI6p+vk9Vfczg9+i4+bdLtwiH5pnOnAfEq+MOvLQApgw8IqOKCbNQlTuWa8BpYxh5fWjDbJzi3tBqwCwvWUBW42jnZUufXQ/zZeCSQ+3Dz4xgG20/mkxUCsd6A9C99CSYXMqgNKFNnSobkI0t/QICRb2XVw712N2Arlz3I7BojqPZY9YwTk9JhG/MdUn1HHOdhfotGcCFwQ+9SJgTxV/bJLepfAOW9db19WH16pP5x
*/