/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_futex.hpp
 *
 * This header contains implementation of the waiting/notifying atomic operations based on futexes.
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_FUTEX_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_FUTEX_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/futex.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct wait_operations< Base, 4u, true, false > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = true;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return true;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        while (new_val == old_val)
        {
            atomics::detail::futex_wait_private(const_cast< storage_type* >(&storage), old_val);
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        atomics::detail::futex_signal_private(const_cast< storage_type* >(&storage));
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        atomics::detail::futex_broadcast_private(const_cast< storage_type* >(&storage));
    }
};

template< typename Base >
struct wait_operations< Base, 4u, true, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = true;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return true;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        while (new_val == old_val)
        {
            atomics::detail::futex_wait(const_cast< storage_type* >(&storage), old_val);
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        atomics::detail::futex_signal(const_cast< storage_type* >(&storage));
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        atomics::detail::futex_broadcast(const_cast< storage_type* >(&storage));
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_FUTEX_HPP_INCLUDED_

/* wait_ops_futex.hpp
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
*/