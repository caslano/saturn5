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
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
*/