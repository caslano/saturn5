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
 * \file   atomic/detail/ops_gcc_arm.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/ops_gcc_arm_common.hpp>
#include <boost/atomic/capabilities.hpp>

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
// FIXME these are not yet used; should be mostly a matter of copy-and-paste.
// I think you can supply an immediate offset to the address.

template< bool Signed >
struct operations< 4u, Signed > :
    public gcc_arm_operations_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
        storage_type original;
        fence_before(order);
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex %[original], %[storage]\n"          // load the original value
            "strex %[tmp], %[value], %[storage]\n"     // store the replacement, tmp = store failed
            "teq   %[tmp], #0\n"                       // check if store succeeded
            "bne   1b\n"
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
        uint32_t success;
        uint32_t tmp;
        storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov     %[success], #0\n"                      // success = 0
            "ldrex   %[original], %[storage]\n"             // original = *(&storage)
            "cmp     %[original], %[expected]\n"            // flags = original==expected
            "itt     eq\n"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexeq %[success], %[desired], %[storage]\n"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq   %[success], %[success], #1\n"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (expected),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        uint32_t success;
        uint32_t tmp;
        storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov     %[success], #0\n"                      // success = 0
            "1:\n"
            "ldrex   %[original], %[storage]\n"             // original = *(&storage)
            "cmp     %[original], %[expected]\n"            // flags = original==expected
            "bne     2f\n"                                  // if (!flags.equal) goto end
            "strex   %[success], %[desired], %[storage]\n"  // *(&storage) = desired, success = store failed
            "eors    %[success], %[success], #1\n"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq     1b\n"                                  // if (flags.equal) goto retry
            "2:\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (expected),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n"  // result = original + value
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n"  // result = original - value
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "and     %[result], %[original], %[value]\n"  // result = original & value
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "orr     %[result], %[original], %[value]\n"  // result = original | value
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "eor     %[result], %[original], %[value]\n"  // result = original ^ value
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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

template< bool Signed >
struct operations< 1u, Signed > :
    public gcc_arm_operations_base
{
    typedef typename storage_traits< 1u >::type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
        extended_storage_type original;
        fence_before(order);
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb %[original], %[storage]\n"          // load the original value and zero-extend to 32 bits
            "strexb %[tmp], %[value], %[storage]\n"     // store the replacement, tmp = store failed
            "teq    %[tmp], #0\n"                       // check if store succeeded
            "bne    1b\n"
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
        uint32_t success;
        uint32_t tmp;
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov      %[success], #0\n"                      // success = 0
            "ldrexb   %[original], %[storage]\n"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n"            // flags = original==expected
            "itt      eq\n"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexbeq %[success], %[desired], %[storage]\n"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq    %[success], %[success], #1\n"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        uint32_t success;
        uint32_t tmp;
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov      %[success], #0\n"                      // success = 0
            "1:\n"
            "ldrexb   %[original], %[storage]\n"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n"            // flags = original==expected
            "bne      2f\n"                                  // if (!flags.equal) goto end
            "strexb   %[success], %[desired], %[storage]\n"  // *(&storage) = desired, success = store failed
            "eors     %[success], %[success], #1\n"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq      1b\n"                                  // if (flags.equal) goto retry
            "2:\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "add      %[result], %[original], %[value]\n"  // result = original + value
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "sub      %[result], %[original], %[value]\n"  // result = original - value
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "and      %[result], %[original], %[value]\n"  // result = original & value
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "orr      %[result], %[original], %[value]\n"  // result = original | value
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "eor      %[result], %[original], %[value]\n"  // result = original ^ value
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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

template< >
struct operations< 1u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n"  // result = original + value
            "uxtb    %[result], %[result]\n"              // zero extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n"  // result = original - value
            "uxtb    %[result], %[result]\n"              // zero extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
};

template< >
struct operations< 1u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n"  // result = original + value
            "sxtb    %[result], %[result]\n"              // sign extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n"  // result = original - value
            "sxtb    %[result], %[result]\n"              // sign extend result from 8 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< bool Signed >
struct operations< 2u, Signed > :
    public gcc_arm_operations_base
{
    typedef typename storage_traits< 2u >::type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
        extended_storage_type original;
        fence_before(order);
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh %[original], %[storage]\n"          // load the original value and zero-extend to 32 bits
            "strexh %[tmp], %[value], %[storage]\n"     // store the replacement, tmp = store failed
            "teq    %[tmp], #0\n"                       // check if store succeeded
            "bne    1b\n"
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
        uint32_t success;
        uint32_t tmp;
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov      %[success], #0\n"                      // success = 0
            "ldrexh   %[original], %[storage]\n"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n"            // flags = original==expected
            "itt      eq\n"                                  // [hint that the following 2 instructions are conditional on flags.equal]
            "strexheq %[success], %[desired], %[storage]\n"  // if (flags.equal) *(&storage) = desired, success = store failed
            "eoreq    %[success], %[success], #1\n"          // if (flags.equal) success ^= 1 (i.e. make it 1 if store succeeded)
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        uint32_t success;
        uint32_t tmp;
        extended_storage_type original;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "mov      %[success], #0\n"                      // success = 0
            "1:\n"
            "ldrexh   %[original], %[storage]\n"             // original = zero_extend(*(&storage))
            "cmp      %[original], %[expected]\n"            // flags = original==expected
            "bne      2f\n"                                  // if (!flags.equal) goto end
            "strexh   %[success], %[desired], %[storage]\n"  // *(&storage) = desired, success = store failed
            "eors     %[success], %[success], #1\n"          // success ^= 1 (i.e. make it 1 if store succeeded); flags.equal = success == 0
            "beq      1b\n"                                  // if (flags.equal) goto retry
            "2:\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [success] "=&r" (success),    // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            : [expected] "Ir" (atomics::detail::zero_extend< extended_storage_type >(expected)),   // %4
              [desired] "r" (desired)       // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = static_cast< storage_type >(original);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "add      %[result], %[original], %[value]\n"  // result = original + value
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "sub      %[result], %[original], %[value]\n"  // result = original - value
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "and      %[result], %[original], %[value]\n"  // result = original & value
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "orr      %[result], %[original], %[value]\n"  // result = original | value
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "eor      %[result], %[original], %[value]\n"  // result = original ^ value
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
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

template< >
struct operations< 2u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n"  // result = original + value
            "uxth    %[result], %[result]\n"              // zero extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n"  // result = original - value
            "uxth    %[result], %[result]\n"              // zero extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
};

template< >
struct operations< 2u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "add     %[result], %[original], %[value]\n"  // result = original + value
            "sxth    %[result], %[result]\n"              // sign extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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
            "1:\n"
            "ldrex   %[original], %[storage]\n"           // original = *(&storage)
            "sub     %[result], %[original], %[value]\n"  // result = original - value
            "sxth    %[result], %[result]\n"              // sign extend result from 16 to 32 bits
            "strex   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq     %[tmp], #0\n"                        // flags = tmp==0
            "bne     1b\n"                                // if (!flags.equal) goto retry
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

template< bool Signed >
struct operations< 8u, Signed > :
    public gcc_arm_operations_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "ldrexd %1, %H1, [%2]\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original)   // %1
            : "r" (&storage)     // %2
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original;
        fence_before(order);
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd %1, %H1, [%3]\n"        // load the original value
            "strexd %0, %2, %H2, [%3]\n"    // store the replacement, tmp = store failed
            "teq    %0, #0\n"               // check if store succeeded
            "bne    1b\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original)   // %1
            : "r" (v),           // %2
              "r" (&storage)     // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        uint32_t tmp;
        storage_type original, old_val = expected;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "ldrexd   %1, %H1, [%3]\n"               // original = *(&storage)
            "cmp      %1, %2\n"                      // flags = original.lo==old_val.lo
            "ittt     eq\n"                          // [hint that the following 3 instructions are conditional on flags.equal]
            "cmpeq    %H1, %H2\n"                    // if (flags.equal) flags = original.hi==old_val.hi
            "strexdeq %0, %4, %H4, [%3]\n"           // if (flags.equal) *(&storage) = desired, tmp = store failed
            "teqeq    %0, #0\n"                      // if (flags.equal) flags = tmp==0
            "ite      eq\n"                          // [hint that the following 2 instructions are conditional on flags.equal]
            "moveq    %2, #1\n"                      // if (flags.equal) old_val.lo = 1
            "movne    %2, #0\n"                      // if (!flags.equal) old_val.lo = 0
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "+r" (old_val)     // %2
            : "r" (&storage),    // %3
              "r" (desired)      // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        const uint32_t success = (uint32_t)old_val;
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        uint32_t tmp;
        storage_type original, old_val = expected;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "cmp     %1, %2\n"                      // flags = original.lo==old_val.lo
            "it      eq\n"                          // [hint that the following instruction is conditional on flags.equal]
            "cmpeq   %H1, %H2\n"                    // if (flags.equal) flags = original.hi==old_val.hi
            "bne     2f\n"                          // if (!flags.equal) goto end
            "strexd  %0, %4, %H4, [%3]\n"           // *(&storage) = desired, tmp = store failed
            "teq     %0, #0\n"                      // flags.equal = tmp == 0
            "bne     1b\n"                          // if (flags.equal) goto retry
            "2:\n"
            "ite      eq\n"                         // [hint that the following 2 instructions are conditional on flags.equal]
            "moveq    %2, #1\n"                     // if (flags.equal) old_val.lo = 1
            "movne    %2, #0\n"                     // if (!flags.equal) old_val.lo = 0
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "+r" (old_val)     // %2
            : "r" (&storage),    // %3
              "r" (desired)      // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        const uint32_t success = (uint32_t)old_val;
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = original;
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "adds    %2, %1, %4\n"                  // result = original + value
            "adc     %H2, %H1, %H4\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage),    // %3
              "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
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
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "subs    %2, %1, %4\n"                  // result = original - value
            "sbc     %H2, %H1, %H4\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage),    // %3
              "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
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
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "and     %2, %1, %4\n"                  // result = original & value
            "and     %H2, %H1, %H4\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage),    // %3
              "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
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
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "orr     %2, %1, %4\n"                  // result = original | value
            "orr     %H2, %H1, %H4\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage),    // %3
              "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
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
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "eor     %2, %1, %4\n"                  // result = original ^ value
            "eor     %H2, %H1, %H4\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage),    // %3
              "r" (v)            // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
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


BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        gcc_arm_operations_base::hardware_full_fence();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_HPP_INCLUDED_

/* ops_gcc_arm.hpp
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
*/