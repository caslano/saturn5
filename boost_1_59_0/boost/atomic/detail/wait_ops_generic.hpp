/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_generic.hpp
 *
 * This header contains generic (lock-based) implementation of the waiting/notifying atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/pause.hpp>
#include <boost/atomic/detail/lock_pool.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of waiting/notifying operations
template< typename Base, bool Interprocess >
struct wait_operations_generic;

template< typename Base >
struct wait_operations_generic< Base, false > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef lock_pool::scoped_lock< base_type::storage_alignment, true > scoped_lock;
    typedef lock_pool::scoped_wait_state< base_type::storage_alignment > scoped_wait_state;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = false;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return false;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        if (new_val == old_val)
        {
            scoped_wait_state wait_state(&storage);
            new_val = base_type::load(storage, order);
            while (new_val == old_val)
            {
                wait_state.wait();
                new_val = base_type::load(storage, order);
            }
        }

        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        scoped_lock lock(&storage);
        lock_pool::notify_one(lock.get_lock_state(), &storage);
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        scoped_lock lock(&storage);
        lock_pool::notify_all(lock.get_lock_state(), &storage);
    }
};

template< typename Base >
struct wait_operations_generic< Base, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = false;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return false;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        if (new_val == old_val)
        {
            for (unsigned int i = 0u; i < 16u; ++i)
            {
                atomics::detail::pause();
                new_val = base_type::load(storage, order);
                if (new_val != old_val)
                    goto finish;
            }

            do
            {
                atomics::detail::wait_some();
                new_val = base_type::load(storage, order);
            }
            while (new_val == old_val);
        }

    finish:
        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile&) BOOST_NOEXCEPT
    {
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile&) BOOST_NOEXCEPT
    {
    }
};

template< typename Base, std::size_t Size, bool Interprocess >
struct wait_operations< Base, Size, true, Interprocess > :
    public wait_operations_generic< Base, Interprocess >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_GENERIC_HPP_INCLUDED_

/* wait_ops_generic.hpp
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
*/