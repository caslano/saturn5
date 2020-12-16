/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_cas_based.hpp
 *
 * This header contains CAS-based implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base >
struct cas_based_exchange :
    public Base
{
    typedef typename Base::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, v, order, memory_order_relaxed)) {}
        return old_val;
    }
};

template< typename Base >
struct cas_based_operations :
    public Base
{
    typedef typename Base::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = true;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val + v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val - v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val & v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val | v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!Base::compare_exchange_weak(storage, old_val, old_val ^ v, order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Base::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        Base::store(storage, (storage_type)0, order);
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_CAS_BASED_HPP_INCLUDED_

/* ops_cas_based.hpp
B6LihG+AfAIKTX9tt7ZOeOSzYPpBPxEzbTV+wnZkusIvdrAwwMz/U5l2lmu9plkH8Q951gzz7nUPZTSbI2sfgtL2bmnWNZySxdpXVJFZi15/POZDwkL8SFg8a9GNf6PTke4/caymo3zUwXy4yhtn7vwVNx2pudbynDWCEk5Wxph9Fk6Q513p8QyaNV8LCV+xhrFHA8Jo0orn/e/V/Qb6a1h6oT7GQE0kLEPC273U7eRhmf1HbN1/RMOhZnq5+pnFhL7r8PO28j7lvfDcmUHKD7PPz+WrosuIXkeQH/ATYcRPkfyg71H8wbvVPKL3HLcb+y7/M32XWac69/ddUlv40Y8nvvlW7ou/f7FNtzGNfZdfpe8y39J6OAxq32UAdkVxyTwzh4tgIlwMw+YK1NwQH3MnINccjtP5XpNc5raruaN9zPVQcz3hUbCfy9zBeswNV3Mj1NxoaMK3Mr65AWpuoJob4jK3Rc0N8jHXSs1lwP6wrZobjzrgMZcEh6u5aci1hCfDdnA67AZnwF7wFLUPvc6z07IeHuszz26m+mMOzIZzYXtYBDvD02EeLIT5en+Q6j/Ud1ej9vdX+xNhH7W/o9rfCabBHPVnLqxs7OP9n+nj/bb7dxvnVx15H2/7DUFrLKoctRX1OOogKmNj0BqCmr+xsf+38Wq8Gq/Gq/FqvBqvxqvxarwar8brv/36Fsf/V1R8Dfv/Z1spaQuysGRIkL5uHZ5YUbKssKrKytNnW9zPphw/pnDs8TOOVyHpO0JuDx1kOcci54xfMDl4UVF1eZU+z+V53zz653hu7GH6wHQGDxZULSgPywzFrYNeGeMOMurO/KHIyH6a/m790hmjEBnPdAV1LlfDtX1YrIwJu7qVPzxWZrqcDS8OGrkat9zxp8wY78hGBGWexdg8y4ytXKVzGZI13TRB7cae1OUytuJj0eHXWmTilyexY7v4RcYpMRe9d0dKwN/dg8vEXc/LObybTvp5qy12yHsrq2BCfgXOYjZ6j+bt6m4HlPanWnfnk2aWe92VbWdkzO+GfBkX1DGksGwHM/5zZtrhx7jC5yljlzNmF+WnjET/uDgQGxdEY71xMdEd//lD/eJf52skxsbDj/FbQWw8sN2PZcJa0YCwetfaeN151skX6o4nM5s43+GJ85qvEOc7NM7d/toc9I/zPcv8/HVk8X5wSEy8G3c/84mPX+G/Wt/4+GpxX5kUJ10t986halDaisrbBbF52+zt9G4cdy11N6YwbIC74fxdOcw3f5swb2wSG7+39+Sd+LotyY341TFvk96Q/wrpDbti0ts/m/jHyd5lfv4iRo8gvVnD46e30uTY+Kh1yrsVPu5Kcjvy9DYgnLZ93NrrlClut1xxvis6jyP35eN8lyuPDzDnFPjHeY3bP0cY1/Nj87Zx75mmseHfh7+2uN37inH8eLNYN57HjT11bhQPKNON8ay6OP6NJ45FDtMy/wEbbfKSZfYUi36eLvMjoucC7fG8o6Wph/d/+B39Rt+R2QcrzdHjfmR+BHTuxZ75sycUG+7fYd9Bb7jlm1UX9hc8YT94mLAfPEzYD36FsL/wJcI+NBz2lNiwv+jk4SoTds93oy78+z3hR76+8PO83vDz/MuHf/9XCX/z2PC/4pQrnvCbckzT/kve8uUw4S84TPgLvkL4X/oS4Q/n+Y0tYsP/R+yrqQt/2YBik+d9y9UaV7jWSriXVle595z1hOuSIwjXLk+4sB899nvy7+SWsWF4FbO1njBo/vWtd9ceJhy1XyEcN9QfDpMWs1Jjw/E6Zg+YcPjnRW999sBhwnLgK4RlRwPD8oZPWN7EbGq1CYsnX/nWlZCvNyw8//Jhwa16w3I=
*/