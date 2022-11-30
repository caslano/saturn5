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
 * \file   atomic/detail/core_arch_ops_gcc_sparc.hpp
 *
 * This header contains implementation of the \c core_arch_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_SPARC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_ARCH_OPS_GCC_SPARC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_arch_operations_fwd.hpp>
#include <boost/atomic/detail/core_ops_cas_based.hpp>
#include <boost/atomic/detail/cas_based_exchange.hpp>
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#include <boost/atomic/detail/header.hpp>

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

template< bool Signed, bool Interprocess >
struct gcc_sparc_cas32 :
    public gcc_sparc_cas_base
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 4u, Signed, Interprocess > :
    public core_operations_cas_based< gcc_sparc_cas32< Signed, Interprocess > >
{
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_arch_operations< 4u, Signed, Interprocess >, 1u, Signed >
{
};

template< bool Signed, bool Interprocess >
struct core_arch_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_arch_operations< 4u, Signed, Interprocess >, 2u, Signed >
{
};

template< bool Signed, bool Interprocess >
struct gcc_sparc_cas64 :
    public gcc_sparc_cas_base
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

template< bool Signed, bool Interprocess >
struct core_arch_operations< 8u, Signed, Interprocess > :
    public core_operations_cas_based< cas_based_exchange< gcc_sparc_cas64< Signed, Interprocess > > >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_ARCH_OPS_GCC_SPARC_HPP_INCLUDED_

/* core_arch_ops_gcc_sparc.hpp
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
*/