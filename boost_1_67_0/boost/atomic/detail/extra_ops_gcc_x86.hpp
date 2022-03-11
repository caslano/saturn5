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
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
*/