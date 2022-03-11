/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009, 2011 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * Linux-specific code by Phil Endecott
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_linux_arm.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_LINUX_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_LINUX_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/ops_cas_based.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// Different ARM processors have different atomic instructions.  In particular,
// architecture versions before v6 (which are still in widespread use, e.g. the
// Intel/Marvell XScale chips like the one in the NSLU2) have only atomic swap.
// On Linux the kernel provides some support that lets us abstract away from
// these differences: it provides emulated CAS and barrier functions at special
// addresses that are guaranteed not to be interrupted by the kernel.  Using
// this facility is slightly slower than inline assembler would be, but much
// faster than a system call.
//
// While this emulated CAS is "strong" in the sense that it does not fail
// "spuriously" (i.e.: it never fails to perform the exchange when the value
// found equals the value expected), it does not return the found value on
// failure. To satisfy the atomic API, compare_exchange_{weak|strong} must
// return the found value on failure, and we have to manually load this value
// after the emulated CAS reports failure. This in turn introduces a race
// between the CAS failing (due to the "wrong" value being found) and subsequently
// loading (which might turn up the "right" value). From an application's
// point of view this looks like "spurious failure", and therefore the
// emulated CAS is only good enough to provide compare_exchange_weak
// semantics.

struct linux_arm_cas_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before_store(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
        typedef void (*kernel_dmb_t)(void);
        ((kernel_dmb_t)0xffff0fa0)();
    }
};

template< bool Signed >
struct linux_arm_cas :
    public linux_arm_cas_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before_store(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        while (true)
        {
            storage_type tmp = expected;
            if (compare_exchange_weak(storage, tmp, desired, success_order, failure_order))
                return true;
            if (tmp != expected)
            {
                expected = tmp;
                return false;
            }
        }
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        typedef storage_type (*kernel_cmpxchg32_t)(storage_type oldval, storage_type newval, volatile storage_type* ptr);

        if (((kernel_cmpxchg32_t)0xffff0fc0)(expected, desired, &storage) == 0)
        {
            return true;
        }
        else
        {
            expected = storage;
            return false;
        }
    }
};

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< cas_based_operations< cas_based_exchange< linux_arm_cas< Signed > > >, 1u, Signed >
{
};

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< cas_based_operations< cas_based_exchange< linux_arm_cas< Signed > > >, 2u, Signed >
{
};

template< bool Signed >
struct operations< 4u, Signed > :
    public cas_based_operations< cas_based_exchange< linux_arm_cas< Signed > > >
{
};

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        linux_arm_cas_base::hardware_full_fence();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_LINUX_ARM_HPP_INCLUDED_

/* ops_linux_arm.hpp
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
*/