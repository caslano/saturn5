//
// detail/consuming_buffers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONSUMING_BUFFERS_HPP
#define BOOST_ASIO_DETAIL_CONSUMING_BUFFERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/limits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper template to determine the maximum number of prepared buffers.
template <typename Buffers>
struct prepared_buffers_max
{
  enum { value = buffer_sequence_adapter_base::max_buffers };
};

template <typename Elem, std::size_t N>
struct prepared_buffers_max<boost::array<Elem, N> >
{
  enum { value = N };
};

#if defined(BOOST_ASIO_HAS_STD_ARRAY)

template <typename Elem, std::size_t N>
struct prepared_buffers_max<std::array<Elem, N> >
{
  enum { value = N };
};

#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

// A buffer sequence used to represent a subsequence of the buffers.
template <typename Buffer, std::size_t MaxBuffers>
struct prepared_buffers
{
  typedef Buffer value_type;
  typedef const Buffer* const_iterator;

  enum { max_buffers = MaxBuffers < 16 ? MaxBuffers : 16 };

  prepared_buffers() : count(0) {}
  const_iterator begin() const { return elems; }
  const_iterator end() const { return elems + count; }

  Buffer elems[max_buffers];
  std::size_t count;
};

// A proxy for a sub-range in a list of buffers.
template <typename Buffer, typename Buffers, typename Buffer_Iterator>
class consuming_buffers
{
public:
  typedef prepared_buffers<Buffer, prepared_buffers_max<Buffers>::value>
    prepared_buffers_type;

  // Construct to represent the entire list of buffers.
  explicit consuming_buffers(const Buffers& buffers)
    : buffers_(buffers),
      total_consumed_(0),
      next_elem_(0),
      next_elem_offset_(0)
  {
    using boost::asio::buffer_size;
    total_size_ = buffer_size(buffers);
  }

  // Determine if we are at the end of the buffers.
  bool empty() const
  {
    return total_consumed_ >= total_size_;
  }

  // Get the buffer for a single transfer, with a size.
  prepared_buffers_type prepare(std::size_t max_size)
  {
    prepared_buffers_type result;

    Buffer_Iterator next = boost::asio::buffer_sequence_begin(buffers_);
    Buffer_Iterator end = boost::asio::buffer_sequence_end(buffers_);

    std::advance(next, next_elem_);
    std::size_t elem_offset = next_elem_offset_;
    while (next != end && max_size > 0 && (result.count) < result.max_buffers)
    {
      Buffer next_buf = Buffer(*next) + elem_offset;
      result.elems[result.count] = boost::asio::buffer(next_buf, max_size);
      max_size -= result.elems[result.count].size();
      elem_offset = 0;
      if (result.elems[result.count].size() > 0)
        ++result.count;
      ++next;
    }

    return result;
  }

  // Consume the specified number of bytes from the buffers.
  void consume(std::size_t size)
  {
    total_consumed_ += size;

    Buffer_Iterator next = boost::asio::buffer_sequence_begin(buffers_);
    Buffer_Iterator end = boost::asio::buffer_sequence_end(buffers_);

    std::advance(next, next_elem_);
    while (next != end && size > 0)
    {
      Buffer next_buf = Buffer(*next) + next_elem_offset_;
      if (size < next_buf.size())
      {
        next_elem_offset_ += size;
        size = 0;
      }
      else
      {
        size -= next_buf.size();
        next_elem_offset_ = 0;
        ++next_elem_;
        ++next;
      }
    }
  }

  // Get the total number of bytes consumed from the buffers.
  std::size_t total_consumed() const
  {
    return total_consumed_;
  }

private:
  Buffers buffers_;
  std::size_t total_size_;
  std::size_t total_consumed_;
  std::size_t next_elem_;
  std::size_t next_elem_offset_;
};

// Base class of all consuming_buffers specialisations for single buffers.
template <typename Buffer>
class consuming_single_buffer
{
public:
  // Construct to represent the entire list of buffers.
  template <typename Buffer1>
  explicit consuming_single_buffer(const Buffer1& buffer)
    : buffer_(buffer),
      total_consumed_(0)
  {
  }

  // Determine if we are at the end of the buffers.
  bool empty() const
  {
    return total_consumed_ >= buffer_.size();
  }

  // Get the buffer for a single transfer, with a size.
  Buffer prepare(std::size_t max_size)
  {
    return boost::asio::buffer(buffer_ + total_consumed_, max_size);
  }

  // Consume the specified number of bytes from the buffers.
  void consume(std::size_t size)
  {
    total_consumed_ += size;
  }

  // Get the total number of bytes consumed from the buffers.
  std::size_t total_consumed() const
  {
    return total_consumed_;
  }

private:
  Buffer buffer_;
  std::size_t total_consumed_;
};

template <>
class consuming_buffers<mutable_buffer, mutable_buffer, const mutable_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_MUTABLE_BUFFER>
{
public:
  explicit consuming_buffers(const mutable_buffer& buffer)
    : consuming_single_buffer<BOOST_ASIO_MUTABLE_BUFFER>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer, mutable_buffer, const mutable_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>
{
public:
  explicit consuming_buffers(const mutable_buffer& buffer)
    : consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer, const_buffer, const const_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>
{
public:
  explicit consuming_buffers(const const_buffer& buffer)
    : consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>(buffer)
  {
  }
};

#if !defined(BOOST_ASIO_NO_DEPRECATED)

template <>
class consuming_buffers<mutable_buffer,
    mutable_buffers_1, const mutable_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_MUTABLE_BUFFER>
{
public:
  explicit consuming_buffers(const mutable_buffers_1& buffer)
    : consuming_single_buffer<BOOST_ASIO_MUTABLE_BUFFER>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer, mutable_buffers_1, const mutable_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>
{
public:
  explicit consuming_buffers(const mutable_buffers_1& buffer)
    : consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer, const_buffers_1, const const_buffer*>
  : public consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>
{
public:
  explicit consuming_buffers(const const_buffers_1& buffer)
    : consuming_single_buffer<BOOST_ASIO_CONST_BUFFER>(buffer)
  {
  }
};

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Buffer, typename Elem>
class consuming_buffers<Buffer, boost::array<Elem, 2>,
    typename boost::array<Elem, 2>::const_iterator>
{
public:
  // Construct to represent the entire list of buffers.
  explicit consuming_buffers(const boost::array<Elem, 2>& buffers)
    : buffers_(buffers),
      total_consumed_(0)
  {
  }

  // Determine if we are at the end of the buffers.
  bool empty() const
  {
    return total_consumed_ >=
      Buffer(buffers_[0]).size() + Buffer(buffers_[1]).size();
  }

  // Get the buffer for a single transfer, with a size.
  boost::array<Buffer, 2> prepare(std::size_t max_size)
  {
    boost::array<Buffer, 2> result = {{
      Buffer(buffers_[0]), Buffer(buffers_[1]) }};
    std::size_t buffer0_size = result[0].size();
    result[0] = boost::asio::buffer(result[0] + total_consumed_, max_size);
    result[1] = boost::asio::buffer(
        result[1] + (total_consumed_ < buffer0_size
          ? 0 : total_consumed_ - buffer0_size),
        max_size - result[0].size());
    return result;
  }

  // Consume the specified number of bytes from the buffers.
  void consume(std::size_t size)
  {
    total_consumed_ += size;
  }

  // Get the total number of bytes consumed from the buffers.
  std::size_t total_consumed() const
  {
    return total_consumed_;
  }

private:
  boost::array<Elem, 2> buffers_;
  std::size_t total_consumed_;
};

#if defined(BOOST_ASIO_HAS_STD_ARRAY)

template <typename Buffer, typename Elem>
class consuming_buffers<Buffer, std::array<Elem, 2>,
    typename std::array<Elem, 2>::const_iterator>
{
public:
  // Construct to represent the entire list of buffers.
  explicit consuming_buffers(const std::array<Elem, 2>& buffers)
    : buffers_(buffers),
      total_consumed_(0)
  {
  }

  // Determine if we are at the end of the buffers.
  bool empty() const
  {
    return total_consumed_ >=
      Buffer(buffers_[0]).size() + Buffer(buffers_[1]).size();
  }

  // Get the buffer for a single transfer, with a size.
  std::array<Buffer, 2> prepare(std::size_t max_size)
  {
    std::array<Buffer, 2> result = {{
      Buffer(buffers_[0]), Buffer(buffers_[1]) }};
    std::size_t buffer0_size = result[0].size();
    result[0] = boost::asio::buffer(result[0] + total_consumed_, max_size);
    result[1] = boost::asio::buffer(
        result[1] + (total_consumed_ < buffer0_size
          ? 0 : total_consumed_ - buffer0_size),
        max_size - result[0].size());
    return result;
  }

  // Consume the specified number of bytes from the buffers.
  void consume(std::size_t size)
  {
    total_consumed_ += size;
  }

  // Get the total number of bytes consumed from the buffers.
  std::size_t total_consumed() const
  {
    return total_consumed_;
  }

private:
  std::array<Elem, 2> buffers_;
  std::size_t total_consumed_;
};

#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

// Specialisation for null_buffers to ensure that the null_buffers type is
// always passed through to the underlying read or write operation.
template <typename Buffer>
class consuming_buffers<Buffer, null_buffers, const mutable_buffer*>
  : public boost::asio::null_buffers
{
public:
  consuming_buffers(const null_buffers&)
  {
    // No-op.
  }

  bool empty()
  {
    return false;
  }

  null_buffers prepare(std::size_t)
  {
    return null_buffers();
  }

  void consume(std::size_t)
  {
    // No-op.
  }

  std::size_t total_consumed() const
  {
    return 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CONSUMING_BUFFERS_HPP

/* consuming_buffers.hpp
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
*/