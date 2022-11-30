/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_aarch64.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH64_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH64_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/ops_gcc_aarch64_common.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct core_arch_operations_gcc_aarch64_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;
};

// Due to bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63359 we have to explicitly specify size of the registers
// to use in the asm blocks below. Use %w prefix for the 32-bit registers and %x for 64-bit ones.

// A note about compare_exchange implementations. Since failure_order must never include release semantics and
// must not be stronger than success_order, we can always use success_order to select instructions. Thus, when
// CAS fails, only the acquire semantics of success_order is applied, which may be stronger than failure_order.

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch64_base
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
                "stlrb %w[value], %[storage]\n\t"
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_RCPC)
            if (order == memory_order_consume || order == memory_order_acquire)
            {
                __asm__ __volatile__
                (
                    "ldaprb %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
            else
#endif
            {
                __asm__ __volatile__
                (
                    "ldarb %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "swp" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[value], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo "b %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxtb %w[expected], %w[expected]\n\t"\
            "mov %w[success], #0\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 1f\n\t"\
            "st" st_mo "xrb %w[success], %w[desired], %[storage]\n\t"\
            "eor %w[success], %w[success], #1\n\t"\
            "1:\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "r" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo "b %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxtb %w[expected], %w[expected]\n\t"\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 2f\n\t"\
            "st" st_mo "xrb %w[success], %w[desired], %[storage]\n\t"\
            "cbnz %w[success], 1b\n\t"\
            "2:\n\t"\
            "cset %w[success], eq\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "r" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "add %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = -v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );

#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "sub %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = ~v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldclr" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "and %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldset" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "orr %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldeor" ld_mo st_mo "b %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrb %w[original], %[storage]\n\t"\
            "eor %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrb %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

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
    public core_arch_operations_gcc_aarch64_base
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
                "stlrh %w[value], %[storage]\n\t"
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_RCPC)
            if (order == memory_order_consume || order == memory_order_acquire)
            {
                __asm__ __volatile__
                (
                    "ldaprh %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
            else
#endif
            {
                __asm__ __volatile__
                (
                    "ldarh %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "swp" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[value], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo "h %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxth %w[expected], %w[expected]\n\t"\
            "mov %w[success], #0\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 1f\n\t"\
            "st" st_mo "xrh %w[success], %w[desired], %[storage]\n\t"\
            "eor %w[success], %w[success], #1\n\t"\
            "1:\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "r" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo "h %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "uxth %w[expected], %w[expected]\n\t"\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 2f\n\t"\
            "st" st_mo "xrh %w[success], %w[desired], %[storage]\n\t"\
            "cbnz %w[success], 1b\n\t"\
            "2:\n\t"\
            "cset %w[success], eq\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "r" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "add %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = -v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );

#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "sub %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = ~v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldclr" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "and %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldset" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "orr %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldeor" ld_mo st_mo "h %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xrh %w[original], %[storage]\n\t"\
            "eor %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xrh %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

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
    public core_arch_operations_gcc_aarch64_base
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
                "stlr %w[value], %[storage]\n\t"
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_RCPC)
            if (order == memory_order_consume || order == memory_order_acquire)
            {
                __asm__ __volatile__
                (
                    "ldapr %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
            else
#endif
            {
                __asm__ __volatile__
                (
                    "ldar %w[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "swp" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "st" st_mo "xr %w[tmp], %w[value], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo " %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %w[success], #0\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 1f\n\t"\
            "st" st_mo "xr %w[success], %w[desired], %[storage]\n\t"\
            "eor %w[success], %w[success], #1\n\t"\
            "1:\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "Ir" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo " %w[original], %w[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "cmp %w[original], %w[expected]\n\t"\
            "b.ne 2f\n\t"\
            "st" st_mo "xr %w[success], %w[desired], %[storage]\n\t"\
            "cbnz %w[success], 1b\n\t"\
            "2:\n\t"\
            "cset %w[success], eq\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "Ir" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "add %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = -v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );

#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "sub %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = ~v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldclr" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "and %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldset" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "orr %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldeor" ld_mo st_mo " %w[value], %w[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %w[original], %[storage]\n\t"\
            "eor %w[result], %w[original], %w[value]\n\t"\
            "st" st_mo "xr %w[tmp], %w[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Kr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

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
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch64_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
        {
            __asm__ __volatile__
            (
                "stlr %x[value], %[storage]\n\t"
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_RCPC)
            if (order == memory_order_consume || order == memory_order_acquire)
            {
                __asm__ __volatile__
                (
                    "ldapr %x[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
            else
#endif
            {
                __asm__ __volatile__
                (
                    "ldar %x[value], %[storage]\n\t"
                    : [value] "=r" (v)
                    : [storage] "Q" (storage)
                    : "memory"
                );
            }
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
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "swp" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "st" st_mo "xr %w[tmp], %x[value], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo " %x[original], %x[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %w[success], #0\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "cmp %x[original], %x[expected]\n\t"\
            "b.ne 1f\n\t"\
            "st" st_mo "xr %w[success], %x[desired], %[storage]\n\t"\
            "eor %w[success], %w[success], #1\n\t"\
            "1:\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "Ir" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        original = expected;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "cas" ld_mo st_mo " %x[original], %x[desired], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "+r" (original)\
            : [desired] "r" (desired)\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
        bool success = original == expected;
#else
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "cmp %x[original], %x[expected]\n\t"\
            "b.ne 2f\n\t"\
            "st" st_mo "xr %w[success], %x[desired], %[storage]\n\t"\
            "cbnz %w[success], 1b\n\t"\
            "2:\n\t"\
            "cset %w[success], eq\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [desired] "r" (desired), [expected] "Ir" (expected)\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#endif
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "add %x[result], %x[original], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = -v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldadd" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );

#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "sub %x[result], %x[original], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Ir" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
        v = ~v;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldclr" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "and %x[result], %x[original], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Lr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldset" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "orr %x[result], %x[original], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Lr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_LSE)
#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "ldeor" ld_mo st_mo " %x[value], %x[original], %[storage]\n\t"\
            : [storage] "+Q" (storage), [original] "=r" (original)\
            : [value] "r" (v)\
            : "memory"\
        );
#else
        storage_type result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xr %x[original], %[storage]\n\t"\
            "eor %x[result], %x[original], %x[value]\n\t"\
            "st" st_mo "xr %w[tmp], %x[result], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [result] "=&r" (result), [storage] "+Q" (storage), [original] "=&r" (original)\
            : [value] "Lr" (v)\
            : "memory"\
        );
#endif

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

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

// For 128-bit atomic operations we always have to use ldxp+stxp (optionally, with acquire/release semantics), even in load and store operations.
// ARM Architecture Reference Manual Armv8, for Armv8-A architecture profile, Section B2.2.1 "Requirements for single-copy atomicity"
// specifies that ldxp does not guarantee an atomic load, and we have to perform ldxp+stxp loop to ensure that the loaded value
// is consistent with a previous atomic store.
//
// The ldxp and stxp instructions operate on pairs of registers, meaning that each load loads two integers from memory in
// successive address order, to the first and second registers in the pair, respectively, and store similarly stores two integers.
// The order of these integers does not depend on the active endianness mode (although the byte order in the integers themselves
// obviously does depend on endianness). This means we need to account for the current endianness mode ourselves, where it matters.
//
// Unlike AArch32/A32 or ARMv7, ldxp/stxp do not require adjacent even+odd registers in the pair and accept any two different
// registers. Still, it may be more preferable to select the adjacent registers as 128-bit objects are represented by two adjacent
// registers in the ABI. Unfortunately, clang 10 and probably older doesn't seem to support allocating register pairs in the asm blocks,
// like in ARMv7. For now we use a union to convert between a pair of 64-bit elements and 128-bit storage.

template< bool Signed, bool Interprocess >
struct core_arch_operations< 16u, Signed, Interprocess > :
    public core_arch_operations_gcc_aarch64_base
{
    typedef typename storage_traits< 16u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 16u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 16u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    // Union to convert between two 64-bit registers and a 128-bit storage
    union storage_union
    {
        storage_type as_storage;
        uint64_t as_uint64[2u];
    };

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_union v;
        uint32_t tmp;
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
        {
            __asm__ __volatile__
            (
                "1:\n\t"
                "ldaxp %x[value_0], %x[value_1], %[storage]\n\t"
                "stxp %w[tmp], %x[value_0], %x[value_1], %[storage]\n\t"
                "cbnz %w[tmp], 1b\n\t"
                : [tmp] "=&r" (tmp), [value_0] "=&r" (v.as_uint64[0u]), [value_1] "=&r" (v.as_uint64[1u])
                : [storage] "Q" (storage)
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "1:\n\t"
                "ldxp %x[value_0], %x[value_1], %[storage]\n\t"
                "stxp %w[tmp], %x[value_0], %x[value_1], %[storage]\n\t"
                "cbnz %w[tmp], 1b\n\t"
                : [tmp] "=&r" (tmp), [value_0] "=&r" (v.as_uint64[0u]), [value_1] "=&r" (v.as_uint64[1u])
                : [storage] "Q" (storage)
                : "memory"
            );
        }

        return v.as_storage;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "st" st_mo "xp %w[tmp], %x[value_0], %x[value_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage), [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u])\
            : [value_0] "r" (value.as_uint64[0u]), [value_1] "r" (value.as_uint64[1u])\
            : "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union e = { expected };
        storage_union d = { desired };
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "mov %w[success], #0\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "cmp %x[original_0], %x[expected_0]\n\t"\
            "ccmp %x[original_1], %x[expected_1], #0, eq\n\t"\
            "b.ne 1f\n\t"\
            "st" st_mo "xp %w[success], %x[desired_0], %x[desired_1], %[storage]\n\t"\
            "eor %w[success], %w[success], #1\n\t"\
            "1:\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u])\
            : [desired_0] "r" (d.as_uint64[0u]), [desired_1] "r" (d.as_uint64[1u]), [expected_0] "r" (e.as_uint64[0u]), [expected_1] "r" (e.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original.as_storage;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union e = { expected };
        storage_union d = { desired };
        bool success;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "cmp %x[original_0], %x[expected_0]\n\t"\
            "ccmp %x[original_1], %x[expected_1], #0, eq\n\t"\
            "b.ne 2f\n\t"\
            "st" st_mo "xp %w[success], %x[desired_0], %x[desired_1], %[storage]\n\t"\
            "cbnz %w[success], 1b\n\t"\
            "2:\n\t"\
            "cset %w[success], eq\n\t"\
            : [success] "=&r" (success), [storage] "+Q" (storage), [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u])\
            : [desired_0] "r" (d.as_uint64[0u]), [desired_1] "r" (d.as_uint64[1u]), [expected_0] "r" (e.as_uint64[0u]), [expected_1] "r" (e.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(success_order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        expected = original.as_storage;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "adds %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[original_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "]\n\t"\
            "adc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[original_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "r" (value.as_uint64[0u]), [value_1] "r" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "subs %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[original_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_LO "]\n\t"\
            "sbc %x[result_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[original_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "], %x[value_" BOOST_ATOMIC_DETAIL_AARCH64_ASM_ARG_HI "]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "r" (value.as_uint64[0u]), [value_1] "r" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "and %x[result_0], %x[original_0], %x[value_0]\n\t"\
            "and %x[result_1], %x[original_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "orr %x[result_0], %x[original_0], %x[value_0]\n\t"\
            "orr %x[result_1], %x[original_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_union original;
        storage_union value = { v };
        storage_union result;
        uint32_t tmp;

#define BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN(ld_mo, st_mo)\
        __asm__ __volatile__\
        (\
            "1:\n\t"\
            "ld" ld_mo "xp %x[original_0], %x[original_1], %[storage]\n\t"\
            "eor %x[result_0], %x[original_0], %x[value_0]\n\t"\
            "eor %x[result_1], %x[original_1], %x[value_1]\n\t"\
            "st" st_mo "xp %w[tmp], %x[result_0], %x[result_1], %[storage]\n\t"\
            "cbnz %w[tmp], 1b\n\t"\
            : [tmp] "=&r" (tmp), [storage] "+Q" (storage),\
              [original_0] "=&r" (original.as_uint64[0u]), [original_1] "=&r" (original.as_uint64[1u]),\
              [result_0] "=&r" (result.as_uint64[0u]), [result_1] "=&r" (result.as_uint64[1u])\
            : [value_0] "Lr" (value.as_uint64[0u]), [value_1] "Lr" (value.as_uint64[1u])\
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
        );

        BOOST_ATOMIC_DETAIL_AARCH64_MO_SWITCH(order)
#undef BOOST_ATOMIC_DETAIL_AARCH64_MO_INSN

        return original.as_storage;
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

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_AARCH64_HPP_INCLUDED_

/* core_arch_ops_gcc_aarch64.hpp
5/cR9rc4HTg9evyW2UHaVXez6QGubnz1Kds/R8pd/YvIP+RsARerJey/ezBwqgeOLCedb/HX271zyjwccKv6j5kaf70BMHMw4BZEOo/gr0fzzSnzy58ZQSjhE/Rvm/veNfrNUl8GpN+TzmP762l9c9JfH3AL+TtmZhPnn6WRvreAi+2BwRRSSsM/Md8l7jy4z5Dxor9C9CtB4e3CvwqA+9AFvbAGeXQKce0Bcc8f+Ejc/R31z2KyxJ1QCxBYgDcP/0qPMtApCqKfE6oEDRIU+kT8Lj2Qg9gkgIy0gek5769LVk/RUk+cSDPQsHnMjn0fc/yRRwpikwgy0gWGdRy9+0/MNyDEJiFkpAMMa+cfGIr9tfRub4A/erenJMQmNmSkFAwrCZiRgNhEh4wUhmH9/rz7mzjEJtrfM2IQm0iQkSzgMsGMaA6rPsnn0PM3EP1oUHjC8K8eyAJ/Z7b4AuMOIfoxofBaUF/pkQc6hUD0Y0PhacFjYRdzZY/Ww6J8msHTDcSh/AtQ/MdA/u+h5hSiv/N84Bpik8U6Rwr904LHc8EIMm8c0UvGoD1tmKk6+J3iw17DAxE06IB2NNbvqvDeeKKXrEF4Q0jGL1jexbWTRQc/AfDiSbQxCA+GXyN+EyH8hI+GIdCRvk4wsH+G9eqh7c3qIUhgJ09QULMHVmRhQAtVIPq5yB3WB4Zjl8LHAWkpPavDw7YPDPpgE1Qwouvr11fq/+xI3JbimhKVDJUClRz159ZxNPk/No8pQvwG10If/gP0b7fJf4oeB9di/hMEPSgc+J+gN4PC7/4TJD4oHPyfoN5B4cj/BFG+NIQ5jHjlh17BEnQl+aETfg734x3FT+HGvcS5X943IRXfbNpOJaw1mvCH/EHhX5Ha9ecUEZ+kfw2DSvOGvwz/wSOGZfVfIPsvEPMfgXkaaSfpUj7M/wHI/guk/xeQCrOUIsGqz9JIeiwD9f8OUAQ9UAyy/AOhHStA/QUo4ndCTyOuqV//O4hr5FbZIpX8/hMBtkjF/xMUMtj1/BaX4ofYluG7B6Q4B/ILJonOkMGm57c4FGtiW7rvfH8RinVKDjbB3+KQr/3+SeZvhES3/XG/ob44wz+iT3FKRLdYlNnGW2qRvuFxSoBOQ8C1DeCCCdjZN9iEd4tDuWa8pRt5qv3rxxolsi6YC7knJEOW/c/ou6mmrAPkJsvLoksc1u8wWrJKkFLPpdA3lZz6pq8K/L0ZgoU/YstfGUI9HsDczSJclkPeR6VSzW77yZZbMwxbW599UzxIGf2KVKOyb4JifvcezX7E5OXsZXGM0pdrf8aOjhg83C5qZn8FvYe05m+cTuc2Gxvznxzfh8F9lNdDTt9/8wpheUfpC1cAVNPteWJFarf7C1aiUCMOYRLxi03Ai78GJt/GYgYiHz66vkc7NSkemMIPz2fHkrKgjR5XJsrM5eETd3J9u7GH3Pd15koCfeA5LgWzGJGUXiRPYcGvEX/KgevgpNfeN8Ubnu+CJbULFqkQZebz8Ek9SZ3OcaQs6KLHVYkyC3n45Jxckzf2GPumtMPz67D+T0SsO9RCAr//TQLm1Y1mz4j8r+AWgUVqRJnFPHxKTq5ZT9LNDabocXWizFIePjUn16KNPfm+qVRwh7ClLOijI5p4+DR+dqgl/CmhouZTB10bN/Zs+6YWwZWAUzFEj2sSZVby8On+HlEcYID5xpAc2T+E9Rt2zxct+Dca5MgGIdPCDOGfjcmXcZDWG1/CN/WJdV7C9X8Lg4i+Ub7zeD16+bFBGeDvqnL0/aEGT7iS1j1AJ657NPiePfnplui1YPxC8u15+rvHd9Dv3rw730R+mI0Ve7oxA+IaJu8k53imiyKuiwMyFz5lKwLOi5Xkd3ezHm73SWsg6Y+U0UPDw6nm0FDCZ7flZOnPUnSdrAcHbhF/YMY+qKdA9Bt+6/uxAhlg3v8pOxUy8utLoXGT229qcXRqFnfT/AmWF49g4Inpn6EBOMFNfCIWwPQ4kw+4E1JEaX5jsYGaFcbvSd2fPXaJSpLFc7Wpdekv4HUwkFD8FCgVABRReLa/Ye57svRHgLHpHW4xADUs7pIMOP0GTwZtuzgAEleD4DN6j3vwB2JyWyn44iLlDzwrus24mIo/Xiav3Z7Tdn3dVBEJqUmcGAorKn339cVJefCMcO22hz/P8OmDI5ayKOOs48RU3rt8yeZ5DFS+CUniVZXi75atV4rp+SiJM3dgCoV3f45fGA9WvfXKiGbg6QOFbJPQxhZHosOgXNPq+qbcPImL87Qdi6vztBsuL6/iyvi3i9tpt4EZ3v3sdxf8wujgnNfGNDR7yuShsnLU61s8TNf88R8fLxxLyAfiIk2wffdWQ8QVbR4UDx8VD522wLQctOKtiDhJo9DWGQJPJRpP5YDfueOglXi3VUf+ROcrcOtQond4hYm2B0ijg1QVj1G8JyfnP7oeZvqgOHw+A+aCqV0CT24QqWzTqpULNLa7Dqli0+pU+oeZOzA4tl5FMxdK2Q5OFTq2HkevSmQ0SoFhOoFFcRWv9J1JAUV0XDgPkH7jv8FssUfHTfAAmTfwWsAMRZa98D/o6LgInv99TMggKSWeU+SrT4Ag9AF4ING/Ys4pLmnPuvaHY/J24753keTteUnU6GEJxoiNsnx66HH1H6akc2es2R+1KmIvTt0nFYeh31JGUZIgohfsGbuMIYfadqGdyX36ABbKXpc6PmoOJP5JN91mtoxlfwdI5MiHXvCrd+cGoWI7l3wQlyQa/tOnLiTTXGL+O8Ih17ebGOme9MOfeLs/qalQZ4WzAAss9NOdqyeGza39gSnOkxfANtsopcVUkkzdV1PxTPsUUyzzsH5Z+qbe4a3PDZ4QfA4Lroghc2CnHoQf7wPaMcQmCQczZdC+GWf/3IYkDxtrP84Ani6Ria1TZE0foB9H6Qu89DnAr/QGMmPa9eH7DGPPj9gq+B/irRQPaPvhZ8IFDIiFI7Dooc9D0Z/c1ZOhV3xk9FHBO0QwETSqoDFbNzEyJPgZpcrT8AB3tKfwIgAptbvNbtQm87F/s51/Ea7b8wZFkN/UYV3fKxTlsQ6J6+s4YXojK+GAtwtLbkG131VPA+IX8kA7CKjUcX4xfxy9CciXiGfPu7kCuSFeiH2xXrmCUodcRvww0drLf3ZN2L6oXVPVjiLw+S3r9PsmCjiIeIgM094Glm7LwH2IFOhlRLLF7YoM+kAXiEbIh1drdF8qufS2QxublhzDorjGy1mPTWXoeY9N+VvOP9HRCTjbIg6EFoVfyWFDow31+yGqNdtUY9mn2TA3fNgBNA3oXCSfxTPlriOtyy7WFQAKX6RXrDNJC0JsYuxgnRURtm2lNtlvQuVmOMnKyrg78xcTCiiMvu+PP4Kwkq1dvDlqAxFfr/QDFUZ1TXoXaLaeOpnhBxUgbE6a4LIgJLfjSAzjyADu6DwkKoS0LenDClLAzQfBAsD9u0tYPBhW4i+a4BxwEKbX6Hp1C/YlUQtaESQw3Qv2zeY1+mc6bV+W3vvBg0KPxC2XPhP2qLhEKFweRUi4M2NULpFP1Re2pHY0rE+c5Kh4Tc7kqMScK5qSnX9VJHT2W0z3OkSBHq7jrlPi9vYxrw7brvMAd+pNcjt0xhq5QSAAgh0CB0papAMJ1GZK140NYQNxACky8iUN9osZC3Q74hnzEBwtBB50zgduLoj0saMrFK+QxZpkWzif1/VQYV39BvXn5UdehF09WXXncoH8UP6pgl25Jlxh+47Z3ezagXUQNyH3FD7WJilFi0MvMRtRTFNQ5jsh3kAAoeXhmolEjD+/LEYpXFTIjR8YHEF8HU84OM/Vmb5cFRvktQjrJZkTaHAYP38Kk/PFufxmTkAztungmbROSvtIFdRw65b+Bwzaw3iPuxYR7ZT2cMknPO31hEtnXtcye+XTQMCmjNle5eu3modKTRSvvjRpxCuo/wXew9vWXKU80L20a7MSjyEhqyFE8nY/jetwZdC/49Hni2buyGRmypebKJKbKJSDmywsniwU3J++drWSaq0PZPaLBIpgyVl9LMqPnwqac90fcd2HdrVC0U+TStmZLtTfU2VBwbU15yV8e2enbpsfBbCZhBQyInuZ3c8I9yINmi8bmsuIUM8QTnqpFIp26ziRfrkoP4Tf7ghAm3QyM1ERjmI00f1mQoRbQPwaCn5SdCKQQBA6SQAam+PtIRlY8z+DVegF5AvaFQQC/xY/O+SfA1oEnQHtCCFSm+4CERhHb7sh7t57Z5wvpUt3jfxwDBPg8lJRNLTiWluw7u3ZyOeZfuL9veihaEZ5ncYXwRx2eRyL8oIxDye3mx5oKib0bZH6inwiUnqvv12gBLgPrspXr8XevHSvgO2IdsUSObRM3JrS60ZXNSl+U9BhvA5hNXECbWtvKYxAYtNOXq11rbk06H0QdyT8OSD50e1+DHmwekk4+THLo06E2/Q0OOOeZMi/+LFvkeVqpUJkfNMrnS6n0qBtL/k67gjOoDEiC4nbfjnWrzGEZEio/PHL0e3xMaFZKWExSKQsx+m6ub10UTyn0/M+dRGWU3mXcvHNUna8IJkGvaXgV2l3IY5ci/AjyKjj1VXzpZZ8/fVPZ+Z8TTkp7bJZjDHJ4rV0N/EuW7Ytb5YV7as4NGoTgeG5luF50uE5rCG0Y9w0N9iXLybdxgoZkWSC3LBt+SK0tZoXgDH0kciUV2PfHLl8fcmJDbr8cPCFZnR/fP42nl7K5W7dsdASO8dNrPhWibYi5pKoU1sxuhzthsiAJYbX6sJbliUdquXK9tZcllp+VT5Bcy7k+CAdR2FVjNbOeb3wmHH5uEeuWJ68UpeZAOStPPNaIS/sG4CZ/Wypbl3pMH8P9ar8bUy2XldVb6L3DEU8cRFydZd3u8fSFtMlzZ24ky/S45SYGrXDOvS+Ut9mha8Qq5DZ8NmYa7x+tOd+jDIqx45UWwYUZp1GtGdSdKkzd9Hwds9X5aqIkJyMsni9Nr2qsqVtGOskXcOZQp7OTjncNnkGltKaEVD9RetIewaSmbPLMRtTSnzKMRtLk551UimpJa7VGkm4q60Dbq6djE+btM/SHDNbaa60IaNzjdqWcTpmMYrZUvGw53XhiOe1aGrWj+Ps2p4swf3+72rmCgzMh3oC+S5O+N2Rd3I4Y3b6Xa5F823+c1iHb5uydsfe89pUhcgNHxS7MkfMTxwQ3VSdCh/jNRVrN917RFfTzITTyBsIV+YwduYGiP7YGKc6pyOEi0EIjtlwq+llYN3BS4qqoUd62f4sNMaJ33aFxPYcUbe9B6f6I+wbO4NPc+eAhHmGAkfZqXqs1UFXlEs3YFsGXQhTHQ5qfVJTgOJh3Wc7WAczpikfxVJuPtw5H4gK3Q6TDpM5Jjy1uUpg7AqeQ4NQW4BiW6Ur0+pw0BF1JpLMxFJrGt90a7NA1p0WdABZeeM4hufBUt1O9vfujo27oHhPBSby3kOfSFIDYcsj0NChGb6zxctq9TWWzOLDvvSEz2qpfmR12UlDLWqTw4SvtkvpcR58fsyTM9cCP6peLwB1JuPm4tPo2js3zxCQ5T8Gl55VzRQpriJ2JnIKguRf41bkCloptKLauk9kvUiinuMvzm1EpUuUZNoAJZxJK+i8GCeVeylIHDZ7fXT7AyKUjcvPzN7UxdXZzMgOEUw5GFsjAnjJWMmeCAEBFnFwhKuVg72EkasZGa0EHxsrKy+AjY0HwM7BxcbBxMpJw8pKQ/dLMgdnMloyUXARZmTKlg6uDi6WDo5k4mocZApGJlb2Tzwdi4KD6e9FAVhZeVg5ATzg4gBMrBy/FKXs7GDqZmIGLuufizIHV/B7UUJCv7WXjfX39qpZeZuRsQFYVB0cXMkAYLkqi4y9uQPZzz6BaQldASCAh4ObTZxVHMgqwSHKxSrGLikmLsktJsEKAHBy8/AIkQkAJdnZJcXZJCTYeLnAHRXjZRXjlOThBIpJ8AIB4MRC+izqXo5mLC9VzcxZtHQBZGxkAH0WeTN7C1dLMh4OcNN+HVEI8AUJgQbGMD8gIQSeWHDoAAEJiQ4BCU0NvkEQkDD6EJDPGiAgEeggIJGeQ0CiJENAop5DQD4HgO9HCEgMVghITBQIyFxwfO4ixF+el4urkbOrp7OZOSIHgIOdHZGKSlIJSKUsAWQCMHMjUm1sTswgAn4fImUjCzMXMvaf4/GzF+JGrka2Dha/Dyj7H56/g5s9eCBZ5KxMXXQ5n/L82vWfpfyehfP3LKLOrmIOnrpPD4Wdk4ybXR9ciL2rmb2rCxnXz0oVzEytjP4pibKRMzjFr61SNXNxcHM2AbeS+/dWPlX4e31cv9f367BzcLCyAK1sXc2cWYC2YBWTMDNxMDX7/VF4Ltmp8UdjiyILfFxe1w/s+6HUibAOJPpCBcNoeZqtbIeGAW8OJChfcl80uxm4cioVhnc4eMg6DdwLkWgdH5Kj0QoTXK1WCgxbpIKgQS/d3mxuLSAdeTGtjmpOvj4QsyJTQTKRAAqPu8qhaVvydIdFe0uGyfdejTAqyU6xc2r8I9eieJRLswJI36F8LpzVOHtYJ98uLy7TVOVAbdDINmTzTNnsihd7Zm7n46T4kES6FD5bFMxbf0XlAvppZum9C5Amtn45kkBCSgfC7GFtby16cgP/sYM8RuF+lNUksLjpIJs2n5u+4f04e2HMrAHKd8L8pT3X/AoNhl6gW1NQy53urGXOs6652S5157zC9hZvZVG0mlazKiBqupI9aI2k68pC3/5Sb0QaT0KpAznk1DsI87D+5XpqWDZns4W5d7iwZY3j6tTGDBMn5bZttEz/DnlkpIO9SUSlQg2gHgdoj7m5LSn0Mn7XaB3RtdPPZMKl2GSBX0On/4hHoBnz5eHQYBVH8cKeALdxvhwMZl8GT8ap3SedAc9GiynLuwlOn+83F35dnfqG1aTzuyynl56PXh3631arDOXKWoj+ou7cvz96SU9XKTVX8MMG01JqADAGmwlXZzfwYxcSerIkJmpmrros4KnAom7m6coiYwdWIrFfAvFfAhl9lpdKxtZmJq7g3DJ2rGQ8Tyr3lP+3+nh+r++XSf9LchY1N2PXJ/5nMSxiVq4uymbO4g52jg72T6rMA1Z7WwdnNUcjEzMWCTN3KxMzVSmx31RUQlz9FwX9TX3JyNhZuVi0rEzBNDsni7SZlYWlK3hq/K7APxZ+fIF4LguUAYLNx5NZAaMfnyHEIeCfPYN7BgsPBweHgACPiIyFgoyEhIyPgYmGRUxASkJMQERE9oKZhoyCkZKIiJabjpEVwMHBQUrDK8jDJsDMzsH2VAgkAgICMhIyHgoKHhs5ETnbf/v60Q2BDg8hA0EJDUkBAYUOCY0O+eMTBPbPpv7pggeLsZ7/sxTiSQr5t1L0v0qXIJChIcG1QKNDCENkd0P83QX3Y/EvqvMvHRvg6eIGeyR2Du7/yLFxkmlZgcv1cPlnt/Z08QA4Obk4AP8o6L/v1gD/7NYAf3Vrv3s1ACtQHAgU5wJwc0lw8HCz80hycfBwACVExTkkRIFcQLBX4+AUlZAUl2TlYuVklZQQFWOX4BBn5eUGcrFK8ohxsP1rr8bxn3g1iDUISKglsFeThYCEBT972J5/5a0AHNwc/4ucFRcZF8+/
*/