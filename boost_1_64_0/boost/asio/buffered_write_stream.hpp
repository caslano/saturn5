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
42jsivKmm1XXkZeApurjN/jHu7I9k1uvsRjZoEfp3YVenmRTfBEmk4Kkhqo/lNg9WnSTNoW1d4WjQeDRKqPgo3FW4o3ne01cgwkT+qebGK3VeyV931Toe2zecVqB3YypHyf8EWOjXuSrdV3EQloapseHUit5pk6GGc2nFF9KRZDhFFs9xhfOMu2Mpqmk/ERuhs5uodlDN15VnWB27TZ49d3pDInHYcb1M991q1JMEmS59DpWlW9pkvgoG6VULtpuxn8iYZhRL864K7Bm3cYWqpZS45jBnqMedYdlJt1W1s/n84033az5YUN9wexGUYuFqriqy/17qeVGdXogytRvOiHXi8ne346+dJQ8KLl30nUKPl/d29hXI6BQ97GFDS1P5YxxNsvAp/xcvi2PyK4e9Xzpr15sG1qK5OO0ZGXpG6K2hvZOhh2XyeeR5Aa64h0WpnMzEzOa3pleleFr80P0EL36Ds3pKXmjktzcU9L3vh0pHAUATOR4aslpiHmtJnqtoiskdGOT4qY9Se8oeuZU9PvkcoFNLjw2KVbE6p44LJfKqVVI3oG8KF/Qz2fpC5LeT9PL8o+OF/IAKXqt/EbVoXx5vxyWT/tWkhfIDpgr9CA+WjdClr8g+AsjuZFBxSf1CR2BV/QZfdR9eosLAGv3/cmRMmVfejl2ZC7FdyC/xreEXamZ8kBpF8lXUnyJfpIvaoVN4srUW/LRp/pRyl/kT2Ay9wLigKLnS+On+rVyQIM8aRzZH8fdSDyAY/8r+rITSz2bqxP0yC7HXL1/pvktXcBoc9WSAtpGe/KHuWJOXssHR49MDgk/2Jt2A2gs1YaIvoQsxVKJ1kVu7DFxv3sU2cUogmx7n1gsZdp3JVFO3Mu4Vza/ai+ip3seRddLt1eWX156SX7Jv3mgmhA/PZSSf/JnAbpzkPjlU27mvkchR106qPQRXTTrrxVHyFV3Fir9RNfN+rFZvnzuQO3xsaPAmem5Q/Nzc3nq+QKy9jSVpz9npO3bUT4qpt/DyHdmRyeKAOQvGZYwQonzNgtkeXXxixTx2wvjc6oYV/k0Fvi+VxzaNxgOmZ/vdLqY6LL4A3nFT3dDIq2Jjvhlf1B3Sqbp8vkRk7y08jp9Wm5B3FpqoNu7Ly3XoV5hosvIk71DpxvOD2bkUS8x0en6TRrl7R/R9atVjHR6feeN8vYO5TPyqJeY6EjenWan1wQVS8WJwvTktLyJ9p6eW0luOceVf3onLigFzOEjMM0/rG0QlX5ZwmWcl2zL5qK4Oj6VuPGpai0XOXWmrevMQ2lnOegDaUmyDjPTJ9YvH9s6yyfnkFPBunzD+/XyZIiSRzS+TFqPH23egX9xtmTdgVXkox4XxKc4R66QjfVx/JrtxH5oMKoMjueiHC5uQ37dmEb9Com8C9LPaHQZ+C/sSuJdwgZyzI0gQwHlWFJQZznmxtDf5xRDP6YzR1T9eGvmkFGkJ3Kc0FKUik6WRsRyPm+wUmw3AtLPNC+ioZTdkd6SDB3mxTR9I+IWmG5WzfOilG/Yb0Med9mt8u8PMkY0z4/mcgt+Izs/dlFusuEQOm7ncpFvvXIXZzmL9KO4jEMVf2oqR04cGcpbDFtRbPEHMVWUCoVFqyj41zYlCouRLKt0pNBeTuC7kd/Uy5E9+QjKqNI+67rlFEmMLGtisqTVB7VlYVs5NG1jIZOuh+quRjFrrFeftBhoUp2wnIzR5P6MsRrZehQ0Y6nnXrnpiuHurdCNqm7SRWbVeD/OyZJVttrFaqNPdoLdeDX9YIwsC8wmg2n0pUVCZtfxgj5xMsrU+WKswnyIfXnZbaY3O2Htd9eoxbgdd+Dndpxeo7OI0EDH33mGmepA6QQ=
*/