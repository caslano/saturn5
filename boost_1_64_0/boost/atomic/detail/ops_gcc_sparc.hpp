/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2010 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_sparc.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_SPARC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_SPARC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/ops_cas_based.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct gcc_sparc_cas_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
        else if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __asm__ __volatile__ ("membar #StoreStore | #LoadStore" ::: "memory");
    }

    static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
        else if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            __asm__ __volatile__ ("membar #StoreStore | #LoadStore" ::: "memory");
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
    }
};

template< bool Signed >
struct gcc_sparc_cas32 :
    public gcc_sparc_cas_base
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

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        storage_type previous = expected;
        __asm__ __volatile__
        (
            "cas [%1], %2, %0"
            : "+r" (desired)
            : "r" (&storage), "r" (previous)
            : "memory"
        );
        const bool success = (desired == previous);
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = desired;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before(order);
        __asm__ __volatile__
        (
            "swap [%1], %0"
            : "+r" (v)
            : "r" (&storage)
            : "memory"
        );
        fence_after(order);
        return v;
    }
};

template< bool Signed >
struct operations< 4u, Signed > :
    public cas_based_operations< gcc_sparc_cas32< Signed > >
{
};

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 1u, Signed >
{
};

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< operations< 4u, Signed >, 2u, Signed >
{
};

template< bool Signed >
struct gcc_sparc_cas64 :
    public gcc_sparc_cas_base
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

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        fence_before(success_order);
        storage_type previous = expected;
        __asm__ __volatile__
        (
            "casx [%1], %2, %0"
            : "+r" (desired)
            : "r" (&storage), "r" (previous)
            : "memory"
        );
        const bool success = (desired == previous);
        if (success)
            fence_after(success_order);
        else
            fence_after(failure_order);
        expected = desired;
        return success;
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }
};

template< bool Signed >
struct operations< 8u, Signed > :
    public cas_based_operations< cas_based_exchange< gcc_sparc_cas64< Signed > > >
{
};


BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    switch (order)
    {
    case memory_order_release:
        __asm__ __volatile__ ("membar #StoreStore | #LoadStore" ::: "memory");
        break;
    case memory_order_consume:
    case memory_order_acquire:
        __asm__ __volatile__ ("membar #LoadLoad | #LoadStore" ::: "memory");
        break;
    case memory_order_acq_rel:
        __asm__ __volatile__ ("membar #LoadLoad | #LoadStore | #StoreStore" ::: "memory");
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("membar #Sync" ::: "memory");
        break;
    case memory_order_relaxed:
    default:
        break;
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

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_SPARC_HPP_INCLUDED_

/* ops_gcc_sparc.hpp
+eefe+a/fU7G/X9lVUX1JYvqtRsAT/j+v++SFVkP/ZbKbXCYTjDZMMX4k3AWrYFyjZ5QRGthC4dln1509vRCz1qoq2kt1Dy3fj0s3MgZ03v7aPb1ZDdO7PqaruN3iX2SYjyLdbLYdZO1KXvjA56jlaff4381rT3h7+Q1Jfg2vKsnHpfJGvlC7xp5WvsxktMqwu6fVnPwx21IKywbN6YXrx+f45Ne7gDp5W4hvdwB0sttSK8X25BezevO55xQenlk6yCn12hOL83/UqRXkze9aI2dJJa1bLGbQRTf96J0aSV2p0h893N8C1uIb7GJfJQD4T/FV5/3tzv84zIvC7KZa4iLPvOt8x7uLOMDO9/4vNKG+HD+mcdH1jFZr1cyX+fS9vUpbV1fY76exXq9lfk6Kev1VubriazXVZmvz2q/9VZ/o3VS91/3QdrNURFf7fvwqw+6PfnEsbavk2qvdVvm66Ss11WZr3uyWp/V9vVQNA6ssO5nnduAHyowhgU/Gq88fO5W8jUx3+jAfCiDgfkwltjiGEdxRnCcI+A4x5c/jbGOyOPB8Y4TGe9Iusqp5MOUw6y7KjgeEXyCT/D533lOVv8fvYp26f//O1mRO6APWvT/m8707/8H6PuD37IvC7uAfVnYW/ZlYffD9v09fVmHRd8/cqR53z9Avx9uLNMKdgHTCvaWaQW7H7bf75GpvRb9/uKRJv1+a5kCv2UfGXbfX5/fk+ebLPr8TSMt+vwB8rzJOi6wC/b3f+r9/V7nae/v+WDMtKfqY5ZUXz9/a+3Cd6qD/X1Dfx/6vnX9+MiRreMrHtm6/n7TyGB/P9jfD/b3T0Z//zD6+I6rnUoSTP7Vwf5+8Ak+wed/9zlJ/f/aigur26X/f0zX/8f+FXoO8J3Bj8DMQsPHPUL6OFMR7jkV1SVYgivnP8IOxz96+zfMnyT3lF5D9N1yL6iq4PNxHJacjyZusuUslG1EX8t3PrAb3TnnLnEzQO6C2UL0rT5nsJUt8d6vuZHsf+OdGyc6VX8maxGCMDn/hD5Wzqy6mdzdhHSWs23lbJQIarN2YBqn/3jGLDjuCEPOE2oif6qVU9DX06xOifKeb5mC39rhFCWtOINJu58E4XjvJ+H+4LV0bkVz3sT6nB8u6W+4413SmPyol3PmKB2N9zBRWunPkdxl9z8jcDYcNJzpIz9jqivqLGUHvHI24A1pmj2drityAnvfswGjWn+OnqSH7kwkhIF3FIbPuEWTwz8uF8CTbb5xme4uxZGH1mUB/BwfkX04KOH4GOwXKeS+ZlF1HdmXi32kxLfPCca3Of+1b+DxHslPCjc4TvAjGieYROMEF55TNf9898P3bp+uvHLssV2zguME+nECt8J6nOutBsO+n958HkUi0AXsB5wOTALWApOBi4BpwHXA/sAbgJnArcABwFuA2cBHgIOBvD+EdRF0BIfL+0NknKATsCswEhgDhAGtO0ckgPs4dh/P7rsDY5guCI4/nPj4w09g7CE47tD2cYdG/N6JcYYDMJ8ExxuCT/AJPu34nKT+v9Yha5f+/xHd+v913P9/CKYfzHUwU7Q17YN857XzC9wlC0uqagOsAWA3WdI330r0KuoHb+unm/MU3kzp+99A9EWm897jVXwX2V9CtEvcpxvnwamPvYHsFnj7/ESnyL0EHQeD5ntqMmKkry/uVbLv4McfxnO7mPmX817vG+Tbn58P+wXcn6+E+RhpXeW5k7AV8/Bmaxa29WvbPLwnb8u5P/sA5+1GmFvRnyoe7JO3ukP8LfMWbnzz9kqiV1Ka9Ir3yVvw+ubtOqIXWebtpWS/TPIW7i3zdjXZVUjegtcnb7/U5e3BKP+8PWrIW/A=
*/