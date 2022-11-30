/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2021 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_darwin_ulock.hpp
 *
 * This header contains implementation of the waiting/notifying atomic operations based on Darwin systems using ulock syscalls.
 *
 * https://github.com/apple/darwin-xnu/blob/master/bsd/sys/ulock.h
 * https://github.com/apple/darwin-xnu/blob/master/bsd/kern/sys_ulock.c
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_DARWIN_ULOCK_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_DARWIN_ULOCK_HPP_INCLUDED_

#include <stdint.h>
#include <cerrno>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/wait_capabilities.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

extern "C" {
// Timeout is in microseconds with zero meaning no timeout
int __ulock_wait(uint32_t operation, void* addr, uint64_t value, uint32_t timeout);
#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_WAIT2)
// Timeout is in nanoseconds with zero meaning no timeout
int __ulock_wait2(uint32_t operation, void* addr, uint64_t value, uint64_t timeout, uint64_t value2);
#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_WAIT2)
int __ulock_wake(uint32_t operation, void* addr, uint64_t wake_value);
} // extern "C"

enum ulock_op
{
    ulock_op_compare_and_wait = 1,
#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)
    ulock_op_compare_and_wait_shared = 3,
#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)
#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK64)
    ulock_op_compare_and_wait64 = 5,
#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)
    ulock_op_compare_and_wait64_shared = 6,
#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)
#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK64)

    // Flags for __ulock_wake
    ulock_flag_wake_all = 0x00000100,

    // Generic flags
    ulock_flag_no_errno = 0x01000000
};

template< typename Base, uint32_t Opcode >
struct wait_operations_darwin_ulock_common :
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
#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_WAIT2)
            __ulock_wait2(Opcode | ulock_flag_no_errno, const_cast< storage_type* >(&storage), old_val, 0u, 0u);
#else
            __ulock_wait(Opcode | ulock_flag_no_errno, const_cast< storage_type* >(&storage), old_val, 0u);
#endif
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        while (true)
        {
            const int res = __ulock_wake(Opcode | ulock_flag_no_errno, const_cast< storage_type* >(&storage), 0u);
            if (BOOST_LIKELY(res != -EINTR))
                break;
        }
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        while (true)
        {
            const int res = __ulock_wake(Opcode | ulock_flag_wake_all | ulock_flag_no_errno, const_cast< storage_type* >(&storage), 0u);
            if (BOOST_LIKELY(res != -EINTR))
                break;
        }
    }
};

template< typename Base >
struct wait_operations< Base, sizeof(uint32_t), true, false > :
    public wait_operations_darwin_ulock_common< Base, ulock_op_compare_and_wait >
{
};

#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)

template< typename Base >
struct wait_operations< Base, sizeof(uint32_t), true, true > :
    public wait_operations_darwin_ulock_common< Base, ulock_op_compare_and_wait_shared >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)

#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK64)

template< typename Base >
struct wait_operations< Base, sizeof(uint64_t), true, false > :
    public wait_operations_darwin_ulock_common< Base, ulock_op_compare_and_wait64 >
{
};

#if defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)

template< typename Base >
struct wait_operations< Base, sizeof(uint64_t), true, true > :
    public wait_operations_darwin_ulock_common< Base, ulock_op_compare_and_wait64_shared >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK_SHARED)
#endif // defined(BOOST_ATOMIC_DETAIL_HAS_DARWIN_ULOCK64)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_DARWIN_ULOCK_HPP_INCLUDED_

/* wait_ops_darwin_ulock.hpp
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
*/