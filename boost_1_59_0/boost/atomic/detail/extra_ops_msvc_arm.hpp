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
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
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

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

/* extra_ops_msvc_arm.hpp
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
*/