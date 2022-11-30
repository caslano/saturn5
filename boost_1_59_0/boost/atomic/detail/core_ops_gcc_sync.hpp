/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_ops_gcc_sync.hpp
 *
 * This header contains implementation of the \c core_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_SYNC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_SYNC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_operations_fwd.hpp>
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>
#include <boost/atomic/detail/capabilities.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct core_operations_gcc_sync_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before_store(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __sync_synchronize();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_acquire) | static_cast< unsigned int >(memory_order_consume))) != 0u)
            __sync_synchronize();
    }
};

template< std::size_t Size, bool Signed, bool Interprocess >
struct core_operations_gcc_sync :
    public core_operations_gcc_sync_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< storage_size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    // In general, we cannot guarantee atomicity of plain loads and stores of anything larger than a single byte on
    // an arbitrary CPU architecture. However, all modern architectures seem to guarantee atomic loads and stores of
    // suitably aligned objects of up to a pointer size. For larger objects we should probably use intrinsics to guarantee
    // atomicity. If there appears an architecture where this doesn't hold, this threshold needs to be updated (patches are welcome).
    typedef atomics::detail::integral_constant< bool, storage_size <= sizeof(void*) > plain_stores_loads_are_atomic;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, v, order, plain_stores_loads_are_atomic());
    }

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order, atomics::detail::true_type) BOOST_NOEXCEPT
    {
        fence_before_store(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order, atomics::detail::false_type) BOOST_NOEXCEPT
    {
        exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return load(storage, order, plain_stores_loads_are_atomic());
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order, atomics::detail::true_type) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order, atomics::detail::false_type) BOOST_NOEXCEPT
    {
        // Note: don't use fetch_add or other arithmetics here since storage_type may not be an arithmetic type.
        storage_type expected = storage_type();
        storage_type desired = expected;
        // We don't care if CAS succeeds or not. If it does, it will just write the same value there was before.
        return __sync_val_compare_and_swap(const_cast< storage_type volatile* >(&storage), expected, desired);
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_add(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_sub(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        // GCC docs mention that not all architectures may support full exchange semantics for this intrinsic. However, GCC's implementation of
        // std::atomic<> uses this intrinsic unconditionally. We do so as well. In case if some architectures actually don't support this, we can always
        // add a check here and fall back to a CAS loop.
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
        return __sync_lock_test_and_set(&storage, v);
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type expected2 = expected;
        storage_type old_val = __sync_val_compare_and_swap(&storage, expected2, desired);

        if (old_val == expected2)
        {
            return true;
        }
        else
        {
            expected = old_val;
            return false;
        }
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_and(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_or(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_xor(&storage, v);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
        return !!__sync_lock_test_and_set(&storage, 1);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        __sync_lock_release(&storage);
        if (order == memory_order_seq_cst)
            __sync_synchronize();
    }
};

#if BOOST_ATOMIC_INT8_LOCK_FREE > 0
template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)
    public core_operations_gcc_sync< 1u, Signed, Interprocess >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 2u, Signed, Interprocess >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 4u, Signed, Interprocess >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 8u, Signed, Interprocess >, 1u, Signed >
#else
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 16u, Signed, Interprocess >, 1u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT16_LOCK_FREE > 0
template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public core_operations_gcc_sync< 2u, Signed, Interprocess >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 4u, Signed, Interprocess >, 2u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 8u, Signed, Interprocess >, 2u, Signed >
#else
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 16u, Signed, Interprocess >, 2u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT32_LOCK_FREE > 0
template< bool Signed, bool Interprocess >
struct core_operations< 4u, Signed, Interprocess > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public core_operations_gcc_sync< 4u, Signed, Interprocess >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 8u, Signed, Interprocess >, 4u, Signed >
#else
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 16u, Signed, Interprocess >, 4u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT64_LOCK_FREE > 0
template< bool Signed, bool Interprocess >
struct core_operations< 8u, Signed, Interprocess > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public core_operations_gcc_sync< 8u, Signed, Interprocess >
#else
    public extending_cas_based_arithmetic< core_operations_gcc_sync< 16u, Signed, Interprocess >, 8u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT128_LOCK_FREE > 0
template< bool Signed, bool Interprocess >
struct core_operations< 16u, Signed, Interprocess > :
    public core_operations_gcc_sync< 16u, Signed, Interprocess >
{
};
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPS_GCC_SYNC_HPP_INCLUDED_

/* core_ops_gcc_sync.hpp
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
*/