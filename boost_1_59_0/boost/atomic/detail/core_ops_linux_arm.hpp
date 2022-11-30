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
 * \file   atomic/detail/core_ops_linux_arm.hpp
 *
 * This header contains implementation of the \c core_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPS_LINUX_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPS_LINUX_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_operations_fwd.hpp>
#include <boost/atomic/detail/core_ops_cas_based.hpp>
#include <boost/atomic/detail/cas_based_exchange.hpp>
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#include <boost/atomic/detail/fence_operations.hpp>
#include <boost/atomic/detail/header.hpp>

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
// https://lwn.net/Articles/314561/
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
            fence_operations::hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            fence_operations::hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            fence_operations::hardware_full_fence();
    }
};

template< bool Signed, bool Interprocess >
struct linux_arm_cas :
    public linux_arm_cas_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

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

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_cas_based< cas_based_exchange< linux_arm_cas< Signed, Interprocess > > >, 1u, Signed >
{
};

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_cas_based< cas_based_exchange< linux_arm_cas< Signed, Interprocess > > >, 2u, Signed >
{
};

template< bool Signed, bool Interprocess >
struct core_operations< 4u, Signed, Interprocess > :
    public core_operations_cas_based< cas_based_exchange< linux_arm_cas< Signed, Interprocess > > >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPS_LINUX_ARM_HPP_INCLUDED_

/* core_ops_linux_arm.hpp
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
*/