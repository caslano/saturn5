/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_ppc.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_PPC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/ops_gcc_ppc_common.hpp>
#include <boost/atomic/detail/gcc_ppc_asm_common.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// The implementation below uses information from this document:
// http://www.rdrop.com/users/paulmck/scalability/paper/N2745r.2010.02.19a.html

/*
    Refer to: Motorola: "Programming Environments Manual for 32-Bit
    Implementations of the PowerPC Architecture", Appendix E:
    "Synchronization Programming Examples" for an explanation of what is
    going on here (can be found on the web at various places by the
    name "MPCFPE32B.pdf", Google is your friend...)

    Most of the atomic operations map to instructions in a relatively
    straight-forward fashion, but "load"s may at first glance appear
    a bit strange as they map to:

            lwz %rX, addr
            cmpw %rX, %rX
            bne- 1f
        1:

    That is, the CPU is forced to perform a branch that "formally" depends
    on the value retrieved from memory. This scheme has an overhead of
    about 1-2 clock cycles per load, but it allows to map "acquire" to
    the "isync" instruction instead of "sync" uniformly and for all type
    of atomic operations. Since "isync" has a cost of about 15 clock
    cycles, while "sync" hast a cost of about 50 clock cycles, the small
    penalty to atomic loads more than compensates for this.

    Byte- and halfword-sized atomic values are implemented in two ways.
    When 8 and 16-bit instructions are available (in Power8 and later),
    they are used. Otherwise operations are realized by encoding the
    value to be represented into a word, performing sign/zero extension
    as appropriate. This means that after add/sub operations the value
    needs fixing up to accurately preserve the wrap-around semantic of
    the smaller type. (Nothing special needs to be done for the bit-wise
    and the "exchange type" operators as the compiler already sees to
    it that values carried in registers are extended appropriately and
    everything falls into place naturally).

    The register constraint "b"  instructs gcc to use any register
    except r0; this is sometimes required because the encoding for
    r0 is used to signify "constant zero" in a number of instructions,
    making r0 unusable in this place. For simplicity this constraint
    is used everywhere since I am to lazy to look this up on a
    per-instruction basis, and ppc has enough registers for this not
    to pose a problem.
*/

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_gcc_ppc_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        __asm__ __volatile__
        (
            "stw %1, %0\n\t"
            : "+m" (storage)
            : "r" (v)
        );
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("sync" ::: "memory");
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "lwz %0, %1\n\t"
                "cmpw %0, %0\n\t"
                BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+4")
                BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
                "isync\n\t"
                : "=&r" (v)
                : "m" (storage)
                : "cr0", "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lwz %0, %1\n\t"
                : "=&r" (v)
                : "m" (storage)
            );
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y1\n\t"
            "stwcx. %2,%y1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-8")
            : "=&b" (original), "+Z" (storage)
            : "b" (v)
            : "cr0"
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            "lwarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stwcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+8")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("0")
            "lwarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stwcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "0b", "-16")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_gcc_ppc_base
{
    typedef typename storage_traits< 1u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        __asm__ __volatile__
        (
            "stb %1, %0\n\t"
            : "+m" (storage)
            : "r" (v)
        );
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("sync" ::: "memory");
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "lbz %0, %1\n\t"
                "cmpw %0, %0\n\t"
                BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+4")
                BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
                "isync\n\t"
                : "=&r" (v)
                : "m" (storage)
                : "cr0", "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lbz %0, %1\n\t"
                : "=&r" (v)
                : "m" (storage)
            );
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y1\n\t"
            "stbcx. %2,%y1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-8")
            : "=&b" (original), "+Z" (storage)
            : "b" (v)
            : "cr0"
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            "lbarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stbcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+8")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("0")
            "lbarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stbcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "0b", "-16")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

#else // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

template< bool Interprocess >
struct core_arch_operations< 1u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xff\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xff\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

template< bool Interprocess >
struct core_arch_operations< 1u, true, Interprocess > :
    public core_arch_operations< 4u, true, Interprocess >
{
    typedef core_arch_operations< 4u, true, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "extsb %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "extsb %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_gcc_ppc_base
{
    typedef typename storage_traits< 2u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        __asm__ __volatile__
        (
            "sth %1, %0\n\t"
            : "+m" (storage)
            : "r" (v)
        );
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("sync" ::: "memory");
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "lhz %0, %1\n\t"
                "cmpw %0, %0\n\t"
                BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+4")
                BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
                "isync\n\t"
                : "=&r" (v)
                : "m" (storage)
                : "cr0", "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lhz %0, %1\n\t"
                : "=&r" (v)
                : "m" (storage)
            );
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y1\n\t"
            "sthcx. %2,%y1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-8")
            : "=&b" (original), "+Z" (storage)
            : "b" (v)
            : "cr0"
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            "lharx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "sthcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+8")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("0")
            "lharx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "sthcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "0b", "-16")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

#else // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< bool Interprocess >
struct core_arch_operations< 2u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xffff\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xffff\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

template< bool Interprocess >
struct core_arch_operations< 2u, true, Interprocess > :
    public core_arch_operations< 4u, true, Interprocess >
{
    typedef core_arch_operations< 4u, true, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "extsh %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "extsh %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-16")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_ppc_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        __asm__ __volatile__
        (
            "std %1, %0\n\t"
            : "+m" (storage)
            : "r" (v)
        );
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("sync" ::: "memory");
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "ld %0, %1\n\t"
                "cmpd %0, %0\n\t"
                BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+4")
                BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
                "isync\n\t"
                : "=&b" (v)
                : "m" (storage)
                : "cr0", "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "ld %0, %1\n\t"
                : "=&b" (v)
                : "m" (storage)
            );
        }
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y1\n\t"
            "stdcx. %2,%y1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-8")
            : "=&b" (original), "+Z" (storage)
            : "b" (v)
            : "cr0"
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            "ldarx %0,%y2\n\t"
            "cmpd %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stdcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+8")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "li %1, 0\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("0")
            "ldarx %0,%y2\n\t"
            "cmpd %0, %3\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1f", "+16")
            "stdcx. %4,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "0b", "-16")
            "li %1, 1\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            : "=&b" (expected), "=&b" (success), "+Z" (storage)
            : "b" (expected), "b" (desired)
            : "cr0"
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_PPC_HPP_INCLUDED_

/* core_arch_ops_gcc_ppc.hpp
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
*/