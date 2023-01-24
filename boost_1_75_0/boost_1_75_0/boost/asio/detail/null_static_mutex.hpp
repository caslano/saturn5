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
9xUrngxPNiP4ZDcNnJ9hKBPRSQGYfBtDmfB5RJmajYp/lRVdIlpXQpkuQSi3KcOPysfbEV4aD1e89uBIKw76XEk6SaawItOPOVFEyobCFcydOM8iMApqTMQmevzDHJyFAGcU94ZwJEZBmnRM6RY00hVfWCTfiRuost5v8W2nQL9A69Lfm9QuPf8xFS/5hcnQXzbWX8wYOwOf22THVt346p3EPBu3O+CaXjY1wCp/zNqCE0KoN9Ucg64jSIIt4VdEk3/tMLManJIusIKXBtdg7Yx2qrSPeH+KoJEyTI02P2PPMAKq9o4mHRknebB2XJPko29LkxpPHVYTUhISHWGhVrhNFkN/3m7W+1NTmByzZs4lSl4RX8HCEF/BoAaVKUyGL0TKxC8EReLzNY43ahyf9BNdiRj9yH3M7UiVhOGaAu2AS6Awypxbj8QrmVoxW7Vibv8VCzxuN3TSrVvO0kliXbO1Re8ZpFHvk8LoPqlJHLBPLgyftU9wZV0ZxubnRXqBcz/Uq7H7VAsNLFf7Kf9rYpEDb/OZFWuFz8xcGsumWVLYW4sp/2SGO7DseoWSD4m9MMyfA64kQ4hluWk08acTzHoq3FIh0ZAEeU+fn/mZOmGEdBghAmAeF7zrm3C4UDEXySj/ZSxMEveSt1uByBH6F/mdVESO9mL0ZhbiiuQA/pYI+6jau79HA41qewygEWJGVy9EzKgI/8m/nGw2
*/