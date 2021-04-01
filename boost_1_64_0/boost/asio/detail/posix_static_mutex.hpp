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
kxgbqx8gK8ZP2UxQ2ZdO/a/KFcRwYTOG8NGhC9vDN3uC8MI7vXGLqPBBkhVw8jS1Zi8eHvbWjGGppnPcn0UWPAf2EHcEWoldsqS5F4v6DqU5OlWWrMv7Y+8Pn7+AaxhYnBypkmKS7kKkTqte8PzU2iqrk2DbVichMYD4IGT30aa+7NFBrDAMO39DxoFPpVwrjU0DJfHe6HDr+rg2aGyePCGEIu3iQVludr88uwlhdBj5H/oxcdLP3NpKsksHjiElAFqfxmrpIMtByEcg1SZV/PE/P0kxSUB+a3c99LaziBxwo2MAsPjh3zINXF7XH7SKHJ7Ez28El8LwRXNwpg/jhGc/TV/a1avhklRfM0T94Znd2smeZ0HQJ5xwwiRwelNY74MtkqDsOUh6yEwC9SBPirQZJEpQUS0an6i+RHpH6fgZGMPXcPGB4de+l7XP2q1q78hSs6l6Mr6OQywYD2Z4PuQQ5wd9PpiBhEKBdkcmR5sc06TEZWtmUPwQstr3GcQdw5FkqXc3IOyPYf1GYnPR+LVfOffd2QPF8G8FO8F0kHdBXBBkFgY6S8AnrQ==
*/