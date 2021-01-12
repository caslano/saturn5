//
// detail/std_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#include <exception>
#include <mutex>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct std_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~std_global_impl()
  {
    delete ptr_;
  }

  static std::once_flag init_once_;
  static std_global_impl instance_;
  T* ptr_;
};

template <typename T>
std::once_flag std_global_impl<T>::init_once_;

template <typename T>
std_global_impl<T> std_global_impl<T>::instance_;

template <typename T>
T& std_global()
{
  std::call_once(std_global_impl<T>::init_once_, &std_global_impl<T>::do_init);
  return *std_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#endif // BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

/* std_global.hpp
nE69jsKpOWTxVfP8g7Xy+aFmD+fIE+aFpIjMkvbezTlan2y0X2mvq9/+ltFvSHafPdErzXTbu/035AyBuOHdxA25O62v1EdL3PMSpF4gEO4EEGMF4tN9ifN/tN95F0fmvkM+6LPMUyW/W3rn13g0/wpKB+rslA4MslM6YN9L2ed498rTUkU0YL9VRAN3LushGtClN43unaD+CbamaRR+8wc9Ot9+Af/2L73BtxngK3qCHxDw
*/