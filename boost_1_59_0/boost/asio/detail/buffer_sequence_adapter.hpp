//
// detail/buffer_sequence_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/registered_buffer.hpp>

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
  enum { is_single_buffer = false };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 8192 };

  static Buffer linearise(const Buffers& buffer_sequence,
      const boost::asio::mutable_buffer& storage)
  {
    return buffer_sequence_adapter::linearise(
        boost::asio::buffer_sequence_begin(buffer_sequence),
        boost::asio::buffer_sequence_end(buffer_sequence), storage);
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

  template <typename Iterator>
  static Buffer linearise(Iterator begin, Iterator end,
      const boost::asio::mutable_buffer& storage)
  {
    boost::asio::mutable_buffer unused_storage = storage;
    Iterator iter = begin;
    while (iter != end && unused_storage.size() != 0)
    {
      Buffer buffer(*iter);
      ++iter;
      if (buffer.size() == 0)
        continue;
      if (unused_storage.size() == storage.size())
      {
        if (iter == end)
          return buffer;
        if (buffer.size() >= unused_storage.size())
          return buffer;
      }
      unused_storage += boost::asio::buffer_copy(unused_storage, buffer);
    }
    return Buffer(storage.data(), storage.size() - unused_storage.size());
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
  enum { is_single_buffer = true };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(const boost::asio::mutable_buffer& buffer_sequence,
      const Buffer&)
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
  enum { is_single_buffer = true };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(const boost::asio::const_buffer& buffer_sequence,
      const Buffer&)
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
  enum { is_single_buffer = true };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(const boost::asio::mutable_buffers_1& buffer_sequence,
      const Buffer&)
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
  enum { is_single_buffer = true };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(const boost::asio::const_buffers_1& buffer_sequence,
      const Buffer&)
  {
    return Buffer(buffer_sequence);
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
};

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::mutable_registered_buffer>
  : buffer_sequence_adapter_base
{
public:
  enum { is_single_buffer = true };
  enum { is_registered_buffer = true };

  explicit buffer_sequence_adapter(
      const boost::asio::mutable_registered_buffer& buffer_sequence)
  {
    init_native_buffer(buffer_, buffer_sequence.buffer());
    total_buffer_size_ = buffer_sequence.size();
    registered_id_ = buffer_sequence.id();
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

  registered_buffer_id registered_id() const
  {
    return registered_id_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(
      const boost::asio::mutable_registered_buffer& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(
      const boost::asio::mutable_registered_buffer& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(
      const boost::asio::mutable_registered_buffer& buffer_sequence)
  {
    return Buffer(buffer_sequence.buffer());
  }

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(
      const boost::asio::mutable_registered_buffer& buffer_sequence,
      const Buffer&)
  {
    return Buffer(buffer_sequence.buffer());
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
  registered_buffer_id registered_id_;
};

template <typename Buffer>
class buffer_sequence_adapter<Buffer, boost::asio::const_registered_buffer>
  : buffer_sequence_adapter_base
{
public:
  enum { is_single_buffer = true };
  enum { is_registered_buffer = true };

  explicit buffer_sequence_adapter(
      const boost::asio::const_registered_buffer& buffer_sequence)
  {
    init_native_buffer(buffer_, buffer_sequence.buffer());
    total_buffer_size_ = buffer_sequence.size();
    registered_id_ = buffer_sequence.id();
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

  registered_buffer_id registered_id() const
  {
    return registered_id_;
  }

  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }

  static bool all_empty(
      const boost::asio::const_registered_buffer& buffer_sequence)
  {
    return buffer_sequence.size() == 0;
  }

  static void validate(
      const boost::asio::const_registered_buffer& buffer_sequence)
  {
    buffer_sequence.data();
  }

  static Buffer first(
      const boost::asio::const_registered_buffer& buffer_sequence)
  {
    return Buffer(buffer_sequence.buffer());
  }

  enum { linearisation_storage_size = 1 };

  static Buffer linearise(
      const boost::asio::const_registered_buffer& buffer_sequence,
      const Buffer&)
  {
    return Buffer(buffer_sequence.buffer());
  }

private:
  native_buffer_type buffer_;
  std::size_t total_buffer_size_;
  registered_buffer_id registered_id_;
};

template <typename Buffer, typename Elem>
class buffer_sequence_adapter<Buffer, boost::array<Elem, 2> >
  : buffer_sequence_adapter_base
{
public:
  enum { is_single_buffer = false };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 8192 };

  static Buffer linearise(const boost::array<Elem, 2>& buffer_sequence,
      const boost::asio::mutable_buffer& storage)
  {
    if (buffer_sequence[0].size() == 0)
      return Buffer(buffer_sequence[1]);
    if (buffer_sequence[1].size() == 0)
      return Buffer(buffer_sequence[0]);
    return Buffer(storage.data(),
        boost::asio::buffer_copy(storage, buffer_sequence));
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
  enum { is_single_buffer = false };
  enum { is_registered_buffer = false };

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

  registered_buffer_id registered_id() const
  {
    return registered_buffer_id();
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

  enum { linearisation_storage_size = 8192 };

  static Buffer linearise(const std::array<Elem, 2>& buffer_sequence,
      const boost::asio::mutable_buffer& storage)
  {
    if (buffer_sequence[0].size() == 0)
      return Buffer(buffer_sequence[1]);
    if (buffer_sequence[1].size() == 0)
      return Buffer(buffer_sequence[0]);
    return Buffer(storage.data(),
        boost::asio::buffer_copy(storage, buffer_sequence));
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