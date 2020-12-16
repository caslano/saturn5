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
 * \file   atomic/detail/ops_gcc_sync.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct gcc_sync_operations_base
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

template< std::size_t Size, bool Signed >
struct gcc_sync_operations :
    public gcc_sync_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before_store(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after_load(order);
        return v;
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
template< bool Signed >
struct operations< 1u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)
    public gcc_sync_operations< 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public extending_cas_based_operations< gcc_sync_operations< 2u, Signed >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_operations< gcc_sync_operations< 4u, Signed >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 1u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 1u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT16_LOCK_FREE > 0
template< bool Signed >
struct operations< 2u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public gcc_sync_operations< 2u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_operations< gcc_sync_operations< 4u, Signed >, 2u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 2u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 2u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT32_LOCK_FREE > 0
template< bool Signed >
struct operations< 4u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public gcc_sync_operations< 4u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 4u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 4u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT64_LOCK_FREE > 0
template< bool Signed >
struct operations< 8u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public gcc_sync_operations< 8u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 8u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT128_LOCK_FREE > 0
template< bool Signed >
struct operations< 16u, Signed > :
    public gcc_sync_operations< 16u, Signed >
{
};
#endif

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __sync_synchronize();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_

/* ops_gcc_sync.hpp
W+btVrKrtMzbs/qceN72im9b3nr2I9yAdzR+B9MF5u8w0/ARuUP816NI2bVen8DuTteXVTm3v4bsypAjKuexhz/LfJ2K2GearVNhu0Rj+ZP7//YMkXusJd8O0LvzyY2b4l5dpb+bSu714LEWvKe0M95JXcC80Z67rRU5j1jyeTfK7ACMGQyE0fK6RHeHXHEL+ew2WZNRbyjDDSb5vMabzyILbqIRT/a70DCWQzJkuDMd8QDK+d4+MnN3B/zh83KigHTPkKbrh/rLjEuTmLK6soW1ljLD7s420wFslyH3SWwmuj/u+7Uby6bIWRPxhKq4C8iYz6DzKI0eIZ4uqll+51rnN4/Z1iJRvOdTf0N+NRnlQc6Y3kP23yoZkIuOLBf7YG4F85ZEnA8EhNHJSOvORDaVEYMuWGOS/7mtyP8G3/ynO4DyhjWPOWTH+8pDh04KPQu1s2GA04HPpyGMU03kQeoIS3lgd9PN5IHtxoluXUB0ks3q/sC5ZH+ferqaxTrF48corldwV1OORi830zHMO1Tqq2lED7cZ786PZdn7C9nfpfZW7sX5XufSXfme9R/jyW6z0oPegRmP/TS8wwkd9+JtF9XpJ6+xXLfdQ27L1GSs/VqhbPmv9ZVRfulMdvqGrjLvEEfpkWCu39ifi7uS3zkV1fOk/n2FvnEQ05yuaGCa3RFYzP6Uxjf7o6/HB9L3bDH6YxIut/mIP8uYn7r4LqAIxHJ8JxJ/AdUL/ZVOxHcL+aupqnK5Q+Aj4ktk2psuM1COY7gcb0UCbePyexPM+BjvfWLn4vd7yYR6Hir7d+FDbtaV+b48Nl/fwv1ixQ7vvfKn5ejmbUBHM+3OwRsu69sc/jridoevjthhcqfYTsf3U4/w/JL+PjLSLeMprek7fNqe+7so9ByB6Q3zBkyhdvfG6Ya1k17FYtX2ZDcDqGwc1K+dFLsE0SsuoncwjdpkON/HAbf7oviOMUURGSwk/keIdol/abq5mwW1dQu9Mj6V7J9hPePh7ycyq7LM6u4gA4/hDjKjzmPebAMv6gTTe81yDHwN/vOWci/lH4jvNORNtsxlKpQmoUxLGhnbwKQXi8n93Yp2r0wE6osY5OunKAf2mSEh9khc1Zg9OMI2BOGjbNng8jPYvQWjv1tmUFRzealqxbwmy6yhray/96xeZHEf0chPcqef66Q8M9w/w/nCda2x3DRYtLMd2l8+qzwZZi3fF1Y83CDHhkaTRR3J7rJEXq8keqmfbNM5imR3Ecu6x20mzY8/SXqPlgUgqtIOlnzYFOldR7xDCaybtgGhmyhtmkzaJru9aS93ECJ80BK+T5odj1boyeJ51BSYWVrf5AyzNJPyb5Vm7C7LtPyznWn5dhnsjeV5st7euvyCp/XlN/eM1pVf5uPy61d+KN+gk/mxvlec8+oHKydjPWvluyn07IRJ02jO84bAeV5Ut7CktKKuogbLS6zyn/2YJDr4JaLnmckD844X/b6X6Pnm8iH8w6Wd+CjRS8zlRfiHyDqXB4leHlB+GnR5Han6yY/ogh3Et8orTwa38XhnNibyNHiM8qV3h/Pi2qwzdrZBZ3xiIofHDXKoqP5y2EH1l0Okj1EOEW8/OUScRA4D6qQvgIod50MmavPJN9+/+alX9vz8+MXRO2P6d/hyAtoLTu39W78sveK2uM9/e7jbnHd3r3oy4/9vHUSkk+bbXVtGH76zcmhj5v4XP/7m8tQf3/qIlbQ+4rH7DpR9mvPeo4/95YqUBxOT0q3XR2RM1d4XrV98S+n+6ieG9n5x9c4Dr572/7du4p+8ngkPtd92I54l+E3nVCs8Rs7zAJpdR+A05ke20jm+h4H5wL8BS4F/B5Y=
*/