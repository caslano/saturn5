/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_msvc_arm.hpp
 *
 * This header contains implementation of the extra atomic operations for ARM.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
#endif
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
#endif
    }
};

#endif // defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

/* extra_ops_msvc_arm.hpp
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
*/