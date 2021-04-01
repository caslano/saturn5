//
// detail/null_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct null_global_impl
{
  null_global_impl()
    : ptr_(0)
  {
  }

  // Destructor automatically cleans up the global.
  ~null_global_impl()
  {
    delete ptr_;
  }

  static null_global_impl instance_;
  T* ptr_;
};

template <typename T>
null_global_impl<T> null_global_impl<T>::instance_;

template <typename T>
T& null_global()
{
  if (null_global_impl<T>::instance_.ptr_ == 0)
    null_global_impl<T>::instance_.ptr_ = new T;
  return *null_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP

/* null_global.hpp
TL0xo0zIQzRfFmZWB4hBFQYYmGrTD2lnbNoX9fhDtXvFDbBqT9LMwVeqcy3Z/ggvH+lD79+0qumTEyx5faYXgQurI90utU2aVIc4Kn6MaqAXUSEv+CZayVCdHQYthVOxKOtzyjVsR5rHbbAtLHF5T9kQbPtaSdryZiGc5u0xQJtDemgFhJ9A2C/m4AsVr14A1B59FmWVYdsGhBmvV1Vwvkm6jc/T3gUSjPoYz/S3KhQryTdABppm7lz2PdJaq++PS/hRyKAwaDI8rkCn2UuPlWZhlJZOF7a8ddHdDmPZOd6tVNK01RnQlIwM1XxtKEZU6/Lz0QmeIBVeTVreLPC4FT06kisvW18g0vQ6aQ/KVUkfGQFK8XJrp+9nU2FRfTL27WkvKtywd2Alh7tsufMeqp+alfOOz6eDMmXmdjfEQrmLuvmNGa2/ktQdNuwHfoHfZ/HSbo+Pr7PqsNEWaea3+wJem5ARZvTLcEx16MFiLahEfIr9WFBw+GdlMWX7KC0HA2SpOqTKoPOsFe+F18tbM1WpS3r4/a2wBWjAhHQQFMZUQPxfgvUp4xjBGg==
*/