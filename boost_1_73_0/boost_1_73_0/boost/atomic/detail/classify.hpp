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
LRKtm0lykTUTsrX9N20maSPCNlNG5thT6BosCSWaXReZ+EIbu1EfqQqNaAKEqQlKi70IH1LCRObNBNGsKiRLLUjoLzJNW3wPVYvjK3lNUESyRS6iltESU97iIBrXrIv6Sg+jogE8qlEqjJuHFFyIdbOZPBXrsmbbMlJg3AKhRGwpTpHnbQVj17S3HYbN1C9Ra1ri4h/pbMHE/jLVC5H2G7QXZd+lXdUCtnYZnRtt8bi4OZ7Fgv3tFdd3SQpX9n83YqxvS57mOrOtpWSo1Tajd92SxsIKp6O2JIeLFh9UGVh2D0mbCptEuqX8pIq1ycqKWSFeP1QschEmLZVRqM3692Pq1NRrpUJ4P/gYXAwuB+fno3N4cQR0Jqgio8GEzz0rsyJ1QqEu6Bg1QtmYzlTu9LX45Op9cHV5PiPWL6jjLvdbr795qVqwt23MvBw4WBnpMAgXG3oknPBrmto+0Ylzo2VELdyiyb0ON3ByzolrhJCP2825zOJARyad/XKptKlHITqN8VbQ2YnsL0CXtXnMfbx9K1Xzq0FHkwCow/S4833rb2lfRFFQh94dUqzv4TDM+Dh0ICu3eBUOMaFjhs+iAIVdB1JJ1/VY+W7NoqPZp4s02bDM9GIefLgcz0dvrybD+Xg68bfYPC5IN5pV
*/