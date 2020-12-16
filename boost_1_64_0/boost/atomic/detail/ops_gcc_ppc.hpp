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
 * \file   atomic/detail/ops_gcc_ppc.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/ops_gcc_ppc_common.hpp>
#include <boost/atomic/capabilities.hpp>

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

template< bool Signed >
struct operations< 4u, Signed > :
    public gcc_ppc_operations_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
                "bne- 1f\n\t"
                "1:\n\t"
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
            "1:\n\t"
            "lwarx %0,%y1\n\t"
            "stwcx. %2,%y1\n\t"
            "bne- 1b\n\t"
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
            "bne- 1f\n\t"
            "stwcx. %4,%y2\n\t"
            "bne- 1f\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "0: lwarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            "bne- 1f\n\t"
            "stwcx. %4,%y2\n\t"
            "bne- 0b\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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

template< bool Signed >
struct operations< 1u, Signed > :
    public gcc_ppc_operations_base
{
    typedef typename storage_traits< 1u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
                "bne- 1f\n\t"
                "1:\n\t"
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
            "1:\n\t"
            "lbarx %0,%y1\n\t"
            "stbcx. %2,%y1\n\t"
            "bne- 1b\n\t"
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
            "bne- 1f\n\t"
            "stbcx. %4,%y2\n\t"
            "bne- 1f\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "0: lbarx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            "bne- 1f\n\t"
            "stbcx. %4,%y2\n\t"
            "bne- 0b\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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

template< >
struct operations< 1u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xff\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xff\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

template< >
struct operations< 1u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "extsb %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "extsb %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< bool Signed >
struct operations< 2u, Signed > :
    public gcc_ppc_operations_base
{
    typedef typename storage_traits< 2u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
                "bne- 1f\n\t"
                "1:\n\t"
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
            "1:\n\t"
            "lharx %0,%y1\n\t"
            "sthcx. %2,%y1\n\t"
            "bne- 1b\n\t"
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
            "bne- 1f\n\t"
            "sthcx. %4,%y2\n\t"
            "bne- 1f\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "0: lharx %0,%y2\n\t"
            "cmpw %0, %3\n\t"
            "bne- 1f\n\t"
            "sthcx. %4,%y2\n\t"
            "bne- 0b\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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

template< >
struct operations< 2u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xffff\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "rlwinm %1, %1, 0, 0xffff\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

template< >
struct operations< 2u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "extsh %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "extsh %1, %1\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            : "b" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

template< bool Signed >
struct operations< 8u, Signed > :
    public gcc_ppc_operations_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
                "bne- 1f\n\t"
                "1:\n\t"
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
            "1:\n\t"
            "ldarx %0,%y1\n\t"
            "stdcx. %2,%y1\n\t"
            "bne- 1b\n\t"
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
            "bne- 1f\n\t"
            "stdcx. %4,%y2\n\t"
            "bne- 1f\n\t"
            "li %1, 1\n\t"
            "1:"
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
            "0: ldarx %0,%y2\n\t"
            "cmpd %0, %3\n\t"
            "bne- 1f\n\t"
            "stdcx. %4,%y2\n\t"
            "bne- 0b\n\t"
            "li %1, 1\n\t"
            "1:\n\t"
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
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "add %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "sub %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "and %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "or %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "xor %1,%0,%3\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
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


BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
    {
#if defined(__powerpc64__) || defined(__PPC64__)
        if (order != memory_order_seq_cst)
            __asm__ __volatile__ ("lwsync" ::: "memory");
        else
            __asm__ __volatile__ ("sync" ::: "memory");
#else
        __asm__ __volatile__ ("sync" ::: "memory");
#endif
    }
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
#if defined(__ibmxl__) || defined(__IBMCPP__)
        __fence();
#else
        __asm__ __volatile__ ("" ::: "memory");
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_HPP_INCLUDED_

/* ops_gcc_ppc.hpp
2waXi944SDXfBPzgSR8Hpmmixp22sB/cQnhr3eFdXm9ZqbLtzft8RvRdbL81aZOMfDeztuaFOvO+a9Iwbv1ant+r6SNsvpOpZ/7hjLp6pmftlmfdVQXyug+GmM+y/dZ15ccpb9OMuSQzD/2A6Ftof4P/2veA+O0937Vio3zWivXwWStGuo9Zs1bjHw6zjmyIltO1pOfdU7S8XNfOKQJjy1WVO2DkkuuVS56qcjUf1yuXb+Re85XLVrm5Ksdsx6dCLepK6Xiym8KyqTX3I5mUhUw892vD7i937GwVV25/WG4mcomZXjkzV6w9Mu1kHV54DV5D1qEyx9knT25yr7Xz3/vCsxau2LPGrkLLvNg1daN81tT18Hxfcoy+UvQ1Rl+i5WbsGrtDuueG/xka8c8A8T9DI/5ZGf5nccQ7s+LrO1vj6zrjYrec0TGm50XXv/bE+9Urt79669zeo1bGP6PD/8yN+GeM+J+JEf8MDf8zN478TBX/s1y+vrM4jvRMmHhnvHxi8W5QXDIHI8dG8TtNf/e3oP6ex+82+vsafof09wNOuaK/q1C5+nszqpf+vgLVWX/fhGqivxcRvk76+3x+f2iRJizdn1H3l+SZnN+9U/35Ctu194Kvwr7wdTgGvgEXwjfhGfAd+Cj8M3xK9XwTRV8F34U3wvfgLfB9+Dj8AL4N/wEDjp9gNvwIDoWH4HD4CZwD/wZXwL9DOSMlvG8cbIvK8ZyRssLmjBRYBaW+ATNEHzG/R81n+Zg/R82fC1vC82Ar0UfMH1Dz2T7mV6v5NTANngVbq17NM7kzvv/Xq/kN6v+N4n/0an5meF8w3bMsR/vWJkM5V4rX2x1+DHvBf8Gx8As4GVrYM8MBXAQDcD1MguerfpPqb4VN4S9gc/gMTIEvqP5l2BK+ofqPVP8xTIUZTtqC7WFr2A22gUfDbDgXdoDFsBNcBXPhd2E3eCvMgz+C3eFu2AMegr1hRgLxBtvDvrAr7Af7wf7waJgPR8Kj4Dg4AE6FA+GpcBCcCQdr/K42eyiRVzR+nXdTrvF7LHLd4VDYC46Cg+DxcBYcDYvgGFgGx8Kz4Ti4AZ4IN8MJ8Gk4CX4Ap8B/wamwLW4VaLw5+k6qHwpPhjPhDLgSngqvgjPhTjgb7lL9T1T/gOofVv2jcA58FZ6u8VkIv4DzYRPCXQTT4QLYHRbDE2EJnAYXwdPgYlgIS2EZLIMr4BnwHHgmvBCWw0vhEngNrIA3wKVwO6zU+N8U3s8FjtT80QKudZ0V5PAamAy3whR4A0yDN8K28G6YDW+FuarvAnfAHvAO2Efv94XXwoHwx3CE3v8Qbjf7oUgaFv/IPDn1z0v4Owu+ArPhATgNvqrp4DW4BL4Bt8C34FXwT/D78B24Ax6EP4CH4APwL/CX8D24T58/p89fhx/CgC169afufwFv8vHnp8jlwX/AYfCf8CT4uabbL+BCaFHOlgMbVsIEuAoG4LkwBV4Lm8P7YEv4JEyFf4StYYmTv+H5sB28ELbX8rsgvA8AvEffbxM4NnxGj353zoeD4QVwKLwEXgo3wy3wUrgVboGab3VNOGkvMTbfXq32XAOHw2vhcfA6OA1+D86C2+ACeBM8C94M18Nb4AXwVngbvA3+EO6Aj8M79Dv4A/gO/CF8H/4IkkesWlgB74bVcBc8G94Lvwfvg9vhbv1e3g/vgA/A5+BD8BD8KXQ2E94DB8GfwanwMTgPPg43wF/AK+AT8B74FNwLfwk/gs/AYIC6F+wGfwV7wX3wWPgbOBy+ALsRn7+D/eF+OBb+Hp4IX9T4fzu8Xg/KWag6b/Jlfa+zkGsOZ8NWcC7MgqfDDnCevo+V8Hh4HhwHF8BJcCE=
*/