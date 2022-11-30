/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fence_arch_ops_gcc_arm.hpp
 *
 * This header contains implementation of the \c fence_arch_operations struct.
 */

#ifndef BOOST_ATOMIC_DETAIL_FENCE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FENCE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/gcc_arm_asm_common.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Fence operations for legacy ARM
struct fence_arch_operations_gcc_arm
{
    static BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
    {
        if (order != memory_order_relaxed)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
    {
        if (order != memory_order_relaxed)
            __asm__ __volatile__ ("" ::: "memory");
    }

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
        // A memory barrier is effected using a "co-processor 15" instruction,
        // though a separate assembler mnemonic is available for it in v7.

#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_DMB)
        // Older binutils (supposedly, older than 2.21.1) didn't support symbolic or numeric arguments of the "dmb" instruction such as "ish" or "#11".
        // As a workaround we have to inject encoded bytes of the instruction. There are two encodings for the instruction: ARM and Thumb. See ARM Architecture Reference Manual, A8.8.43.
        // Since we cannot detect binutils version at compile time, we'll have to always use this hack.
        __asm__ __volatile__
        (
#if defined(__thumb2__)
            ".short 0xF3BF, 0x8F5B\n\t" // dmb ish
#else
            ".word 0xF57FF05B\n\t" // dmb ish
#endif
            :
            :
            : "memory"
        );
#else
        uint32_t tmp;
        __asm__ __volatile__
        (
            BOOST_ATOMIC_DETAIL_ARM_ASM_START(%0)
            "mcr p15, 0, r0, c7, c10, 5\n\t"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : "=&l" (tmp)
            :
            : "memory"
        );
#endif
    }
};

typedef fence_arch_operations_gcc_arm fence_arch_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_FENCE_ARCH_OPS_GCC_ARM_HPP_INCLUDED_

/* fence_arch_ops_gcc_arm.hpp
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
*/