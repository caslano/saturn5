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
k6zagdliST+sXww8WD8igJYiSDyuKVibuCnXGsZlQ8hAWwzFL7Wg8SkWeoWh1nS6/lw+T5UUzFmHhP5X9LeAnXF8Og4W2jdkWHtek6GwvDbNNGJO2vAf8k9o+59n/rSa7PdMZaYZ27i8lhO59nS+kxvSa4u8VbVpWMoljCdg8GDg05xt549hBX+a7pJi4hkxqcV1l9CKO6qc76Ew1QAI7EeQmnR2CQAr1QcxN2tHByevNaRV4sUhJ+JFm52Zv6NpDFQkRB+RrpE5Da6UHHvFGYRJ78iq1AiPu53ezl3+gZPR1jS93zLvFlgNsC6PrkCk2SGLAFg2vEaOlbFPy6xwo3F2idreogz7GLqtlOGiSlxWqJ49NLZf3cgrk0D+nvP22ST+9xX4cDtM/iNtbQU2gNbVl+cW4a7MpaZ0lyhxt0TF2KFiab2Q/wy5ErCVWFmtAAYlUaz3rC+okjX6vog1euzdPn+H607gZul33S7iTYlsOv6De28lYcl2OTyWWktnbVrh1AN3vOdrYzIPBpVW+XB7Fq/Ql6VZuKNbtpcD9gRB0WRSygWoXNTTGA==
*/