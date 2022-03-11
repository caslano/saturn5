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
 * \file   atomic/detail/ops_gcc_x86.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_X86_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)
#include <boost/atomic/detail/ops_gcc_x86_dcas.hpp>
#include <boost/atomic/detail/ops_cas_based.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct gcc_x86_operations_base
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

template< std::size_t Size, bool Signed, typename Derived >
struct gcc_x86_operations :
    public gcc_x86_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

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

template< bool Signed >
struct operations< 1u, Signed > :
    public gcc_x86_operations< 1u, Signed, operations< 1u, Signed > >
{
    typedef gcc_x86_operations< 1u, Signed, operations< 1u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 1u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 1u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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

template< bool Signed >
struct operations< 2u, Signed > :
    public gcc_x86_operations< 2u, Signed, operations< 2u, Signed > >
{
    typedef gcc_x86_operations< 2u, Signed, operations< 2u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< 4u >::type temp_storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 2u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 2u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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

template< bool Signed >
struct operations< 4u, Signed > :
    public gcc_x86_operations< 4u, Signed, operations< 4u, Signed > >
{
    typedef gcc_x86_operations< 4u, Signed, operations< 4u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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

template< bool Signed >
struct operations< 8u, Signed > :
    public cas_based_operations< gcc_dcas_x86< Signed > >
{
};

#elif defined(__x86_64__)

template< bool Signed >
struct operations< 8u, Signed > :
    public gcc_x86_operations< 8u, Signed, operations< 8u, Signed > >
{
    typedef gcc_x86_operations< 8u, Signed, operations< 8u, Signed > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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

template< bool Signed >
struct operations< 16u, Signed > :
    public cas_based_operations< gcc_dcas_x86_64< Signed > >
{
};

#endif // defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order == memory_order_seq_cst)
    {
        __asm__ __volatile__
        (
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_MFENCE)
            "mfence\n"
#else
            "lock; addl $0, (%%esp)\n"
#endif
            ::: "memory"
        );
    }
    else if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_acquire) | static_cast< unsigned int >(memory_order_release))) != 0u)
    {
        __asm__ __volatile__ ("" ::: "memory");
    }
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_X86_HPP_INCLUDED_

/* ops_gcc_x86.hpp
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
*/