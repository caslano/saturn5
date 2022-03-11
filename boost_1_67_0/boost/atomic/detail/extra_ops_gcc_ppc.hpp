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
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct gcc_ppc_extra_operations_common :
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
struct gcc_ppc_extra_operations;

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

template< typename Base, bool Signed >
struct gcc_ppc_extra_operations< Base, 1u, Signed > :
    public generic_extra_operations< Base, 1u, Signed >
{
    typedef generic_extra_operations< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lbarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stbcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public gcc_ppc_extra_operations_common< gcc_ppc_extra_operations< Base, 1u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX)

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< typename Base, bool Signed >
struct gcc_ppc_extra_operations< Base, 2u, Signed > :
    public generic_extra_operations< Base, 2u, Signed >
{
    typedef generic_extra_operations< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lharx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "sthcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX)

template< typename Base, bool Signed >
struct gcc_ppc_extra_operations< Base, 4u, Signed > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "lwarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stwcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public gcc_ppc_extra_operations_common< gcc_ppc_extra_operations< Base, 4u, Signed > >
{
};

#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

template< typename Base, bool Signed >
struct gcc_ppc_extra_operations< Base, 8u, Signed > :
    public generic_extra_operations< Base, 8u, Signed >
{
    typedef generic_extra_operations< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "neg %1,%0\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        gcc_ppc_operations_base::fence_before(order);
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
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_ppc_operations_base::fence_before(order);
        storage_type original, result;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldarx %0,%y2\n\t"
            "nor %1,%0,%0\n\t"
            "stdcx. %1,%y2\n\t"
            "bne- 1b\n\t"
            : "=&b" (original), "=&b" (result), "+Z" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_ppc_operations_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public gcc_ppc_extra_operations_common< gcc_ppc_extra_operations< Base, 8u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_PPC_INCLUDED_

/* extra_ops_gcc_ppc.hpp
LOwtM1EuGYxFo4CeloNvM13u5Tqn2DKes1PafiWzMU1mgRTBfZH1+QCbE/vQ5nl3P3fSZnvNvagfCcPKCYHWlkVzxiZ6RALC0tpDADPPAyJYvL2MeVurZnuWG3X09+dUypG74TI8F0viErZN/BW20S2Y1SwVuxsSU6VSL4zNCyI6QAN82o8hkd80+8tUyZv/eMCieky5pTQlC8IXACQTwqtySDNqDwbrsF2tFxCO2jGbCC2of6CmdnEaR6LsE3PinYc2hqho3KniJ3zv8Ncimk9zDFTZSKRs0EojvYeDXSybYcV9h+jpbLmVN4yiEyYioykYEtSSspsp9SN6ATSybgvUuEQ15nzOnTzpqlSJvW/GuOStCzfVXb7GTVy9fJ1H1lmJXXJXOnPwHJFcEmqvPSukhfX+O/McHPf8whWtCOq2K5iqgeeEF2EklZhBHTbdOTsgTDNxaxUzSN++5MwOhNrV2qFeO3fHknmH327YWsA7UmuwuPI6dfOSClb3MNhfJzLWr5dQ0mDTNzFGUzaRV0ooruxKylydf1gcMrtZyQY9vqmYO7yg3PzhLil5AOsTskwDbxi1GHElXn+QmCxoeh/OIwp9VvyO6sncuxMzbm+e/o+zxV2ZOLk+oqCqO6Lpk8xSdDkYtar6+ej48AdxPLTgZ85HorUkBFPx+kWl7XF9ZeC9XuGyYeK/yEHKdZADy/lkIs5bnt/D40LH73Qg43UHcNXVsgYm/Go9lHVod+Xh8nH6HJa8BCaYa2ot45AJMKHsHEaxuQfK08xlDYqlFGBUYv866bWAdvYV1KrE5SB2NdFIaboT/ZwBWKmRgRvoCRrkNUfY484NhapGIPVn/m0uutZ342OatRWxWKmagZj/Qp/V59Esm+R79Vxc/CIioGFKJIZOdbA19a0v6flXAw03HhOIh62w6guPY/uhmyY6omNiEnR5FDK2gM+63RFmMLaxhGOoXE6My1cImXHSpCkemYSPh4uFtzjgyZYrdmeHbYtXNj7YbehWEZNsqzCCFOiS1LEJE4/2Kn3YPdXLdSaAT0ta7jQzPmo/n5I8uy/UQFUjv4/WS6A1II3Oc85FnhNvWNYjwhffieXb00stWKWHfYIeOOZveg2d++cOfBkwHW6u85aj1Jn0cuaqvn+yFxk8leaUBiNmClX7/G4lysnZHERhP26040XMIhklI/ydd5wSlgrjd60N2/OBXqW6ZlvNKlPbRVVvps6AnX0OC8mf6hcS+KmJmiaIxHc7CzQFI6GjCIioaDXIVZw0gKa0mJhhmWOHtILkBxw42mKEuOFGtVpE9rIJ4dzCQESBXMOoAnfriTv+we0pTTzTUTkyqzWqTkjaXkSj5/mjH5Wk/ouNJtxP6dMMyJfOFahOzAmA1ue4SIF2i8u9B4de+w+rYbkBh3Du/J97cmm+DpGnkFsfymarE8aCWrg2OvgCchoUrFxpzTuRY+3egp4r2lILGuUGPSzhhkghxFdO6ZWFon8Z9Ll9QOBaZn+pdt7uZaA55PxBEdijK4ZlQjlkwsGDaz62WIZgcxElBKqBLNitSz92WIZgmaN/RqAKsbUDZCawCjEiiuDEnfYhF/imqzvO29Z323B0oqXycWAbsX24BHHcUvCJYXa029Zi9Z1xIWFUXEqPCeLkBKkdFLNQ6m2FrmGnacv9JfziMBGM/DWFrmGHaRMk01AdTPsSSFN4FZLWkMnVg9Yjz/u3dXrZNPNgwpx3lWuLh8rV0F4/zRPzuGIZ2pWHbiHCrmJRahUcz5veEs0686LiXGURHMLb3DDNF/O6Vjy0FvY8jXtYAH5VMFCGkwy9o1A/9JQDmyVBdPqSQ9n4kxdOVbNSNcaqQ0n4v0012BiM6/S3aIzbdLpVaGscFOmXjPRLhz5vnbkq+Gl7ntqQOyxGX4DGutOkgvRq8OP0uckm/5C8JHawqyhgk5nMdNpSPC2dvnxcU3wtn9l8nFJfI52bfAxTOyOf/aRuJFewXiuCBYR6cHTZLCnACCSlEKJkdokQs31oEe0LN51qDKuQpmJ2mZC5/qZRBt4VBFZTVOuWc6W56mRwbFmFkjUhgo2iseo8cAHPhhh8bZ8FpVwkI08O654LouX4h+pgcCvPghg1Y4JNopX4JiQRz4mOPGufw6UJhJlqKcmPjrALo0uE2eoYcB1PVFpeHdzl+DikCFeGWnwdn6Ul7O5+vMn2ZuP7/+ph47PCVoLWfWg3e5h9Q9SRrLJYuB26nH3BHmLO4Veoy7KUuBu6nH3ANJG2xzTZAzxFnmUu4TfGTjkeup59wLwiXxBcsjU6ma3efXJ+HcRcKt+i7lNuCOfSSzmV3YdcKtcTjglX1MdYIb0oX6KeUh5ozjJ32VHsLj+gf1BfaYB4lx2h+gnTJXnF9N+UY+lo3iv/M5S7VxWUKTkioL7I+8I8GbIXYS55f/LgxnSmAG9CKHRwrnoXOrRIZchBQMocwp2hqH5P67agBS/hVR2/+F4lrtf+WerGXY6waKFJIuWeZQaj2E64QJ9rhi37sLXoqfKpEwGM9KjyrxvhjnSp+kEQaY80qepHGAleflHZMtdmKBGTHKLR07JfICFTkTMfTLogM/8GbUY3LjcUabaoMzdEvWAz5/5kxn3UTpPcqlJn8ihZ5i9VobHTEscAPiwxU/5XGkADUT2+sd00Ir7srRJXfc40UqGsJDlRikpTVx2+AYxSYqWsJmhaWgSzb1nI8hHNTBlpWmpHY5RxeAqmFGlZ2kbjVC1vidTmcccMWQoCk89V2PYhzwwcifrY/aj8rMKWgdRWohYppiJE2V3VbCQZUXrySke5nctLLRlTevPKl0N/3c1BkqxcIZlSOvOqR/l9KUIpafdalmN+zX05oiWZU7rz6kc7v9NNs2xZGgKzOxulizoug3JLr7PQ7euMfq6iSlOfbcFi5A7nlPagDJgbsU3YXdTl/InuqgKe1bET2DvU/dyv/JolYAfzCyJAdgGE8AZEgQBD8Q+cghuSQgguA1k6DdyYZg1Rui8q6T9ppDQyMeE8MxHF0DroYpqx5EVc6UXkoGwkeOnjIC+cs2Qk1nIfsbMgIBQzwrOMR2+FeOz0zdwhGCbJmDf6sVuohjz8bVQHmULt8aI1AhQGpnC9emxzvThgwH3qBUYmu71WG69vCg99Jwn0Ij2zgr40G4dvDg95pwqnBbsiH7OivvS8OJsD6rTq2g9mBxBdhP/yEEHkt5gTxHsL0vmmnH2XZZMIMYWbIQ6WYotUqQUGoZGXZ4tWlQdlSfNFcEVxRNFFMUQxRQu/A/4LBwsGCwfLBokHSQbBQBVa6F6trgNtJm4XbjeuD24vrh9uP64HbSHuEK7INVC1RDMRVWYxCHT5OcZmR9hASaCoYx5jnGM8I74jhuCC5yLL1yzLdJD0hdKX9Ink7/VBHGoo78lU7P1uKJfok7azt+vnR5V4UR1nD9mIYJYgkSBRIMmYQcMxwhHCUcIBwUHGIcJpeqaFiWuRo+Rn287YptzW2q7eZtDk0tzR7NMU0BT6EFfOiLWIFCole41Th1eXU49Tn+uA75DriOuYw4LHkqPlR/NH43fz79uW327YRtp22k7ebtkG0qzRvNNs0HTSnHexuApaI+OFRIgADwaNEyY6EBZKEioyFQ5KE05IgIQSmIbRSIBUi18YMPNAgilDR642w4RXEViGaaOxthTCTAzX6mF7EcY0Illsx3cINn9VQffSTOIp7v49wMBsgqz6UXxmEToqpZmCAwQ78BRSB5kFWFavV6RYokMMNGBe2OMBB8uDBdX15H2hrX3vbeldQ6v3HS6J/vqHmrHJ2Rxto3uSMkETKE36KIwaTcVUk1qeWm47hh+mTZStQKzknrneE6xdBr3M1NSCttjDH23BM1Tfup7njZDL/FTyao51FrHBM1rdT71QPUC9WD14rZnolqmV6ZapkWmXqbCpSm2hAcLRVCS3jFeRX0FQoQ/FiyqAJoA6sOZTF9wQHPVU8mz+YvFS/VTzZP/s8HxtbWkrqL2uta9zrnWv864FqAO5dsorwiruUe4O6Unu7r1coA9Tf1W9e9Jk62tlgXiHqEXcym8ElQiTDBMPk/mWv67Zo9153ebdCNON00LdzN0g3azdYd3u3RDdPO1BbL27QXREfFx8TnxS3CExz7/Cfxp4K3gj6BVzhhmCdrK+2TPtGexU7DbsdOwG6k3sLOxs7B7sXGy++552v/aDvjfyS/FLcV/xQ/FQ8UUxLf0j8ylzJ3MvExAJgUeykmmZJxSWFidF9ZOoVkAi20UkWzAs1qXHqkIgGy6gwRBOPyvUX89mptIfMKTW8HWrcp3INILELsp5JEphNLLIPuogYX6qTOaVmcxT0h35EgcdgVJJULMVDUV8IxTzogrPSzKO3yWZJO6G+jrDSoZaIoU+U6lQgDL+KH/3bcgobLA2pGef/7VrGQucjkLnWyuJyjqVO96Y68L46mqhnyJLPIM/lhcnUzRVmKZCoUIWTh2XNj4qV2aqIkWcjlQ7vUqWIk6MKck289vNkm5FBam8pQTE0cuySz9L/0tyS4LHIWvEYaZh1GGbYcThu+G20cc1VN4uUy5cJ5wv3CBcKNwkXCxcIlwqnCfcIywQ6BTtEW0X7RDtFO0SrRcdQHLOpSK8pXzB/8X/wH/A/58Otk4Cxa9nzoPTLNO8003TfpNwfRCYvPtA15D4Dx/PFdNCU5m7VnZHaEBoUWhI6BlDvrOAiYCJlkmCTJNMl0yVTIFMlEyATJbMgodTYFD1kQTPTNPJ0wTTqtNl0xTCbPwrwl38HEK8u0L2SeMGw7z6QLdQiluKUYpQSlJNW03Rze02wTArke4D7QPNw/2DX2lhiXEpacl5CWWpdSlojFbsXqxR7FlMQfYSG6Q9og/DCHIsJmQepiQRZmQZuuQsFlQ9JmkxEipsJmdTEVLdcHH03BUJh5w92cYc00gVdCWnHXNr6eJX/agRR7Ll13SNquNWxQd7viXQU010oOXjq7LwhlsOJqLsIRX1QSo375UbAXgH6dGJSG2Ccr0jRRMCYqgB9cKtJyx2EJw9LWFf527N/XZlW7A9+f5hTyz89YhWYueqfeSBgnG8yDBMFP71zFWwFhJvP5e3c+38v7hocmwZO7G9lJmi7DCabcn2EhvU6SJ1dJefLGkVs/l6GBEtx07XpvtHifM403kjBGN543jj+fODxeGFYd+ccCd6J0gnezNChU5Cz/dVslXI1YlVx1Wq1efVmVXX1bpVhNWF1ShZEtkyWQrZKlkaWTtZhptpHXHrAJwMHAOcCpwGnA6eLx4HDmSvoeR6t3A3ejdIN/sKwoXcxtUHFgwcDh6NzbMqs5b9pu36yzbL4ct0yxJLpdeF1YbVp9UW1d/V3Nr6Wuba/Fri2vJa6tp+6wWeiMsmtHmseqxwLHosyJpBNEE0QrdAt0E3wepOy1Xg1babZOuG24FbiVvd3eYd0F2UHeJd5h3h3d8tSDA82g3WHdYV1nnWEdZ+VlifNsch1znXNdezT5tZ5gFFhJYHOP4koLC5f/dzDA9ziI1z/z3NHZS4GSEaQw6fg6R9JZlTP2ZxEMNEIItPfoWZJxMEG0c0glT2PGg7ZLlVf22tDWhXRL3Zizd9KQRbkQ6jUuS8SY1nWbtf9CyMug30SMS9WQmBwkUIPLyADIPoiG97Mf/nPg4iktDgRhH0VWWuHWWFTkwX4QcSoM9+aCRCHZVlRywfsQUSot/MbXLoJJKddPUUUStRhFxyVJJkDyk3kh81MSxBfH8yKDPS/99xoQQJMtWgyjvFcMTnUQwk7jvQicQnMitk3uDFYICniueap4bnlqeOJ98IPSw7LD3sMiwB7DAsObPFBW8zRVky5RFFEgUyhRLFEWUSJTKlkvWRVZIVMiL5WhnmOBY5Fjlmuda4NrkoosahfMhqiHvIZmh36G6IfyhwCPErRBRSTWWNrxaaNumqWRrlVKImCRuc59U6FrgW+MoY7bF6uRGFMYVRhdEEa5wlSRoJ9hAeUd5wITHRMClx2UglCdUQLVHdsCZcKUwnum+vTJdNW0xXTZm8U6rzqveBb4Inou4Er/K+cjvpq9QdLgkWDTYLDg+6CJYMpgqODroJlg32y/rhxuMW8O5j58x3V7JF7WCNZO0i9lFOU25QDnJuEdtDnfK/8WHECKJkCfTkY6EklKjk4+RklOzTo6LTB6iICGoFRUqpiBGTV+q8y8dU4tEkJslqUywqxFTjKkppCWu1oZmGV0m7kzZ1p9kHLSWNyKZTv4vFlOZZh5vkvORCqgjnk//kI73VGvpPClKL3YRmJhglb451JT6oBJgkECOfL5v/ReyY7MYCZjWyD9tP7B31pj5N2eAIsp3aSxwkiU7AJSGj3k7p4ARusbP/HiXtIRzIT5EpkitkUbeMrY6lylNRGWc029HsJVGkslJXt47tIU+SZdMGN48dJ02XFSVnyvFR0lNzk3GQsZPxkAlT/pcZnAOVCZOZmJGcgZV+zSnS5WhH8wLxMPYqdlf2GnZH9jp2Z/YKcTf2HGb5vlGzQ7NQs0WzXbNNs1RTpl2fo0vgmu9A4Jvvle+WH0EaWlqkAaSrxfHpLWOlYmWj5zLzr0ZYqbNJwD6fqQLZMsWK5SBtqf2F/Zb9p/2GvUvYqDqoNak1rrWBsLOwjLC2sOrQVFRctP83k9vx6HdV2zEG8qaCK8hdQkjdZ0I07TNRYyhBIwRVrQhVDSxTbW4hTGxaepV9HkIdtY7KLG1+qdIMecpS7WRldnmp3cxtwYxDw8HMb7EsB/k6ndc8Lnl1JjIrKS+tejnbsi8VrQK5nVFyW+0uJXJXDWgBGXT5nErRbC2HPFl0ulJhWnKFPMk3uGVrEZ6HvEsTgBG4Bk1tpfGnvyJIGaAT30JEibbXygRnpmKAOFr5rffKzfB998rV8HuauJ4/RjJRMkoyWTJFsjVZl1G2U4xTtlPqs9Ql3AVw2qtAPaFYiVsZR9nbXNu82zjb+Ft8W5xbBUfFWyP7/mGNYdrhveH5YZ1hxmGkYRCj2jlOslAySbL4L9lp9663S2BAaZsJjyzGrGwOYk7Aw/sSR4oxzGUUGI5sdbJVDvaluspjk0fDx0DHgMciR4ZxMuMzYwzj61+7G8+YwHjImMR4zJjCeMqodtn0GQB2nZz18vXy8LL1stC4/pz+DLojvqO+Y472uPJR5pFjjHNZ9Rn3efCZ9Hnymff59Rn0+fEZ9vkAto2WjpaNBlhz1VrQ2tXa0JprS2wLytbIA3WbeNt4u2h3snsZnnJsLhHHENNbwD5Oyl5eyUFOy2beyE7egSvvlmSEipyj50bXzOrbM4LGKsO4Pe2p15xqesI6U5VF1WwmI2WPw+IZdj8mQ2WHY7w171HW8qiL3EbjhvuwBVlzbNFSxoMd3nQ2gPff3RG31KSMew4yrueui5vS5ZcUB8uLXKEm/sOe5e3R8ShlQC4YL0LHtHvJq80ByhBlTAYqJ31XtQ+Lr8mrzSHK3uIMxUcWv5TMVEJ2HhehZ+oZciXu9BYu92CTpRGKrJTmDo170iWyjBQO9q47SBWa9BR2Ft/uyg4YNy23IxcrbycvL3cgD1IPZA9CD0YXQQ95F72HqiuEq8V5ytnJGerlyWXK5clFygXqhYqNkS2y9dH89NrMpsz6zPrMGo2WlM4USXYbrvx2y477jsdO91bPlv9uwC4xFxS3Ys95L0HXeC+922rtqbIMNXbu1g73LVdgN7/HqYuYVdI9yuPxY/Lj8YYMM64stiy2dNYczgLOIs58thKuCq4qrnLOGm7NVsN2Nvdg93yXeu9+l7knWo9pj2uXr+ese+x53AbZK3VnmgebT3tyd3J3Zlt2W2FncWdlV3VXY3dzt6eni7ePW4gvmBeSJ6Eno7egp6K3oeekj63374/OW84R4YxqCCuKMxWeH08lWtUr4ZoZ3Voe2doRnRovu5tQFj9BQLqZdRwPiiEVkLISBSvBSFeMM8Y2RwAHq6GFd5yzMpPDxSo+FGlJp9no0lx+MpIgFEkZmabNpdJsPjsDiQ2coeYdCPthpRkaCAm/TYL32dJ/n1v5+9SSZiAGN1Tsiq1mjECDjCOaIHq8vfpMg/86AKEl6URkQQZOt9hz9DG26bKEQ8rxDEmBGn7LdNfoVnjWevz0y8N6ALTpBRhc2daPKDMhP7R+VQeF3AflVSIhZAbFQoL/sUzZyQ9KhcAwdzsZWpzYr9iH2KfYl9izaHgoQTNJMUEzVRE9EU0RRdVBJPx0+wTjlOGM40zgROJM4UTjzODE4tThzOMoDCJ/anzSfSp8Mn2qfN6+BC9XShNafFSuVIZUplSWVLZseWyZGE+1RVGg36nJn8mnyaMXIxSFICw/WpQYW7VZVZ01nKkhLHyTcCJyInOecKKH6C872jzaHNpc2vRulWyFbKVsfWydbI1srWx5oEpvTFWvac1Z01vV08zR0rX/wx3A+7c3uE9YMND8ae0CDVNYgYYq3Q3dRdUl1WXV9dQ91R3VXfW7ATQTigubDZcIFwhXidSN1IgEzGVAGECbRVvAqFWm63sa+n0Vu7TDpUAiJ2yCKKyCLIyKKsyyhmFinTiHHBmQRJi4VyxPmQnmMb30MF/b/Cz5rZJCQm5a+EoCI1oVU2hHgiKpWCjFashAUtKsL+m49FRNbmnYRtLQnNg6Hi5KtUNCL2rVR5JIR35dGFF4+TlM4tacfKESPv5OQo5eRWjIm0IiY71/1q8ILOJ77WtPdYA+3BJehCY5jZO9IepK5Sh7jD7akpyfakwoGY1ljGmMicUAeXAm2Sonrrxj6mK1f0ZuyCxdjTPsZCXXmiVrj23NYq67YCjdjeG9Ad6R7zJlb2sX61RrN+t0a/e7wrXGss6y1rK2ssmyyVJhLDzJN5qSVJFRlVGRUZDREtcV1xHXEDeSMpUykcLAkMFSwl7B3sLQwTDCPMHc0lrbDeds6BjoWeg46HnoCOxGuJf2i7zNddV8tnzJfMlcYTydYcCu0Tt7vvaztPQ1Wem5PBUSTy3NoswizGL9T92xyavXZdf+1wTPg9dK18LXKNei12nX4dcIzzL3WWSjvrl91HLIctiyz1J/uWuwaXBFdHZ0avQsa54Zhnbasck79xXsXOQ+5HzkHuxD5CLkYuQB7FJksf6R/LD8m7yv+9L5wvnM+bz51vnGOWo=
*/