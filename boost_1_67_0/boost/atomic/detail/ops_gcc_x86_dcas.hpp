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
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
*/