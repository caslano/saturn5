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
70uCN2BvbvjGk8FjUOi7XMxzhNt32RQlscipX3JYhg3W92ngkKgJl8P7i7khHKSjB5G9Swvx+nuuyJ5YLYSkDRBuh2YKcY5As9FmKq+TCedqq5lSEqLqOw5z9G7HcKDGbTeAio7A9/+OWeg3W+Ds4tVnIbPACKJWpd/2ZZsw2PuA2nUO6Au5l41SYrtV+vokuUyUuPvzHMoZqbJvAA2ZFPeOfo+4kNHuL0Akw1NDjm3hCo/7
*/