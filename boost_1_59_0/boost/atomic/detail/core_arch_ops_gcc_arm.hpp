/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_arm.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/ops_gcc_arm_common.hpp>
#include <boost/atomic/detail/gcc_arm_asm_common.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// From the ARM Architecture Reference Manual for architecture v6:
//
// LDREX{<cond>} <Rd>, [<Rn>]
// <Rd> Specifies the destination register for the memory word addressed by <Rd>
// <Rn> Specifies the register containing the address.
//
// STREX{<cond>} <Rd>, <Rm>, [<Rn>]
// <Rd> Specifies the destination register for the returned status value.
//      0  if the operation updates memory
//      1  if the operation fails to update memory
// <Rm> Specifies the register containing the word to be stored to memory.
// <Rn> Specifies the register containing the address.
// Rd must not be the same register as Rm or Rn.
//
// ARM v7 is like ARM v6 plus:
// There are half-word and byte versions of the LDREX and STREX instructions,
// LDREXH, LDREXB, STREXH and STREXB.
// There are also double-word versions, LDREXD and STREXD.
// (Actually it looks like these are available from version 6k onwards.)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_gcc_arm_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex %[original], %[storage]\n\t"          // load the original value
            "strex %[tmp], %[value], %[storage]\n\t"     // store the replacement, tmp = store failed
            "teq   %[tmp], #0\n\t"                       // check if store succeeded
            "bne   1b\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [tmp] "=&l" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)
            : [value] "r" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "ldrex   %[original], %[storage]\n\t"             // original = *(&storage)
            "cmp     %[original], %[expected]\n\t"            // flags = original==expected
            "itt     eq\n\t"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexeq %[success], %[desired], %[storage]\n\t"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq   %[success], %[success], #1\n\t"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (expected),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"             // original = *(&storage)
            "cmp     %[original], %[expected]\n\t"            // flags = original==expected
            "bne     2f\n\t"                                  // if (!flags.equal) goto end
            "strex   %[success], %[desired], %[storage]\n\t"  // *(&storage) = desired, success = store failed
            "eors    %[success], %[success], #1\n\t"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq     1b\n\t"                                  // if (flags.equal) goto retry
            "2:\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (expected),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n\t"  // result = original + value
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n\t"  // result = original - value
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "and     %[result], %[original], %[value]\n\t"  // result = original & value
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "orr     %[result], %[original], %[value]\n\t"  // result = original | value
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "eor     %[result], %[original], %[value]\n\t"  // result = original ^ value
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
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

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_gcc_arm_base
{
    typedef typename storage_traits< 1u >::type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        extended_storage_type original;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb %[original], %[storage]\n\t"          // load the original value and zero-extend to 32 bits
            "strexb %[tmp], %[value], %[storage]\n\t"     // store the replacement, tmp = store failed
            "teq    %[tmp], #0\n\t"                       // check if store succeeded
            "bne    1b\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [tmp] "=&l" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)
            : [value] "r" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "ldrexb   %[original], %[storage]\n\t"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n\t"            // flags = original==expected
            "itt      eq\n\t"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexbeq %[success], %[desired], %[storage]\n\t"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq    %[success], %[success], #1\n\t"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n\t"            // flags = original==expected
            "bne      2f\n\t"                                  // if (!flags.equal) goto end
            "strexb   %[success], %[desired], %[storage]\n\t"  // *(&storage) = desired, success = store failed
            "eors     %[success], %[success], #1\n\t"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq      1b\n\t"                                  // if (flags.equal) goto retry
            "2:\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "add      %[result], %[original], %[value]\n\t"  // result = original + value
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "sub      %[result], %[original], %[value]\n\t"  // result = original - value
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "and      %[result], %[original], %[value]\n\t"  // result = original & value
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "orr      %[result], %[original], %[value]\n\t"  // result = original | value
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "eor      %[result], %[original], %[value]\n\t"  // result = original ^ value
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
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

#else // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

template< bool Interprocess >
struct core_arch_operations< 1u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n\t"  // result = original + value
            "uxtb    %[result], %[result]\n\t"              // zero extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n\t"  // result = original - value
            "uxtb    %[result], %[result]\n\t"              // zero extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
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
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n\t"  // result = original + value
            "sxtb    %[result], %[result]\n\t"              // sign extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n\t"  // result = original - value
            "sxtb    %[result], %[result]\n\t"              // sign extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_gcc_arm_base
{
    typedef typename storage_traits< 2u >::type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        extended_storage_type original;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh %[original], %[storage]\n\t"          // load the original value and zero-extend to 32 bits
            "strexh %[tmp], %[value], %[storage]\n\t"     // store the replacement, tmp = store failed
            "teq    %[tmp], #0\n\t"                       // check if store succeeded
            "bne    1b\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [tmp] "=&l" (tmp), [original] "=&r" (original), [storage] "+Q" (storage)
            : [value] "r" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "ldrexh   %[original], %[storage]\n\t"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n\t"            // flags = original==expected
            "itt      eq\n\t"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexheq %[success], %[desired], %[storage]\n\t"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq    %[success], %[success], #1\n\t"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        bool success = false;
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        uint32_t tmp;
#endif
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n\t"            // flags = original==expected
            "bne      2f\n\t"                                  // if (!flags.equal) goto end
            "strexh   %[success], %[desired], %[storage]\n\t"  // *(&storage) = desired, success = store failed
            "eors     %[success], %[success], #1\n\t"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq      1b\n\t"                                  // if (flags.equal) goto retry
            "2:\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),
              [success] "+r" (success),
#if !defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
              [tmp] "=&l" (tmp),
#endif
              [storage] "+Q" (storage)
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),
              [desired] "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "add      %[result], %[original], %[value]\n\t"  // result = original + value
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "sub      %[result], %[original], %[value]\n\t"  // result = original - value
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "and      %[result], %[original], %[value]\n\t"  // result = original & value
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "orr      %[result], %[original], %[value]\n\t"  // result = original | value
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "eor      %[result], %[original], %[value]\n\t"  // result = original ^ value
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return static_cast< storage_type >(original);
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

#else // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< bool Interprocess >
struct core_arch_operations< 2u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n\t"  // result = original + value
            "uxth    %[result], %[result]\n\t"              // zero extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n\t"  // result = original - value
            "uxth    %[result], %[result]\n\t"              // zero extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
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
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n\t"  // result = original + value
            "sxth    %[result], %[result]\n\t"              // sign extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex   %[original], %[storage]\n\t"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n\t"  // result = original - value
            "sxth    %[result], %[result]\n\t"              // sign extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n\t"                        // flags = tmp==0
            "bne     1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [value] "Ir" (v)              // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

// Unlike 32-bit operations, for 64-bit loads and stores we must use ldrexd/strexd.
// Any other instructions result in a non-atomic sequence of 32-bit accesses.
// See "ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition",
// Section A3.5.3 "Atomicity in the ARM architecture".

// In the asm blocks below we have to use 32-bit register pairs to compose 64-bit values.
// In order to pass the 64-bit operands to/from asm blocks, we use undocumented gcc feature:
// the lower half (Rt) of the operand is accessible normally, via the numbered placeholder (e.g. %0),
// and the upper half (Rt2) - via the same placeholder with an 'H' after the '%' sign (e.g. %H0).
// See: http://hardwarebug.org/2010/07/06/arm-inline-asm-secrets/

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_arm_base
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
        // ARMv7 says ldrex (and other load-exclusive instructions) can be used without a matching strex, see
        // "ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition", Section A3.4.5 "Load-Exclusive and Store-Exclusive usage restrictions".
        storage_type original;
#if defined(BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_UNUSED)
        __asm__ __volatile__
        (
            "ldrexd %0, %H0, %1\n\t"
            : "=&r" (original)   // %0
            : "Q" (storage)      // %1
        );
#else
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "ldrexd %1, %H1, %2\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original)   // %1
            : "Q" (storage)      // %2
        );
#endif
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd %1, %H1, %2\n\t"        // load the original value
            "strexd %0, %3, %H3, %2\n\t"    // store the replacement, tmp = store failed
            "teq    %0, #0\n\t"               // check if store succeeded
            "bne    1b\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "+Q" (storage)     // %2
            : "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        storage_type original;
        bool success = false;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "ldrexd   %1, %H1, %3\n\t"               // original = *(&storage)
            "cmp      %1, %4\n\t"                    // flags = original.lo==expected.lo
            "it       eq\n\t"                        // [hint that the following 1 instruction is conditional on flags.equal]
            "cmpeq    %H1, %H4\n\t"                  // if (flags.equal) flags = original.hi==expected.hi
            "bne      1f\n\t"
            "strexd   %2, %5, %H5, %3\n\t"           // *(&storage) = desired, success = store failed
            "eor      %2, %2, #1\n\t"                // success ^= 1 (i.e. make it 1 if store succeeded)
            "1:\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "+r" (success),    // %2
              "+Q" (storage)     // %3
            : "r" (expected),    // %4
              "r" (desired)      // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        storage_type original;
        bool success = false;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd   %1, %H1, %3\n\t"               // original = *(&storage)
            "cmp      %1, %4\n\t"                    // flags = original.lo==expected.lo
            "it       eq\n\t"                        // [hint that the following 1 instruction is conditional on flags.equal]
            "cmpeq    %H1, %H4\n\t"                  // if (flags.equal) flags = original.hi==expected.hi
            "bne      2f\n\t"
            "strexd   %2, %5, %H5, %3\n\t"           // *(&storage) = desired, success = store failed
            "eors     %2, %2, #1\n\t"                // success ^= 1 (i.e. make it 1 if store succeeded), flags.equal = success == 0
            "beq      1b\n\t"                        // if (flags.equal) goto retry
            "2:\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "+r" (success),    // %2
              "+Q" (storage)     // %3
            : "r" (expected),    // %4
              "r" (desired)      // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "adds   " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(1) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(4) "\n\t" // result = original + value
            "adc    " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(1) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(4) "\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            : "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "subs   " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(1) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(4) "\n\t" // result = original - value
            "sbc    " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(1) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(4) "\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            : "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "and     %2, %1, %4\n\t"                  // result = original & value
            "and     %H2, %H1, %H4\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            : "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "orr     %2, %1, %4\n\t"                  // result = original | value
            "orr     %H2, %H1, %H4\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            : "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "eor     %2, %1, %4\n\t"                  // result = original ^ value
            "eor     %H2, %H1, %H4\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            : "r" (v)            // %4
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

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_

/* core_arch_ops_gcc_arm.hpp
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
*/