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
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(_M_IX86)

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
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
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
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
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
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
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
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

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_X86_HPP_INCLUDED_

/* extra_ops_msvc_x86.hpp
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
*/