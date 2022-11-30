/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_freebsd_umtx.hpp
 *
 * This header contains implementation of the waiting/notifying atomic operations based on FreeBSD _umtx_op syscall.
 * https://www.freebsd.org/cgi/man.cgi?query=_umtx_op&apropos=0&sektion=2&manpath=FreeBSD+11-current&format=html
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_FREEBSD_UMTX_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_FREEBSD_UMTX_HPP_INCLUDED_

#include <sys/types.h>
#include <sys/umtx.h>
#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/int_sizes.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(UMTX_OP_WAIT_UINT) || defined(UMTX_OP_WAIT)

template< typename Base >
struct wait_operations_freebsd_umtx_common :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = true;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return true;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        ::_umtx_op(const_cast< storage_type* >(&storage), UMTX_OP_WAKE, 1u, NULL, NULL);
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        ::_umtx_op(const_cast< storage_type* >(&storage), UMTX_OP_WAKE, (~static_cast< unsigned int >(0u)) >> 1, NULL, NULL);
    }
};

#endif // defined(UMTX_OP_WAIT_UINT) || defined(UMTX_OP_WAIT)

// UMTX_OP_WAIT_UINT only appeared in FreeBSD 8.0
#if defined(UMTX_OP_WAIT_UINT) && BOOST_ATOMIC_DETAIL_SIZEOF_INT < BOOST_ATOMIC_DETAIL_SIZEOF_LONG

template< typename Base, bool Interprocess >
struct wait_operations< Base, sizeof(unsigned int), true, Interprocess > :
    public wait_operations_freebsd_umtx_common< Base >
{
    typedef wait_operations_freebsd_umtx_common< Base > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        while (new_val == old_val)
        {
            ::_umtx_op(const_cast< storage_type* >(&storage), UMTX_OP_WAIT_UINT, old_val, NULL, NULL);
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }
};

#endif // defined(UMTX_OP_WAIT_UINT) && BOOST_ATOMIC_DETAIL_SIZEOF_INT < BOOST_ATOMIC_DETAIL_SIZEOF_LONG

#if defined(UMTX_OP_WAIT)

template< typename Base, bool Interprocess >
struct wait_operations< Base, sizeof(unsigned long), true, Interprocess > :
    public wait_operations_freebsd_umtx_common< Base >
{
    typedef wait_operations_freebsd_umtx_common< Base > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        while (new_val == old_val)
        {
            ::_umtx_op(const_cast< storage_type* >(&storage), UMTX_OP_WAIT, old_val, NULL, NULL);
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }
};

#endif // defined(UMTX_OP_WAIT)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_FREEBSD_UMTX_HPP_INCLUDED_

/* wait_ops_freebsd_umtx.hpp
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
*/