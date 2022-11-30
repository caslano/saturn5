/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_gcc_aarch64.hpp
 *
 * This header contains implementation of the extra atomic operations for AArch64.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH64_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH64_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/ops_gcc_aarch64_common.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct extra_operations_gcc_aarch64_common :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    // Note: For opaque operations prefer operations returning the resulting values instead of the original values
    //       as these operations require less registers. That is unless LSE is available, in which case
    //       it is better to use the dedicated atomic instructions. The LSE check is done in the base_type,
    //       where needed (e.g. for 128-bit operations there are no LSE instructions).
    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::bitwise_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::bitwise_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::bitwise_xor(storage, v, order);
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
struct extra_operations_gcc_aarch64;

template< typename Base, bool Signed >
struct extra_operations_gcc_aarch64< Base, 1u, Signed > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "neg %w[result], %w[original]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "neg %w[result], %w[result]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#if !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "add %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "sub %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "and %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "orr %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "eor %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "mvn %w[result], %w[original]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[result], %[storage]\n\t"\
            "mvn %w[result], %w[result]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#endif // !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_gcc_aarch64_common< extra_operations_gcc_aarch64< Base, 1u, Signed > >
{
};


template< typename Base, bool Signed >
struct extra_operations_gcc_aarch64< Base, 2u, Signed > :
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "neg %w[result], %w[original]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "neg %w[result], %w[result]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#if !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "add %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "sub %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "and %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "orr %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "eor %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "mvn %w[result], %w[original]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[result], %[storage]\n\t"\
            "mvn %w[result], %w[result]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#endif // !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public extra_operations_gcc_aarch64_common< extra_operations_gcc_aarch64< Base, 2u, Signed > >
{
};


template< typename Base, bool Signed >
struct extra_operations_gcc_aarch64< Base, 4u, Signed > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "neg %w[result], %w[original]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "neg %w[result], %w[result]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#if !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "add %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "sub %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "and %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "orr %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "eor %w[result], %w[result], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Kr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "mvn %w[result], %w[original]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[result], %[storage]\n\t"\
            "mvn %w[result], %w[result]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#endif // !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_gcc_aarch64_common< extra_operations_gcc_aarch64< Base, 4u, Signed > >
{
};


template< typename Base, bool Signed >
struct extra_operations_gcc_aarch64< Base, 8u, Signed > :
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "neg %x[result], %x[original]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "neg %x[result], %x[result]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#if !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "add %x[result], %x[result], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "sub %x[result], %x[result], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Ir" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "and %x[result], %x[result], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Lr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "orr %x[result], %x[result], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Lr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "eor %x[result], %x[result], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : [value] "Lr" (v)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "mvn %x[result], %x[original]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[result], %[storage]\n\t"\
            "mvn %x[result], %x[result]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [result] "=&r" (result)\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result;
    }

#endif // !defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public extra_operations_gcc_aarch64_common< extra_operations_gcc_aarch64< Base, 8u, Signed > >
{
};


template< typename Base, bool Signed >
struct extra_operations_gcc_aarch64< Base, 16u, Signed > :
    public extra_operations_generic< Base, 16u, Signed >
{
    typedef extra_operations_generic< Base, 16u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::storage_union storage_union;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "mvn %x[result_0], %x[original_0]\n\t"\
            "mvn %x[result_1], %x[original_1]\n\t"\
            "adds %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], #1\n\t"\
            "adc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], xzr\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "mvn %x[result_0], %x[result_0]\n\t"\
            "mvn %x[result_1], %x[result_1]\n\t"\
            "adds %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], #1\n\t"\
            "adc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], xzr\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "adds %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "]\n\t"\
            "adc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "r" (value.as_uint64[0u]), [value_1] "r" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "subs %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "]\n\t"\
            "sbc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "r" (value.as_uint64[0u]), [value_1] "r" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "and %x[result_0], %x[result_0], %x[value_0]\n\t"\
            "and %x[result_1], %x[result_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "orr %x[result_0], %x[result_0], %x[value_0]\n\t"\
            "orr %x[result_1], %x[result_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "eor %x[result_0], %x[result_0], %x[value_0]\n\t"\
            "eor %x[result_1], %x[result_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "mvn %x[result_0], %x[original_0]\n\t"\
            "mvn %x[result_1], %x[original_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[result_0], %x[result_1], %[storage]\n\t"\
            "mvn %x[result_0], %x[result_0]\n\t"\
            "mvn %x[result_1], %x[result_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : \
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return result.as_storage;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 16u, Signed, true > :
    public extra_operations_gcc_aarch64_common< extra_operations_gcc_aarch64< Base, 16u, Signed > >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH64_HPP_INCLUDED_

/* extra_ops_gcc_aarch64.hpp
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
*/