//
// detail/null_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct null_static_mutex
{
  typedef boost::asio::detail::scoped_lock<null_static_mutex> scoped_lock;

  // Initialise the mutex.
  void init()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }

  int unused_;
};

#define BOOST_ASIO_NULL_STATIC_MUTEX_INIT { 0 }

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

/* null_static_mutex.hpp
MI5gIdhEoR/8eQM9Jl7zYP2lfWxhp/BkhPhWcQYZW7Q6nAkIpJG5BtGmgMVQRG5mGCDYG9OZYcQzDPDxvF6Zf8hHoF+5E57mJ8EkZTvjSdNbnOV20plv4bhrIA4w3IN9yVjORKTNMOHHs2l6YnuSuZBYDQzk8zj5Oz9oGCzyqOMAF3VAedWZ0EBK9Hd8yAWc09lNkV7cUCXmtkZYhDGhfoY7O2rKSKdo9ztH80Y2hnApgHipbuPlF9EM6lJJdOpoZ4jiBfZ3EtfSLi6peHi3ZtfUK0mhSj7Y2L3x9tiTaN281AdbNALrA/0H6aH3PQXPcECQjqgEMs5NlaujBBzthy60XjEEDiDjP8XuLmdKMoyr1dzry0C3XYf6T1aGGnMjqFuyDdl+VRUU4u94JCvmtQwHtUfZB8fG0jY5eyAD29OLTXcv+kpI3j+yWmD4IWk8v3uScRlpOLQ8xM9pa52URkhWpZdVCuLpt0Z7ZJDkwsJGWEoIVR82yK4KVRE1dGFfWA0LT8fjS7S2YCTU8q3buDJEtjegywli0EM0CtmLcyeLHz2Sy7BbZj9xyA==
*/