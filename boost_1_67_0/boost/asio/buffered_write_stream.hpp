//
// buffered_write_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
+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
*/