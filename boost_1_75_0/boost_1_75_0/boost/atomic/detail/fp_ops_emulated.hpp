/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type fetch_sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }
};

template< typename Base, typename Value, std::size_t Size >
struct fp_operations< Base, Value, Size, false > :
    public emulated_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

/* fp_ops_emulated.hpp
BYdCH/uD5c9UFyn4CKBUHGO4QX6aiTqWObGZVmC7xoD5wdCR1HF5uYo48fqd6c+KRee6mGH32gyvv+lTkeyNVW/8M22o8y96w2lNpjOlNXnsFCPpDQLzPC6f2jmttrkZAb55IG5uNFY7eYJyBrry8BGIgKXf1uKltb2d+9m1rjeXBwGE1Jbcq302lxICeJLIVeCN4LfgU+gmdH5GOMBoYu7jdBJTUPPnHecXn2D0yHXyG+d2i6qsg73r3OohOvLAGIFYNb0KbKvLAiHZ8Up3EGpOnx33J5+sVSBDNu8nBHO3/flTQO2FlOwvAXpawN7ZjzQg3eLr01hKvgvEA2r4xepO4+xarE631uA9YPi5GyugPrPq3W4ggkbtE1e91rWPPTZggPZXOzx3nkpqP/YabnqA1yT56uYqZPreVv6eQQrQrHLQv1uZ0pl71A9Q/uQD8uZp8N+cPO+mHpvLmrzzSn5muxbq1t0xtrxpHBlQyLf5CmjGfQTd/IGIustM+zmdQt2nm/v27lLnrP6m5wlzRG2FJn94Z8uP5MDOK0FXnDovkPTWQ9p9v75LA5nXbX2EHH4i/p2lTD32J4C/s5Tpv7GU9j+ylOVfN88ilmYmNsz/VKmfI9FI6k37a0MfchN9DAo8PFQT7NrKTN1PmqHXNUb1ZxlPu/Xf7ivF241sDRvYzc1pYcON5O5/IPKYMFCNq6lKVzG9/FiXkZWd
*/