/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_extending_cas_based.hpp
 *
 * This header contains a boilerplate of the \c operations template implementation that requires sign/zero extension in arithmetic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, std::size_t Size, bool Signed >
struct extending_cas_based_operations :
    public Base
{
    typedef typename Base::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        storage_type new_val;
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val + v));
        }
        while (!Base::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        storage_type new_val;
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val - v));
        }
        while (!Base::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return old_val;
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_EXTENDING_CAS_BASED_HPP_INCLUDED_

/* ops_extending_cas_based.hpp
AHPglbAz3AV7wodgL7gHdoO/gnlwH+xt9njQujMc47PHw1XItYJXw37wOjW31dK6KnhdzaXCza7xi0w4AHaBA+HxcBAcA0+AU+HRsAgeA5fCIfBseCw8Bw6H18AR8D44Bj4Gx8Kfqz0vwFFwv+o/hE+a+o/URc05bA+p/07T8MyFw+DpcBacB+dDlJyZVqT+WAjXw0XwclgGd8Iz1V9LdJ/hCvgEXAqfgsvgi3A5fAuugJ/CKpiPn1bBAngunAnPg3Ph2bAQ1pg9MPS7DRb57IGxDbl0eD3sCm+AY+F2OA7eAh3Z78O5qi9Svdqv31XiwMf+CWr/RJgDJ8FRcAocDQvgeDgNzlD9LNXrniD6HeK76rMnyEY9w+p8zQcXwKPgJZpuLoQbVL/6S+65wfhU474bX2Fc6r9lTOrLjEc17r/RsPGngu8ErSrUNtQe1Buo5Es52wg149LG8aPGq/FqvBqvxqvxarwar8ar4Vci6oxvcPy/ZMncypVnLlpS9TWN/QfzLLPeZZBWfZkCZuUqF+U7jWDpE17grPc5dVLhgrKldf3A302NXssz0Q7LDrbS9cy0e0U/LuFZ2xYzQ3PkfDuzT/MkY6aXmDkF/Q9Ef1LCb+2A1cyMo1cjP1rGLW+X5zMSwvs8/2y0o28j9hUY+44V9/anRc6pS9fz8H4kz6cm7LOD2C97uXNV1p2FF3X+24LqRWpuMuY6iTsv04/TV/qnW/d1ZHgdhaXFy/X8uFFmnE/NO13EakcmTBI7PrbGE0eLrClpu7hXTqJpwnsInJGUkBJsFhrhIBgaGuoWGhjKDfVIyk0JtktqGUgJ9QoNdm4mJQQykhID7ZKaBlKTWgSa8SwIgy4GYAL2EA4zPsz4gag83O3DjYwA/R+4i1XicjApmBJMTwqkBFsmJaUkJDvxUO055y8Ntj5eznOQMKWjzxb9ZYxcp+o92xot93rbjKLZCdbUtF7q5mZ1EweCNc85bnV2/jVx/jUTVy0rnrsXu9zNQn+Z6MvtZ6weei/sbl6Mu4mJJqw1T7kDa5yN7+5Sl7sZ6KtEf6H9J3U3w7jbOcbd0oi76zoZd5s1yN2HPfH8qOhPsTowi8Jxw1HhMfAqfbeFwoi+KW531vGiLcjVd9bgfD1r0BlTfGl09Hh4Lc/I71Fr53ZD8jP3ND9zb4+Za1Et+iHmjIJKMzZJvkGv+cazXi1F17C31flHqaglzpyKMZEyaHnZyqKqkknO1CPfNYUTbZXX/cTNmsLFVaVhmVZQZczcolD9e6ZPNHMnPOsIdV94XUeo7njGC3dquLI0XC1RlVi0xy9cUsTGLWPVTJbxd/Mj2OvdvENPvG9s4pn3pfF+wOW/6gXlZQsl2uPGu8pn1xvvKtPQeB/9VeK9a7InPWm8W2O94dJojx/vaqbt1xLv/XTPhpm6xrhSzsRFD5diICfiv+IVK3ziW799L5yAHPapH9XcBPkW1ei3qBoyd6JMh+z1PRhZ91yMFZXVC+R5qccuyg7v99ScL1slcukJzvOfymGIelavzkM5RZ4PTIiUcxUL1lSVWNn6TTxZnv/QvptU94L1S+tmOyhutW0lHeoLKvQMgCFwtsgenRB5vlie5+oYcqLExyVUwE7iS51svc9IzyeogJ1spWPHVmRfFDvus3O45/r+m3kbE11u9MiQk4dWFLnO4i2X57kJ6cYPlWTdQpkLman+6C7+eJszFc+yfsaXMVfrQ9vk/kHGdkL4MGCdSuzOQ51pNTf1mwVifz9XGCsljJlaPzpdnv/EHmePsG514kru2/TDOvdXWhF/8TbFW5G5esVitmdCNt+nHuSNvc3I66TjQM2t1CpaJyWmBJqG03dqG0s=
*/