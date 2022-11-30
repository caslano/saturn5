//
// detail/buffered_stream_storage.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/