//
// buffered_write_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERED_WRITE_STREAM_HPP
#define BOOST_ASIO_BUFFERED_WRITE_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/buffered_write_stream_fwd.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffered_stream_storage.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/write.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Adds buffering to the write-related operations of a stream.
/**
 * The buffered_write_stream class template can be used to add buffering to the
 * synchronous and asynchronous write operations of a stream.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class buffered_write_stream
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
  explicit buffered_write_stream(Arg& a)
    : next_layer_(a),
      storage_(default_buffer_size)
  {
  }

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  buffered_write_stream(Arg& a, std::size_t buffer_size)
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

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation. Throws an
  /// exception on failure.
  std::size_t flush();

  /// Flush all data from the buffer to the next layer. Returns the number of
  /// bytes written to the next layer on the last write operation, or 0 if an
  /// error occurred.
  std::size_t flush(boost::system::error_code& ec);

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
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Write the given data to the stream. Returns the number of bytes written.
  /// Throws an exception on failure.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers);

  /// Write the given data to the stream. Returns the number of bytes written,
  /// or 0 if an error occurred and the error handler did not throw.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec);

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
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Read some data from the stream. Returns the number of bytes read. Throws
  /// an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    return next_layer_.read_some(buffers);
  }

  /// Read some data from the stream. Returns the number of bytes read or 0 if
  /// an error occurred.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return next_layer_.read_some(buffers, ec);
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
    return next_layer_.async_read_some(buffers,
        BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read.
  /// Throws an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    return next_layer_.peek(buffers);
  }

  /// Peek at the incoming data on the stream. Returns the number of bytes read,
  /// or 0 if an error occurred.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return next_layer_.peek(buffers, ec);
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail()
  {
    return next_layer_.in_avail();
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail(boost::system::error_code& ec)
  {
    return next_layer_.in_avail(ec);
  }

private:
  /// Copy data into the internal buffer from the specified source buffer.
  /// Returns the number of bytes copied.
  template <typename ConstBufferSequence>
  std::size_t copy(const ConstBufferSequence& buffers);

  /// The next layer.
  Stream next_layer_;

  // The data in the buffer.
  detail::buffered_stream_storage storage_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/buffered_write_stream.hpp>

#endif // BOOST_ASIO_BUFFERED_WRITE_STREAM_HPP

/* buffered_write_stream.hpp
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
*/