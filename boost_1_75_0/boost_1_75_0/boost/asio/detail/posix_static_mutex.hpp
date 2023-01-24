//
// detail/posix_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct posix_static_mutex
{
  typedef boost::asio::detail::scoped_lock<posix_static_mutex> scoped_lock;

  // Initialise the mutex.
  void init()
  {
    // Nothing to do.
  }

  // Lock the mutex.
  void lock()
  {
    (void)::pthread_mutex_lock(&mutex_); // Ignore EINVAL.
  }

  // Unlock the mutex.
  void unlock()
  {
    (void)::pthread_mutex_unlock(&mutex_); // Ignore EINVAL.
  }

  ::pthread_mutex_t mutex_;
};

#define BOOST_ASIO_POSIX_STATIC_MUTEX_INIT { PTHREAD_MUTEX_INITIALIZER }

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP

/* posix_static_mutex.hpp
oLvo13b4tRJR4cTOReBI34RRbPnAxi8pTmkARn5/H1dSbEIvV1K8Jauowd/AwAsPo5cqMPHjo2KJiUcEERO/KwRHTUGsqdhErHmewVDR/TX2hILEGnEO8trJyGtfGbBcYnMF508xngz5bXzVU0ZXBvWqiK5689v2Kfnosq2x3K2BRiDjNI0DQJY7OLKesbE0xTtVlruJUA8sN/5QWW4qd9bIzUDYT8/ncKHWpXHdrJNz3cFpJLj+hNFtHDOeVzBFEZWiephWDwvWQ6BlI+FG8s8T8yR/iZhhX1GQUiOOkfxrNLzca9TYPOK3+e3iZKMjjlIJ+bmhCNnxGpUdf6UHJfH8wU2eg4EXKO3ctY4J8kF6XVofcbVjlNxAQcAqCOTTy4mxsYSWuyq8HOfbc3vQ852moVBZH4Pe3TQThcpX+MV2ungWzTR+4OOfoh/AyD/OH2+hx2hBQSw3Eh3C6W/LaqBJg9SbuccCy+5ZFqOiCNjtK0gXtVdjtzHKQlynsdv5Grv9kygK3Is80kDTk6f9Pk1sFuE/wHDjxHDv6wosO5w3PyOGG8sRw/1pCMN9UkdwB6tTyvNmkN8eHHKf1/J60Izll/fhDJHqDS76Id/fRfrVZwIsN26FQBTqgSg4TwebowiPvAxlNmKO28pnDeh5gNRLeLk6y8ZOJ1Jkh0wvFIj6VJleSk0PBZHynuBeDS96/0icek0Et5bRt2+Q
*/