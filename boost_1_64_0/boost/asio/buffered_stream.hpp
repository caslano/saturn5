//
// buffered_stream.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
klZPqKcRry5e1rxB3m+n46VyOj5iiXbkQpAtb1xcKT3J24dKTOOPBdidWZo++ZFVu34TTV2OxJvlHB1fqwuRS3zSc9bS/AxYXppMF8cmytiOa+fHGfBleXe0nq9sm8VHiYoa/UyhtD9Ppyml8YjJJ5nteFEbw32IMl+2Uie8PGPOlF9tBTpe3gfeCS/dq2O+71XBlC8v2DLjpdhO+eJiQ8bCtnwmnMGIN+sr89fXd4nFg+XxqQ740qgJT1etd5ZXb9iOCb/QLk9ePGbGd7ZXk51Op9MXlRnxUpKWTxeZZdOSNoVXV60b8ZKjYz6/Hg//3CjfKKeEKiWDA6WPJywCQ4HOK1wRZqFzR/YmPRQN6S6TYSR+OW/I0vNnxifzikTLp47flh8gInFiGkhCJ19u2EuuU4799OGXoZOaEcS8YyErXZulXRIF4l451WXVvNOJScwc6sAS7XwSeT6i4VYtmR+spnm4rh3PQZT56rKujpR8hZfk0r3qjN98l6x6sneaVd1acspenFSQGzPS8OYLcxOV5XmzFl8FWrQKpPyVgDlJnt20sJvSWYfm/DCyKduUb1XrlKvjiU3Hs1RhruexJduzhBu1V0aeZXhP23yuY3KcpTCzpFRmVuck6haQeNVUhBfDjXZejjrHy3MbLj9802GsqsrRz6MQp3e2PC+dH9f9Tm4mzk8kV8U2E2nyaJmvVFXYjvfCJWc5x3U36Uz6XK74iM1gOmwIjvJWk2MoPDsIsO3oGLO0owWpg+/E/ZfURoZ81jTkqxMdURPuaQIvz3PTz/eQeD+gRtPwQYW1H3Kfvf9tw3zREO14VDLVN435VjJ9iwbRjsw009NCzZAvzwFNrsTkp6hGneiCsGbGK9urOhvoItuLLc1J+LI76S9Js6Aj+KdTDivvxUseSQzDVnfPlahXF8+VTSRLn0PAJ8vZibkji1Mb8LnLabbp48TV43M96um5lS70TO9POvQwuR793TvSy3ApEN+BDADAa3ar/ZrthN+m4cdpX/qwhp9I7bd85zaEpz2hixH9pe6i8I/j+hrwjweAmxvwTwCAmxnwTwSAnQb8kwCgYsA/L6XnE66k8C+leul2eBnhdTu8nOyTtgOHF5D8w0CB8NcZEPhtGv66hH9BfxZ/PcI/V8NbhH+ehr8+4Z+v4W9K+N0DWfzXCf9FDf8Nwn8phe83tS/hPzmg8H+8Wm/7ff/q0E0/CyrZDbTFOxYnDvbCTwOKKfT1ATyqT+3vnnwL7ZNSfI7iTCAfqsLGYRtk3zdZb6X3AhQ/962bkx8S3IjS50je4NtE/Nq3dZb/Aa7P22W+OZS5TVL6n30nvbekeMe7DPxU513QeyiSvJMUB1K+sYyNQwsATgPAlaX+7yL9Kd7x7s72qcPGgdONkvxLcv1J3hmKP7OR/Pdk8/mY8hyEa5O8115Eer6X7PLezvJWDHg+Fj2zX30ncm6T8vgY9iyEQZJ3lvjPU3z4fWZ5Z3jZBjwf+56NcJjkXbRJef+qsNG40qBtRn1cudGAtJ8I5z9C39l+lPz5o53t/dpN6BPg43IYxF2sRyaOyx3M1M7lLrG2bdv/blTLcSPo6jzFlFx32SB2aN8F1Ce/x9mgXFp9q0UTR/RQDt+w2+P0QM+avdFnV4k7I7Xktm6wM7qBlVpxb0+Ng+L5Z0bWRR4kLhHFtQfibvXgeT3eU5zwoZ9fEJ/YuOrpHlvOl5xnVmteGN/SBfL1fn5asi/R673PK8kLvAzTHQYEyHCjB9C5sBTr4eTBy3a1Xjt3m+7oug3nSd5hKv+1FJ88tPly+BnWQEHeS8dxdJfDhnbl21T4T9k23EgnbfuZ2wo9d4yK+Mzh9fU+P3o=
*/