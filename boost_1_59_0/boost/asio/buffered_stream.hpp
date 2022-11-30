//
// buffered_stream.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERED_STREAM_HPP
#define BOOST_ASIO_BUFFERED_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffered_read_stream.hpp>
#include <boost/asio/buffered_write_stream.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Adds buffering to the read- and write-related operations of a stream.
/**
 * The buffered_stream class template can be used to add buffering to the
 * synchronous and asynchronous read and write operations of a stream.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class buffered_stream
  : private noncopyable
{
public:
  /// The type of the next layer.
  typedef typename remove_reference<Stream>::type next_layer_type;

  /// The type of the lowest layer.
  typedef typename next_layer_type::lowest_layer_type lowest_layer_type;

  /// The type of the executor associated with the object.
  typedef typename lowest_layer_type::executor_type executor_type;

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_stream(Arg& a)
    : inner_stream_impl_(a),
      stream_impl_(inner_stream_impl_)
  {
  }

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_stream(Arg& a, std::size_t read_buffer_size,
      std::size_t write_buffer_size)
    : inner_stream_impl_(a, write_buffer_size),
      stream_impl_(inner_stream_impl_, read_buffer_size)
  {
  }

  /// Get a reference to the next layer.
  next_layer_type& next_layer()
  {
    return stream_impl_.next_layer().next_layer();
  }

  /// Get a reference to the lowest layer.
  lowest_layer_type& lowest_layer()
  {
    return stream_impl_.lowest_layer();
  }

  /// Get a const reference to the lowest layer.
  const lowest_layer_type& lowest_layer() const
  {
    return stream_impl_.lowest_layer();
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return stream_impl_.lowest_layer().get_executor();
  }

  /// Close the stream.
  void close()
  {
    stream_impl_.close();
  }

  /// Close the stream.
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    stream_impl_.close(ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation. Throws an
  /// exception on failure.
  std::size_t flush()
  {
    return stream_impl_.next_layer().flush();
  }

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation, or 0 if an
  /// error occurred.
  std::size_t flush(boost::system::error_code& ec)
  {
    return stream_impl_.next_layer().flush(ec);
  }

  /// Start an asynchronous flush.
  /**
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_flush(
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.next_layer().async_flush(
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Write the given data to the stream. Returns the number of bytes written.
  /// Throws an exception on failure.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return stream_impl_.write_some(buffers);
  }

  /// Write the given data to the stream. Returns the number of bytes written,
  /// or 0 if an error occurred.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.write_some(buffers, ec);
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
    return stream_impl_.async_write_some(buffers,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation. Throws an exception on failure.
  std::size_t fill()
  {
    return stream_impl_.fill();
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation, or 0 if an error occurred.
  std::size_t fill(boost::system::error_code& ec)
  {
    return stream_impl_.fill(ec);
  }

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
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.async_fill(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
  }

  /// Read some data from the stream. Returns the number of bytes read. Throws
  /// an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    return stream_impl_.read_some(buffers);
  }

  /// Read some data from the stream. Returns the number of bytes read or 0 if
  /// an error occurred.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.read_some(buffers, ec);
  }

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
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return stream_impl_.async_read_some(buffers,
        BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read.
  /// Throws an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    return stream_impl_.peek(buffers);
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read,
  /// or 0 if an error occurred.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return stream_impl_.peek(buffers, ec);
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail()
  {
    return stream_impl_.in_avail();
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail(boost::system::error_code& ec)
  {
    return stream_impl_.in_avail(ec);
  }

private:
  // The buffered write stream.
  typedef buffered_write_stream<Stream> write_stream_type;
  write_stream_type inner_stream_impl_;

  // The buffered read stream.
  typedef buffered_read_stream<write_stream_type&> read_stream_type;
  read_stream_type stream_impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BUFFERED_STREAM_HPP

/* buffered_stream.hpp
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
*/