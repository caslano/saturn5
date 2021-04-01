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

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct generic_fp_operations :
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
    public generic_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* fp_ops_generic.hpp
prB/649ZSNYg8lfhdMapiFu16YAwn9YII63ZU7gifN8gkTAUOaYgUEF2Rc0kfiReIUudTYZxJ8CrgYJ6sDRDDXksk/jcCXoA5BbXjtBggvxcb2xjFF89261uYBxxiW8eXZ8ws9Riz6hO+vTo9VHSt9rO9WZar/Kd5rJ0M+u9/I8UDOwsTh/wMXs9vFSHQr39v8Ox9MrPY3i4hr1sBDLEwSs6Oi1+U0pw+c5/jCKhJHSSPg/v/1xODucI6tMnxShRJSZ6fpwKGnpWmCbG58o9NLuDR5l/jMLartZiPGH63Cuq0wuRMz63H9ZWuDfk7eesRJQiRfBqs19k9QsHVjub3gkzUFG2dj3JOVP01Enbk7eUeXjypoRmKXEc85UHIn4irY5lduVaegRHoTYwf2yveh5cEJBtKaxzXkGAtqHGc9+ZzUX+HnEV2Lss/rlAlaAmk0nRF0D7HIETpjPAX002mfhZ/uRcnsDWJyoJ6EEYEAY9u/D7v2aLVuqIDTms+MDrx9iAjN3p6RD0RRqDVsRjQEIkRgpbeBMF4JUeUqKWNfSeXtqFsOxrXQAdUw==
*/