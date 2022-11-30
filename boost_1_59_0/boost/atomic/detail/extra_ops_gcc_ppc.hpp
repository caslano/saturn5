/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 - 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_gcc_ppc.hpp
 *
 * This header contains implementation of the extra atomic operations for PowerPC.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_PPC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
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

template< typename Base >
struct extra_operations_gcc_ppc_common :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::negate(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::add(storage, v, order);
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::sub(storage, v, order);
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::bitwise_and(storage, v, order);
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::bitwise_or(storage, v, order);
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::bitwise_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!base_type::bitwise_complement(storage, order);
    }
};

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations_gcc_ppc;

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

template< typename Base, bool Signed >
struct extra_operations_gcc_ppc< Base, 1u, Signed > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lbarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stbcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_gcc_ppc_common< extra_operations_gcc_ppc< Base, 1u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< typename Base, bool Signed >
struct extra_operations_gcc_ppc< Base, 2u, Signed > :
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lharx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "sthcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< typename Base, bool Signed >
struct extra_operations_gcc_ppc< Base, 4u, Signed > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "lwarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stwcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_gcc_ppc_common< extra_operations_gcc_ppc< Base, 4u, Signed > >
{
};

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

template< typename Base, bool Signed >
struct extra_operations_gcc_ppc< Base, 8u, Signed > :
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        core_arch_operations_gcc_ppc_base::fence_before(order);
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
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_ppc_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_PPC_ASM_LABEL("1")
            "ldarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stdcx. %1,%y2\n\t"
            BOOST_ATOMIC_DETAIL_PPC_ASM_JUMP("bne-", "1b", "-12")
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_ppc_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public extra_operations_gcc_ppc_common< extra_operations_gcc_ppc< Base, 8u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_PPC_INCLUDED_

/* extra_ops_gcc_ppc.hpp
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
*/