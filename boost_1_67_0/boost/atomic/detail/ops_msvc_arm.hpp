/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_msvc_arm.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_MSVC_ARM_HPP_INCLUDED_

#include <intrin.h>
#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/ops_msvc_common.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_DETAIL_ARM_LOAD8(p) __iso_volatile_load8((const volatile __int8*)(p))
#define BOOST_ATOMIC_DETAIL_ARM_LOAD16(p) __iso_volatile_load16((const volatile __int16*)(p))
#define BOOST_ATOMIC_DETAIL_ARM_LOAD32(p) __iso_volatile_load32((const volatile __int32*)(p))
#define BOOST_ATOMIC_DETAIL_ARM_LOAD64(p) __iso_volatile_load64((const volatile __int64*)(p))
#define BOOST_ATOMIC_DETAIL_ARM_STORE8(p, v) __iso_volatile_store8((volatile __int8*)(p), (__int8)(v))
#define BOOST_ATOMIC_DETAIL_ARM_STORE16(p, v) __iso_volatile_store16((volatile __int16*)(p), (__int16)(v))
#define BOOST_ATOMIC_DETAIL_ARM_STORE32(p, v) __iso_volatile_store32((volatile __int32*)(p), (__int32)(v))
#define BOOST_ATOMIC_DETAIL_ARM_STORE64(p, v) __iso_volatile_store64((volatile __int64*)(p), (__int64)(v))

namespace boost {
namespace atomics {
namespace detail {

// A note about memory_order_consume. Technically, this architecture allows to avoid
// unnecessary memory barrier after consume load since it supports data dependency ordering.
// However, some compiler optimizations may break a seemingly valid code relying on data
// dependency tracking by injecting bogus branches to aid out of order execution.
// This may happen not only in Boost.Atomic code but also in user's code, which we have no
// control of. See this thread: http://lists.boost.org/Archives/boost/2014/06/213890.php.
// For this reason we promote memory_order_consume to memory_order_acquire.

struct msvc_arm_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
        __dmb(0xB); // _ARM_BARRIER_ISH, see armintr.h from MSVC 11 and later
    }

    static BOOST_FORCEINLINE void fence_before_store(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if (order == memory_order_seq_cst)
            hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE BOOST_CONSTEXPR memory_order cas_common_order(memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        // Combine order flags together and promote memory_order_consume to memory_order_acquire
        return static_cast< memory_order >(((static_cast< unsigned int >(failure_order) | static_cast< unsigned int >(success_order)) & ~static_cast< unsigned int >(memory_order_consume))
            | (((static_cast< unsigned int >(failure_order) | static_cast< unsigned int >(success_order)) & static_cast< unsigned int >(memory_order_consume)) << 1u));
    }
};

template< std::size_t Size, bool Signed, typename Derived >
struct msvc_arm_operations :
    public msvc_arm_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        typedef typename boost::atomics::detail::make_signed< storage_type >::type signed_storage_type;
        return Derived::fetch_add(storage, static_cast< storage_type >(-static_cast< signed_storage_type >(v)), order);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return Derived::compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Derived::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        Derived::store(storage, (storage_type)0, order);
    }
};

template< bool Signed >
struct operations< 1u, Signed > :
    public msvc_arm_operations< 1u, Signed, operations< 1u, Signed > >
{
    typedef msvc_arm_operations< 1u, Signed, operations< 1u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before_store(order);
        BOOST_ATOMIC_DETAIL_ARM_STORE8(&storage, v);
        base_type::fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = BOOST_ATOMIC_DETAIL_ARM_LOAD8(&storage);
        base_type::fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE8_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE8(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected, old_val;

        switch (cas_common_order(success_order, failure_order))
        {
        case memory_order_relaxed:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_RELAXED(&storage, desired, previous));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_ACQUIRE(&storage, desired, previous));
            break;
        case memory_order_release:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8_RELEASE(&storage, desired, previous));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8(&storage, desired, previous));
            break;
        }
        expected = old_val;

        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND8_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND8_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND8_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND8(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR8_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR8_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR8_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR8(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR8_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR8_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR8_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR8(&storage, v));
            break;
        }
        return v;
    }
};

template< bool Signed >
struct operations< 2u, Signed > :
    public msvc_arm_operations< 2u, Signed, operations< 2u, Signed > >
{
    typedef msvc_arm_operations< 2u, Signed, operations< 2u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before_store(order);
        BOOST_ATOMIC_DETAIL_ARM_STORE16(&storage, v);
        base_type::fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = BOOST_ATOMIC_DETAIL_ARM_LOAD16(&storage);
        base_type::fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE16_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE16(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected, old_val;

        switch (cas_common_order(success_order, failure_order))
        {
        case memory_order_relaxed:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_RELAXED(&storage, desired, previous));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_ACQUIRE(&storage, desired, previous));
            break;
        case memory_order_release:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16_RELEASE(&storage, desired, previous));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16(&storage, desired, previous));
            break;
        }
        expected = old_val;

        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND16_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND16_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND16_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND16(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR16_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR16_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR16_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR16(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR16_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR16_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR16_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR16(&storage, v));
            break;
        }
        return v;
    }
};

template< bool Signed >
struct operations< 4u, Signed > :
    public msvc_arm_operations< 4u, Signed, operations< 4u, Signed > >
{
    typedef msvc_arm_operations< 4u, Signed, operations< 4u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before_store(order);
        BOOST_ATOMIC_DETAIL_ARM_STORE32(&storage, v);
        base_type::fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = BOOST_ATOMIC_DETAIL_ARM_LOAD32(&storage);
        base_type::fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected, old_val;

        switch (cas_common_order(success_order, failure_order))
        {
        case memory_order_relaxed:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_RELAXED(&storage, desired, previous));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_ACQUIRE(&storage, desired, previous));
            break;
        case memory_order_release:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_RELEASE(&storage, desired, previous));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&storage, desired, previous));
            break;
        }
        expected = old_val;

        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR(&storage, v));
            break;
        }
        return v;
    }
};

template< bool Signed >
struct operations< 8u, Signed > :
    public msvc_arm_operations< 8u, Signed, operations< 8u, Signed > >
{
    typedef msvc_arm_operations< 8u, Signed, operations< 8u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before_store(order);
        BOOST_ATOMIC_DETAIL_ARM_STORE64(&storage, v);
        base_type::fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = BOOST_ATOMIC_DETAIL_ARM_LOAD64(&storage);
        base_type::fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE64_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected, old_val;

        switch (cas_common_order(success_order, failure_order))
        {
        case memory_order_relaxed:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_RELAXED(&storage, desired, previous));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_ACQUIRE(&storage, desired, previous));
            break;
        case memory_order_release:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64_RELEASE(&storage, desired, previous));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(&storage, desired, previous));
            break;
        }
        expected = old_val;

        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND64_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND64_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND64_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND64(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR64_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR64_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR64_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR64(&storage, v));
            break;
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        switch (order)
        {
        case memory_order_relaxed:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR64_RELAXED(&storage, v));
            break;
        case memory_order_consume:
        case memory_order_acquire:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR64_ACQUIRE(&storage, v));
            break;
        case memory_order_release:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR64_RELEASE(&storage, v));
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR64(&storage, v));
            break;
        }
        return v;
    }
};


BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    if (order != memory_order_relaxed)
        msvc_arm_operations_base::hardware_full_fence();
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

} // namespace detail
} // namespace atomics
} // namespace boost

#undef BOOST_ATOMIC_DETAIL_ARM_LOAD8
#undef BOOST_ATOMIC_DETAIL_ARM_LOAD16
#undef BOOST_ATOMIC_DETAIL_ARM_LOAD32
#undef BOOST_ATOMIC_DETAIL_ARM_LOAD64
#undef BOOST_ATOMIC_DETAIL_ARM_STORE8
#undef BOOST_ATOMIC_DETAIL_ARM_STORE16
#undef BOOST_ATOMIC_DETAIL_ARM_STORE32
#undef BOOST_ATOMIC_DETAIL_ARM_STORE64

#endif // BOOST_ATOMIC_DETAIL_OPS_MSVC_ARM_HPP_INCLUDED_

/* ops_msvc_arm.hpp
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
*/