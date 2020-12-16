//
// detail/posix_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper function to create thread-specific storage.
BOOST_ASIO_DECL void posix_tss_ptr_create(pthread_key_t& key);

template <typename T>
class posix_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  posix_tss_ptr()
  {
    posix_tss_ptr_create(tss_key_);
  }

  // Destructor.
  ~posix_tss_ptr()
  {
    ::pthread_key_delete(tss_key_);
  }

  // Get the value.
  operator T*() const
  {
    return static_cast<T*>(::pthread_getspecific(tss_key_));
  }

  // Set the value.
  void operator=(T* value)
  {
    ::pthread_setspecific(tss_key_, value);
  }

private:
  // Thread-specific storage to allow unlocked access to determine whether a
  // thread is a member of the pool.
  pthread_key_t tss_key_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_tss_ptr.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

/* posix_tss_ptr.hpp
PPOLBHk5E+e0FzX4UlXwRdXHFgtygftki3fixeHSYzCNJYKawL3N7ihep4E29oQ0bk32nyWDnPA/r5EbE+TEBnMu21KKk58fVp8ZRn7pEL+sj1/Gx4f9uqzm9dodznu5ACeaXAUqXLbp5Q2+1Qz7bIVOvDhcsgfTWNHUeOG6W6kTbw+rtr+yTxO2Y5VOvDEHWVVqcMucXBJO56eE4vT6oNX8mIyA9iRDnNpahXFTmh8NtuW0jwv7ozeCD/p0dZ8m7I81IvhgGpmghk946luaIV639bVCnN6H3hfi+FvinG5/iNf9JGtyup8gNyA537Y4ynMwyOndbuiPtX282NSAj8D5aTU/J9aaKnYCxvMKF/FwmwfiBR+u30G1jg/X7z1ZV+HCOGU/2rfeL4ydB5hcVRXHQZEqKAiCIFWa9GwIBLCw2Z0kC8lm2dmERMBhdubtZsjuzDJvJiQIAvYuCIh0ESkCUpRiA2wgYAMLgqiICCiKdOzifef87z3nlo1+H99H9v8775Zz77v3zrtNMTMG8N8D9GVLQ5v4XaGwlqXsgjmDd0Q26XfmKLFr1Ub9enx0yIJ7/Y6JeWuKvpwyf6fH4/6iEnGkD/xYj8f1txpxqb+jEZN5/VrEpH7WIybteKZY0A7zvLZwtLJc9uOiY41BtdbpVifo4BSEvTyyoQCqnYx/rzUiLuczHBcyV705/hXT8Eq91cxgMzGNDbkU8zGTa7Jp8BlutmyakW03N5TS24rYiZxePDuleNgOHK8Yv+e81dvmtR3xuB3IlU2nbd5f6B1PbxrAcXZFX9XJ43Jf6TgygnycUOgjCxbNq5RHFg3juDGkc5XP+PPERGu8+FzQqPM7vNq34Z8d+K3APz84fScm7JhjTt3nbi/jSU6Xu/FPtpqkyCQH8+geo1+hFP8pvj7VHZ1o1OijMObUHZc+5DSt0RJdbFwHfw/xCq0dWFYpLeld4L5u8H2bSc4JwGd+snvfGuwaed7N2ly335+0EyfknVbbvisfmNa20mnAJx9M25jMcro+lOT8aVWn/8PT27n09xi7j0xrV8lpCq6iaoCdo5/2GcnHxwobU9ATE41qsL6F+McVD0anxD8R8qCN/2TAwz7gdMWDESjV1zM0r2de2j6lWLCWhp49U/EwX2dphtZex3u24rKuBnsmDesvlcldtRV5dxL6OaJ7YX2G9WCJEM7xFOb59TzWcbCdibz4wNDouLU954PrsC6ABjfNtH64ELpx0cxwvdFFjvnxX2z1ejYzVS8+q7ifMeaXBDx8/nOKp9Y0XQoOcYbbQ+nrPVa/zNdnWj9dDn1MhX0Fa7SoOauSd0m/knXydk6TG+y/L0BvJtZ/XQXWSpTt1cK8OatroGOxJYXzRWhTOg6Ecy0z2rnEFY7161inBZOtSTnX6HroqLYU/g2+xvUK80JfCli3CYo8fll4sTIdNZHZjczwSbRYP9hjguA83RQxmQO8GWxVIr+3FGx+5fD+uWbfT2X/HluWX2F90VTWLJcX8NrEr5JGSzfJ5mv0N2VP9kEqjVdicvq+4endUf2O3womR/Cwfhv01qTZBZ7RE+TD2yPdxFSvGx9yOr9JnPo3nsOlv2VPiV138W1f5+RmnayNb7XfmZbLfqjvkg2mKJvjjSb2F9whehEfaXcqber4cd4D6TTa8VGZccB+pN/ldNqd4dY43x3qsw6gvNwDPf4CivMwwWUMyPoPRMfx2TgPk3QKo1Lv4jxM0bw1jD8WnTInV6ljnla4jHbw7H0+M5uu7Lp85j/xuS503hsZcPyqIfYzn6Fqcdn+3Gd+5YDN/dPY6Hr9C9+Gh/jw4QPC3PlwDyotT/jqlz6foX31kGYJX/0=
*/