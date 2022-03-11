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
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
*/