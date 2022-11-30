/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_gcc_aarch32.hpp
 *
 * This header contains implementation of the extra atomic operations for AArch32.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH32_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH32_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/ops_gcc_aarch32_common.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct extra_operations_gcc_aarch32_common :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    // Note: For opaque operations prefer operations returning the resulting values instead of the original values
    //       as these operations require less registers.
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
struct extra_operations_gcc_aarch32;

template< typename Base, bool Signed >
struct extra_operations_gcc_aarch32< Base, 1u, Signed > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "rsb %[result], %[original], #0\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "rsb %[result], #0\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "add %[result], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "sub %[result], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "and %[result], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "orr %[result], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "eor %[result], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "mvn %[result], %[original]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[result], %[storage]\n\t"\
            "mvn %[result], %[result]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_gcc_aarch32_common< extra_operations_gcc_aarch32< Base, 1u, Signed > >
{
};


template< typename Base, bool Signed >
struct extra_operations_gcc_aarch32< Base, 2u, Signed > :
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "rsb %[result], %[original], #0\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "rsb %[result], #0\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "add %[result], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "sub %[result], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "and %[result], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "orr %[result], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "eor %[result], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "mvn %[result], %[original]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[result], %[storage]\n\t"\
            "mvn %[result], %[result]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public extra_operations_gcc_aarch32_common< extra_operations_gcc_aarch32< Base, 2u, Signed > >
{
};

template< typename Base, bool Signed >
struct extra_operations_gcc_aarch32< Base, 4u, Signed > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "rsb %[result], %[original], #0\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "rsb %[result], #0\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "add %[result], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "sub %[result], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "and %[result], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "orr %[result], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "eor %[result], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "mvn %[result], %[original]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[result], %[storage]\n\t"\
            "mvn %[result], %[result]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_gcc_aarch32_common< extra_operations_gcc_aarch32< Base, 4u, Signed > >
{
};

template< typename Base, bool Signed >
struct extra_operations_gcc_aarch32< Base, 8u, Signed > :
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "mvn %3, %0\n\t"\
            "mvn %H3, %H0\n\t"\
            "adds " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(3) ", #1\n\t"\
            "adc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(3) ", #0\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "mvn %0, %0\n\t"\
            "mvn %H0, %H0\n\t"\
            "adds " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(0) ", #1\n\t"\
            "adc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(0) ", #0\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "adds " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(3) "\n\t"\
            "adc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(3) "\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "subs " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(3) "\n\t"\
            "sbc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(3) "\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "and %0, %3\n\t"\
            "and %H0, %H3\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "orr %0, %3\n\t"\
            "orr %H0, %H3\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "eor %0, %3\n\t"\
            "eor %H0, %H3\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "mvn %3, %0\n\t"\
            "mvn %H3, %H0\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "mvn %0, %0\n\t"\
            "mvn %H0, %H0\n\t"\
            "st" st_mo "exd %1, %0, %H0, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (result), "=&r" (tmp), "+Q" (storage)\
            : \
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public extra_operations_gcc_aarch32_common< extra_operations_gcc_aarch32< Base, 8u, Signed > >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_AARCH32_HPP_INCLUDED_

/* extra_ops_gcc_aarch32.hpp
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
*/