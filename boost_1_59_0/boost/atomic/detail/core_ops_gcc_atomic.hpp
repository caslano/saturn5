/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_ops_gcc_atomic.hpp
 *
 * This header contains implementation of the \c core_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_ATOMIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_ATOMIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_operations_fwd.hpp>
#include <boost/atomic/detail/core_arch_operations.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/gcc_atomic_memory_order_utils.hpp>

#if BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT8_LOCK_FREE < BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT16_LOCK_FREE || BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT16_LOCK_FREE < BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT32_LOCK_FREE ||\
    BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT32_LOCK_FREE < BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE || BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE < BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE
// There are platforms where we need to use larger storage types
#include <boost/atomic/detail/int_sizes.hpp>
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#endif
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__INTEL_COMPILER)
// This is used to suppress warning #32013 described in gcc_atomic_memory_order_utils.hpp
// for Intel Compiler.
// In debug builds the compiler does not inline any functions, so basically
// every atomic function call results in this warning. I don't know any other
// way to selectively disable just this one warning.
#pragma system_header
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, bool Signed, bool Interprocess >
struct core_operations_gcc_atomic
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;

    // Note: In the current implementation, core_operations_gcc_atomic are used only when the particularly sized __atomic
    // intrinsics are always lock-free (i.e. the corresponding LOCK_FREE macro is 2). Therefore it is safe to
    // always set is_always_lock_free to true here.
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_GCC) && BOOST_GCC < 100100 && (defined(__x86_64__) || defined(__i386__))
        // gcc up to 10.1 generates mov + mfence for seq_cst stores, which is slower than xchg
        if (order != memory_order_seq_cst)
            __atomic_store_n(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
        else
            __atomic_exchange_n(&storage, v, __ATOMIC_SEQ_CST);
#else
        __atomic_store_n(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
#endif
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_AARCH64_HAS_RCPC)
        // At least gcc 9.3 and clang 10 do not generate relaxed ldapr instructions that are available in ARMv8.3-RCPC extension.
        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95751
        typedef atomics::detail::core_arch_operations< storage_size, is_signed, is_interprocess > core_arch_operations;
        return core_arch_operations::load(storage, order);
#else
        return __atomic_load_n(&storage, atomics::detail::convert_memory_order_to_gcc(order));
#endif
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_fetch_add(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_fetch_sub(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_exchange_n(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return __atomic_compare_exchange_n
        (
            &storage, &expected, desired, false,
            atomics::detail::convert_memory_order_to_gcc(success_order),
            atomics::detail::convert_memory_order_to_gcc(failure_order)
        );
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return __atomic_compare_exchange_n
        (
            &storage, &expected, desired, true,
            atomics::detail::convert_memory_order_to_gcc(success_order),
            atomics::detail::convert_memory_order_to_gcc(failure_order)
        );
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_fetch_and(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_fetch_or(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_fetch_xor(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_test_and_set(&storage, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        __atomic_clear(const_cast< storage_type* >(&storage), atomics::detail::convert_memory_order_to_gcc(order));
    }
};

// We want to only enable __atomic* intrinsics when the corresponding BOOST_ATOMIC_DETAIL_GCC_ATOMIC_*_LOCK_FREE macro indicates
// the same or better lock-free guarantees as the BOOST_ATOMIC_*_LOCK_FREE macro. Otherwise, we want to leave core_operations
// unspecialized, so that core_arch_operations is used instead.

#if BOOST_ATOMIC_INT128_LOCK_FREE > 0 && BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE >= BOOST_ATOMIC_INT128_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 16u, Signed, Interprocess > :
    public core_operations_gcc_atomic< 16u, Signed, Interprocess >
{
};

#endif

#if BOOST_ATOMIC_INT64_LOCK_FREE > 0
#if BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE >= BOOST_ATOMIC_INT64_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 8u, Signed, Interprocess > :
    public core_operations_gcc_atomic< 8u, Signed, Interprocess >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE >= BOOST_ATOMIC_INT64_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 8u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 16u, Signed, Interprocess >, 8u, Signed >
{
};

#endif
#endif // BOOST_ATOMIC_INT64_LOCK_FREE > 0


#if BOOST_ATOMIC_INT32_LOCK_FREE > 0
#if BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT32_LOCK_FREE >= BOOST_ATOMIC_INT32_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 4u, Signed, Interprocess > :
    public core_operations_gcc_atomic< 4u, Signed, Interprocess >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE >= BOOST_ATOMIC_INT32_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 4u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 8u, Signed, Interprocess >, 4u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE >= BOOST_ATOMIC_INT32_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 8u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 16u, Signed, Interprocess >, 4u, Signed >
{
};

#endif
#endif // BOOST_ATOMIC_INT32_LOCK_FREE > 0


#if BOOST_ATOMIC_INT16_LOCK_FREE > 0
#if BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT16_LOCK_FREE >= BOOST_ATOMIC_INT16_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public core_operations_gcc_atomic< 2u, Signed, Interprocess >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT32_LOCK_FREE >= BOOST_ATOMIC_INT16_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 4u, Signed, Interprocess >, 2u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE >= BOOST_ATOMIC_INT16_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 8u, Signed, Interprocess >, 2u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE >= BOOST_ATOMIC_INT16_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 16u, Signed, Interprocess >, 2u, Signed >
{
};

#endif
#endif // BOOST_ATOMIC_INT16_LOCK_FREE > 0


#if BOOST_ATOMIC_INT8_LOCK_FREE > 0
#if BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT8_LOCK_FREE >= BOOST_ATOMIC_INT8_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public core_operations_gcc_atomic< 1u, Signed, Interprocess >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT16_LOCK_FREE >= BOOST_ATOMIC_INT8_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 2u, Signed, Interprocess >, 1u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT32_LOCK_FREE >= BOOST_ATOMIC_INT8_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 4u, Signed, Interprocess >, 1u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT64_LOCK_FREE >= BOOST_ATOMIC_INT8_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 8u, Signed, Interprocess >, 1u, Signed >
{
};

#elif BOOST_ATOMIC_DETAIL_GCC_ATOMIC_INT128_LOCK_FREE >= BOOST_ATOMIC_INT8_LOCK_FREE

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations_gcc_atomic< 16u, Signed, Interprocess >, 1u, Signed >
{
};

#endif
#endif // BOOST_ATOMIC_INT8_LOCK_FREE > 0

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_ATOMIC_HPP_INCLUDED_

/* core_ops_gcc_atomic.hpp
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
*/