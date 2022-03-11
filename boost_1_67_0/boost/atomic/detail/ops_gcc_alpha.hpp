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
 * \file   atomic/detail/ops_gcc_alpha.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_ALPHA_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_ALPHA_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>

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

struct gcc_alpha_operations_base
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


template< bool Signed >
struct operations< 4u, Signed > :
    public gcc_alpha_operations_base
{
    typedef typename storage_traits< 4u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 4u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 4u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
            "1:\n"
            "mov %3, %1\n"
            "ldl_l %0, %2\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %2, %4\n"                // current = *(&storage)
            "cmpeq %2, %0, %3\n"            // success = current == expected
            "mov %2, %0\n"                  // expected = current
            "beq %3, 2f\n"                  // if (success == 0) goto end
            "stl_c %1, %4\n"                // storage = desired; desired = store succeeded
            "mov %1, %3\n"                  // success = desired
            "2:\n"
            : "+&r" (expected),  // %0
              "+&r" (desired),   // %1
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
            "1:\n"
            "mov %5, %1\n"                  // tmp = desired
            "ldl_l %2, %4\n"                // current = *(&storage)
            "cmpeq %2, %0, %3\n"            // success = current == expected
            "mov %2, %0\n"                  // expected = current
            "beq %3, 2f\n"                  // if (success == 0) goto end
            "stl_c %1, %4\n"                // storage = tmp; tmp = store succeeded
            "beq %1, 3f\n"                  // if (tmp == 0) goto retry
            "mov %1, %3\n"                  // success = tmp
            "2:\n"

            ".subsection 2\n"
            "3: br 1b\n"
            ".previous\n"

            : "+&r" (expected),  // %0
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
            "1:\n"
            "ldl_l %0, %2\n"
            "addl %0, %3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "subl %0, %3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "and %0, %3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "bis %0, %3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "xor %0, %3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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


template< >
struct operations< 1u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n"
            "ldl_l %0, %2\n"
            "addl %0, %3, %1\n"
            "zapnot %1, #1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "subl %0, %3, %1\n"
            "zapnot %1, #1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

template< >
struct operations< 1u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n"
            "ldl_l %0, %2\n"
            "addl %0, %3, %1\n"
            "sextb %1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "subl %0, %3, %1\n"
            "sextb %1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};


template< >
struct operations< 2u, false > :
    public operations< 4u, false >
{
    typedef operations< 4u, false > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n"
            "ldl_l %0, %2\n"
            "addl %0, %3, %1\n"
            "zapnot %1, #3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "subl %0, %3, %1\n"
            "zapnot %1, #3, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};

template< >
struct operations< 2u, true > :
    public operations< 4u, true >
{
    typedef operations< 4u, true > base_type;
    typedef base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type original, modified;
        fence_before(order);
        __asm__ __volatile__
        (
            "1:\n"
            "ldl_l %0, %2\n"
            "addl %0, %3, %1\n"
            "sextw %1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldl_l %0, %2\n"
            "subl %0, %3, %1\n"
            "sextw %1, %1\n"
            "stl_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

            : "=&r" (original),  // %0
              "=&r" (modified)   // %1
            : "m" (storage),     // %2
              "r" (v)            // %3
            : BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
        );
        fence_after(order);
        return original;
    }
};


template< bool Signed >
struct operations< 8u, Signed > :
    public gcc_alpha_operations_base
{
    typedef typename storage_traits< 8u >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

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
            "1:\n"
            "mov %3, %1\n"
            "ldq_l %0, %2\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldq_l %2, %4\n"                // current = *(&storage)
            "cmpeq %2, %0, %3\n"            // success = current == expected
            "mov %2, %0\n"                  // expected = current
            "beq %3, 2f\n"                  // if (success == 0) goto end
            "stq_c %1, %4\n"                // storage = desired; desired = store succeeded
            "mov %1, %3\n"                  // success = desired
            "2:\n"
            : "+&r" (expected),  // %0
              "+&r" (desired),   // %1
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
            "1:\n"
            "mov %5, %1\n"                  // tmp = desired
            "ldq_l %2, %4\n"                // current = *(&storage)
            "cmpeq %2, %0, %3\n"            // success = current == expected
            "mov %2, %0\n"                  // expected = current
            "beq %3, 2f\n"                  // if (success == 0) goto end
            "stq_c %1, %4\n"                // storage = tmp; tmp = store succeeded
            "beq %1, 3f\n"                  // if (tmp == 0) goto retry
            "mov %1, %3\n"                  // success = tmp
            "2:\n"

            ".subsection 2\n"
            "3: br 1b\n"
            ".previous\n"

            : "+&r" (expected),  // %0
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
            "1:\n"
            "ldq_l %0, %2\n"
            "addq %0, %3, %1\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldq_l %0, %2\n"
            "subq %0, %3, %1\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldq_l %0, %2\n"
            "and %0, %3, %1\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldq_l %0, %2\n"
            "bis %0, %3, %1\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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
            "1:\n"
            "ldq_l %0, %2\n"
            "xor %0, %3, %1\n"
            "stq_c %1, %2\n"
            "beq %1, 2f\n"

            ".subsection 2\n"
            "2: br 1b\n"
            ".previous\n"

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


BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("mb" ::: "memory");
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_ALPHA_HPP_INCLUDED_

/* ops_gcc_alpha.hpp
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
*/