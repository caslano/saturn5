//
// detail/buffer_resize_guard.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP
#define BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/limits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to manage buffer resizing in an exception safe way.
template <typename Buffer>
class buffer_resize_guard
{
public:
  // Constructor.
  buffer_resize_guard(Buffer& buffer)
    : buffer_(buffer),
      old_size_(buffer.size())
  {
  }

  // Destructor rolls back the buffer resize unless commit was called.
  ~buffer_resize_guard()
  {
    if (old_size_ != (std::numeric_limits<size_t>::max)())
    {
      buffer_.resize(old_size_);
    }
  }

  // Commit the resize transaction.
  void commit()
  {
    old_size_ = (std::numeric_limits<size_t>::max)();
  }

private:
  // The buffer being managed.
  Buffer& buffer_;

  // The size of the buffer at the time the guard was constructed.
  size_t old_size_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP

/* buffer_resize_guard.hpp
ElNa0DonGW/jPtPK38DILcT05fltTZmmdOFhB+mD3F+qcrcG+L7u1nY+Vtpb0hLurhtUUhehN3hxF8gXvmPTXJOlKX3YWuEqTUXcK3KfGFRyIkIf62EVP6EVpw4r4HsTcxCWMQjLQYQXxF3/wEzDyigpwvxRSroY4evmIEUvIwx+KFZudIqhujL5YmJLoBQGKOXXO0gpxtCVqvc2afP54t9nEC/JT7QEbOQo5n8s9Z1yxefF/wveTpmIm5lGqZp+AxA1INVq4vuQ+x0qhE+MpYdr2jkMB4dS80sYMf0Notcio5c/SNq2UjQepSpClSjUOchdNLIPTHWK0IccpGzB/wahcWTX3GD+ozEALsMnf0Mgy8RPUJFqlJGa/BJNXStm1eJBT1NajlHoSZv4YoqiM8Sc6oKWKGFPmZ7rgPPsVMR5fr2Eo5v1GMX505r7sio64D0cMIxkiYiuTsGLzzQU2Yd0CwI9EoDegY18Ixwk8TEZbw5yeNb5QLZ5u3b+8dBALgCzP0VDALsxDqu0q/l/9l/0Tp4cem0AuXo9EgKehaWEYAAKLPXTyqv7AOBLSdEsG1Nw2dx9qwqkezRbNnhZAjH9VVk2q9eFLpu62/5Xy6barsLSPEqzbIbiDMdIESBxioBvtwQifN2pj+ns7PMYqdDJ8nlyAsWeiWKvsIBNZVf4q/qA4o80FqEZkEClIjrAZWaX4ztBsTvq81a8
*/