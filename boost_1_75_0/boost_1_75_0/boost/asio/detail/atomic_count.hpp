//
// detail/atomic_count.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP
#define BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
// Nothing to include.
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <atomic>
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <boost/detail/atomic_count.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef long atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef std::atomic<long> atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef boost::detail::atomic_count atomic_count;
inline void increment(atomic_count& a, long b) { while (b > 0) ++a, --b; }
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

/* atomic_count.hpp
kWMap0jNDXva8X705yYBMS9CXPPdkMjc+LwQ7YOgWrEyQz4+gNdv9lmXb8FcI2v7UvI1slQbOaVueC2EA8S+n5XogG8ycG+YN7DknfS8cCCOe1UNwTWyyygwOCcncCUKQLkl5YFAm2/fp9Jm5dRQlmsJkUWW2XSzcYxOe3qayaLcYB+eqaEywKKRAZYQGWCxzcH+vuU0/ckw9Q72d22XMKkQNWsFiQzRkTy1hzNT/o8QfR52IUSFwf5en9IJRB0EU5BlWDSyyaTIpuuCvc1lvTV8GJRNls5k07+/UWTTp99cIJsS92hlE9mkyqbbbRrZ9KxGNm14QRUDN8iy6egxdYmM6lw2TflGlk2JKJvm1iiyiVDZhGd+nTjwc2zgIJ4O04U5b5NWPH0xSxVPJkU8bVfFU9smFa6/0sb9N6niibv3QvG0taN4+nSTKp6WIOP/+7GuxNNmVTwlkDdzkR3EUvFkQfFkCkoo1ByhowMpoRJqV8qFEupfNwQlFOP8t+SqM734BiahZtCLPBQJZbIxzJHjv3WQUCaaPPPVMyiiQEqSrBQmoqwpF4goS4iUsnSQUvJWbDz5/B4VmG+vl/dJZFn1PW7Bo6lExVI40B3UfypY/325vg7zz6y4h0YwWc+S+++heBuc4sDLQUjP8wE6t2DhmNztAbMH83uTGffIgmyDLLZWlyhi6zFFUNFMimTcjFA5tQnlFBrEqflt
*/