//
// detail/win_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/static_mutex.hpp>
#include <boost/asio/detail/tss_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct win_global_impl
{
  // Destructor automatically cleans up the global.
  ~win_global_impl()
  {
    delete ptr_;
  }

  static win_global_impl instance_;
  static static_mutex mutex_;
  T* ptr_;
  static tss_ptr<T> tss_ptr_;
};

template <typename T>
win_global_impl<T> win_global_impl<T>::instance_ = { 0 };

template <typename T>
static_mutex win_global_impl<T>::mutex_ = BOOST_ASIO_STATIC_MUTEX_INIT;

template <typename T>
tss_ptr<T> win_global_impl<T>::tss_ptr_;

template <typename T>
T& win_global()
{
  if (static_cast<T*>(win_global_impl<T>::tss_ptr_) == 0)
  {
    win_global_impl<T>::mutex_.init();
    static_mutex::scoped_lock lock(win_global_impl<T>::mutex_);
    if (win_global_impl<T>::instance_.ptr_ == 0)
      win_global_impl<T>::instance_.ptr_ = new T;
    win_global_impl<T>::tss_ptr_ = win_global_impl<T>::instance_.ptr_;
  }

  return *win_global_impl<T>::tss_ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP

/* win_global.hpp
0mpEZkzSYbtWaNAs/d8mCPSdSqfrDh+qV9kDTfK8runsvAcjkaWtVMcl8va1zvdSSDi1jdywichDiqWTxEiYIwUR9S5gM5TC2Ym9kEYsHe8vce6VXEME1obLulxW9BK24PzzdtU2o7hoD+wWzM3d68xAAVvwsXayO/UfUEsDBAoAAAAIAC1nSlJv6lairQAAAPgAAAAoAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZWdkLWZpbGUuZFVUBQABtkgkYC2OQQ7CMAwE73mFPxAeECEkBAgOPSClH4jSbYhI7Soxh/6eFnqyvbteTSecHCENdswF5lzX67itJ/NAmR3d7ldqEt9QmoO+aJRKNfAgEw1Bg3lWUYlSmqO+88YDNpQmbg/9ay9BkaQujrQ0Y601fkbM40L6wr+XwwRS+Qk31irzQvfVQM2c6BowCe8gB+rX0A6Vm/k0DNtrwzZXa+cDp8z4EXvfURRmRM3C7WC+UEsDBAoAAAAIAC1nSlL/aGh5wQAAACABAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZW5naW5lLmRVVAUAAbZIJGBtjrFqxEAMRPv9iimTYu8DTAiEa1KYJODkA9Y+nb0gS4tWDvjvsz5c
*/