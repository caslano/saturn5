/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_extending_cas_based.hpp
 *
 * This header contains a boilerplate of the \c operations template implementation that requires sign/zero extension in arithmetic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, std::size_t Size, bool Signed >
struct extending_cas_based_operations :
    public Base
{
    typedef typename Base::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        storage_type new_val;
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val + v));
        }
        while (!Base::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        storage_type new_val;
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val - v));
        }
        while (!Base::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return old_val;
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_

/* ops_extending_cas_based.hpp
FjDKMioOvM2ii8L8SAjdH5aSFm2fVnT9wvkQ6tNJXCT5qzVEz5P2ILmoE3D1sBSE4abupUv5LwKKDdYtx6lfWFZMOGDXDtdIaEdncCDcFDBAXAZ0zDWhI7NFKrhSTKJSpsoGqJM+CLVSnWQyZsYz6FFPQGtl92vUGhb2fClkneF7CDFtPkaCz7cBQgrdf6r7/k8pOSJ30S3wUAq1aQOPmkwlTyGoGhO2NLrEc4RGsE9+ylReFOCjwpe1e+qU4KvfPLoQa+LHFEnI9uAXKK+1x5+0TwGY+SZPD/lk8cPZC0lVhY5ileGXiklGCNkeEAS3a/757Z+zIPKbVKisy+MGgTZqJG8yCA1UAOMPedkSXL+5XRx1ZAoOWkqRg5O18HXl2p/NUPFEPhb8JI1bDIeOznp4WJ/kpI0RdrRXtMKXw1IOdSahrodcBrCkOD8jwT9BahNMIv1MObLGZwAsBvmqQV8Xz4u7WxUuCbxhEJIckWQDTo9LBC+RbccQZGV/ECcKWTjDLn/efwqrXBafCkXLwSRHFysXWwwx6+Tg5ZEWg5cz6InUDiK/faMpuw==
*/