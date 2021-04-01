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
leqmKRaB/O6jedK+njAxP1Tb9g6EQIrLoa7GdFQRKR51Kqvu0sYhJPVQ3T5A3N3IN0D+IUqKT+BFMw7EjAItNczroSf3omGdeKyd10MUhBJYKRKH6OVSPu8krCSofAXOEG1b9XdD1WLmYdNLKVExdAz301TWdNWedMi2VUnbNNI0ix7S9m7xUMoU7ej39MPEVWnLfBz8fa3KNUpPSz7BLWxwFM/BFKJzQgMXxMb8dPXeQn7y4zdmhA09Te7vTLcz7+TCFxi00zs/GLw+iYk+8ntTBA83eoeI+EdpiaC88J2RDA1vz/VNKGXLy6ly7pu1lP75pNunIv43boxrOTdnVud+nvuqKtBqAxKmrM3+EegEWn20BupPjsuB4Rctn5xbMnz5J0gARf/5S/n+sgF3juoxRNv7e3WTPost3pEgS5icdV+qqnwnEl1HPB3pO9tUrytZQOx3tCmk/whhUAsnBeZ/JabNarm1ZZADBibirGvIo13IJIVGnr1CG29p3GgUblKIsgqRA9xb0boiXelwmbovOTtZCTFnbBOAyYUWyQmCDmCxDNv9VYjeGQ==
*/