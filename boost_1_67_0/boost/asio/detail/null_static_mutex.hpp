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
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
*/