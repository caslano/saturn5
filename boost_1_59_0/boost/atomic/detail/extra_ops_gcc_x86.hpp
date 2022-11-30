/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2015 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_gcc_x86.hpp
 *
 * This header contains implementation of the extra atomic operations for x86.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
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

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public extra_operations_generic< Base, 1u, Signed >
{
    typedef extra_operations_generic< Base, 1u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: movzbl %[orig], %2\n\t"\
        op " %b2\n\t"\
        "lock; cmpxchgb %b2, %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), "=&q" (result)\
        : \
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negb", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notb", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negb", original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notb", original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %2\n\t"\
        op " %%al, %b2\n\t"\
        "lock; cmpxchgb %b2, %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), "=&q" (result)\
        : [arg] "ir" ((temp_storage_type)argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andb", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orb", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorb", v, original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incb %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addb %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decb %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subb %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; negb %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; andb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; orb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xorb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; notb %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : "memory"
        );
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incb %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addb %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "iq" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incb %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addb %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decb %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subb %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "iq" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decb %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subb %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; andb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; andb %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; orb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; orb %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; xorb %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; xorb %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 2u, Signed, true > :
    public extra_operations_generic< Base, 2u, Signed >
{
    typedef extra_operations_generic< Base, 2u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: movzwl %[orig], %2\n\t"\
        op " %w2\n\t"\
        "lock; cmpxchgw %w2, %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), "=&q" (result)\
        : \
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negw", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notw", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negw", original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notw", original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %2\n\t"\
        op " %%ax, %w2\n\t"\
        "lock; cmpxchgw %w2, %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), "=&q" (result)\
        : [arg] "ir" ((temp_storage_type)argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andw", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orw", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        temp_storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorw", v, original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incw %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addw %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decw %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subw %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; negw %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; andw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; orw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xorw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; notw %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : "memory"
        );
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incw %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addw %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "iq" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incw %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addw %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decw %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subw %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "iq" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decw %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subw %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "iq" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; andw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; andw %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; orw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; orw %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; xorw %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "iq" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; xorw %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "iq" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btsw %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btsw %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btrw %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btrw %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btcw %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btcw %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kq" ((uint16_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }
};

template< typename Base, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public extra_operations_generic< Base, 4u, Signed >
{
    typedef extra_operations_generic< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[orig], %[res]\n\t"\
        op " %[res]\n\t"\
        "lock; cmpxchgl %[res], %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), [res] "=&r" (result)\
        : \
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negl", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notl", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negl", original, result);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notl", original, result);
        return result;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %[res]\n\t"\
        op " %%eax, %[res]\n\t"\
        "lock; cmpxchgl %[res], %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), [res] "=&r" (result)\
        : [arg] "ir" (argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andl", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orl", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorl", v, original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incl %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addl %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "ir" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decl %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subl %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "ir" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; negl %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; andl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; orl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xorl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; notl %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : "memory"
        );
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incl %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addl %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "ir" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incl %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addl %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "ir" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decl %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subl %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "ir" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decl %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subl %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "ir" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; andl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "ir" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; andl %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; orl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "ir" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; orl %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; xorl %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "ir" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; xorl %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "ir" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btsl %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btsl %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btrl %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btrl %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btcl %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btcl %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint32_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }
};

#if defined(__x86_64__)

template< typename Base, bool Signed >
struct extra_operations< Base, 8u, Signed, true > :
    public extra_operations_generic< Base, 8u, Signed >
{
    typedef extra_operations_generic< Base, 8u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[orig], %[res]\n\t"\
        op " %[res]\n\t"\
        "lock; cmpxchgq %[res], %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), [res] "=&r" (result)\
        : \
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negq", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notq", original, result);
        return original;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("negq", original, result);
        return result;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("notq", original, result);
        return result;
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

#define BOOST_ATOMIC_DETAIL_CAS_LOOP(op, argument, original, result)\
    __asm__ __volatile__\
    (\
        ".align 16\n\t"\
        "1: mov %[arg], %[res]\n\t"\
        op " %%rax, %[res]\n\t"\
        "lock; cmpxchgq %[res], %[storage]\n\t"\
        "jne 1b"\
        : [orig] "+a" (original), [storage] "+m" (storage), [res] "=&r" (result)\
        : [arg] "r" (argument)\
        : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"\
    )

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("andq", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("orq", v, original, result);
        return static_cast< storage_type >(result);
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type original = storage;
        storage_type result;
        BOOST_ATOMIC_DETAIL_CAS_LOOP("xorq", v, original, result);
        return static_cast< storage_type >(result);
    }

#undef BOOST_ATOMIC_DETAIL_CAS_LOOP

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incq %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addq %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "er" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decq %[storage]\n\t"
                : [storage] "+m" (storage)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subq %[argument], %[storage]\n\t"
                : [storage] "+m" (storage)
                : [argument] "er" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; negq %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; andq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; orq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; xorq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        __asm__ __volatile__
        (
            "lock; notq %[storage]\n\t"
            : [storage] "+m" (storage)
            :
            : "memory"
        );
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incq %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addq %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "er" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; incq %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; addq %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "er" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decq %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                :
                : "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subq %[argument], %[storage]\n\t"
                : [storage] "+m" (storage), [result] "=@ccnz" (res)
                : [argument] "er" (v)
                : "memory"
            );
        }
#else
        if (BOOST_ATOMIC_DETAIL_IS_CONSTANT(v) && v == 1)
        {
            __asm__ __volatile__
            (
                "lock; decq %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                :
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
        else
        {
            __asm__ __volatile__
            (
                "lock; subq %[argument], %[storage]\n\t"
                "setnz %[result]\n\t"
                : [storage] "+m" (storage), [result] "=q" (res)
                : [argument] "er" (v)
                : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
        }
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; andq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "er" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; andq %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; orq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "er" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; orq %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; xorq %[argument], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccnz" (res)
            : [argument] "er" (v)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; xorq %[argument], %[storage]\n\t"
            "setnz %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [argument] "er" (v)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btsq %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btsq %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btrq %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btrq %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order) BOOST_NOEXCEPT
    {
        bool res;
#if defined(BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS)
        __asm__ __volatile__
        (
            "lock; btcq %[bit_number], %[storage]\n\t"
            : [storage] "+m" (storage), [result] "=@ccc" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : "memory"
        );
#else
        __asm__ __volatile__
        (
            "lock; btcq %[bit_number], %[storage]\n\t"
            "setc %[result]\n\t"
            : [storage] "+m" (storage), [result] "=q" (res)
            : [bit_number] "Kr" ((uint64_t)bit_number)
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif
        return res;
    }
};

#endif // defined(__x86_64__)

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_X86_HPP_INCLUDED_

/* extra_ops_gcc_x86.hpp
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
*/