//
// buffered_read_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  /**
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   */
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
  /**
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   */
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
  /**
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   */
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