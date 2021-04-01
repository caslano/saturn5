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
AzqSCrt1XXUXaW3JNKU/wa5SNkCHZ1kTD+OhT4lnK8O+ycpNLnGoSaxilpCxZF9O1Cweh788JnbEEPWepkpGI5h8f+Se5l5ULwlj8KRl1mmgpE4XjK1/6j1YTYnQZ21681tk6wLIBetEHVCDfrWT/8FAi0Z1m/2hwHEmlsO5qO07GcKbKWxrhjhaFpyVBzFcPbH8g6Kmh/4vKaXjXWVC6AgI/i/gwb/hWltDhqvJH3+01h7AqxLyHoOIXCjwmNjiHqYPEfAlfdECAmCcc6nhDmEmHgB4v/cbiTIT7/v0/A0BwYSH/tgrli9h4hZG0CyTHNLx3nKJOrZdSGbmCuU1fO/KVsvYuFQZzM9cC5tRVcWBEzxrdozrVRmJ5LET2+whB7nFeFgXoBaJFQTZL4VIgR5RtSy0z4/pmPCF1LLgi96qu00amRh5bFn1Q9BbAG+Khw0IAVflnwIHYVQ06aayOUys+daaq87tQ8K/8bpPkAs4BQKB0eZKhsR1LY2szYcaougNHisFtjlvQ0lmmMUeBErgzYgwxk/3l8MrSXMEqbLPC/i3xoNOmDYSBQ==
*/