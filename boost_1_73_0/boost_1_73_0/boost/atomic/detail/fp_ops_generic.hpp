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
xw0GFcGK7tNeMYD8hAces1bzE0DH/hja49VqVZ/O/RW2OJrDQc4gxJDXwmiaBIEXawBfaxweHR6+bhzXv7qh0ry5BCngsdIaYCqHrGZNbpWrS+HKxdxxI2AwvELXL6CPgkVHZGOahwsrmot2VtQgaPZl/hOUC8byOSYoQxmwlQMaU+7zyMJaRah3js0cK7Go0ZPJP+fRPxi0q/xFDLgL13cXlAuB910qL+ZAnHS9Glx+apNn8BGGpkw/81q4fIaOPaiATVT24lQ/7/TYf8JIJDT4lkcVKKof/3X0b/W/L1ix3qV0uo/T8TBYdtFB4/q2t3S4qCyyrXX9SQCJB70/x9PUJIKzBhZdeF+fKTVXohxURAqqmkSswxukee4FYzDdxLOmMVkYSmSWdbHSOus2zw32EmWHfFZZrU2lAK49fQRnCR3uLpofddgCemedc/OC1fwgThwin9aOVkutypDH4tFtUwp4DqYALgWT9xIVK+PBO2A4GOrd67ZOG00bmy1gG7CDD6yG9RoOW9izI4HOqf6J9jNAxXQS9FDqGmQViMLAEFTSg8kEaMAJ0MdiDHaPoYKzGmwVNnv99s0aMhQ0686kuo3GgAqS26O2gnMWPEp1TD1VxWqNWuav5O6gVo/Ec8akZhQS0LebhKPB
*/