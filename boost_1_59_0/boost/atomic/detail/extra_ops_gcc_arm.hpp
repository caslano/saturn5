/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 - 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_gcc_arm.hpp
 *
 * This header contains implementation of the extra atomic operations for ARM.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
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

template< typename Base >
struct extra_operations_gcc_arm_common :
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
struct extra_operations_gcc_arm;

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

template< typename Base, bool Signed >
struct extra_operations_gcc_arm< Base, 1u, Signed > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexb   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strexb   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_gcc_arm_common< extra_operations_gcc_arm< Base, 1u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< typename Base, bool Signed >
struct extra_operations_gcc_arm< Base, 2u, Signed > :
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrexh   %[original], %[storage]\n\t"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strexh   %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return static_cast< storage_type >(result);
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public extra_operations_gcc_arm_common< extra_operations_gcc_arm< Base, 2u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< typename Base, bool Signed >
struct extra_operations_gcc_arm< Base, 4u, Signed > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex    %[original], %[storage]\n\t"           // original = *(&storage)
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strex    %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex    %[original], %[storage]\n\t"           // original = *(&storage)
            "rsb      %[result], %[original], #0\n\t"        // result = 0 - original
            "strex    %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex    %[original], %[storage]\n\t"           // original = *(&storage)
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strex    %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n\t"
            "ldrex    %[original], %[storage]\n\t"           // original = *(&storage)
            "mvn      %[result], %[original]\n\t"            // result = NOT original
            "strex    %[tmp], %[result], %[storage]\n\t"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n\t"                        // flags = tmp==0
            "bne      1b\n\t"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_gcc_arm_common< extra_operations_gcc_arm< Base, 4u, Signed > >
{
};

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

template< typename Base, bool Signed >
struct extra_operations_gcc_arm< Base, 8u, Signed > :
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "mvn     %2, %1\n\t"                      // result = NOT original
            "mvn     %H2, %H1\n\t"
            "adds   " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", #1\n\t" // result = result + 1
            "adc    " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", #0\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "mvn     %2, %1\n\t"                      // result = NOT original
            "mvn     %H2, %H1\n\t"
            "adds   " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_LO(2) ", #1\n\t" // result = result + 1
            "adc    " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", " BOOST_ATOMIC_DETAIL_ARM_ASM_ARG_HI(2) ", #0\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
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
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "mvn     %2, %1\n\t"                      // result = NOT original
            "mvn     %H2, %H1\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        core_arch_operations_gcc_arm_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n\t"
            "ldrexd  %1, %H1, %3\n\t"                 // original = *(&storage)
            "mvn     %2, %1\n\t"                      // result = NOT original
            "mvn     %H2, %H1\n\t"
            "strexd  %0, %2, %H2, %3\n\t"             // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n\t"                      // flags = tmp==0
            "bne     1b\n\t"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result),    // %2
              "+Q" (storage)     // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        core_arch_operations_gcc_arm_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public extra_operations_gcc_arm_common< extra_operations_gcc_arm< Base, 8u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_HPP_INCLUDED_

/* extra_ops_gcc_arm.hpp
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
*/