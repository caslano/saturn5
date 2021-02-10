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
ppTzF3jCoCyhlDN+3ObKprkyuBa4O7iK5o/ix50s6/WOKs7Bg0j5JxK36V76apoK6n+f5gwWW6Tft1rCFGaPMRXmEJZpFJgxdVTSdtiM6qWXP/ty5RACi2yF7h5E+Z7iRnyzXLGLwJD+S5EtD819DGF99N9ewurACiyPj2PAedo4F0QaPG0qIqzhDmOYe8gw+6nIsAZeApkSI8P8Er+Ywe/hg5lcxQdrqsJSw3/MxxfZ+GpJvJsG7xIqIqypTxGFtwACGdRUdl2whyxP3yvCvK4W2f4eYpZKVLSsqios89hDieF/RYg1VcFUYQ9ZfjdVEeZ1tQix905G7ImzEXs4HdN9SrKouKJjVZVF0fu80YvvzwQloQZKTn8720PGk+aKlLeoCk+299up5np5ndmJO+ATNC9i8YpN0aDy6P1J9N0mfZfTd/fSYxgskmNdLaJmgVgZjvujmwHbHrShDr88ehKKVSBVNcHiwj0LYyDYkxTCboqtgTE1xgNj3B8aphgCw2j8xTGu7+u2tEeHLs4InGSAC1AbiSPBpQoW+Vn3dKm6/STOMEgIdQYsLjXnvfmwD9sIdIqBUZpB0llF6Hk0aJgwqogNc7vIMH6PIGv5AgPh4G7NkOZM62BuTMMqBAiKYNfooMntAPUR8o4c
*/