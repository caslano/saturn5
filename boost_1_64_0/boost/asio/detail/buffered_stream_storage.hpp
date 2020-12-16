//
// detail/buffered_stream_storage.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BUFFERED_STREAM_STORAGE_HPP
#define BOOST_ASIO_DETAIL_BUFFERED_STREAM_STORAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/assert.hpp>
#include <cstddef>
#include <cstring>
#include <vector>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class buffered_stream_storage
{
public:
  // The type of the bytes stored in the buffer.
  typedef unsigned char byte_type;

  // The type used for offsets into the buffer.
  typedef std::size_t size_type;

  // Constructor.
  explicit buffered_stream_storage(std::size_t buffer_capacity)
    : begin_offset_(0),
      end_offset_(0),
      buffer_(buffer_capacity)
  {
  }

  /// Clear the buffer.
  void clear()
  {
    begin_offset_ = 0;
    end_offset_ = 0;
  }

  // Return a pointer to the beginning of the unread data.
  mutable_buffer data()
  {
    return boost::asio::buffer(buffer_) + begin_offset_;
  }

  // Return a pointer to the beginning of the unread data.
  const_buffer data() const
  {
    return boost::asio::buffer(buffer_) + begin_offset_;
  }

  // Is there no unread data in the buffer.
  bool empty() const
  {
    return begin_offset_ == end_offset_;
  }

  // Return the amount of unread data the is in the buffer.
  size_type size() const
  {
    return end_offset_ - begin_offset_;
  }

  // Resize the buffer to the specified length.
  void resize(size_type length)
  {
    BOOST_ASIO_ASSERT(length <= capacity());
    if (begin_offset_ + length <= capacity())
    {
      end_offset_ = begin_offset_ + length;
    }
    else
    {
      using namespace std; // For memmove.
      memmove(&buffer_[0], &buffer_[0] + begin_offset_, size());
      end_offset_ = length;
      begin_offset_ = 0;
    }
  }

  // Return the maximum size for data in the buffer.
  size_type capacity() const
  {
    return buffer_.size();
  }

  // Consume multiple bytes from the beginning of the buffer.
  void consume(size_type count)
  {
    BOOST_ASIO_ASSERT(begin_offset_ + count <= end_offset_);
    begin_offset_ += count;
    if (empty())
      clear();
  }

private:
  // The offset to the beginning of the unread data.
  size_type begin_offset_;

  // The offset to the end of the unread data.
  size_type end_offset_;
  
  // The data in the buffer.
  std::vector<byte_type> buffer_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BUFFERED_STREAM_STORAGE_HPP

/* buffered_stream_storage.hpp
PhZPH09krYE8sRbmZXg9ZOLeJfVFdweIh9dN8N+KrGF2aQD2SMsjtsCVNeicIMWZ/y3D41ny3jfPrJkfjkNXJ/kl2OfuSvoZNvqU+MkfBA3KPvNAj/bhHmTqT7npX+SLOrsqkLUBOZOZ52zSolIpyUu/KUSX+Yw12fiYti/h1yXQi4V+PenOeMlil+JGEbv9SLHPV/h/HXKs9SEr9fu00I6y51MZy1OYO2jbTv2XbcQh+g5Kw+fYJxrMmEG7ZmyfxHhI/o7xktfMw+j5RRE0oNODGNoKrVpipAnZMocx/pg9R7S7w9xrhWZ4LnQstPHi0/Gk8E1OJg4ZC/aae/6U30YM3t4Ibxc2NH2jRFoMdhVIIxkvLVXENPgdbV7FvlcjW2QWY28RPMhfN5RYou3p6LK+gjm3nDUKvk6zY/98+gZ+KcKXy1oJYWQ6vlYU4id41liIf5u034UMxEA8ts8wc44Zv4nzfGjkVcNjDn7PZP1CDLwGzTRsPtYqbaPstHTqNOPbQmIP/AodY9F1dB1xhfw3gdfQqye0nyaWt7ZJzyHrrci1k/RP4B3y2mizdyDn2CQO3RKKpanmmeBI9CrB9+jwDLyf7Yev0HED+ec2UN9DObJ+HCcmKHyNT1LgE4OtCuKxd47knINcZgwx6w9o/MJcuyURYxnEm7nWcRKH+K7Gx1hu1iMzkHkKYyMyZHtpO4pj4mV5DXbC15/C/1TzLAq9FyHHPtrX4ZN6ypdn4lfqPz0P2nHYLJm+ZeU8Dnnh2YqdK+H1cAlxSD1fAnXIe6uCmITnn2n/MnLeiS2qsMkbPvLs9HUzV5v7OnPxJ3qXYb+cHHRHz/HIMh3+PyPOP4fOxix8Bo1yOyl0doLkIfDETmuwz5t1mGoydjc+amQ9Ye5po18KNn6c87Ez4AP9a/BFIrJuot0vkSXN7G8pgw80WqB/NrgVe66i7FnqXUu7PI5PMuOgFfnnIjsyz6qWllqwv43xh7bvI9+lGcxX2PFF7J+ObkOxxwO0/91U8W5V6PjwwVzoO+iDpF/Npn9Bq86CTl58iE8/mAUNbNZjAbbPZN4w1wsjoI/fHNSNpewnxPw5+GgnMX3vQOSA5zPwn0r7dtCL4++AC4npp6g3eCh0zfoaOZuSSc3+BnONQdnZNtZW5lkZdc/HJh8h9+3ge+h7CT5ZkiDlZxKrbtZW6LIEW42ExlvotBVZnwcH8vFtEboWQg8bnDKF+knwAEuQOdklucBtKfQt2k7Jw1dgG+0+nCRZS6lbgL+H4St8utojHUf9FbSPRY/qNuJiIrFSRTnpY9CJR57N6O7En1Gk70zGR7T700BkqZVsxNDHxOvVyHQe+pXBKw5eHvM82ssaCn6vtGLfHOxGm1PrGFfK4YXPt6dLo7KxYRo+7U/MQK8Um9Rinyj0XGvysc8F47FtPP2zBvkGoFM//D4Wv0L7KsrnVIj3PuCjDOIZ+05Mpxz9fuOTxpC3sFmK4Pz8qfiT9i/PhDfnVnC9uT8Fz/XEyLnE8OS5yNMMrXjiBzu9W4p/4ujH+LuI9HXOXyUdYZHeNHv64uEB3nBIS8x1awLxAGZC6wV4fZ5EHCNT9Ehk9Uq55N/WH/9QVmjFlshy8UTSWmLCJeXXSdZG+ixjRRS6tSYTu3n0IejvKMceA4n3Bslpw94WbFNMv5hOmigtgl4aNioYCM1SUvhUZdFPoTGyEZ7IkDCX9i3Ua5MiOL+ugn6ZKrnS0Qn/baDe7+ulYsp7I/eZyFsGjWjyj8PHFvIWwH+52ctH2Vf46id1+MBcl3C+mPMqi7TJ3HfMIyXvr3apxYu82DOJvpTiJJYd+HEE/iDW70amh1yMjc3QcUvVCcQ=
*/