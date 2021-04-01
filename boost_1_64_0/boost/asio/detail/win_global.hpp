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
RjDVLOQhJ1v1cYcrqLjiUtQrcRz7QCB/6vpZ0l/xj+SrkSDdk1bYn4A+YbNf4aYbvlCXuiPaIU5V+et42GxspQ8bQT2wYgiJCkpNTcF4aylkRGJsWdKnf9BRM+DEZV5H9XcTuy80GL9BSdxkT1rdUai+qdCKgFEav3tRdOCpuWtviCpU3hVCvCJF7qdqpWnLWwjK+2TI7ow0+45QzIDjOChlhv0+bhAdu0tnChe5qIa76eq9wKVd7lhKylyMXWUaGWT097RYwm4VfLuuAMI+mO2box5K9v73qksvkZLImdgOAeBmLeS2EK9FT6nEohI7WKzQSfXhJRr+VlFOQaTWnWbx4GnBLOwhnL3zaSZXO0+NwkaP8ok3O2ZCNkHpTpf3bffyMeG9zRSnVIZcwAzRB8bVBi0jGNwA8LsxgW7nGMopQimD/sD5/45aSDw84DC71y5wUO0h1I7CFUFJ/KYP7zi2/+79I6hhbUrY1TfoulkB342+FDrCMnNr1VDZ/EHwnZxbz7CKC7wCN4FsPFZPJFng6YBvx12XwL11HYwCP9Gk666aIIS7/fc3pQ==
*/