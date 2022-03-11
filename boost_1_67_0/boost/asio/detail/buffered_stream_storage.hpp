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
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
*/