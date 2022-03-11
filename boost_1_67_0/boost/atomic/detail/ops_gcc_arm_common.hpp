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
 * \file   atomic/detail/ops_gcc_arm_common.hpp
 *
 * This header contains basic utilities for gcc ARM backend.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_COMMON_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_COMMON_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// A memory barrier is effected using a "co-processor 15" instruction,
// though a separate assembler mnemonic is available for it in v7.
//
// "Thumb 1" is a subset of the ARM instruction set that uses a 16-bit encoding.  It
// doesn't include all instructions and in particular it doesn't include the co-processor
// instruction used for the memory barrier or the load-locked/store-conditional
// instructions.  So, if we're compiling in "Thumb 1" mode, we need to wrap all of our
// asm blocks with code to temporarily change to ARM mode.
//
// You can only change between ARM and Thumb modes when branching using the bx instruction.
// bx takes an address specified in a register.  The least significant bit of the address
// indicates the mode, so 1 is added to indicate that the destination code is Thumb.
// A temporary register is needed for the address and is passed as an argument to these
// macros.  It must be one of the "low" registers accessible to Thumb code, specified
// using the "l" attribute in the asm statement.
//
// Architecture v7 introduces "Thumb 2", which does include (almost?) all of the ARM
// instruction set.  (Actually, there was an extension of v6 called v6T2 which supported
// "Thumb 2" mode, but its architecture manual is no longer available, referring to v7.)
// So in v7 we don't need to change to ARM mode; we can write "universal
// assembler" which will assemble to Thumb 2 or ARM code as appropriate.  The only thing
// we need to do to make this "universal" assembler mode work is to insert "IT" instructions
// to annotate the conditional instructions.  These are ignored in other modes (e.g. v6),
// so they can always be present.

// A note about memory_order_consume. Technically, this architecture allows to avoid
// unnecessary memory barrier after consume load since it supports data dependency ordering.
// However, some compiler optimizations may break a seemingly valid code relying on data
// dependency tracking by injecting bogus branches to aid out of order execution.
// This may happen not only in Boost.Atomic code but also in user's code, which we have no
// control of. See this thread: http://lists.boost.org/Archives/boost/2014/06/213890.php.
// For this reason we promote memory_order_consume to memory_order_acquire.

#if defined(__thumb__) && !defined(__thumb2__)
#define BOOST_ATOMIC_DETAIL_ARM_ASM_START(TMPREG) "adr " #TMPREG ", 8f\n" "bx " #TMPREG "\n" ".arm\n" ".align 4\n" "8:\n"
#define BOOST_ATOMIC_DETAIL_ARM_ASM_END(TMPREG)   "adr " #TMPREG ", 9f + 1\n" "bx " #TMPREG "\n" ".thumb\n" ".align 2\n" "9:\n"
#define BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(var) "=&l" (var)
#else
// The tmpreg may be wasted in this case, which is non-optimal.
#define BOOST_ATOMIC_DETAIL_ARM_ASM_START(TMPREG)
#define BOOST_ATOMIC_DETAIL_ARM_ASM_END(TMPREG)
#define BOOST_ATOMIC_DETAIL_ARM_ASM_TMPREG_CONSTRAINT(var) "=&r" (var)
#endif

struct gcc_arm_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            hardware_full_fence();
    }

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_DMB)
        // Older binutils (supposedly, older than 2.21.1) didn't support symbolic or numeric arguments of the "dmb" instruction such as "ish" or "#11".
        // As a workaround we have to inject encoded bytes of the instruction. There are two encodings for the instruction: ARM and Thumb. See ARM Architecture Reference Manual, A8.8.43.
        // Since we cannot detect binutils version at compile time, we'll have to always use this hack.
        __asm__ __volatile__
        (
#if defined(__thumb2__)
            ".short 0xF3BF, 0x8F5B\n" // dmb ish
#else
            ".word 0xF57FF05B\n" // dmb ish
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
            "mcr\tp15, 0, r0, c7, c10, 5\n"
            BOOST_ATOMIC_DETAIL_ARM_ASM_END(%0)
            : "=&l" (tmp)
            :
            : "memory"
        );
#endif
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_ARM_COMMON_HPP_INCLUDED_

/* ops_gcc_arm_common.hpp
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
*/