//
// detail/consuming_buffers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/registered_buffer.hpp>

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

template <>
class consuming_buffers<mutable_buffer,
    mutable_registered_buffer, const mutable_buffer*>
  : public consuming_single_buffer<mutable_registered_buffer>
{
public:
  explicit consuming_buffers(const mutable_registered_buffer& buffer)
    : consuming_single_buffer<mutable_registered_buffer>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer,
    mutable_registered_buffer, const mutable_buffer*>
  : public consuming_single_buffer<mutable_registered_buffer>
{
public:
  explicit consuming_buffers(const mutable_registered_buffer& buffer)
    : consuming_single_buffer<mutable_registered_buffer>(buffer)
  {
  }
};

template <>
class consuming_buffers<const_buffer,
    const_registered_buffer, const const_buffer*>
  : public consuming_single_buffer<const_registered_buffer>
{
public:
  explicit consuming_buffers(const const_registered_buffer& buffer)
    : consuming_single_buffer<const_registered_buffer>(buffer)
  {
  }
};

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