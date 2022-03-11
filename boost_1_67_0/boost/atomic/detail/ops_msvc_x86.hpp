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
 * \file   atomic/detail/ops_msvc_x86.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_MSVC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_MSVC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/capabilities.hpp>
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)
#include <boost/cstdint.hpp>
#include <boost/atomic/detail/ops_cas_based.hpp>
#endif
#include <boost/atomic/detail/ops_msvc_common.hpp>
#if !defined(_M_IX86) && !(defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8) && defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16))
#include <boost/atomic/detail/ops_extending_cas_based.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// frame pointer register 'ebx' modified by inline assembly code. See the note below.
#pragma warning(disable: 4731)
#endif

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE)
extern "C" void _mm_mfence(void);
#if defined(BOOST_MSVC)
#pragma intrinsic(_mm_mfence)
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

/*
 * Implementation note for asm blocks.
 *
 * http://msdn.microsoft.com/en-us/data/k1a8ss06%28v=vs.105%29
 *
 * Some SSE types require eight-byte stack alignment, forcing the compiler to emit dynamic stack-alignment code.
 * To be able to access both the local variables and the function parameters after the alignment, the compiler
 * maintains two frame pointers. If the compiler performs frame pointer omission (FPO), it will use EBP and ESP.
 * If the compiler does not perform FPO, it will use EBX and EBP. To ensure code runs correctly, do not modify EBX
 * in asm code if the function requires dynamic stack alignment as it could modify the frame pointer.
 * Either move the eight-byte aligned types out of the function, or avoid using EBX.
 *
 * Since we have no way of knowing that the compiler uses FPO, we have to always save and restore ebx
 * whenever we have to clobber it. Additionally, we disable warning C4731 above so that the compiler
 * doesn't spam about ebx use.
 */

struct msvc_x86_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void hardware_full_fence() BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE)
        _mm_mfence();
#else
        long tmp;
        BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&tmp, 0);
#endif
    }

    static BOOST_FORCEINLINE void fence_before(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        // On x86 and x86_64 there is no need for a hardware barrier,
        // even if seq_cst memory order is requested, because all
        // seq_cst writes are implemented with lock-prefixed operations
        // or xchg which has implied lock prefix. Therefore normal loads
        // are already ordered with seq_cst stores on these architectures.
    }
};

template< std::size_t Size, bool Signed, typename Derived >
struct msvc_x86_operations :
    public msvc_x86_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
        fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        typedef typename boost::atomics::detail::make_signed< storage_type >::type signed_storage_type;
        return Derived::fetch_add(storage, static_cast< storage_type >(-static_cast< signed_storage_type >(v)), order);
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

template< bool Signed >
struct operations< 4u, Signed > :
    public msvc_x86_operations< 4u, Signed, operations< 4u, Signed > >
{
    typedef msvc_x86_operations< 4u, Signed, operations< 4u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&storage, v));
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&storage, desired, previous));
        expected = old_val;
        return (previous == old_val);
    }

#if defined(BOOST_ATOMIC_INTERLOCKED_AND)
    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND(&storage, v));
    }
#else
    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res & v, order, memory_order_relaxed)) {}
        return res;
    }
#endif

#if defined(BOOST_ATOMIC_INTERLOCKED_OR)
    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR(&storage, v));
    }
#else
    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res | v, order, memory_order_relaxed)) {}
        return res;
    }
#endif

#if defined(BOOST_ATOMIC_INTERLOCKED_XOR)
    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR(&storage, v));
    }
#else
    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res ^ v, order, memory_order_relaxed)) {}
        return res;
    }
#endif
};

#if defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8)

template< bool Signed >
struct operations< 1u, Signed > :
    public msvc_x86_operations< 1u, Signed, operations< 1u, Signed > >
{
    typedef msvc_x86_operations< 1u, Signed, operations< 1u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD8(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE8(&storage, v));
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8(&storage, desired, previous));
        expected = old_val;
        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND8(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR8(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR8(&storage, v));
    }
};

#elif defined(_M_IX86)

template< bool Signed >
struct operations< 1u, Signed > :
    public msvc_x86_operations< 1u, Signed, operations< 1u, Signed > >
{
    typedef msvc_x86_operations< 1u, Signed, operations< 1u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xadd byte ptr [edx], al
            mov v, al
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            xchg byte ptr [edx], al
            mov v, al
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order) BOOST_NOEXCEPT
    {
        base_type::fence_before(success_order);
        bool success;
        __asm
        {
            mov esi, expected
            mov edi, storage
            movzx eax, byte ptr [esi]
            movzx edx, desired
            lock cmpxchg byte ptr [edi], dl
            mov byte ptr [esi], al
            sete success
        };
        // The success and failure fences are equivalent anyway
        base_type::fence_after(success_order);
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, byte ptr [edi]
            align 16
        again:
            mov dl, al
            and dl, cl
            lock cmpxchg byte ptr [edi], dl
            jne again
            mov v, al
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, byte ptr [edi]
            align 16
        again:
            mov dl, al
            or dl, cl
            lock cmpxchg byte ptr [edi], dl
            jne again
            mov v, al
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, byte ptr [edi]
            align 16
        again:
            mov dl, al
            xor dl, cl
            lock cmpxchg byte ptr [edi], dl
            jne again
            mov v, al
        };
        base_type::fence_after(order);
        return v;
    }
};

#else

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 1u, Signed >
{
};

#endif

#if defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16)

template< bool Signed >
struct operations< 2u, Signed > :
    public msvc_x86_operations< 2u, Signed, operations< 2u, Signed > >
{
    typedef msvc_x86_operations< 2u, Signed, operations< 2u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD16(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE16(&storage, v));
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16(&storage, desired, previous));
        expected = old_val;
        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND16(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR16(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR16(&storage, v));
    }
};

#elif defined(_M_IX86)

template< bool Signed >
struct operations< 2u, Signed > :
    public msvc_x86_operations< 2u, Signed, operations< 2u, Signed > >
{
    typedef msvc_x86_operations< 2u, Signed, operations< 2u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xadd word ptr [edx], ax
            mov v, ax
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            xchg word ptr [edx], ax
            mov v, ax
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order) BOOST_NOEXCEPT
    {
        base_type::fence_before(success_order);
        bool success;
        __asm
        {
            mov esi, expected
            mov edi, storage
            movzx eax, word ptr [esi]
            movzx edx, desired
            lock cmpxchg word ptr [edi], dx
            mov word ptr [esi], ax
            sete success
        };
        // The success and failure fences are equivalent anyway
        base_type::fence_after(success_order);
        return success;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, word ptr [edi]
            align 16
        again:
            mov dx, ax
            and dx, cx
            lock cmpxchg word ptr [edi], dx
            jne again
            mov v, ax
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, word ptr [edi]
            align 16
        again:
            mov dx, ax
            or dx, cx
            lock cmpxchg word ptr [edi], dx
            jne again
            mov v, ax
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            movzx ecx, v
            xor edx, edx
            movzx eax, word ptr [edi]
            align 16
        again:
            mov dx, ax
            xor dx, cx
            lock cmpxchg word ptr [edi], dx
            jne again
            mov v, ax
        };
        base_type::fence_after(order);
        return v;
    }
};

#else

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 2u, Signed >
{
};

#endif


#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

template< bool Signed >
struct msvc_dcas_x86
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    // Intel 64 and IA-32 Architectures Software Developer's Manual, Volume 3A, 8.1.1. Guaranteed Atomic Operations:
    //
    // The Pentium processor (and newer processors since) guarantees that the following additional memory operations will always be carried out atomically:
    // * Reading or writing a quadword aligned on a 64-bit boundary
    //
    // Luckily, the memory is almost always 8-byte aligned in our case because atomic<> uses 64 bit native types for storage and dynamic memory allocations
    // have at least 8 byte alignment. The only unfortunate case is when atomic is placed on the stack and it is not 8-byte aligned (like on 32 bit Windows).

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        storage_type volatile* p = &storage;
        if (((uint32_t)p & 0x00000007) == 0)
        {
#if defined(_M_IX86_FP) && _M_IX86_FP >= 2
#if defined(__AVX__)
            __asm
            {
                mov edx, p
                vmovq xmm4, v
                vmovq qword ptr [edx], xmm4
            };
#else
            __asm
            {
                mov edx, p
                movq xmm4, v
                movq qword ptr [edx], xmm4
            };
#endif
#else
            __asm
            {
                mov edx, p
                fild v
                fistp qword ptr [edx]
            };
#endif
        }
        else
        {
            uint32_t backup;
            __asm
            {
                mov backup, ebx
                mov edi, p
                mov ebx, dword ptr [v]
                mov ecx, dword ptr [v + 4]
                mov eax, dword ptr [edi]
                mov edx, dword ptr [edi + 4]
                align 16
            again:
                lock cmpxchg8b qword ptr [edi]
                jne again
                mov ebx, backup
            };
        }

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        storage_type const volatile* p = &storage;
        storage_type value;

        if (((uint32_t)p & 0x00000007) == 0)
        {
#if defined(_M_IX86_FP) && _M_IX86_FP >= 2
#if defined(__AVX__)
            __asm
            {
                mov edx, p
                vmovq xmm4, qword ptr [edx]
                vmovq value, xmm4
            };
#else
            __asm
            {
                mov edx, p
                movq xmm4, qword ptr [edx]
                movq value, xmm4
            };
#endif
#else
            __asm
            {
                mov edx, p
                fild qword ptr [edx]
                fistp value
            };
#endif
        }
        else
        {
            // We don't care for comparison result here; the previous value will be stored into value anyway.
            // Also we don't care for ebx and ecx values, they just have to be equal to eax and edx before cmpxchg8b.
            __asm
            {
                mov edi, p
                mov eax, ebx
                mov edx, ecx
                lock cmpxchg8b qword ptr [edi]
                mov dword ptr [value], eax
                mov dword ptr [value + 4], edx
            };
        }

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        return value;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        // MSVC-11 in 32-bit mode sometimes generates messed up code without compiler barriers,
        // even though the _InterlockedCompareExchange64 intrinsic already provides one.
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        storage_type volatile* p = &storage;
#if defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64)
        const storage_type old_val = (storage_type)BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(p, desired, expected);
        const bool result = (old_val == expected);
        expected = old_val;
#else
        bool result;
        uint32_t backup;
        __asm
        {
            mov backup, ebx
            mov edi, p
            mov esi, expected
            mov ebx, dword ptr [desired]
            mov ecx, dword ptr [desired + 4]
            mov eax, dword ptr [esi]
            mov edx, dword ptr [esi + 4]
            lock cmpxchg8b qword ptr [edi]
            mov dword ptr [esi], eax
            mov dword ptr [esi + 4], edx
            mov ebx, backup
            sete result
        };
#endif
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        return result;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        storage_type volatile* p = &storage;
        uint32_t backup;
        __asm
        {
            mov backup, ebx
            mov edi, p
            mov ebx, dword ptr [v]
            mov ecx, dword ptr [v + 4]
            mov eax, dword ptr [edi]
            mov edx, dword ptr [edi + 4]
            align 16
        again:
            lock cmpxchg8b qword ptr [edi]
            jne again
            mov ebx, backup
            mov dword ptr [v], eax
            mov dword ptr [v + 4], edx
        };

        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();

        return v;
    }
};

template< bool Signed >
struct operations< 8u, Signed > :
    public cas_based_operations< msvc_dcas_x86< Signed > >
{
};

#elif defined(_M_AMD64)

template< bool Signed >
struct operations< 8u, Signed > :
    public msvc_x86_operations< 8u, Signed, operations< 8u, Signed > >
{
    typedef msvc_x86_operations< 8u, Signed, operations< 8u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD64(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE64(&storage, v));
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE64(&storage, desired, previous));
        expected = old_val;
        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND64(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR64(&storage, v));
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR64(&storage, v));
    }
};

#endif

#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

template< bool Signed >
struct msvc_dcas_x86_64
{
    typedef typename storage_traits< 16u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 16u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 16u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type value = const_cast< storage_type& >(storage);
        while (!BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE128(&storage, v, &value)) {}
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type value = storage_type();
        BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE128(&storage, value, &value);
        return value;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        return !!BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE128(&storage, desired, &expected);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }
};

template< bool Signed >
struct operations< 16u, Signed > :
    public cas_based_operations< cas_based_exchange< msvc_dcas_x86_64< Signed > > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    if (order == memory_order_seq_cst)
        msvc_x86_operations_base::hardware_full_fence();
    BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
}

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_OPS_MSVC_X86_HPP_INCLUDED_

/* ops_msvc_x86.hpp
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
*/