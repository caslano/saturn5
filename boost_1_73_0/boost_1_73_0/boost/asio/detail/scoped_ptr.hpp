//
// detail/scoped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_PTR_HPP
#define BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class scoped_ptr
{
public:
  // Constructor.
  explicit scoped_ptr(T* p = 0)
    : p_(p)
  {
  }

  // Destructor.
  ~scoped_ptr()
  {
    delete p_;
  }

  // Access.
  T* get()
  {
    return p_;
  }

  // Access.
  T* operator->()
  {
    return p_;
  }

  // Dereference.
  T& operator*()
  {
    return *p_;
  }

  // Reset pointer.
  void reset(T* p = 0)
  {
    delete p_;
    p_ = p;
  }

  // Release ownership of the pointer.
  T* release()
  {
    T* tmp = p_;
    p_ = 0;
    return tmp;
  }

private:
  // Disallow copying and assignment.
  scoped_ptr(const scoped_ptr&);
  scoped_ptr& operator=(const scoped_ptr&);

  T* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

/* scoped_ptr.hpp
ZTzEdaxQjKumFMcCsiAisrqijfbWDexC8TXWEkRTzvOiFtsg+lO8AtXQVpxT7R4AVk4hXoqw8IgBEFDAomlGUHkJGt2MsoeOZSsP+abvQ/umwt9TYRPhhqzAsoXjJoUlZqDg6ZyCpTsh3KWroHTkPb+uBQRliRAINzVTtKkWJ0N72UzJzVBDBOJkSE3EWdTH0mNS5/GefFxDgekuwTHxpWWzmkBNhDWVGHCd/F+VLZrCVcIkaM3K1WIhkM9qkpfKIaFdWaP00HcQWMSpd4aiJprZaUpSUaC1VSkE1RCRhQAmNAo1B1Eg+jQSrX5lJVYq7keoDfA7tIuWXg3jQhM0JFEPcjRS7SGcSTRbF03YM0YUE87IL8r8V3FZvUxG9G2TSTIgO223FYpKx2sXlW9KysiX4ts2GdZmoXaTIg9LvG+30Q8zkASGHMSka5ok3EoKxGDziuwskOwEjbZETg0pTKt8XQf1ddA96BWMtvqIb0Ol4usdDyN8JznzbIME6jqGZ7VdcYiMcgDiq5k4cA2VB36did9C5MGfKpoYzMAL2AoSlpgPEZeZcPUOoDlIy5hRKRqVT0WRxi+9Gtb52C5hOSJ7woETo8m1wW9aiCfbiDt2ndExD5owAMJ2c4YMcUoDG/wqU38I31GTF4oA
*/