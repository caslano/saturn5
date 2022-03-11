//
// buffered_read_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERED_READ_STREAM_HPP
#define BOOST_ASIO_BUFFERED_READ_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_resize_guard.hpp>
#include <boost/asio/detail/buffered_stream_storage.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Adds buffering to the read-related operations of a stream.
/**
 * The buffered_read_stream class template can be used to add buffering to the
 * synchronous and asynchronous read operations of a stream.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class buffered_read_stream
  : private noncopyable
{
public:
  /// The type of the next layer.
  typedef typename remove_reference<Stream>::type next_layer_type;

  /// The type of the lowest layer.
  typedef typename next_layer_type::lowest_layer_type lowest_layer_type;

  /// The type of the executor associated with the object.
  typedef typename lowest_layer_type::executor_type executor_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The default buffer size.
  static const std::size_t default_buffer_size = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(std::size_t, default_buffer_size = 1024);
#endif

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_read_stream(Arg& a)
    : next_layer_(a),
      storage_(default_buffer_size)
  {
  }

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  buffered_read_stream(Arg& a, std::size_t buffer_size)
    : next_layer_(a),
      storage_(buffer_size)
  {
  }

  /// Get a reference to the next layer.
  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  /// Get a reference to the lowest layer.
  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  /// Get a const reference to the lowest layer.
  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return next_layer_.lowest_layer().get_executor();
  }

  /// Close the stream.
  void close()
  {
    next_layer_.close();
  }

  /// Close the stream.
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    next_layer_.close(ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Write the given data to the stream. Returns the number of bytes written.
  /// Throws an exception on failure.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return next_layer_.write_some(buffers);
  }

  /// Write the given data to the stream. Returns the number of bytes written,
  /// or 0 if an error occurred.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return next_layer_.write_some(buffers, ec);
  }

  /// Start an asynchronous write. The data being written must be valid for the
  /// lifetime of the asynchronous operation.
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return next_layer_.async_write_some(buffers,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation. Throws an exception on failure.
  std::size_t fill();

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation, or 0 if an error occurred.
  std::size_t fill(boost::system::error_code& ec);

  /// Start an asynchronous fill.
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_fill(
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Read some data from the stream. Returns the number of bytes read. Throws
  /// an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers);

  /// Read some data from the stream. Returns the number of bytes read or 0 if
  /// an error occurred.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec);

  /// Start an asynchronous read. The buffer into which the data will be read
  /// must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Peek at the incoming data on the stream. Returns the number of bytes read.
  /// Throws an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers);

  /// Peek at the incoming data on the stream. Returns the number of bytes read,
  /// or 0 if an error occurred.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers,
      boost::system::error_code& ec);

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail()
  {
    return storage_.size();
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail(boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    return storage_.size();
  }

private:
  /// Copy data out of the internal buffer to the specified target buffer.
  /// Returns the number of bytes copied.
  template <typename MutableBufferSequence>
  std::size_t copy(const MutableBufferSequence& buffers)
  {
    std::size_t bytes_copied = boost::asio::buffer_copy(
        buffers, storage_.data(), storage_.size());
    storage_.consume(bytes_copied);
    return bytes_copied;
  }

  /// Copy data from the internal buffer to the specified target buffer, without
  /// removing the data from the internal buffer. Returns the number of bytes
  /// copied.
  template <typename MutableBufferSequence>
  std::size_t peek_copy(const MutableBufferSequence& buffers)
  {
    return boost::asio::buffer_copy(buffers, storage_.data(), storage_.size());
  }

  /// The next layer.
  Stream next_layer_;

  // The data in the buffer.
  detail::buffered_stream_storage storage_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/buffered_read_stream.hpp>

#endif // BOOST_ASIO_BUFFERED_READ_STREAM_HPP

/* buffered_read_stream.hpp
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
*/