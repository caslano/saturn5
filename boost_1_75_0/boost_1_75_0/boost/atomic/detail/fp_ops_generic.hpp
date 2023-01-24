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
UePidumkva53TK3SjVv6GCz1dQtIkKFdGknX/cPnxm12Kk6dTqt68kNI7XXZoaz87cFnu96gP287L8DbY/ptt8N1tL+xaGmSdm30RVv96k8YTD52lqNvs6TAe69qLggQHCUdINrhuLOSea8Z5pF1rxZJIEpfhKoUbylYI74V3KHW8UUnRNOmzW7ozc78c/YsOfGxEStpkALHVKrnwraKC+tn5kozrc90MmmOle3e8aqo29j4291j2VW/PASLlnk3IP3PamP0NKNDya+r/JG9XEH8C15Rg2xT1OlzuxO698Yzzq/vVqLpMkdvw7MPIwhtL20R6QLmFtaGDAWtQjZGna+LkW+Zpf31QJEAjT1lx5HXSRJIcSTd4/PbK1VI1EByrwNsW+0AfCzdXD+cU0uXZMDsw94H3SIaVvdYeVp1/oLdQ9qnBky2yKZv/TMDHI+vB8p7d39rjX6NxAcWHeHEXD2T+U112qfcJzXMakh58LGVRY0V3GM8D3jxU65O0Id73bEUFEB8Ex0JuUBv/8HxnYP8WnArai20wCyA84AkNLQDdz6mIz6KHfSlCK4xc37DvAYF9P2A7New7CW9DqgPZT7O8YdpKMK+mOv3th886HqR9r/Kv/FHSnzjxevdZFqJOJVA/u77hwB5YIEZHsvDnCoyOYnIpeil8KX4pdClGDIZCacXIs0UqSBytlnErT8eCPbgj4OKkKfQHwZf
*/