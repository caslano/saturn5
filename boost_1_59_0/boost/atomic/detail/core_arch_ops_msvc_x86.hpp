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
 * \file   atomic/detail/core_arch_ops_msvc_x86.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)
#include <boost/cstdint.hpp>
#include <boost/atomic/detail/cas_based_exchange.hpp>
#include <boost/atomic/detail/core_ops_cas_based.hpp>
#endif
#include <boost/atomic/detail/ops_msvc_common.hpp>
#if !defined(_M_IX86) && !(defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE8) && defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16))
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#endif
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
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
 * whenever we have to clobber it. Additionally, we disable warning C4731 in header.hpp so that the compiler
 * doesn't spam about ebx use.
 */

struct core_arch_operations_msvc_x86_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

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

template< std::size_t Size, bool Signed, bool Interprocess, typename Derived >
struct core_arch_operations_msvc_x86 :
    public core_arch_operations_msvc_x86_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 4u, Signed, Interprocess, core_arch_operations< 4u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 1u, Signed, Interprocess, core_arch_operations< 1u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_arch_operations< 4u, Signed, Interprocess >, 1u, Signed >
{
};

#endif

#if defined(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE16)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 2u, Signed, Interprocess, core_arch_operations< 2u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_arch_operations< 4u, Signed, Interprocess >, 2u, Signed >
{
};

#endif


#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

template< bool Signed, bool Interprocess >
struct msvc_dcas_x86
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
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
        if (((uintptr_t)p & 0x00000007) == 0)
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

        if (((uintptr_t)p & 0x00000007) == 0)
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_operations_cas_based< msvc_dcas_x86< Signed, Interprocess > >
{
};

#elif defined(_M_AMD64)

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_msvc_x86< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > >
{
    typedef core_arch_operations_msvc_x86< 8u, Signed, Interprocess, core_arch_operations< 8u, Signed, Interprocess > > base_type;
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

template< bool Signed, bool Interprocess >
struct msvc_dcas_x86_64
{
    typedef typename storage_traits< 16u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 16u, Signed, Interprocess > :
    public core_operations_cas_based< cas_based_exchange< msvc_dcas_x86_64< Signed, Interprocess > > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_MSVC_X86_HPP_INCLUDED_

/* core_arch_ops_msvc_x86.hpp
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
*/