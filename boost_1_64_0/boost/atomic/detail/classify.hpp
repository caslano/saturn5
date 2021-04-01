/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/classify.hpp
 *
 * This header contains type traits for type classification.
 */

#ifndef BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/type_traits/is_integral.hpp>
#include <boost/atomic/detail/type_traits/is_function.hpp>
#include <boost/atomic/detail/type_traits/is_floating_point.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool IsFunction = atomics::detail::is_function< T >::value >
struct classify_pointer
{
    typedef void* type;
};

template< typename T >
struct classify_pointer< T, true >
{
    typedef void type;
};

template< typename T, bool IsInt = atomics::detail::is_integral< T >::value, bool IsFloat = atomics::detail::is_floating_point< T >::value >
struct classify
{
    typedef void type;
};

template< typename T >
struct classify< T, true, false > { typedef int type; };

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
template< typename T >
struct classify< T, false, true > { typedef float type; };
#endif

template< typename T >
struct classify< T*, false, false > { typedef typename classify_pointer< T >::type type; };

template< >
struct classify< void*, false, false > { typedef void type; };

template< >
struct classify< const void*, false, false > { typedef void type; };

template< >
struct classify< volatile void*, false, false > { typedef void type; };

template< >
struct classify< const volatile void*, false, false > { typedef void type; };

template< typename T, typename U >
struct classify< T U::*, false, false > { typedef void type; };

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_CLASSIFY_HPP_INCLUDED_

/* classify.hpp
kyyIs3/HU6rU1motYw8c0Fu1dOrk39Ol1/QwmGOZO1DUBUOU6iOrOBNsenMbKOrsV3rjz/xAWuRQeo32MdW847h8+N/fgU1/wtIYnRY6x/622MQTkK9C4WsGk52oCjDh3KiMl7vwaOjjqJ4PXRRKhffoEhIS332q4KMjvn5o5F6Jo2fuPWW7QjDi93Ixnl9zhrZznaiT3gT9h7acVVCmmEh69AZKmwH3ycmym3HXfO4sbi+ekIYPBuxKPKJZG9B2w1Z2/kpefwTQgMQsTzhFODMsQNAuc8dgoisfNSJ4a0u9GRH50dHRw11cBVPiFvPfBsDMK5+AxD3EEdPc9uqiZRpkGN+eNkQJ9qtDNC+ZxmzalMaarGwpchkPpzaijqiY6sTwfI1U4RHwPMJog2XjxTmcjh1q93B1efbv/towQDyMcce0sXmJoACPMUJSRKCrjB9MkZFzdAxE53GzjW6WV4izGgWBvtQnQyZCNOr3ZTQ2d71Z4hSmhfIs1PKppmj/MiCsIOyxeLoXmuEd413kqKyYfxkxNEpuMJ2NrJxqlv0iQkdfzLtqVxWBYw==
*/