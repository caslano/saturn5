/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_x86.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)
#include <boost/cstdint.hpp>
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/string_ops.hpp>
#include <boost/atomic/detail/core_ops_cas_based.hpp>
#endif
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct core_arch_operations_gcc_x86_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __asm__ __volatile__ ("" ::: "memory");
    }

    static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            __asm__ __volatile__ ("" ::: "memory");
    }
};

template< std::size_t Size, bool Signed, bool Interprocess, typename Derived >
struct core_arch_operations_gcc_x86 :
    public core_arch_operations_gcc_x86_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = Size;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        if (order != memory_order_seq_cst)
        {
            fence_before(order);
            storage = v;
            fence_after(order);
        }
        else
        {
            Derived::exchange(storage, v, order);
        }
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return Derived::fetch_add(storage, -v, order);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return Derived::compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Derived::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_gcc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > >
{
    typedef core_arch_operations_gcc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xaddb %0, %1"
            : "+q" (v), "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "xchgb %0, %1"
            : "+q" (v), "+m" (storage)
            :
            : "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        bool success;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgb %3, %1"
            : "+a" (previous), "+m" (storage), "=@ccz" (success)
            : "q" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgb %3, %1\n\t"
            "sete %2"
            : "+a" (previous), "+m" (storage), "=q" (success)
            : "q" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        expected = previous;
        return success;
    }

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, result)\
    temp_storage_type new_val;\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %2\n\t"\
        op " %%al, %b2\n\t"\
        "lock; cmpxchgb %b2, %[storage]\n\t"\
        "jne 1b"\
        : [res] "+a" (result), [storage] "+m" (storage), "=&q" (new_val)\
        : [arg] "ir" ((temp_storage_type)argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andb", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orb", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorb", v, res);
        return res;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_gcc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > >
{
    typedef core_arch_operations_gcc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xaddw %0, %1"
            : "+q" (v), "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "xchgw %0, %1"
            : "+q" (v), "+m" (storage)
            :
            : "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        bool success;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgw %3, %1"
            : "+a" (previous), "+m" (storage), "=@ccz" (success)
            : "q" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgw %3, %1\n\t"
            "sete %2"
            : "+a" (previous), "+m" (storage), "=q" (success)
            : "q" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        expected = previous;
        return success;
    }

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, result)\
    temp_storage_type new_val;\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %2\n\t"\
        op " %%ax, %w2\n\t"\
        "lock; cmpxchgw %w2, %[storage]\n\t"\
        "jne 1b"\
        : [res] "+a" (result), [storage] "+m" (storage), "=&q" (new_val)\
        : [arg] "ir" ((temp_storage_type)argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andw", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orw", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorw", v, res);
        return res;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_gcc_x86< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > >
{
    typedef core_arch_operations_gcc_x86< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xaddl %0, %1"
            : "+r" (v), "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "xchgl %0, %1"
            : "+r" (v), "+m" (storage)
            :
            : "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        bool success;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgl %3, %1"
            : "+a" (previous), "+m" (storage), "=@ccz" (success)
            : "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgl %3, %1\n\t"
            "sete %2"
            : "+a" (previous), "+m" (storage), "=q" (success)
            : "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        expected = previous;
        return success;
    }

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, result)\
    storage_type new_val;\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %[new_val]\n\t"\
        op " %%eax, %[new_val]\n\t"\
        "lock; cmpxchgl %[new_val], %[storage]\n\t"\
        "jne 1b"\
        : [res] "+a" (result), [storage] "+m" (storage), [new_val] "=&r" (new_val)\
        : [arg] "ir" (argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andl", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orl", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorl", v, res);
        return res;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP
};

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

// Note: In the 32-bit PIC code guarded with BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX below we have to avoid using memory
// operand constraints because the compiler may choose to use ebx as the base register for that operand. At least, clang
// is known to do that. For this reason we have to pre-compute a pointer to storage and pass it in edi. For the same reason
// we cannot save ebx to the stack with a mov instruction, so we use esi as a scratch register and restore it afterwards.
// Alternatively, we could push/pop the register to the stack, but exchanging the registers is faster.
// The need to pass a pointer in edi is a bit wasteful because normally the memory operand would use a base pointer
// with an offset (e.g. `this` + offset). But unfortunately, there seems to be no way around it.

template< bool Signed, bool Interprocess >
struct gcc_dcas_x86
{
    typedef typename storage_traits< 8u >::type storage_type;
    typedef uint32_t BOOST_ATOMIC_DETAIL_MAY_ALIAS aliasing_uint32_t;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_LIKELY((((uintptr_t)&storage) & 0x00000007) == 0u))
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

        if (BOOST_LIKELY((((uintptr_t)&storage) & 0x00000007) == 0u))
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_operations_cas_based< gcc_dcas_x86< Signed, Interprocess > >
{
};

#elif defined(__x86_64__)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_x86< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > >
{
    typedef core_arch_operations_gcc_x86< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xaddq %0, %1"
            : "+r" (v), "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "xchgq %0, %1"
            : "+r" (v), "+m" (storage)
            :
            : "memory"
        );
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        bool success;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgq %3, %1"
            : "+a" (previous), "+m" (storage), "=@ccz" (success)
            : "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; cmpxchgq %3, %1\n\t"
            "sete %2"
            : "+a" (previous), "+m" (storage), "=q" (success)
            : "r" (desired)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        expected = previous;
        return success;
    }

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, result)\
    storage_type new_val;\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: movq %[arg], %[new_val]\n\t"\
        op " %%rax, %[new_val]\n\t"\
        "lock; cmpxchgq %[new_val], %[storage]\n\t"\
        "jne 1b"\
        : [res] "+a" (result), [storage] "+m" (storage), [new_val] "=&r" (new_val)\
        : [arg] "r" (argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andq", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orq", v, res);
        return res;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorq", v, res);
        return res;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP
};

#endif

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

template< bool Signed, bool Interprocess >
struct gcc_dcas_x86_64
{
    typedef typename storage_traits< 16u >::type storage_type;
    typedef uint64_t BOOST_ATOMIC_DETAIL_MAY_ALIAS aliasing_uint64_t;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 16u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 16u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 16u, Signed, Interprocess > :
    public core_operations_cas_based< gcc_dcas_x86_64< Signed, Interprocess > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_X86_HPP_INCLUDED_

/* core_arch_ops_gcc_x86.hpp
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
*/