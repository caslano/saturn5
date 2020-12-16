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
7q7Tl392N9XE3RnsbgRwIvBMcYdnkLW7G9ndVna3DXhLG/fKt2af/MncI9/W+0ROdE98S3eaYj/8T+JukeC9pie2z/0L7GOP2eRUcmFKYa6BeQjmLZgO1zmVoTCFMKtgHoL5ACZiM97DuGAqYa6B2QVzeHNwT3zwCT7BJ/gEn+ATfIJP8Ak+wSf4BJ/g82N6TtL+/5q68vbZ//+S7v6/HN7X/iJMV5hnYPISMLeSLHsezp46cZBsPvasrVtD88pYju2dd2Y3CXLnUzbR9yhj+D6ntEiaby6p8t7tzm7OMl2/4BL7aTQvfEmU771kaWRXrYxHrHh+mvnjLeec0xTmkblk8znnbAPfJllr579WewPx5Zne6VNgcqePK8AdZHRnBt9RM7uN946tobls5Ilu7hppjneU5jx37b/2YQ3wEt08eKPJXPYmw/1kBSZ3yLgC3SHD6zvXU1rRtwbvnf8RzYn/9TxKhwfTl03bV5q08Wjmve9enl8cvHdeP/fdIDoB+pLnWjoB67gwxvL53XHABGA8MBnYC/gzYG9gETAJOB94CrAG2IfnJhOAa4F9gXcAE4FNwH7AZ4BJwXvg223O5qcwXxOcq/nv52pKrw/OrwSf4BN8gk/wObHnJPX/KyvmtE///znd+X8duP//HN8RfxfMyAT0x77u7Nf/D9T3B7/P/fCXEL3Bst8Pfp874pcSfanpmvbxsF9C9uuJdon7dP24gPTHF5PdMhkTAK/PHfFfEe0MOEYAN9L3L7YaIzDwlXP62E3GCD4nvg6GbzC/d/7K5rS3vHf+xfi27ek2jgsUGMYFLO/cNIwLFJuMC5RbnMuWxueyHWW5OgBToMnVN75yRQdqcLr9KVqBHbY8eOUK/Aa5IvpJK7kCv0GuiH7AWq7I/lGvXBGdzvltkCuy2y5yBV4fuUr6tnOL+zfhxm9vRILF/k3wtnr/pp63kcIU2S6prJxTMneB7x5O8LdqDyf4WrWHszfFPZRpSgtr+SY/77CU71fi27aPE3ID+YPc8LtyE/l2m8h3vchufcB9nAkt7OOM9d3HyeltupdTxl1j+HypTAe6XcCOwPFw3/CtSfnggVdDGZG7y/eTm3Pto9UhOAXgWZXLDvvlEvmMs3UBfbVJ2cmj9PmU+B+zc1li91cqRMP95O802mYyVptHaXmE+JvIvcvg3iXuQ41li8rhc8TbU+WyxW7PkbvER9C3VxnLluiFZ4j/kF1f1uCHyK7LaVLW4HYaePcR31h7gi0F4eMdhwc+b3k0+FfoNCmPfIZBF/zTuGz4F83loxu9+xPyOoTLiCeMam85NoRR7DQvx0hvkvHXiPcNeyyfu/Ao0TNx13w3dbpq85Z3g7/lTr9zHEj//5V4nrV3Zv/eITrbqw8M/rg5DSJos8HcunrdWRgHiW+f3UxfxAHfJVk439ZM++Yv6jc8dC6I6DOvP6W1Fb8oo2/WvucYhfOwPUzsK+SsnDxK82NqiPKU+pKaIGPsXt759C7f/z5+ud/1PfL/SfjvsXdLmyC6uRzhQbOMJAruWKY+orBZnqTsNdJ3F4LPRvG/0252dsR+/p47yO+KxfjjqS/oHu5MfMe2MOwlQDsuImTlrvCwEBvu4rZFxMbK/MHiKDF0F7fHnSMcejAS7mwrq8KT4SasM/44unl1AkVE7tL/jOKRQN+zSOYrvHr/KNlnUBgrEXYfvMvto4AbP7qSTidTROg988Id12yfFwkEngu99lACZK4vnYPhY/cM3KjAT+AmqzvG2sHz+2TiI+PsSih38R9u4byM/bq7+CF3chc/nVXk9K9Pcpz+9Umu0+QcW6dvfeJy+tcn0BvG+gTl3K8+QRk1r0/cEsY=
*/