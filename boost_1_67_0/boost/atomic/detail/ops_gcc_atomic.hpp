/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_atomic.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_ATOMIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_ATOMIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>
#if (defined(__clang__) || (defined(BOOST_GCC) && (BOOST_GCC+0) >= 70000)) && (defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B))
#include <boost/atomic/detail/ops_gcc_x86_dcas.hpp>
#include <boost/atomic/detail/ops_cas_based.hpp>
#endif

#if __GCC_ATOMIC_LLONG_LOCK_FREE != BOOST_ATOMIC_LLONG_LOCK_FREE || __GCC_ATOMIC_LONG_LOCK_FREE != BOOST_ATOMIC_LONG_LOCK_FREE ||\
    __GCC_ATOMIC_INT_LOCK_FREE != BOOST_ATOMIC_INT_LOCK_FREE || __GCC_ATOMIC_SHORT_LOCK_FREE != BOOST_ATOMIC_SHORT_LOCK_FREE ||\
    __GCC_ATOMIC_CHAR_LOCK_FREE != BOOST_ATOMIC_CHAR_LOCK_FREE || __GCC_ATOMIC_BOOL_LOCK_FREE != BOOST_ATOMIC_BOOL_LOCK_FREE ||\
    __GCC_ATOMIC_WCHAR_T_LOCK_FREE != BOOST_ATOMIC_WCHAR_T_LOCK_FREE
// There are platforms where we need to use larger storage types
#include <boost/atomic/detail/int_sizes.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__INTEL_COMPILER)
// This is used to suppress warning #32013 described below for Intel Compiler.
// In debug builds the compiler does not inline any functions, so basically
// every atomic function call results in this warning. I don't know any other
// way to selectively disable just this one warning.
#pragma system_header
#endif

namespace boost {
namespace atomics {
namespace detail {

/*!
 * The function converts \c boost::memory_order values to the compiler-specific constants.
 *
 * NOTE: The intention is that the function is optimized away by the compiler, and the
 *       compiler-specific constants are passed to the intrinsics. Unfortunately, constexpr doesn't
 *       work in this case because the standard atomics interface require memory ordering
 *       constants to be passed as function arguments, at which point they stop being constexpr.
 *       However, it is crucial that the compiler sees constants and not runtime values,
 *       because otherwise it just ignores the ordering value and always uses seq_cst.
 *       This is the case with Intel C++ Compiler 14.0.3 (Composer XE 2013 SP1, update 3) and
 *       gcc 4.8.2. Intel Compiler issues a warning in this case:
 *
 *       warning #32013: Invalid memory order specified. Defaulting to seq_cst memory order.
 *
 *       while gcc acts silently.
 *
 *       To mitigate the problem ALL functions, including the atomic<> members must be
 *       declared with BOOST_FORCEINLINE. In this case the compilers are able to see that
 *       all functions are called with constant orderings and call intrinstcts properly.
 *
 *       Unfortunately, this still doesn't work in debug mode as the compiler doesn't
 *       propagate constants even when functions are marked with BOOST_FORCEINLINE. In this case
 *       all atomic operaions will be executed with seq_cst semantics.
 */
BOOST_FORCEINLINE BOOST_CONSTEXPR int convert_memory_order_to_gcc(memory_order order) BOOST_NOEXCEPT
{
    return (order == memory_order_relaxed ? __ATOMIC_RELAXED : (order == memory_order_consume ? __ATOMIC_CONSUME :
        (order == memory_order_acquire ? __ATOMIC_ACQUIRE : (order == memory_order_release ? __ATOMIC_RELEASE :
        (order == memory_order_acq_rel ? __ATOMIC_ACQ_REL : __ATOMIC_SEQ_CST)))));
}

template< std::size_t Size, bool Signed >
struct gcc_atomic_operations
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;

    // Note: In the current implementation, gcc_atomic_operations are used only when the particularly sized __atomic
    // intrinsics are always lock-free (i.e. the corresponding LOCK_FREE macro is 2). Therefore it is safe to
    // always set is_always_lock_free to true here.
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        __atomic_store_n(&storage, v, atomics::detail::convert_memory_order_to_gcc(order));
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return __atomic_load_n(&storage, atomics::detail::convert_memory_order_to_gcc(order));
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

#if BOOST_ATOMIC_INT128_LOCK_FREE > 0
#if (defined(__clang__) || (defined(BOOST_GCC) && (BOOST_GCC+0) >= 70000)) && defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

// Workaround for clang bug: http://llvm.org/bugs/show_bug.cgi?id=19149
// Clang 3.4 does not implement 128-bit __atomic* intrinsics even though it defines __GCC_HAVE_SYNC_COMPARE_AND_SWAP_16
// A similar problem exists with gcc 7 as well, as it requires to link with libatomic to use 16-byte intrinsics:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80878
template< bool Signed >
struct operations< 16u, Signed > :
    public cas_based_operations< gcc_dcas_x86_64< Signed > >
{
};

#else

template< bool Signed >
struct operations< 16u, Signed > :
    public gcc_atomic_operations< 16u, Signed >
{
};

#endif
#endif


#if BOOST_ATOMIC_INT64_LOCK_FREE > 0
#if defined(__clang__) && defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

// Workaround for clang bug http://llvm.org/bugs/show_bug.cgi?id=19355
template< bool Signed >
struct operations< 8u, Signed > :
    public cas_based_operations< gcc_dcas_x86< Signed > >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = 8u;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
};

#elif (BOOST_ATOMIC_DETAIL_SIZEOF_LLONG == 8 && __GCC_ATOMIC_LLONG_LOCK_FREE != BOOST_ATOMIC_LLONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_LONG == 8 && __GCC_ATOMIC_LONG_LOCK_FREE != BOOST_ATOMIC_LONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_INT == 8 && __GCC_ATOMIC_INT_LOCK_FREE != BOOST_ATOMIC_INT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_SHORT == 8 && __GCC_ATOMIC_SHORT_LOCK_FREE != BOOST_ATOMIC_SHORT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 8 && __GCC_ATOMIC_WCHAR_T_LOCK_FREE != BOOST_ATOMIC_WCHAR_T_LOCK_FREE)

#define BOOST_ATOMIC_DETAIL_INT64_EXTENDED

template< bool Signed >
struct operations< 8u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 16u, Signed >, 8u, Signed >
{
};

#else

template< bool Signed >
struct operations< 8u, Signed > :
    public gcc_atomic_operations< 8u, Signed >
{
};

#endif
#endif

#if BOOST_ATOMIC_INT32_LOCK_FREE > 0
#if (BOOST_ATOMIC_DETAIL_SIZEOF_LLONG == 4 && __GCC_ATOMIC_LLONG_LOCK_FREE != BOOST_ATOMIC_LLONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_LONG == 4 && __GCC_ATOMIC_LONG_LOCK_FREE != BOOST_ATOMIC_LONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_INT == 4 && __GCC_ATOMIC_INT_LOCK_FREE != BOOST_ATOMIC_INT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_SHORT == 4 && __GCC_ATOMIC_SHORT_LOCK_FREE != BOOST_ATOMIC_SHORT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 4 && __GCC_ATOMIC_WCHAR_T_LOCK_FREE != BOOST_ATOMIC_WCHAR_T_LOCK_FREE)

#define BOOST_ATOMIC_DETAIL_INT32_EXTENDED

#if !defined(BOOST_ATOMIC_DETAIL_INT64_EXTENDED)

template< bool Signed >
struct operations< 4u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 8u, Signed >, 4u, Signed >
{
};

#else // !defined(BOOST_ATOMIC_DETAIL_INT64_EXTENDED)

template< bool Signed >
struct operations< 4u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 16u, Signed >, 4u, Signed >
{
};

#endif // !defined(BOOST_ATOMIC_DETAIL_INT64_EXTENDED)

#else

template< bool Signed >
struct operations< 4u, Signed > :
    public gcc_atomic_operations< 4u, Signed >
{
};

#endif
#endif

#if BOOST_ATOMIC_INT16_LOCK_FREE > 0
#if (BOOST_ATOMIC_DETAIL_SIZEOF_LLONG == 2 && __GCC_ATOMIC_LLONG_LOCK_FREE != BOOST_ATOMIC_LLONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_LONG == 2 && __GCC_ATOMIC_LONG_LOCK_FREE != BOOST_ATOMIC_LONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_INT == 2 && __GCC_ATOMIC_INT_LOCK_FREE != BOOST_ATOMIC_INT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_SHORT == 2 && __GCC_ATOMIC_SHORT_LOCK_FREE != BOOST_ATOMIC_SHORT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 2 && __GCC_ATOMIC_WCHAR_T_LOCK_FREE != BOOST_ATOMIC_WCHAR_T_LOCK_FREE)

#define BOOST_ATOMIC_DETAIL_INT16_EXTENDED

#if !defined(BOOST_ATOMIC_DETAIL_INT32_EXTENDED)

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 4u, Signed >, 2u, Signed >
{
};

#elif !defined(BOOST_ATOMIC_DETAIL_INT64_EXTENDED)

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 8u, Signed >, 2u, Signed >
{
};

#else

template< bool Signed >
struct operations< 2u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 16u, Signed >, 2u, Signed >
{
};

#endif

#else

template< bool Signed >
struct operations< 2u, Signed > :
    public gcc_atomic_operations< 2u, Signed >
{
};

#endif
#endif

#if BOOST_ATOMIC_INT8_LOCK_FREE > 0
#if (BOOST_ATOMIC_DETAIL_SIZEOF_LLONG == 1 && __GCC_ATOMIC_LLONG_LOCK_FREE != BOOST_ATOMIC_LLONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_LONG == 1 && __GCC_ATOMIC_LONG_LOCK_FREE != BOOST_ATOMIC_LONG_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_INT == 1 && __GCC_ATOMIC_INT_LOCK_FREE != BOOST_ATOMIC_INT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_SHORT == 1 && __GCC_ATOMIC_SHORT_LOCK_FREE != BOOST_ATOMIC_SHORT_LOCK_FREE) ||\
    (BOOST_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 1 && __GCC_ATOMIC_WCHAR_T_LOCK_FREE != BOOST_ATOMIC_WCHAR_T_LOCK_FREE) ||\
    (__GCC_ATOMIC_CHAR_LOCK_FREE != BOOST_ATOMIC_CHAR_LOCK_FREE) ||\
    (__GCC_ATOMIC_BOOL_LOCK_FREE != BOOST_ATOMIC_BOOL_LOCK_FREE)

#if !defined(BOOST_ATOMIC_DETAIL_INT16_EXTENDED)

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 2u, Signed >, 1u, Signed >
{
};

#elif !defined(BOOST_ATOMIC_DETAIL_INT32_EXTENDED)

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 4u, Signed >, 1u, Signed >
{
};

#elif !defined(BOOST_ATOMIC_DETAIL_INT64_EXTENDED)

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 8u, Signed >, 1u, Signed >
{
};

#else

template< bool Signed >
struct operations< 1u, Signed > :
    public extending_cas_based_operations< gcc_atomic_operations< 16u, Signed >, 1u, Signed >
{
};

#endif

#else

template< bool Signed >
struct operations< 1u, Signed > :
    public gcc_atomic_operations< 1u, Signed >
{
};

#endif
#endif

#undef BOOST_ATOMIC_DETAIL_INT16_EXTENDED
#undef BOOST_ATOMIC_DETAIL_INT32_EXTENDED
#undef BOOST_ATOMIC_DETAIL_INT64_EXTENDED

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    __atomic_thread_fence(atomics::detail::convert_memory_order_to_gcc(order));
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    __atomic_signal_fence(atomics::detail::convert_memory_order_to_gcc(order));
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_ATOMIC_HPP_INCLUDED_

/* ops_gcc_atomic.hpp
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
*/