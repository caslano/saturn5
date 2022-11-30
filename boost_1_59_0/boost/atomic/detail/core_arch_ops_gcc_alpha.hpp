/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_arch_ops_gcc_alpha.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ALPHA_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ALPHA_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

/*
  Refer to http://h71000.www7.hp.com/doc/82final/5601/5601pro_004.html
  (HP OpenVMS systems documentation) and the Alpha Architecture Reference Manual.
 */

/*
    NB: The most natural thing would be to write the increment/decrement
    operators along the following lines:

    __asm__ __volatile__
    (
        "1: ldl_l %0,%1 \n"
        "addl %0,1,%0 \n"
        "stl_c %0,%1 \n"
        "beq %0,1b\n"
        : "=&b" (tmp)
        : "m" (value)
        : "cc"
    );

    However according to the comments on the HP website and matching
    comments in the Linux kernel sources this defies branch prediction,
    as the cpu assumes that backward branches are always taken; so
    instead copy the trick from the Linux kernel, introduce a forward
    branch and back again.

    I have, however, had a hard time measuring the difference between
    the two versions in microbenchmarks -- I am leaving it in nevertheless
    as it apparently does not hurt either.
*/

struct core_arch_operations_gcc_alpha_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __asm__ __volatile__ ("mb" ::: "memory");
    }

    static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            __asm__ __volatile__ ("mb" ::: "memory");
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("mb" ::: "memory");
    }
};


template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_arch_operations_gcc_alpha_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, tmp;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "mov %3, %1\n\t"
            "ldl_l %0, %2\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (tmp)        // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        int success;
        storage_type current;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %2, %4\n\t"                // current = *(&storage)
            "cmpeq %2, %0, %3\n\t"            // success = current == expected
            "mov %2, %0\n\t"                  // expected = current
            "beq %3, 2f\n\t"                  // if (success == 0) goto end
            "stl_c %1, %4\n\t"                // storage = desired; desired = store succeeded
            "mov %1, %3\n\t"                  // success = desired
            "2:\n\t"
            : "+r" (expected),   // %0
              "+r" (desired),    // %1
              "=&r" (current),   // %2
              "=&r" (success)    // %3
            : "m" (storage)      // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        storage_type current, tmp;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "mov %5, %1\n\t"                  // tmp = desired
            "ldl_l %2, %4\n\t"                // current = *(&storage)
            "cmpeq %2, %0, %3\n\t"            // success = current == expected
            "mov %2, %0\n\t"                  // expected = current
            "beq %3, 2f\n\t"                  // if (success == 0) goto end
            "stl_c %1, %4\n\t"                // storage = tmp; tmp = store succeeded
            "beq %1, 3f\n\t"                  // if (tmp == 0) goto retry
            "mov %1, %3\n\t"                  // success = tmp
            "2:\n\t"

            ".subsection 2\n\t"
            "3: br 1b\n\t"
            ".previous\n\t"

            : "+r" (expected),   // %0
              "=&r" (tmp),       // %1
              "=&r" (current),   // %2
              "=&r" (success)    // %3
            : "m" (storage),     // %4
              "r" (desired)      // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "addl %0, %3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "subl %0, %3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "and %0, %3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "bis %0, %3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "xor %0, %3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, 0, order);
    }
};


template< bool Interprocess >
struct core_arch_operations< 1u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "addl %0, %3, %1\n\t"
            "zapnot %1, 1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "subl %0, %3, %1\n\t"
            "zapnot %1, 1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

template< bool Interprocess >
struct core_arch_operations< 1u, true, Interprocess > :
    public core_arch_operations< 4u, true, Interprocess >
{
    typedef core_arch_operations< 4u, true, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "addl %0, %3, %1\n\t"
            "sextb %1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "subl %0, %3, %1\n\t"
            "sextb %1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};


template< bool Interprocess >
struct core_arch_operations< 2u, false, Interprocess > :
    public core_arch_operations< 4u, false, Interprocess >
{
    typedef core_arch_operations< 4u, false, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "addl %0, %3, %1\n\t"
            "zapnot %1, 3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "subl %0, %3, %1\n\t"
            "zapnot %1, 3, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};

template< bool Interprocess >
struct core_arch_operations< 2u, true, Interprocess > :
    public core_arch_operations< 4u, true, Interprocess >
{
    typedef core_arch_operations< 4u, true, Interprocess > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "addl %0, %3, %1\n\t"
            "sextw %1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        base_type::fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldl_l %0, %2\n\t"
            "subl %0, %3, %1\n\t"
            "sextw %1, %1\n\t"
            "stl_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        base_type::fence_after(order);
        return original;
    }
};


template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_arch_operations_gcc_alpha_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, tmp;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "mov %3, %1\n\t"
            "ldq_l %0, %2\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (tmp)        // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        int success;
        storage_type current;
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %2, %4\n\t"                // current = *(&storage)
            "cmpeq %2, %0, %3\n\t"            // success = current == expected
            "mov %2, %0\n\t"                  // expected = current
            "beq %3, 2f\n\t"                  // if (success == 0) goto end
            "stq_c %1, %4\n\t"                // storage = desired; desired = store succeeded
            "mov %1, %3\n\t"                  // success = desired
            "2:\n\t"
            : "+r" (expected),   // %0
              "+r" (desired),    // %1
              "=&r" (current),   // %2
              "=&r" (success)    // %3
            : "m" (storage)      // %4
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        int success;
        storage_type current, tmp;
        fence_before(success_order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "mov %5, %1\n\t"                  // tmp = desired
            "ldq_l %2, %4\n\t"                // current = *(&storage)
            "cmpeq %2, %0, %3\n\t"            // success = current == expected
            "mov %2, %0\n\t"                  // expected = current
            "beq %3, 2f\n\t"                  // if (success == 0) goto end
            "stq_c %1, %4\n\t"                // storage = tmp; tmp = store succeeded
            "beq %1, 3f\n\t"                  // if (tmp == 0) goto retry
            "mov %1, %3\n\t"                  // success = tmp
            "2:\n\t"

            ".subsection 2\n\t"
            "3: br 1b\n\t"
            ".previous\n\t"

            : "+r" (expected),   // %0
              "=&r" (tmp),       // %1
              "=&r" (current),   // %2
              "=&r" (success)    // %3
            : "m" (storage),     // %4
              "r" (desired)      // %5
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        return !!success;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %0, %2\n\t"
            "addq %0, %3, %1\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %0, %2\n\t"
            "subq %0, %3, %1\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %0, %2\n\t"
            "and %0, %3, %1\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %0, %2\n\t"
            "bis %0, %3, %1\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n\t"
            "ldq_l %0, %2\n\t"
            "xor %0, %3, %1\n\t"
            "stq_c %1, %2\n\t"
            "beq %1, 2f\n\t"

            ".subsection 2\n\t"
            "2: br 1b\n\t"
            ".previous\n\t"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_ALPHA_HPP_INCLUDED_

/* core_arch_ops_gcc_alpha.hpp
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
*/