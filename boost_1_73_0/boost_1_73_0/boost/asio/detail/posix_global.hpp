//
// detail/posix_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <exception>
#include <pthread.h>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct posix_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.static_ptr_ = instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~posix_global_impl()
  {
    delete static_ptr_;
  }

  static ::pthread_once_t init_once_;
  static T* static_ptr_;
  static posix_global_impl instance_;
  T* ptr_;
};

template <typename T>
::pthread_once_t posix_global_impl<T>::init_once_ = PTHREAD_ONCE_INIT;

template <typename T>
T* posix_global_impl<T>::static_ptr_ = 0;

template <typename T>
posix_global_impl<T> posix_global_impl<T>::instance_;

template <typename T>
T& posix_global()
{
  int result = ::pthread_once(
      &posix_global_impl<T>::init_once_,
      &posix_global_impl<T>::do_init);

  if (result != 0)
    std::terminate();

  return *posix_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

/* posix_global.hpp
FaN6CB1jtiFCYSwSG6aBIrubWGgyIZgU8E+uzzjcr9Hadvmofl2Dgsxg9XTf+N4A0pW76yt60l1fD12b5be/8Dkjl+dXclKRVHJ9dXH6o8YP8WNGGzzrCrF1Z/PjCSarYR8BHnMQeF/nqLC1uWpL22Jo90T2NEiPabtBVS5+2AVWrX1rGho0rztzopaWpbTlc6hZ72P9y/UPtdSg0Z2gFwXVM69PE+G5SBM6mZv2NhCGPzC2Zk2ahev4wYVr0cML1yI2oYUxiPFAgSN3T9KX1aLYtI2HeQqBcSgto29fr+Qihnwdg/XaBq2E1YnUvhv4b+J6llc5PV4m8UObb0ud3GuMTavjN4nWH0AaORIlXQKys1zBdEMC5NxMVjHKZ3zCURUIfbS741m7JEb/I7q1eKyomq8FyXdeDMDKrd6hKxvVxt0t2gKYbbrE17oXdNwgpbrfUO9CODs3nP+yZLzyd67YU8mID+iWDmoeWy3jxhVcoqj+uyGtHb8j+bSBWdbAKm/RIM4UvSytfVVJtHKh9LonvigtIzddzLHFimj1JszWFVANg18sJ4PuZ1j2WlDCGgbKP1LBgZtdwIKSpMnMVBQV3N65Ja9d8afYpI/CQks0z8CDvSK5OHuaWjXIHFxuQUU7gHt+JwpS78lU
*/