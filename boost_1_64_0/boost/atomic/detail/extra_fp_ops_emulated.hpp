/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_extra_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }
};

template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, false > :
    public emulated_extra_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

/* extra_fp_ops_emulated.hpp
fKnTvR8is0TMq9+Y3fHauXc0uajpM4HUj297CJkQspesKn3NP1ZN/flpF/WYeX3igMb7/faY+Z314Xemh98ZIEd/xoj3Xji/s2KO/syZj+VcDfnJd98dxLPQwq65lu8BIkfYLgtjHdenOeyc7rieZa6lDyrXM62a/ms54ZA2yXH9Iao8vB5P1ysynhH5PEWQn8iu6Qj3wf7wDZgL98NT4Zvwe/AAXADfgZfCd+GV8D14K3wfboeH4B/gR3A/PAyDPOsfsDE8AlPg57A7/AKOgV/CKfAreCq0bFnyMAAvhkF4BQzBa2AMvB7Gwc2wEfwNjIfPw6bwVZgA34TNIW6sFjALJsLOsCUcBFNgHmwPp6l5sZqXwFR4AWwNr4ZZcDPsBO+FneEDMCxzaJul66zgYJWx38qSM0zk94DKWvk1HAofgafBR+EcuA0uhE/A5fC38Cr4NPw5fAHeCHfD2+GLcDN8GT4Jfw93wR3wVfgUfF/Nv4B/0vfynL6Pv8A28Gk4AP4BEg/GVrreB+7RswaawarwwAQr3eFoOAyOgd+DY2EhnADL4CS4Ck6Ba2E+rIZT4T1wBnwQzoSPwdnwcXi6kfmj61h0LQ7hiJL5s0Rl2Fyg+XkFPAmuhMNhNZwIf6jpvBqeBy+Cy/X+xfDHcB28DF6j+p+r/mZ4OdwBfwKfVncvwZ/Ct+GVMJYw/QwmwathZ3gN7APXw37wF3AQ3ABHwxvgGXAjPAfeDMvgHfAC9ecy+CvIPXnu3fCX8Fl4K3we3haWnWO+71M3anqlcH1nRKbvym6wHTwetofTYQacCTvChbAzvABmwxthN30/w+Dv4YnwWXgSfB32ggdgb/gx7ANbBGr07WF/2AkOgAPhQHgiHAxnwCH6vneHv+Pq9/D5KrfoGQ1/uea7SpgHq+BcuASeDZfBlfA8uBEuh7fBFXAL5J7UV6s1/BfBffAS+C5cAz+BP4atefalsB28Fo4L8v7gLHg9PAPeAMvgjXAVvA2uhZvgOngLvAbervHLDek3Kv1GacevSOVZ2b9nsdcW7tL39FfYDz4PB8EX4FD4IhwOX4IF8GUtdxUqo+lV9EvhXrge7oM/1/s3w/3ofwPfhHvgW/BVvX8QvoP+c/gBTLW/hcLB8CN4ArTtjYSfoJ8JP4Xl8Cv4I/g1vE7tbYYx8F4YCx+BjeCTMB7ug43hu7ApTJa2lfwCk2B/2AoOgalwPGwNZ8A0OAu2gWfDdFgG28JzYTxcA3vBu+BxcDvMgbthX/ga7Affg/3h32EzmBSi/YBtYTs4BGbA02AmLILJsBS2hIvgQLgE5sIr4QnwJjgUPgiHwR0wD74Mh8NX4MlwHxwFAzHUqzAZjodd4ATYH06CuXAyHK33Z+r9hXAqLIPT4AVwOtwAZ8C74Uz4ADwdPgLnwJ3we/AleAbcq/rXVf82LIBfwrkwEFvjrgU8C7aGhXAQPBOeqOYTYQmcAc+BC+ACeB4shSvgQngxLINXwHJ4Dfw+/CX8zC6v8HMo+/HD8+SgWNsl5378uSozrhAOgGdqeSmCE1SfL/qIfyvr8O9s9W+++lei/i1Q/9DjH3r1b72l86dgp/qXCC9T/7boGUcPwC7wQdhN9T1VPxBuhSPgQ3As/DU8BT4KS9XeefD3Wq6fghvg01rP/QY+DLdrvf07c4aczuXpGLI8GH2GXI7DXk4D7eU77FGWo+wtddgrb6C9tQ57O1z2ZjrPwqvDXqHD3s4G2jvUQHuJOQ2zl1OPvYOUJ84Eqve8oYllqKHBKJkRh8oiciNihqF4Qd1QThkS69FXo8JnC+0qxx/ul7rOGDpSXvucoYQToa2+j6wGVBFqAOZ5mK3j+peoOVw=
*/