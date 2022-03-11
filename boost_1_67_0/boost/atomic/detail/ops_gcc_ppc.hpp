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
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
*/