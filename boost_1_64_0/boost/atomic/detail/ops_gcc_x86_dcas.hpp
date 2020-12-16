/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 - 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_x86_dcas.hpp
 *
 * This header contains implementation of the double-width CAS primitive for x86.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/string_ops.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// Note: In the 32-bit PIC code guarded with BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX below we have to avoid using memory
// operand constraints because the compiler may choose to use ebx as the base register for that operand. At least, clang
// is known to do that. For this reason we have to pre-compute a pointer to storage and pass it in edi. For the same reason
// we cannot save ebx to the stack with a mov instruction, so we use esi as a scratch register and restore it afterwards.
// Alternatively, we could push/pop the register to the stack, but exchanging the registers is faster.
// The need to pass a pointer in edi is a bit wasteful because normally the memory operand would use a base pointer
// with an offset (e.g. `this` + offset). But unfortunately, there seems to be no way around it.

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

template< bool Signed >
struct gcc_dcas_x86
{
    typedef typename storage_traits< 8u >::type storage_type;
    typedef uint32_t BOOST_ATOMIC_DETAIL_MAY_ALIAS aliasing_uint32_t;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_LIKELY((((uint32_t)&storage) & 0x00000007) == 0u))
        {
#if defined(__SSE__)
            typedef float xmm_t __attribute__((__vector_size__(16)));
            xmm_t xmm_scratch;
            __asm__ __volatile__
            (
#if defined(__AVX__)
                "vmovq %[value], %[xmm_scratch]\n\t"
                "vmovq %[xmm_scratch], %[storage]\n\t"
#elif defined(__SSE2__)
                "movq %[value], %[xmm_scratch]\n\t"
                "movq %[xmm_scratch], %[storage]\n\t"
#else
                "xorps %[xmm_scratch], %[xmm_scratch]\n\t"
                "movlps %[value], %[xmm_scratch]\n\t"
                "movlps %[xmm_scratch], %[storage]\n\t"
#endif
                : [storage] "=m" (storage), [xmm_scratch] "=x" (xmm_scratch)
                : [value] "m" (v)
                : "memory"
            );
#else
            __asm__ __volatile__
            (
                "fildll %[value]\n\t"
                "fistpll %[storage]\n\t"
                : [storage] "=m" (storage)
                : [value] "m" (v)
                : "memory"
            );
#endif
        }
        else
        {
#if defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
            __asm__ __volatile__
            (
                "xchgl %%ebx, %%esi\n\t"
                "movl %%eax, %%ebx\n\t"
                "movl (%[dest]), %%eax\n\t"
                "movl 4(%[dest]), %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b (%[dest])\n\t"
                "jne 1b\n\t"
                "xchgl %%ebx, %%esi\n\t"
                :
                : "a" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "edx", "memory"
            );
#else // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
            __asm__ __volatile__
            (
                "movl %[dest_lo], %%eax\n\t"
                "movl %[dest_hi], %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b %[dest_lo]\n\t"
                "jne 1b\n\t"
                : [dest_lo] "=m" (storage), [dest_hi] "=m" (reinterpret_cast< volatile aliasing_uint32_t* >(&storage)[1])
                : [value_lo] "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "eax", "edx", "memory"
            );
#endif // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
        }
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type value;

        if (BOOST_LIKELY((((uint32_t)&storage) & 0x00000007) == 0u))
        {
#if defined(__SSE__)
            typedef float xmm_t __attribute__((__vector_size__(16)));
            xmm_t xmm_scratch;
            __asm__ __volatile__
            (
#if defined(__AVX__)
                "vmovq %[storage], %[xmm_scratch]\n\t"
                "vmovq %[xmm_scratch], %[value]\n\t"
#elif defined(__SSE2__)
                "movq %[storage], %[xmm_scratch]\n\t"
                "movq %[xmm_scratch], %[value]\n\t"
#else
                "xorps %[xmm_scratch], %[xmm_scratch]\n\t"
                "movlps %[storage], %[xmm_scratch]\n\t"
                "movlps %[xmm_scratch], %[value]\n\t"
#endif
                : [value] "=m" (value), [xmm_scratch] "=x" (xmm_scratch)
                : [storage] "m" (storage)
                : "memory"
            );
#else
            __asm__ __volatile__
            (
                "fildll %[storage]\n\t"
                "fistpll %[value]\n\t"
                : [value] "=m" (value)
                : [storage] "m" (storage)
                : "memory"
            );
#endif
        }
        else
        {
            // Note that despite const qualification cmpxchg8b below may issue a store to the storage. The storage value
            // will not change, but this prevents the storage to reside in read-only memory.

#if defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

            uint32_t value_bits[2];

            // We don't care for comparison result here; the previous value will be stored into value anyway.
            // Also we don't care for ebx and ecx values, they just have to be equal to eax and edx before cmpxchg8b.
            __asm__ __volatile__
            (
                "movl %%ebx, %%eax\n\t"
                "movl %%ecx, %%edx\n\t"
                "lock; cmpxchg8b %[storage]\n\t"
                : "=&a" (value_bits[0]), "=&d" (value_bits[1])
                : [storage] "m" (storage)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
            BOOST_ATOMIC_DETAIL_MEMCPY(&value, value_bits, sizeof(value));

#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

            // We don't care for comparison result here; the previous value will be stored into value anyway.
            // Also we don't care for ebx and ecx values, they just have to be equal to eax and edx before cmpxchg8b.
            __asm__ __volatile__
            (
                "movl %%ebx, %%eax\n\t"
                "movl %%ecx, %%edx\n\t"
                "lock; cmpxchg8b %[storage]\n\t"
                : "=&A" (value)
                : [storage] "m" (storage)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );

#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
        }

        return value;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
#if defined(__clang__)

        // Clang cannot allocate eax:edx register pairs but it has sync intrinsics
        storage_type old_expected = expected;
        expected = __sync_val_compare_and_swap(&storage, old_expected, desired);
        return expected == old_expected;

#elif defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)

        bool success;

#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "xchgl %%ebx, %%esi\n\t"
            "lock; cmpxchg8b (%[dest])\n\t"
            "xchgl %%ebx, %%esi\n\t"
            : "+A" (expected), [success] "=@ccz" (success)
            : "S" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32)), [dest] "D" (&storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "xchgl %%ebx, %%esi\n\t"
            "lock; cmpxchg8b (%[dest])\n\t"
            "xchgl %%ebx, %%esi\n\t"
            "sete %[success]\n\t"
            : "+A" (expected), [success] "=qm" (success)
            : "S" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32)), [dest] "D" (&storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)

        return success;

#else // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)

        bool success;

#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchg8b %[dest]\n\t"
            : "+A" (expected), [dest] "+m" (storage), [success] "=@ccz" (success)
            : "b" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32))
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchg8b %[dest]\n\t"
            "sete %[success]\n\t"
            : "+A" (expected), [dest] "+m" (storage), [success] "=qm" (success)
            : "b" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32))
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)

        return success;

#endif // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
#if defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        uint32_t old_bits[2];
        __asm__ __volatile__
        (
            "xchgl %%ebx, %%esi\n\t"
            "movl (%[dest]), %%eax\n\t"
            "movl 4(%[dest]), %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b (%[dest])\n\t"
            "jne 1b\n\t"
            "xchgl %%ebx, %%esi\n\t"
            : "=a" (old_bits[0]), "=d" (old_bits[1])
            : "S" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        storage_type old_value;
        BOOST_ATOMIC_DETAIL_MEMCPY(&old_value, old_bits, sizeof(old_value));
        return old_value;

#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        storage_type old_value;
        __asm__ __volatile__
        (
            "xchgl %%ebx, %%esi\n\t"
            "movl (%[dest]), %%eax\n\t"
            "movl 4(%[dest]), %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b (%[dest])\n\t"
            "jne 1b\n\t"
            "xchgl %%ebx, %%esi\n\t"
            : "=A" (old_value)
            : "S" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return old_value;

#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
#else // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
#if defined(__MINGW32__) && ((__GNUC__+0) * 100 + (__GNUC_MINOR__+0)) < 407

        // MinGW gcc up to 4.6 has problems with allocating registers in the asm blocks below
        uint32_t old_bits[2];
        __asm__ __volatile__
        (
            "movl (%[dest]), %%eax\n\t"
            "movl 4(%[dest]), %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b (%[dest])\n\t"
            "jne 1b\n\t"
            : "=&a" (old_bits[0]), "=&d" (old_bits[1])
            : "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "DS" (&storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        storage_type old_value;
        BOOST_ATOMIC_DETAIL_MEMCPY(&old_value, old_bits, sizeof(old_value));
        return old_value;

#elif defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        uint32_t old_bits[2];
        __asm__ __volatile__
        (
            "movl %[dest_lo], %%eax\n\t"
            "movl %[dest_hi], %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b %[dest_lo]\n\t"
            "jne 1b\n\t"
            : "=&a" (old_bits[0]), "=&d" (old_bits[1]), [dest_lo] "+m" (storage), [dest_hi] "+m" (reinterpret_cast< volatile aliasing_uint32_t* >(&storage)[1])
            : "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        storage_type old_value;
        BOOST_ATOMIC_DETAIL_MEMCPY(&old_value, old_bits, sizeof(old_value));
        return old_value;

#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        storage_type old_value;
        __asm__ __volatile__
        (
            "movl %[dest_lo], %%eax\n\t"
            "movl %[dest_hi], %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b %[dest_lo]\n\t"
            "jne 1b\n\t"
            : "=&A" (old_value), [dest_lo] "+m" (storage), [dest_hi] "+m" (reinterpret_cast< volatile aliasing_uint32_t* >(&storage)[1])
            : "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return old_value;

#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
#endif // defined(BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX)
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

template< bool Signed >
struct gcc_dcas_x86_64
{
    typedef typename storage_traits< 16u >::type storage_type;
    typedef uint64_t BOOST_ATOMIC_DETAIL_MAY_ALIAS aliasing_uint64_t;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 16u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 16u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "movq %[dest_lo], %%rax\n\t"
            "movq %[dest_hi], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest_lo]\n\t"
            "jne 1b\n\t"
            : [dest_lo] "=m" (storage), [dest_hi] "=m" (reinterpret_cast< volatile aliasing_uint64_t* >(&storage)[1])
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&v)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&v)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "rax", "rdx", "memory"
        );
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        // Note that despite const qualification cmpxchg16b below may issue a store to the storage. The storage value
        // will not change, but this prevents the storage to reside in read-only memory.

#if defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        uint64_t value_bits[2];

        // We don't care for comparison result here; the previous value will be stored into value anyway.
        // Also we don't care for rbx and rcx values, they just have to be equal to rax and rdx before cmpxchg16b.
        __asm__ __volatile__
        (
            "movq %%rbx, %%rax\n\t"
            "movq %%rcx, %%rdx\n\t"
            "lock; cmpxchg16b %[storage]\n\t"
            : "=&a" (value_bits[0]), "=&d" (value_bits[1])
            : [storage] "m" (storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        storage_type value;
        BOOST_ATOMIC_DETAIL_MEMCPY(&value, value_bits, sizeof(value));
        return value;

#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        storage_type value;

        // We don't care for comparison result here; the previous value will be stored into value anyway.
        // Also we don't care for rbx and rcx values, they just have to be equal to rax and rdx before cmpxchg16b.
        __asm__ __volatile__
        (
            "movq %%rbx, %%rax\n\t"
            "movq %%rcx, %%rdx\n\t"
            "lock; cmpxchg16b %[storage]\n\t"
            : "=&A" (value)
            : [storage] "m" (storage)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        return value;

#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
#if defined(__clang__)

        // Clang cannot allocate rax:rdx register pairs but it has sync intrinsics
        storage_type old_expected = expected;
        expected = __sync_val_compare_and_swap(&storage, old_expected, desired);
        return expected == old_expected;

#elif defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        // Some compilers can't allocate rax:rdx register pair either but also don't support 128-bit __sync_val_compare_and_swap
        bool success;
        __asm__ __volatile__
        (
            "lock; cmpxchg16b %[dest]\n\t"
            "sete %[success]\n\t"
            : [dest] "+m" (storage), "+a" (reinterpret_cast< aliasing_uint64_t* >(&expected)[0]), "+d" (reinterpret_cast< aliasing_uint64_t* >(&expected)[1]), [success] "=q" (success)
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        return success;

#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)

        bool success;

#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchg16b %[dest]\n\t"
            : "+A" (expected), [dest] "+m" (storage), "=@ccz" (success)
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchg16b %[dest]\n\t"
            "sete %[success]\n\t"
            : "+A" (expected), [dest] "+m" (storage), [success] "=qm" (success)
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&desired)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)

        return success;

#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
        uint64_t old_bits[2];
        __asm__ __volatile__
        (
            "movq %[dest_lo], %%rax\n\t"
            "movq %[dest_hi], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest_lo]\n\t"
            "jne 1b\n\t"
            : [dest_lo] "+m" (storage), [dest_hi] "+m" (reinterpret_cast< volatile aliasing_uint64_t* >(&storage)[1]), "=&a" (old_bits[0]), "=&d" (old_bits[1])
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&v)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&v)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        storage_type old_value;
        BOOST_ATOMIC_DETAIL_MEMCPY(&old_value, old_bits, sizeof(old_value));
        return old_value;
#else // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
        storage_type old_value;
        __asm__ __volatile__
        (
            "movq %[dest_lo], %%rax\n\t"
            "movq %[dest_hi], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest_lo]\n\t"
            "jne 1b\n\t"
            : "=&A" (old_value), [dest_lo] "+m" (storage), [dest_hi] "+m" (reinterpret_cast< volatile aliasing_uint64_t* >(&storage)[1])
            : "b" (reinterpret_cast< const aliasing_uint64_t* >(&v)[0]), "c" (reinterpret_cast< const aliasing_uint64_t* >(&v)[1])
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        return old_value;
#endif // defined(BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS)
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_

/* ops_gcc_x86_dcas.hpp
zPfdJRDPMLM4Wu6Be5XCOpf3wEXI3tR3k633r91Ee9h4T0EL+9SyeZ8alTuHyT5Vwx60BofJXmbDHrRsk31jL1M8yK3vHYu8j2At7xtbzGcW7OhvKafz3NZtInY3wExO2S5BZGg/0cWW5xQcJPufEe0S92mma/JfJbtxLI8e3n5y7kBKZuBzCk4h+w6m/LxHy63fO3CI/J+lxEIeHLLnCu/b4fyJtp5RMFjpQjEq7K7Q8zq+Lwt4F/AcrW+e2ZyXNdqQJh0zaalnmHe45MFmojerJnUo81bq6sCK2lKMeXIdyvaziK4B/SjRC1WzOrdC+F1EV4LeQfRK1ax9Nh32N5P9Faq+zoUfUj/ifEnT+nsGeO8hvhXiNtvgdjfcGup2chsL+mHiWy5ucwxu9zv86/oeLDdPE9+3CC8U+jdCqYLx+JNr8Oegw7j/JI9k5nniqVE9+283Ej1M/Ckw+HPIYb1f8fgAjS9Czn6ACsO6R9qvSDzxoLsTTyK4wphHVcKJJx40eIROM+psKS9N5Mc4Pp9AVT6j7ztbRSiqQV9LmXypOV5qMy1h6uoYaDfdvpo8lMUuwGd5v/AHyc26+B1G1tf0+0P8DmVd/Rf8fpP0N5850YLOdrHODrRvGGVFv2+Y20lUPujdTod/GwvyamxzQw792l2QL/9210GTeuGQcW+y1AuUblQvFA3wrRdOZV0yu5dCz26uFx6EGaG1ywcadAmqgwB9ZPBb7iWGnaE+IHqLqT6JA32Q7Dd72+gsc2b6JAb4KtlfSnSF8PcTGZ6bxTreoF90+gRuDG14gz4R/WHgRTvYsm+QY+BtDNA3yDXwbrLoGxQY+LZZnK0cA5xN8Q41poN1XUf+bjTWddTnqGrlGRxtGw/ylpN6k75Ig0nfdI1J/6TRpH+yyaQ+3WaxF3n8KQo9E7l/MobHJHZQejVUDC5tWxue3MEXs7LAduZjEWKfb90fzWp5LGJHVhv6o1mt7I9mnZz+6Pc5FuHJ7xEJhvzmOYGEbE9+t60tDHdW+Q27gPkN+4D5DfuW8zshu/X5nZDduvxOyD4548LfZ3575oCyExV6pnJ+T+Sxp0br/IYSCljG2e1E0zxnO/MxJ7HPtcpz2Lc85tTYhjxvbGWeN2afnDL+fY45efI8Kck/zzEHhEotUJ4HLOdwa5nnsAuY57APmOewbznPlUGtz3NlUOvyXBl0csr595nnX4DeGTxj/wffQ/5b2kNe8t2hAZ3z6vJWN76mHHlhc0ZwD/mFrTh7P0EzKdZ3773MezmzYdwGPjswifle472hB4DZTMtdfK30PzL1v/O/mN2NbsH/JuabYOL/3ez/PcAC4L3sTua0gS4Td7eyu9uA44Dbde4a2d3oFuKTa4jPJ2mti48r3To+A9j/gRyfLJ27HenW8Ulhd6kcnzR9OmS0PT47NV529ym70++VX6hZA+uBpwGXAEcAlwKnA5cDZwEvAV7Ae+WXA1cAVwNXAi8DrgJuBv4KeCtwNfBO4BrgA8BLgY8DLwM+DVwHfJ730r8EvAL4CrAR+BpwPX9/ocJjvcC1/P0dgOP5+5/mPd3PAYcBnwdOBe4GngfcAywHvgCsBe4FLgbuY/8Vz7gkj6vCfxoP+cJT4eEVjFIArAOOAV4FHAu8DjgeeAuwHPgQcAHwCWAl8FngfOAefn+A378JnAA8BJwE/A44GWjnve+hwKnAVOA0YBZwOnAIsBCYA5wFLAaeD5wPnA28CPgz4CXAC4BrgCXAzcC5wK3AUuAdwDLeg18t6czjC8DdJun8IKfzw5zOOzmdH+F0fgy4HbgLeD/wceCDwCfYf+lzAieayO9Qlt9hwDHAU/Vyn23tbiO728Q=
*/