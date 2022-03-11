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
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct gcc_arm_extra_operations_common :
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
struct gcc_arm_extra_operations;

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

template< typename Base, bool Signed >
struct gcc_arm_extra_operations< Base, 1u, Signed > :
    public generic_extra_operations< Base, 1u, Signed >
{
    typedef generic_extra_operations< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexb   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strexb   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public gcc_arm_extra_operations_common< gcc_arm_extra_operations< Base, 1u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB)

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< typename Base, bool Signed >
struct gcc_arm_extra_operations< Base, 2u, Signed > :
    public generic_extra_operations< Base, 2u, Signed >
{
    typedef generic_extra_operations< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type extended_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(original);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        extended_storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrexh   %[original], %[storage]\n"           // original = zero_extend(*(&storage))
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strexh   %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return static_cast< storage_type >(result);
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public gcc_arm_extra_operations_common< gcc_arm_extra_operations< Base, 2u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH)

template< typename Base, bool Signed >
struct gcc_arm_extra_operations< Base, 4u, Signed > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex    %[original], %[storage]\n"           // original = *(&storage)
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strex    %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex    %[original], %[storage]\n"           // original = *(&storage)
            "rsb      %[result], %[original], #0\n"        // result = 0 - original
            "strex    %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex    %[original], %[storage]\n"           // original = *(&storage)
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strex    %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        uint32_t tmp;
        storage_type original, result;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%[tmp])
            "1:\n"
            "ldrex    %[original], %[storage]\n"           // original = *(&storage)
            "mvn      %[result], %[original]\n"            // result = NOT original
            "strex    %[tmp], %[result], %[storage]\n"     // *(&storage) = result, tmp = store failed
            "teq      %[tmp], #0\n"                        // flags = tmp==0
            "bne      1b\n"                                // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%[tmp])
            : [original] "=&r" (original),  // %0
              [result] "=&r" (result),      // %1
              [tmp] "=&l" (tmp),            // %2
              [storage] "+Q" (storage)      // %3
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        gcc_arm_operations_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public gcc_arm_extra_operations_common< gcc_arm_extra_operations< Base, 4u, Signed > >
{
};

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

template< typename Base, bool Signed >
struct gcc_arm_extra_operations< Base, 8u, Signed > :
    public generic_extra_operations< Base, 8u, Signed >
{
    typedef generic_extra_operations< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "mvn     %2, %1\n"                      // result = NOT original
            "mvn     %H2, %H1\n"
            "adds    %2, %2, #1\n"                  // result = result + 1
            "adc     %H2, %H2, #0\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage)     // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        gcc_arm_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "mvn     %2, %1\n"                      // result = NOT original
            "mvn     %H2, %H1\n"
            "adds    %2, %2, #1\n"                  // result = result + 1
            "adc     %H2, %H2, #0\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage)     // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
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
        gcc_arm_operations_base::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "mvn     %2, %1\n"                      // result = NOT original
            "mvn     %H2, %H1\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage)     // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        gcc_arm_operations_base::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        gcc_arm_operations_base::fence_before(order);
        storage_type original, result;
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "1:\n"
            "ldrexd  %1, %H1, [%3]\n"               // original = *(&storage)
            "mvn     %2, %1\n"                      // result = NOT original
            "mvn     %H2, %H1\n"
            "strexd  %0, %2, %H2, [%3]\n"           // *(&storage) = result, tmp = store failed
            "teq     %0, #0\n"                      // flags = tmp==0
            "bne     1b\n"                          // if (!flags.equal) goto retry
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(tmp), // %0
              "=&r" (original),  // %1
              "=&r" (result)     // %2
            : "r" (&storage)     // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        gcc_arm_operations_base::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public gcc_arm_extra_operations_common< gcc_arm_extra_operations< Base, 8u, Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_ARM_HPP_INCLUDED_

/* extra_ops_gcc_arm.hpp
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
*/