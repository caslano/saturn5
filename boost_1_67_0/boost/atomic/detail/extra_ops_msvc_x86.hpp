/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_msvc_x86.hpp
 *
 * This header contains implementation of the extra atomic operations for x86.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// frame pointer register 'ebx' modified by inline assembly code
#pragma warning(disable: 4731)
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(_M_IX86)

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public generic_extra_operations< Base, 1u, Signed >
{
    typedef generic_extra_operations< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            mov old_val, al
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            mov new_val, dl
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            test dl, dl
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dl
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dl
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dl
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            mov old_val, al
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            mov new_val, dl
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
            test dl, dl
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            movzx eax, byte ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dl
            lock cmpxchg byte ptr [ecx], dl
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock add byte ptr [edx], al
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock sub byte ptr [edx], al
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock neg byte ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock and byte ptr [edx], al
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock or byte ptr [edx], al
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xor byte ptr [edx], al
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock not byte ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock add byte ptr [edx], al
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock sub byte ptr [edx], al
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock and byte ptr [edx], al
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock or byte ptr [edx], al
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xor byte ptr [edx], al
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public generic_extra_operations< Base, 2u, Signed >
{
    typedef generic_extra_operations< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            mov old_val, ax
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            mov new_val, dx
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            test dx, dx
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg dx
            lock cmpxchg word ptr [ecx], dx
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
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
            mov v, dx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            mov old_val, ax
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            mov new_val, dx
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dx
            lock cmpxchg word ptr [ecx], dx
            jne again
            test dx, dx
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            movzx eax, word ptr [ecx]
            align 16
        again:
            mov edx, eax
            not dx
            lock cmpxchg word ptr [ecx], dx
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock add word ptr [edx], ax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock sub word ptr [edx], ax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock neg word ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock and word ptr [edx], ax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock or word ptr [edx], ax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xor word ptr [edx], ax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock not word ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock add word ptr [edx], ax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock sub word ptr [edx], ax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock and word ptr [edx], ax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock or word ptr [edx], ax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            movzx eax, v
            lock xor word ptr [edx], ax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock bts word ptr [edx], ax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock btr word ptr [edx], ax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock btc word ptr [edx], ax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }
};

#endif // defined(_M_IX86)

#if defined(_M_IX86) || (defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR))

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

#if defined(_M_IX86)
    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            mov old_val, eax
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            mov new_val, edx
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            test edx, edx
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            neg edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            mov ecx, v
            xor edx, edx
            mov eax, dword ptr [edi]
            align 16
        again:
            mov edx, eax
            and edx, ecx
            lock cmpxchg dword ptr [edi], edx
            jne again
            mov v, edx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            mov ecx, v
            xor edx, edx
            mov eax, dword ptr [edi]
            align 16
        again:
            mov edx, eax
            or edx, ecx
            lock cmpxchg dword ptr [edi], edx
            jne again
            mov v, edx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edi, storage
            mov ecx, v
            xor edx, edx
            mov eax, dword ptr [edi]
            align 16
        again:
            mov edx, eax
            xor edx, ecx
            lock cmpxchg dword ptr [edi], edx
            jne again
            mov v, edx
        };
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type old_val;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            not edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            mov old_val, eax
        };
        base_type::fence_after(order);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        storage_type new_val;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            not edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            mov new_val, edx
        };
        base_type::fence_after(order);
        return new_val;
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            not edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
            test edx, edx
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov ecx, storage
            mov eax, dword ptr [ecx]
            align 16
        again:
            mov edx, eax
            not edx
            lock cmpxchg dword ptr [ecx], edx
            jne again
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            mov eax, v
            lock add dword ptr [edx], eax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            mov eax, v
            lock sub dword ptr [edx], eax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock neg dword ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            mov eax, v
            lock and dword ptr [edx], eax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            mov eax, v
            lock or dword ptr [edx], eax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            mov eax, v
            lock xor dword ptr [edx], eax
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        __asm
        {
            mov edx, storage
            lock not dword ptr [edx]
        };
        base_type::fence_after(order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, v
            lock add dword ptr [edx], eax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, v
            lock sub dword ptr [edx], eax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, v
            lock and dword ptr [edx], eax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, v
            lock or dword ptr [edx], eax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, v
            lock xor dword ptr [edx], eax
            setnz result
        };
        base_type::fence_after(order);
        return result;
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock btc dword ptr [edx], eax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }
#endif // defined(_M_IX86)

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS)
    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        return !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
    }
#elif defined(_M_IX86)
    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock bts dword ptr [edx], eax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }
#endif

#if defined(BOOST_ATOMIC_INTERLOCKED_BTR)
    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        return !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
    }
#elif defined(_M_IX86)
    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        bool result;
        __asm
        {
            mov edx, storage
            mov eax, bit_number
            lock btr dword ptr [edx], eax
            setc result
        };
        base_type::fence_after(order);
        return result;
    }
#endif
};

#endif // defined(_M_IX86) || (defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR))

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS64) && defined(BOOST_ATOMIC_INTERLOCKED_BTR64)

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public generic_extra_operations< Base, 8u, Signed >
{
    typedef generic_extra_operations< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        return !!BOOST_ATOMIC_INTERLOCKED_BTS64(&storage, bit_number);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        return !!BOOST_ATOMIC_INTERLOCKED_BTR64(&storage, bit_number);
    }
};

#endif // defined(BOOST_ATOMIC_INTERLOCKED_BTS64) && defined(BOOST_ATOMIC_INTERLOCKED_BTR64)

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_X86_HPP_INCLUDED_

/* extra_ops_msvc_x86.hpp
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
*/