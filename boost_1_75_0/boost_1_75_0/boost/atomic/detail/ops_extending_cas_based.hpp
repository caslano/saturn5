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
j6HdWPBs9kGrPCslkmbsbjKWi1JaB7XvVTpKjy35WiyvnpUNmJz4Xkf1lhq5PJ1QJKMAOQJn+493V/nRUH+npu0HocMFfsDTEfLW2yBcLX3pTKiqnA9ScEPIMnra1tVtsIajnI7z9DWMv4OLaRQ9iGn0yYJp9FlWPv0hgwWi6hXYfbcGYLqEpXV7b3gqpLM9sYW5yZRZBdxsA25q/U7HYAqrj7lVPIURW1YO3KX9QdgZWZAzESj3R4c8fkPJMKMUha4wHhym1lHKedqjoYoN92sW37TWIZeOTEQn9h9O96xHD/M5JxUM1VlVNwtZ1fGkE7ZkRd7QrbzvcMz42+4aYC6u/2OLJuVF0A8IVynHNSR8iPn2NmWXxLJTOV+Lios5nc9Wa+OF9KzbQ7I9V3ahIFTbdslTczXjQm+HelNn98hSSPxhfmQM6HFRHb2yWh09943OYA4m1HKnx0Ca1PVM7BVPAZ/a8IYWeO/EKeH6y2YJxSuIFRmJwhR4n0bk2RngxV1tN5xdAqT3H98Hpm7jiNsfwz8jNvs33RZ2kUcbtqVst5tJEmPcyyMuid2br4agSyAeQXxBfPFRUJfW2yVw0hynXyyhjdQvN/yvvVTTwY3B6h5EeqttBpNTC30djdTwHw5ngLhStAehP1sxtAcyAqQvjQVX8mitJqwHx1+j0FrDxPZKLrFN+hazeu9FHPqGp/SdTSUwG370p4CC
*/