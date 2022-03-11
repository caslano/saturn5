//
// detail/buffer_sequence_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BUFFER_SEQUENCE_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_BUFFER_SEQUENCE_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/array_fwd.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class buffer_sequence_adapter_base
{
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
public:
  // The maximum number of buffers to support in a single operation.
  enum { max_buffers = 1 };

protected:
  typedef Windows::Storage::Streams::IBuffer^ native_buffer_type;

  BOOST_ASIO_DECL static void init_native_buffer(
      native_buffer_type& buf,
      const boost::asio::mutable_buffer& buffer);

  BOOST_ASIO_DECL static void init_native_buffer(
      native_buffer_type& buf,
      const boost::asio::const_buffer& buffer);
#elif defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
public:
  // The maximum number of buffers to support in a single operation.
  enum { max_buffers = 64 < max_iov_len ? 64 : max_iov_len };

protected:
  typedef WSABUF native_buffer_type;

  static void init_native_buffer(WSABUF& buf,
      const boost::asio::mutable_buffer& buffer)
  {
    buf.buf = static_cast<char*>(buffer.data());
    buf.len = static_cast<ULONG>(buffer.size());
  }

  static void init_native_buffer(WSABUF& buf,
      const boost::asio::const_buffer& buffer)
  {
    buf.buf = const_cast<char*>(static_cast<const char*>(buffer.data()));
    buf.len = static_cast<ULONG>(buffer.size());
  }
#else // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
public:
  // The maximum number of buffers to support in a single operation.
  enum { max_buffers = 64 < max_iov_len ? 64 : max_iov_len };

protected:
  typedef iovec native_buffer_type;

  static void init_iov_base(void*& base, void* addr)
  {
    base = addr;
  }

  template <typename T>
  static void init_iov_base(T& base, void* addr)
  {
    base = static_cast<T>(addr);
  }

  static void init_native_buffer(iovec& iov,
      const boost::asio::mutable_buffer& buffer)
  {
    init_iov_base(iov.iov_base, buffer.data());
    iov.iov_len = buffer.size();
  }

  static void init_native_buffer(iovec& iov,
      const boost::asio::const_buffer& buffer)
  {
    init_iov_base(iov.iov_base, const_cast<void*>(buffer.data()));
    iov.iov_len = buffer.size();
  }
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
};

// Helper class to translate buffers into the native buffer representation.
template <typename Buffer, typename Buffers>
class buffer_sequence_adapter
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(const Buffers& buffer_sequence)
    : count_(0), total_buffer_size_(0)
  {
    buffer_sequence_adapter::init(
        boost::asio::buffer_sequence_begin(buffer_sequence),
        boost::asio::buffer_sequence_end(buffer_sequence));
  }

  native_buffer_type* buffers()
  {
    return buffers_;
  }

  std::size_t count() const
  {
    return count_;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const Buffers& buffer_sequence)
  {
    return buffer_sequence_adapter::all_empty(
        boost::asio::buffer_sequence_begin(buffer_sequence),
        boost::asio::buffer_sequence_end(buffer_sequence));
  }

  static void validate(const Buffers& buffer_sequence)
  {
    buffer_sequence_adapter::validate(
        boost::asio::buffer_sequence_begin(buffer_sequence),
        boost::asio::buffer_sequence_end(buffer_sequence));
  }

  static Buffer first(const Buffers& buffer_sequence)
  {
    return buffer_sequence_adapter::first(
        boost::asio::buffer_sequence_begin(buffer_sequence),
        boost::asio::buffer_sequence_end(buffer_sequence));
  }

private:
  template <typename Iterator>
  void init(Iterator begin, Iterator end)
  {
    Iterator iter = begin;
    for (; iter != end && count_ < max_buffers; ++iter, ++count_)
    {
      Buffer buffer(*iter);
      init_native_buffer(buffers_[count_], buffer);
      total_buffer_size_ += buffer.size();
    }
  }

  template <typename Iterator>
  static bool all_empty(Iterator begin, Iterator end)
  {
    Iterator iter = begin;
    std::size_t i = 0;
    for (; iter != end && i < max_buffers; ++iter, ++i)
      if (Buffer(*iter).size() > 0)
        return false;
    return true;
  }

  template <typename Iterator>
  static void validate(Iterator begin, Iterator end)
  {
    Iterator iter = begin;
    for (; iter != end; ++iter)
    {
      Buffer buffer(*iter);
      buffer.data();
    }
  }

  template <typename Iterator>
  static Buffer first(Iterator begin, Iterator end)
  {
    Iterator iter = begin;
    for (; iter != end; ++iter)
    {
      Buffer buffer(*iter);
      if (buffer.size() != 0)
        return buffer;
    }
    return Buffer();
  }

  native_buffer_type buffers_[max_buffers];
  std::size_t count_;
  std::size_t total_buffer_size_;
};

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::mutable_buffer>
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const boost::asio::mutable_buffer& buffer_sequence)
  {
    init_native_buffer(buffer_, Buffer(buffer_sequence));
    total_buffer_size_ = buffer_sequence.size();
  }

  native_buffer_type* buffers()
  {
    return &buffer_;
  }

  std::size_t count() const
  {
    return 1;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const boost::asio::mutable_buffer& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(const boost::asio::mutable_buffer& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(const boost::asio::mutable_buffer& buffer_sequence)
  {
    return Buffer(buffer_sequence);
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
};

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::const_buffer>
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const boost::asio::const_buffer& buffer_sequence)
  {
    init_native_buffer(buffer_, Buffer(buffer_sequence));
    total_buffer_size_ = buffer_sequence.size();
  }

  native_buffer_type* buffers()
  {
    return &buffer_;
  }

  std::size_t count() const
  {
    return 1;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const boost::asio::const_buffer& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(const boost::asio::const_buffer& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(const boost::asio::const_buffer& buffer_sequence)
  {
    return Buffer(buffer_sequence);
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
};

#if !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::mutable_buffers_1>
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const boost::asio::mutable_buffers_1& buffer_sequence)
  {
    init_native_buffer(buffer_, Buffer(buffer_sequence));
    total_buffer_size_ = buffer_sequence.size();
  }

  native_buffer_type* buffers()
  {
    return &buffer_;
  }

  std::size_t count() const
  {
    return 1;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const boost::asio::mutable_buffers_1& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(const boost::asio::mutable_buffers_1& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(const boost::asio::mutable_buffers_1& buffer_sequence)
  {
    return Buffer(buffer_sequence);
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
};

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::const_buffers_1>
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const boost::asio::const_buffers_1& buffer_sequence)
  {
    init_native_buffer(buffer_, Buffer(buffer_sequence));
    total_buffer_size_ = buffer_sequence.size();
  }

  native_buffer_type* buffers()
  {
    return &buffer_;
  }

  std::size_t count() const
  {
    return 1;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const boost::asio::const_buffers_1& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(const boost::asio::const_buffers_1& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(const boost::asio::const_buffers_1& buffer_sequence)
  {
    return Buffer(buffer_sequence);
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
};

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Buffer, typename Elem>
class buffer_sequence_adapter<Buffer, boost::array<Elem, 2> >
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const boost::array<Elem, 2>& buffer_sequence)
  {
    init_native_buffer(buffers_[0], Buffer(buffer_sequence[0]));
    init_native_buffer(buffers_[1], Buffer(buffer_sequence[1]));
    total_buffer_size_ = buffer_sequence[0].size() + buffer_sequence[1].size();
  }

  native_buffer_type* buffers()
  {
    return buffers_;
  }

  std::size_t count() const
  {
    return 2;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const boost::array<Elem, 2>& buffer_sequence)
  {
    return buffer_sequence[0].size() == 0 && buffer_sequence[1].size() == 0;
  }

  static void validate(const boost::array<Elem, 2>& buffer_sequence)
  {
    buffer_sequence[0].data();
    buffer_sequence[1].data();
  }

  static Buffer first(const boost::array<Elem, 2>& buffer_sequence)
  {
    return Buffer(buffer_sequence[0].size() != 0
        ? buffer_sequence[0] : buffer_sequence[1]);
  }

private:
  native_buffer_type buffers_[2];
  std::size_t total_buffer_size_;
};

#if defined(BOOST_ASIO_HAS_STD_ARRAY)

template <typename Buffer, typename Elem>
class buffer_sequence_adapter<Buffer, std::array<Elem, 2> >
  : buffer_sequence_adapter_base
{
public:
  explicit buffer_sequence_adapter(
      const std::array<Elem, 2>& buffer_sequence)
  {
    init_native_buffer(buffers_[0], Buffer(buffer_sequence[0]));
    init_native_buffer(buffers_[1], Buffer(buffer_sequence[1]));
    total_buffer_size_ = buffer_sequence[0].size() + buffer_sequence[1].size();
  }

  native_buffer_type* buffers()
  {
    return buffers_;
  }

  std::size_t count() const
  {
    return 2;
  }

  std::size_t total_size() const
  {
    return total_buffer_size_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(const std::array<Elem, 2>& buffer_sequence)
  {
    return buffer_sequence[0].size() == 0 && buffer_sequence[1].size() == 0;
  }

  static void validate(const std::array<Elem, 2>& buffer_sequence)
  {
    buffer_sequence[0].data();
    buffer_sequence[1].data();
  }

  static Buffer first(const std::array<Elem, 2>& buffer_sequence)
  {
    return Buffer(buffer_sequence[0].size() != 0
        ? buffer_sequence[0] : buffer_sequence[1]);
  }

private:
  native_buffer_type buffers_[2];
  std::size_t total_buffer_size_;
};

#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/buffer_sequence_adapter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_BUFFER_SEQUENCE_ADAPTER_HPP

/* buffer_sequence_adapter.hpp
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
*/