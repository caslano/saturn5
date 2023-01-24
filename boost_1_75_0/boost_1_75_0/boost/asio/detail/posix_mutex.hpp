//
// detail/posix_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP
#define BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_event;

class posix_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<posix_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL posix_mutex();

  // Destructor.
  ~posix_mutex()
  {
    ::pthread_mutex_destroy(&mutex_); // Ignore EBUSY.
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

private:
  friend class posix_event;
  ::pthread_mutex_t mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

/* posix_mutex.hpp
XxmqPdd2Drke5DHBcmJecbJZjJGqI4DCnE2sP+73jg1RgtV7Y+ZVTNeJUanwuC2xnrdVJoKrinCOoZyZRBK9nUQa2Jf1fEKHKMdwyQaVY3gVVI7hVQJfyFw5hpx/4kGqiu4m+l0HZxDhJxUZMXaoFxo0hNJA+VQVGeor3G58iiqyCtr4f0TO/WEqMvX1JPamSVWRFdHEogrFu51K+Z3y26G6MZuP68YWcErEYr9UmQmHJZkeiolq5RrPiTdJOfb8PxBdoo+rxRRxove3pBbDcqgWC3krL5dtINOumTOqnE8F8W4StFucEICNiIC+DzVpHC3pxNYSsvLVgRjfhn2X/+Ej2Qnvega3aYK9x9YC0EFQNqRLNWa+3riqQHhkc4umY0jVFDkR6wZzvY/n8i8RBNbkOfc1yEcfGs2jPjKab4LjGTg++dho/hIOpdlovvlTUqTJVqOkM4KUk+6XF3b9QBZoVK2ezwLNrc7cAt3YHbRAo+mOPXGBX2HRYwIW6D+u4OqvOEp9SWbTE0Jlu25gC/Th7oEs0H/RhVigVQts1XbdeRRWpLwlhdVr05u5EZoBrSXrsWrJPUxsm1Es1izRR/3nsURT352NQWyQwXIAS7QzhxxNsAYgFvFSR4w4gn0RH/z+9ze6b1O5PhePugDVkJ1OqcdQm5II0tIFQUO2M2DI9qzhBmn16g660ntbVJUKQ3P2Z33N2cc4Ml2W
*/