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
DHdXatomTmzLK3I+zpw5MzLmW1/3+n2PL/y++sbZ+/vPpvzDnU/4/fULa3O+8Pn+hfnWhc/muV64Hz38wNf334jqE6PijzXvfbrnSzy5unpqNpt3Zt/HrZcuXcHKz65PeWG85GfJSMp2611qTW5tNkcxsckSTC+N9CZHc/duY2yo1YoLWfqqtWEnuHQyNsEc32ill5W5a8VUQ99LyHSYYxW9cclU1nupaWlhHHzY+RHvWuNj2JnsOoE1u4srBnlHk8biO8lBeuvNQ4hHxmVTDMkcW7g3VQxBquxiKOG7cIj+IEkNd27XZphqrPMMDpHgvzV1rIaOMeoVm7N0+5yYay0ZZ/ESiXQxZdjvOtiOASYBAoy18ciTnctuZ7PwaIeAnz41tzemkj4rxNNrTWBIyJTW3c5l5H0ySMg1J3WTpMdfKATPu8ZVMLoyf8bBBME1C2NPKmu2Q6i9PDFNRFGQycpsRAAcXMQGscLNFLxiwVyDOgASt28/3G1gaEp8jrdYRTIpOZRAy9tJ7ZjYRTya0scWrBj0XLKuvriO1MaE7JiOXl6YE7I4Ou+NPO5xQELFCk9UNK7hiZ6WUtYMImAOkbAH5FLiv4xjTJ9WLmNVU2cw1U54phw8uHqukZJK+TyTs0NR1YBSgSb+E4OR
*/