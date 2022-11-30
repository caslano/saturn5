/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_aarch32.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH32_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH32_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/ops_gcc_aarch32_common.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// ARMv8 (AArch32) instruction set is similar to ARMv7, but adds
// lda(b/h) and ldaex(b/h/d) instructions for acquire loads and
// stl(b/h) and stlex(b/h/d) instructions for release stores. This
// makes explicit memory fences unnecessary for implementation of
// the majority of the atomic operations.
//
// ARMv8 deprecates applying "it" hints to some instructions, including
// strex. It also deprecates "it" hints applying to more than one
// of the following conditional instructions. This means we have to
// use conditional jumps instead of making other instructions conditional.

struct core_arch_operations_gcc_aarch32_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch32_base
{
    typedef typename storage_traits< 1u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
        {
            __asm__ __volatile__
            (
                "stlb %[value], %[storage]\n\t"
                : [storage] "=Q" (storage)
                : [value] "r" (v)
                : "memory"
            );
        }
        else
        {
            storage = v;
        }
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "ldab %[value], %[storage]\n\t"
                : [value] "=r" (v)
                : [storage] "Q" (storage)
                : "memory"
            );
        }
        else
        {
            v = storage;
        }

        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "st" st_mo "exb %[tmp], %[value], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [tmp] "=&r" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)\
            : [value] "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxtb %[expected], %[expected]\n\t"\
            "mov %[success], #0\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 1f\n\t"\
            "st" st_mo "exb %[success], %[desired], %[storage]\n\t"\
            "eor %[success], %[success], #1\n\t"\
            "1:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "r" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxtb %[expected], %[expected]\n\t"\
            "mov %[success], #0\n\t"\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 2f\n\t"\
            "st" st_mo "exb %[success], %[desired], %[storage]\n\t"\
            "eors %[success], %[success], #1\n\t"\
            "beq 1b\n\t"\
            "2:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "r" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "add %[result], %[original], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "sub %[result], %[original], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "and %[result], %[original], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "orr %[result], %[original], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exb %[original], %[storage]\n\t"\
            "eor %[result], %[original], %[value]\n\t"\
            "st" st_mo "exb %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch32_base
{
    typedef typename storage_traits< 2u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
        {
            __asm__ __volatile__
            (
                "stlh %[value], %[storage]\n\t"
                : [storage] "=Q" (storage)
                : [value] "r" (v)
                : "memory"
            );
        }
        else
        {
            storage = v;
        }
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "ldah %[value], %[storage]\n\t"
                : [value] "=r" (v)
                : [storage] "Q" (storage)
                : "memory"
            );
        }
        else
        {
            v = storage;
        }

        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "st" st_mo "exh %[tmp], %[value], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [tmp] "=&r" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)\
            : [value] "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxth %[expected], %[expected]\n\t"\
            "mov %[success], #0\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 1f\n\t"\
            "st" st_mo "exh %[success], %[desired], %[storage]\n\t"\
            "eor %[success], %[success], #1\n\t"\
            "1:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "r" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxth %[expected], %[expected]\n\t"\
            "mov %[success], #0\n\t"\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 2f\n\t"\
            "st" st_mo "exh %[success], %[desired], %[storage]\n\t"\
            "eors %[success], %[success], #1\n\t"\
            "beq 1b\n\t"\
            "2:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "r" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "add %[result], %[original], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "sub %[result], %[original], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "and %[result], %[original], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "orr %[result], %[original], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exh %[original], %[storage]\n\t"\
            "eor %[result], %[original], %[value]\n\t"\
            "st" st_mo "exh %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch32_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
        {
            __asm__ __volatile__
            (
                "stl %[value], %[storage]\n\t"
                : [storage] "=Q" (storage)
                : [value] "r" (v)
                : "memory"
            );
        }
        else
        {
            storage = v;
        }
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v;
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "lda %[value], %[storage]\n\t"
                : [value] "=r" (v)
                : [storage] "Q" (storage)
                : "memory"
            );
        }
        else
        {
            v = storage;
        }

        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "st" st_mo "ex %[tmp], %[value], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [tmp] "=&r" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)\
            : [value] "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %[success], #0\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 1f\n\t"\
            "st" st_mo "ex %[success], %[desired], %[storage]\n\t"\
            "eor %[success], %[success], #1\n\t"\
            "1:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "Ir" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %[success], #0\n\t"\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "cmp %[original], %[expected]\n\t"\
            "bne 2f\n\t"\
            "st" st_mo "ex %[success], %[desired], %[storage]\n\t"\
            "eors %[success], %[success], #1\n\t"\
            "beq 1b\n\t"\
            "2:\n\t"\
            : [original] "=&r" (original), [success] "=&r" (success), [storage] "+Q" (storage)\
            : [expected] "Ir" (expected), [desired] "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "add %[result], %[original], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "sub %[result], %[original], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "and %[result], %[original], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "orr %[result], %[original], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "ex %[original], %[storage]\n\t"\
            "eor %[result], %[original], %[value]\n\t"\
            "st" st_mo "ex %[tmp], %[result], %[storage]\n\t"\
            "teq %[tmp], #0\n\t"\
            "bne 1b\n\t"\
            : [original] "=&r" (original), [result] "=&r" (result), [tmp] "=&r" (tmp), [storage] "+Q" (storage)\
            : [value] "Ir" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

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


// Unlike 32-bit operations, for 64-bit loads and stores we must use ldrexd/strexd.
// Other instructions result in a non-atomic sequence of 32-bit or more fine-grained accesses.
// See "ARM Architecture Reference Manual ARMv8, for ARMv8-A architecture profile", Section E2.2 "Atomicity in the ARM architecture".
// Section E2.3.7 "Memory barriers", subsection "Load-Acquire, Store-Release" extends atomicity guarantees given for ldrexd/strexd
// to the new ldaexd/stlexd instructions with acquire/release semantics.
//
// In the asm blocks below we have to use 32-bit register pairs to compose 64-bit values. In order to pass the 64-bit operands
// to/from asm blocks, we use undocumented gcc feature: the lower half (Rt) of the operand is accessible normally, via the numbered
// placeholder (e.g. %0), and the upper half (Rt2) - via the same placeholder with an 'H' after the '%' sign (e.g. %H0).
// See: http://hardwarebug.org/2010/07/06/arm-inline-asm-secrets/
//
// The ldrexd and strexd instructions operate on pairs of registers, meaning that each load loads two integers from memory in
// successive address order, to the first and second registers in the pair, respectively, and store similarly stores two integers.
// The order of these integers does not depend on the active endianness mode (although the byte order in the integers themselves
// obviously does depend on endianness). This means we need to account for the current endianness mode ourselves, where it matters.

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch32_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "ldaexd %0, %H0, %1\n\t"
                : "=&r" (original)   // %0
                : "Q" (storage)      // %1
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "ldrexd %0, %H0, %1\n\t"
                : "=&r" (original)   // %0
                : "Q" (storage)      // %1
            );
        }

        return original;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %1, %H1, %2\n\t"\
            "st" st_mo "exd %0, %3, %H3, %2\n\t"\
            "teq %0, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (tmp), "=&r" (original), "+Q" (storage)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %1, #0\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "cmp %0, %3\n\t"\
            "it eq\n\t"\
            "cmpeq %H0, %H3\n\t"\
            "bne 1f\n\t"\
            "st" st_mo "exd %1, %4, %H4, %2\n\t"\
            "eor %1, %1, #1\n\t"\
            "1:\n\t"\
            : "=&r" (original), "=&r" (success), "+Q" (storage)\
            : "r" (expected), "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;

        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
        bool success;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %1, #0\n\t"\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "cmp %0, %3\n\t"\
            "it eq\n\t"\
            "cmpeq %H0, %H3\n\t"\
            "bne 2f\n\t"\
            "st" st_mo "exd %1, %4, %H4, %2\n\t"\
            "eors %1, %1, #1\n\t"\
            "beq 1b\n\t"\
            "2:\n\t"\
            : "=&r" (original), "=&r" (success), "+Q" (storage)\
            : "r" (expected), "r" (desired)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        expected = original;

        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "adds " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(3) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(4) "\n\t"\
            "adc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(3) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(4) "\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "subs " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(3) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_LO(4) "\n\t"\
            "sbc " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(3) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(0) ", " BOOST_ATOMIC_DETAIL_AARCH32_ASM_ARG_HI(4) "\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "and %3, %0, %4\n\t"\
            "and %H3, %H0, %H4\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "orr %3, %0, %4\n\t"\
            "orr %H3, %H0, %H4\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, result;
        uint32_t tmp;
#define BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "exd %0, %H0, %2\n\t"\
            "eor %3, %0, %4\n\t"\
            "eor %H3, %H0, %H4\n\t"\
            "st" st_mo "exd %1, %3, %H3, %2\n\t"\
            "teq %1, #0\n\t"\
            "bne 1b\n\t"\
            : "=&r" (original), "=&r" (tmp), "+Q" (storage), "=&r" (result)\
            : "r" (v)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH32_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH32_MO_INSN

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

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH32_HPP_INCLUDED_

/* core_arch_ops_gcc_aarch32.hpp
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
*/