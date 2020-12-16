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
6TLaR/vpAF1OV9CVdJDuSFfR1XQNHaLDdITuREfpGB2na+k6ujNdTzfQXeiudDe6O92DFuietEgnaImWaYVO0ik6Tat0L7qR1ugMrdMGnaV70yYNaIu26Sa6mW6hW+k+dF+6H92fHkAPpAfRg+kh9FB6GD2cHkGPpEfRo+kx9Fh6HD2enkBPpCfRk+kp9FR6Gj2dnkHPpGfRs+k59Fx6Hj2fXkAvpBfRi+kl9FJ6Gb2cXkGvpFfRq+k19Fp6Hb2e3kBvpDfRm+kt9FZ6G72d3kHvpHfRu+k99F56H72fPkAfpA/Rh+kj9FH6GH2cPkGfpE/Rp+kz9Fn6HH2efoZ+ln6Ofp5+gX6Rfol+mX6FfpV+jX6dfoN+k36Lfpt+h36Xfo9+n/6A/pD+iP6Y/oT+lP6M/pz+gv6S/or+mv6G/pb+jv6e/oH+kf6J/pn+hf6V/o3+nf6D/pP+i/6b/of+Fxf7XsRezF7CXspexl7OPEYYZYxxJphkivnsFeyV7FXs1ew17LXsdez17A3sjexN7M3sLeyt7G3s7ewd7J3sXezd7D3svex97P3sA+yD7EPsw+wj7KPsY+zjbAHrZj1sIVvEFrMlbBu2lG3LPsE+yT7FPs22Y9uzHVgvW8b6WD8bYMvZCraSDbId2Sq2mq1hQ2yYjbCd2CgbY+NsLVvHdmbr2Qa2C9uV7cZ2Z3uwAtuTFdkEK7Eyq7BJNsWmWZXtxTayGpthddZgs2xv1mQBa7E228Q2sy1sK9uH7cv2Y/uzA9iB7CB2MDuEHcoOY4ezI9iR7Ch2NDuGHcuOY8ezE9iJ7CR2MjuFncpOY6ezM9iZ7Cx2NjuHncvOY+ezC9iF7CJ2MbuEXcouY5ezK9iV7Cp2NbuGXcuuY9ezG9iN7CZ2M7uF3cpuY7ezO9id7C52N7uH3cvuY/ezB9iD7CH2MHuEPcoeY4+zJ9iT7Cn2NHuGPcueY8+zz7DPss+xz7MvsC+yL7Evs6+wr7Kvsa+zb7Bvsm+xb7PvsO+y77Hvsx+wH7IfsR+zn7Cfsp+xn7NfsF+yX7Ffs9+w37Lfsd+zP7A/sj+xP7O/sL+yv7G/s3+wf7J/sX+z/7D/4lLvi/iL+Uv4S/nL+Mu5xwmnnHHOBZdccZ+/gr+Sv4q/mr+Gv5a/jr+ev4G/kb+Jv5m/hb+Vv42/nb+Dv5O/i7+bv4e/l7+Pv59/gH+Qf4h/mH+Ef5R/jH+cL+DdvIcv5Iv4Yr6Eb8OX8m35J/gn+af4p/l2fHu+A+/ly3gf7+cDfDlfwVfyQb4jX8VX8zV8iA/zEb4TH+VjfJyv5ev4znw938B34bvy3fjufA9e4HvyIp/gJV7mFT7Jp/g0r/K9+EZe4zO8zht8lu/NmzzgLd7mm/hmvoVv5fvwffl+fH9+AD+QH8QP5ofwQ/lh/HB+BD+SH8WP5sfwY/lx/Hh+Aj+Rn8RP5qfwU/lp/HR+Bj+Tn8XP5ufwc/l5/Hx+Ab+QX8Qv5pfwS/ll/HJ+Bb+SX8Wv5tfwa/l1/Hp+A7+R38Rv5rfwW/lt/HZ+B7+T38Xv5vfwe/l9/H7+AH+QP8Qf5o/wR/lj/HH+BH+SP8Wf5s/wZ/lz/Hn+Gf5Z/jn+ef4F/kX+Jf5l/hX+Vf41/nX+Df5N/i3+bf4d/l3+Pf59/gP+Q/4j/mP+E/5T/jP+c/4L/kv+K/5r/hv+W/47/nv+B/5H/if+Z/4X/lf+N/53/g/+T/4v/m/+H/5fXOh/kXixeIl4qXiZeLnwBBFUMMGFEFIo4YtXiFeKV4lXi9eI14rXideLN4g3ijeJN4u3iLeKt4m3i3eId4p3iXeL94j3iveJ94sPiA+KD4kPi4+Ij4qPiY+LBaI=
*/