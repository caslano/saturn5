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
pWM75P5ltdSXNvebsZo2+6j7lrluJH/JZPiae+/mOTt4CyTmEeNVUqyPPoD/vfPggW1mTsA2Xuxo7gsSa5n4PhJcbcU+6NhqbGyV1sdJtWAz9rC0SZXw8MLv1ix8kgQds4ffIQ2gbj1lL7qRy8ocCd/zsMF9BdCE70b4DxyDfZz4EP77sNmaTOxI+zrqzcpn7Oe8DbprQT68+iHHq9CrofwxbBTXH16j8fE4ZO8PTXz/RTwxbcM+xhZj4OfGjuaZv5cy/PkBMmWQ58Bmi4bDZzRl5O+B3h3muWklY4K5twzNImTZBRonYnfo/4Q2T5s95wNpi29WmP2C8Gsz9xvg9SR0ruB4uNl/gu2+xJZDqbPOI7WDAxZs38ZYVyaNh5YbX8ZD/zP4xbiJa3R+Abp9KtDdXHMmsB7Gz1VmbQTdryZgQ9IbGqHLcQL0JicyLpj9kOZ+jI/xNIf2DVK4lzj1EBfETC+z18cNz3Hk25CRNtPR00ZeT5Bv9sTbsSHy/NT0ibGsV+irZcRX4QxiFd2PI73CPG/k+Crovkec5Zr7NfC7Ffp8RkM7M1j3lEvR5jluKf2MNk5sNQa6i5MkFz75FW3Pms4cAJIpX4ZvNpl7PPC8ZwRjxWTsDE6fic3NfkOvtK+CMQmcMYA1TxG+dSEP9S+C7kngh8hyYipji0W60yb1Nf//MetVK7aFf9gsdDTzI/x+g/1mOokVZJ4B7xXZyJ7GGmq8dDt+dprrbNp8ynmRW4qkzA4+9eHfeGiUIhM2OJ+ypDnYmzaVzNFbzV4Q7LHai2wjyW/E/8PxtdlfgXyv4MdqZJhPng89f478jxqbmj1h5nqpUIopQQbaRpYjNzym5+O3Fukas29pAHpTp53jz7HXUsqem4ntaX/TcOgOwa512BR5/oAseejZN4GxxMN4Yf5/Ql0LdhhL+SkWxpwK4r4WO0OvELoeeD9BPwyfRgyWYm/znyVifRJ+a0L2pHgpEl7nEYt9nNjBSr+G75P4YwHnb2Qx/6TiC2ywBfled0n7reiGLfekSKt8jGHQfcTcq0OWk7BdfJzUbpNixmAL7DECma/EXj3g5aGszfz/IE+qQKarsWevYfCG/i/noh/HscjyNfhwIDQ9+B5dflRJLKP/QOr9uYpxlHZrzd4GdJ9VDN9JUoePmEaGNvKj5sCT+ndgzzeRvxFbNMDv58OxE+XxyNYC3X3GtxnEL8fz0NlWQqwmUNdGX2mDJrKPgfbZlB2AzzjkmgyaKfs1vKPNvrkZyJpB+1zJ7qMfxUsr0fdct7SJGPmgH+W0/30adsaeFcTAdyk/hbpvW6RY6P7RrNvRv406d1cTP+aZJPke2vfIQBbzXzA766LZ1KV9TSIy2NEHHxZjj9ZSaZHpc3HSa1nUhecE9N3QhO2gk0jfcRchP8e3E3MZJ6A35S4z5lRIT5t7FzboUf8vtB2YTRwQs+uoM8aDD2n3V/K/55UKsNUrxFsRNPaTPoON+pm9Nxy/gdyfQ2vNLGhjm1dbsGcZsY4OtWZNin9yCokjcEsqthwvRbRKm2vRkfNJbvSLZ35Bz1TsPIOyp5D3nRqpRy350F5B2chC6iFbM3xiE4lRyhfA6zpi9B47tseP75q5lLJd+Hqbg36GfDemSJbJtEOmvdAbhl36N0hboJkF/wTqrc1H1zzJh10/cWEX6pVT72Hz3MwiNRRhQ/J3Y6sLxxFj9ehNm9eH4LtmgA1q4d87AfuTd5+55wbvm8Cz+H1AOvFPuxXwjSlg3IKuN4m1Vit29Elh8LqkgjnQh23NHqQ6afsMfGKeESJXI35OMc9jzHhrZ6yA59mjoGOeD8JjK/kX2RgTzH8uzLqVsqWVUhI=
*/