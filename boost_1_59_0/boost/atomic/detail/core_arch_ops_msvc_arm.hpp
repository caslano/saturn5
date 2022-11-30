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
 * \file   atomic/detail/core_arch_ops_msvc_arm.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/detail/ops_msvc_common.hpp>
#include <boost/atomic/detail/fence_arch_operations.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

extern "C" {
__int8 __iso_volatile_load8(const volatile __int8*);
__int16 __iso_volatile_load16(const volatile __int16*);
__int32 __iso_volatile_load32(const volatile __int32*);
__int64 __iso_volatile_load64(const volatile __int64*);
void __iso_volatile_store8(volatile __int8*, __int8);
void __iso_volatile_store16(volatile __int16*, __int16);
void __iso_volatile_store32(volatile __int32*, __int32);
void __iso_volatile_store64(volatile __int64*, __int64);
}
#if defined(BOOST_MSVC)
#pragma intrinsic(__iso_volatile_load8)
#pragma intrinsic(__iso_volatile_load16)
#pragma intrinsic(__iso_volatile_load32)
#pragma intrinsic(__iso_volatile_load64)
#pragma intrinsic(__iso_volatile_store8)
#pragma intrinsic(__iso_volatile_store16)
#pragma intrinsic(__iso_volatile_store32)
#pragma intrinsic(__iso_volatile_store64)
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

struct core_arch_operations_msvc_arm_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before_store(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            fence_arch_operations::hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if (order == memory_order_seq_cst)
            fence_arch_operations::hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            fence_arch_operations::hardware_full_fence();

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE BOOST_CONSTEXPR memory_order cas_common_order(memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        // Combine order flags together and promote memory_order_consume to memory_order_acquire
        return static_cast< memory_order >(((static_cast< unsigned int >(failure_order) | static_cast< unsigned int >(success_order)) & ~static_cast< unsigned int >(memory_order_consume))
            | (((static_cast< unsigned int >(failure_order) | static_cast< unsigned int >(success_order)) & static_cast< unsigned int >(memory_order_consume)) << 1u));
    }
};

template< std::size_t Size, bool Signed, bool Interprocess, typename Derived >
struct core_arch_operations_msvc_arm :
    public core_arch_operations_msvc_arm_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_msvc_arm< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_arm< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > > base_type;
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

        switch (base_type::cas_common_order(success_order, failure_order))
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_msvc_arm< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_arm< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > > base_type;
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

        switch (base_type::cas_common_order(success_order, failure_order))
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_msvc_arm< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_arm< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > > base_type;
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

        switch (base_type::cas_common_order(success_order, failure_order))
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_msvc_arm< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_arm< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > > base_type;
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

        switch (base_type::cas_common_order(success_order, failure_order))
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

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_ARM_HPP_INCLUDED_

/* core_arch_ops_msvc_arm.hpp
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
*/