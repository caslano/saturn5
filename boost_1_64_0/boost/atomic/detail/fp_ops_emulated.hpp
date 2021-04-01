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
ZmI4RP3r6lKqj1PEDOz8AzF4C+/sX1etCA+K+mzlKZlut13bYJkBJmU3rgTzGwe4EInwr/t42jn68Ww6udu3cb+8G0+xDPCABzj83xmhiwJlVYH8elNgMgWJs6ZB08Xw21cgxlSRUEhzNI1MgQX2kvoPEHqiffapiyYrm16xnASh09dtrLj18zPO8gYCRLTjovoLwGpuMyrvZNQSy7d/7V8dgQ+8rK/YnzncSYlbAMFAOjFhCRW+Y4aEa0whw8aZKaGhrA8ay+JiCjl7c/Q2woIwRbepbjimdRPAul7PFfHz90tRO22zhxSlPSihhTFFC811GmjGVEjFkeYlRqlUghSRNdjUKhJRo08qF/+ieGt1JclFzPqy3JnnPUjpFuY2H4BEVFDGeOXYjHwKTrtZAJaCAc3zhYHNPLQ2Mfh0nWOGw75ByNZH9YoY9F6KlbqQ1Upic9mTdV5wxb1sZfYuEYl5jV+QIA6jHeS85HYfpQ8/iMOHc1PsPlw7EJsSrNK2nDDSJ/IF59v5SDkFrSEyiIVHMfb7jp14Ebr9Kr/6saVG/2NAh9ZzCEo6Bg==
*/