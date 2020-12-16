/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/bitwise_fp_cast.hpp
 *
 * This header defines \c bitwise_fp_cast used to convert between storage and floating point value types
 */

#ifndef BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/float_sizes.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

/*!
 * \brief The type trait returns the size of the value of the specified floating point type
 *
 * This size may be less than <tt>sizeof(T)</tt> if the implementation uses padding bytes for a particular FP type. This is
 * often the case with 80-bit extended double, which is stored in 12 or 16 bytes with padding filled with garbage.
 */
template< typename T >
struct value_sizeof
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = sizeof(T);
};

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_FLOAT_VALUE)
template< >
struct value_sizeof< float >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_FLOAT_VALUE;
};
#endif

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_DOUBLE_VALUE)
template< >
struct value_sizeof< double >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_DOUBLE_VALUE;
};
#endif

#if defined(BOOST_ATOMIC_DETAIL_SIZEOF_LONG_DOUBLE_VALUE)
template< >
struct value_sizeof< long double >
{
    static BOOST_CONSTEXPR_OR_CONST std::size_t value = BOOST_ATOMIC_DETAIL_SIZEOF_LONG_DOUBLE_VALUE;
};
#endif

template< typename T >
struct value_sizeof< const T > : value_sizeof< T > {};

template< typename T >
struct value_sizeof< volatile T > : value_sizeof< T > {};

template< typename T >
struct value_sizeof< const volatile T > : value_sizeof< T > {};


template< typename To, typename From >
BOOST_FORCEINLINE To bitwise_fp_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast< To, atomics::detail::value_sizeof< From >::value >(from);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_BITWISE_FP_CAST_HPP_INCLUDED_

/* bitwise_fp_cast.hpp
Oc8s6ZZj56ek219s//CgtPdfwVMg4kh1fe0HK+A3mF8B/wbvgN/DLWL+OrRw9xF0wb9CD7TTJwomwljYHMbBLJgE28NkWApT4EkwHY6BzeE02AIuhi3htbAdvAlmwV0wB/4GdoXvwwKYwHMWwWGwNxwN+8CzYF84HfaDs2F7eBvMg7thB/guJC2lfsuaKJweon73kfLfD46AA2AZLJZxfn84XvQyfmT9UepHiPFjJ2kv8qW9KISDYTd4NiyClbAnnAW7w4thD3i5mB/QcZX1NbhC7hMPx8l9Wko70krakTbSjrSVepMFp8IcuV+e1Mf28BqYC68V8wP6+WSNCD4t94uCRXK/e6R+3gs7iP540e+A9znan+IjzD8slPbnQpgCL4JNRC/jB+bdxb/VcPyQK/2RPFgMO0s/owtcDbvCDfB4uAvmy/ulAD4Ee8C9sAi+CE+Ar4v5h6L/FBbCaIv8gQnQtt8VpbS8YE+7qKPKDB45CxUkI/izWU45wagapHihQskLfuVNl1qBeR3KJzs45x2PeqkmvAzhQzXh5AijqCx9UVNRPpnCN/J7PWocv3fBcPKF62f7ZQwnzwmUM1yEfiSqCrXUtkN9jPLJHx5LnL/A/Xy4EH1LBnQlTA6Xo5wyiUsw34Qbp2xiD5MEj8Ot2C3G7CV4COWUVZxci6xbVLDM4uJa3MKJMEh2MRUhUH5x/lt+GcZ1tX45xs8Tn0OohcTVJ9P4UC12MHke4aFs+cbFcCluvsXPxHl+Wcd18/zyjp/n92con9zjzHO5L8op/3gs+th3PUYO8o3nNpSF3Bn7QFnI+MXMlof8PO73o8bxPB/bbs6jTBIvn4zk/PMaykl+FvvpmCcW4Ab65CWv5nceZrthKLnJ+8/74bKTO8+nnKAuRznlKG9FX47+fVgLlxD/PZgfQv8xzFvgla3sudj9D8tXLl9wdBnLW7lvOuYLFxxd1vKeBX55y+8vwL/dMScfMs/HH6oz5mNhKBnM8zGvwrzuXc8xyWJeez7+cbsU/W5+tyQdWmIe+55H7T/fL6M5xyGnufQC/MEqGCyvuQ6zQ0U8A6xH/zFMXogZv/OhU4ZzKfpiWAPTS8kz6JPnvGshcS0lDOiU65x4YaBs5xL0ObSZxahxqPmo1ajdqLdRh1CZWVGqJ2osqhZ1I6oO9TzqM1RydpTKR5WhalBLUFtRz6I+RiXmYI8qQ1WhlqC2ovag9udEZEJHrsgVuSJX5IpckStyRa7IFbn+fddPLf+/sqZi5tRxc5DdMqu6wv4AwI8g/3+blv+frOOc7JL9MrJXfj5qWxb7MG7U+4xPGVY2+KSSgu75GJtzGsgHl/3FPnf5Zg9sWzkHYLslPH5Xa7sRxm03s881W7s9y5w7sByyO8qM+xN1WGs6eSWki1wCc8ZgAHEtRvVHxci+0aWhs2pQin6G3t6zQpalz2zUmTMbU7V+lzcd0Hu/abnbnDOQuMnZf+KD2RQt1+DjTObVWfhwq5myVxS99dPv5fyheyo/0nsq19x/ZtQt7/5pz0lqe7+pY8ofD7eXM9yexHB7PMPvSfSuA0t+SllbqgLXgckCve6RAQfDpnAYzIRnwGZwGmwO58EWcD5sCadDey62HLUHVSrfUPsC5ZHvpB1C5cm3zOw5ufWo3SjmuJjDwt1xUaoc9nV8gyuzKHDOpeVxkfmHyBW5IlfkilyRK3JFrsgVuf6fr3/d+H/q2XNr7QmAf378vzmX/TAy/u8p4397b3drWI9ax3izbG7g+H/CkMrqSVUq5FideQBx38nMA1yg9Sdb8bhfS3icY9d2I4zbPHO2fL7Wl1syZ6BT1MhK0na7eT4jm8DcM6sWO4cs0Bc=
*/