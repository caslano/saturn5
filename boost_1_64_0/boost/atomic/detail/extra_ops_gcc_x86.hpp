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
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, bool Signed >
struct extra_operations< Base, 1u, Signed, true > :
    public generic_extra_operations< Base, 1u, Signed >
{
    typedef generic_extra_operations< Base, 1u, Signed > base_type;
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
    public generic_extra_operations< Base, 2u, Signed >
{
    typedef generic_extra_operations< Base, 2u, Signed > base_type;
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
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
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
    public generic_extra_operations< Base, 8u, Signed >
{
    typedef generic_extra_operations< Base, 8u, Signed > base_type;
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

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GCC_X86_HPP_INCLUDED_

/* extra_ops_gcc_x86.hpp
zFzY3MypSH+R50me1HDlUjY2886biL3bE6WcLbFMG2XGKGJONWXkup0h6XEdKXa+yvWgxRSzexjlLrI22vNk+l5Hi3l6MNn4ZabtTFs9QOzEmbOLhoh+rPZ7zPsT+Y29iGde+7CMtVUba43h1E5V+/DYcNUVMjbM9h3DGTeb2ptxXx9xc5y/m3BYnmlvxmJ57rD8BH2We8ykbWFbVYxzzBgkzs4gKOTHiJyJMTCIfmmaUOR/hGA33DXiXi+Utn+8XPHHOa7RsVj0+Ka6nrZwo6MtJE9HtYWHPNrCIx5tYY7HmURzTdvG+1ezXDOmiYxn8uHt4pa86BrPHNS94g8TqNZwMzzY1+Jgeldbd2pxRclZy2T+rBVuApYIoKusKqsodrR56q6TGRfcLPqfBXL4Ej8fZef/DHFP+CJtn7rLNHMuG0V/bWAgfxehvNrMfOOuvbibgf460f8ikEssy1F+smV+LvauDvTnDS1A6Ry/+pfu/n5u6ocx70vbSLqOSpqCvpsVdhOQMl6OXvc285Php2nPJ4jbu1SP/b/L2MN8b7BUpmi4zi0U+9eoPmw/01Mu5K/E7kCrs9Y9vZLlfmGlI42niB1yJGWoWXQZMnL8fkA/cRoD2wugfa9ndo3qld1Q2SyxSel/j+TxdM1/5BnyX1SeMWNt8kNNfj2G88+c38id32cH6J73MSoXbTjqQ/v77N8d+Vq+JaoURfOBtlLS7zdmb3rkm99T4rY3udvIRlP/GLOrDDHeWqV+9jRt4eu2HUJhzyEdIq5fUIH1seu3Ri2aNmnaJS6Y0KRJWI7KKZTn6ajCrjX5KC/ZzIMb/3aLf02cbYmRyZAEn9X7Ug83UD4Z8fWUj3Gf7unfi0pTvkU6Jh5ypONZJYvMh1nN//v7SplbWBSpG9RNhinjfUT/OK0eX6Nql3HT/+op9oqpxkcZ2YTDxexu+31bK2nh1zvPc5B7bWt9R0/V72eD5f4D1uW4WY8t/Xau7rpbWbyLRlZk/JNGSrRFrUq2zRpWDsJjDNKBdCUd1GysR97Od31Hd67VSOiqMvI0H/dBbcfPnA9aRMv3M/nXd+2Pukn3W1+g9ztIPt3Ke9/WRfIp7WPTXmTS2Cb813bb5FNXWTH9uxHiV6ZvHp4t91v45uEpHxx9Ho7UBd7rE5z1w4FsS37nqAym01GH7XbPna4llZWLkZtYSA6vpAksLPWXnXi1uO1IjmymaR72L1XTJWDdKvpGfvJU1H6a+JmGfj36mv5+wLPev1Hu96I/3EzTLvyMoG/f/GW539j9jcG8u2367lxhlr5iIvmxNDvcP5taa548bGdttvb74kdZ7nmPGv2xy5D0kRVj5EQd1MUsp2uZOQX1ol1nfeh6t2XzqviLpC2W4NUhzy9L3I21WvM3z9T96h+hSSXOB4nrJp7bF4Z68J0ivrHliKenHOYkOEL8CH0r6eLM3xN7eNcba91p4L8+yV1/4Lbu+oP7pv441A2DHsdef9z8Yd31x0Mf1l1//OrDBtUf44+2/tB6Gfkwuudd64+7UJ/Y6zKd6VvprJcrfdZ9qRvH3MKnor/W6srz1qC80miCcZdq2tOPRX8j7xrZ2x71RQpXx31U8010stVUynM+72hoT9ZuSlntbvLs1C5antXOXOxcloWdxDbGzqnhb2NqZ21PnesMjZeh3kD+eo7z1P4u7A+w7TevMH4uaKn9Hqe8JH3n0yTszaP8OIIfx0tdNLdWXRTWDzwK+dRea9zcfSNzVlIf7zyw8yNnHvAoY5W+awBxG50X3vmoYXkBd1F54a2P6s8LHQ5H54UZ5Omxvf3zgtphL2AdeUHtbOjd8Lxg29/X++jywskS9uZOP9g=
*/