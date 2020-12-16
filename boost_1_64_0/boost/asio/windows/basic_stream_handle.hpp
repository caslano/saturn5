//
// windows/basic_stream_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_STREAM_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_STREAM_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/windows/basic_overlapped_handle.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Provides stream-oriented handle functionality.
/**
 * The windows::basic_stream_handle class provides asynchronous and blocking
 * stream-oriented handle functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Executor = executor>
class basic_stream_handle
  : public basic_overlapped_handle<Executor>
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the handle type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The handle type when rebound to the specified executor.
    typedef basic_stream_handle<Executor1> other;
  };

  /// The native representation of a handle.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef boost::asio::detail::win_iocp_handle_service::native_handle_type
    native_handle_type;
#endif

  /// Construct a stream handle without opening it.
  /**
   * This constructor creates a stream handle without opening it.
   *
   * @param ex The I/O executor that the stream handle will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the stream
   * handle.
   */
  explicit basic_stream_handle(const executor_type& ex)
    : basic_overlapped_handle<Executor>(ex)
  {
  }

  /// Construct a stream handle without opening it.
  /**
   * This constructor creates a stream handle without opening it. The handle
   * needs to be opened or assigned before data can be sent or received on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the stream handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the stream handle.
   */
  template <typename ExecutionContext>
  explicit basic_stream_handle(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value,
        basic_stream_handle
      >::type* = 0)
    : basic_overlapped_handle<Executor>(context)
  {
  }

  /// Construct a stream handle on an existing native handle.
  /**
   * This constructor creates a stream handle object to hold an existing native
   * handle.
   *
   * @param ex The I/O executor that the stream handle will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the stream
   * handle.
   *
   * @param handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_handle(const executor_type& ex, const native_handle_type& handle)
    : basic_overlapped_handle<Executor>(ex, handle)
  {
  }

  /// Construct a stream handle on an existing native handle.
  /**
   * This constructor creates a stream handle object to hold an existing native
   * handle.
   *
   * @param context An execution context which provides the I/O executor that
   * the stream handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the stream handle.
   *
   * @param handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_stream_handle(ExecutionContext& context,
      const native_handle_type& handle,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_overlapped_handle<Executor>(context, handle)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a stream handle from another.
  /**
   * This constructor moves a stream handle from one object to another.
   *
   * @param other The other stream handle object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_handle(const executor_type&)
   * constructor.
   */
  basic_stream_handle(basic_stream_handle&& other)
    : basic_overlapped_handle<Executor>(std::move(other))
  {
  }

  /// Move-assign a stream handle from another.
  /**
   * This assignment operator moves a stream handle from one object to
   * another.
   *
   * @param other The other stream handle object from which the move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_handle(const executor_type&)
   * constructor.
   */
  basic_stream_handle& operator=(basic_stream_handle&& other)
  {
    basic_overlapped_handle<Executor>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Write some data to the handle.
  /**
   * This function is used to write data to the stream handle. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().write_some(
        this->impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  /// Write some data to the handle.
  /**
   * This function is used to write data to the stream handle. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().write_some(
        this->impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the stream handle.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the handle.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the write operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The write operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some(this), handler, buffers);
  }

  /// Read some data from the handle.
  /**
   * This function is used to read data from the stream handle. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().read_some(
        this->impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return s;
  }

  /// Read some data from the handle.
  /**
   * This function is used to read data from the stream handle. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().read_some(
        this->impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the stream handle.
   * The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the read operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The read operation may not read all of the requested number of bytes.
   * Consider using the @ref async_read function if you need to ensure that the
   * requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_read_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some(this), handler, buffers);
  }

private:
  class initiate_async_write_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some(basic_stream_handle* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_write_some(
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_stream_handle* self_;
  };

  class initiate_async_read_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some(basic_stream_handle* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_read_some(
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_stream_handle* self_;
  };
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_BASIC_STREAM_HANDLE_HPP

/* basic_stream_handle.hpp
EWmRT3uL/mFWiH7hScR/DZd8FDan4fLhhsPNgyuH2wl3+Gil7mDlr/JX+Tv77z+z/9+8aGzpNFMD4Bft/5t7/Xdb7vmvy73+mw2//aqxwBOIX3ZN4Lt6c+5CqWh7zKRtpL99PyX+IWIH4K1c2z4UaXP1t+Sd4h8ZtBlg+S7+iMT1MiJ9kx45374PlSr+jvrb/g5J+9vQfSj9PXyC0M/V+08fir+NCuwTlefC/Qr7RGh/2D7RTvZ5T+4TdYF7G3RlZcE+l10i/NiH9j1xoWvOvjDTnXWfyPKt3V6nNtp2X/g+0YX4hn7KUie9S2SvF+tB2jPsEzFe7xOVn8M+Eco60z6R7ttyd/g+0btmAQt0O7hLFLENoLPvEdWGP+oekdCH7xHtX1CxPaJqQsc9IuYVbY/o4AL7HlGnBeF7RL6Ftj0i1CNsjwgLwOh7RM0XnHmPqOaC6HtE3y+w7xENFT/3iFgX+x4R59g57BG9lfvz94hyMpX8DqT5aZ4Btm2JFiwM7BE1D98hisznTNNV8/Vf7pSz57rfd3AczP2WNf48yDslTBOSh6Rh36PJG5Si/8a00H0i8grTt5Iyttr2dC5R2RzPjxebNDuciepTnBXtYUxydDJqUt75rkMcrF/EYVW+37jOd0VsobE77j4jg9/11kv+LyQnweLEvpgensAee41bzfCVqib3NXZIGdcntIZFkfedXtXQ3cK1O+Y+R2CP48j1Zvwuzyoj0x3Y4/jnDSKvEiZjN6Cm96Trg3i3yuC38e8kv++8e9Xf3Xs9mFP8vpom9f0pYaZR6krwDkR9uH+zlN/W+Y1zkqRfEpevdsQm8tvr6WV+Gt4DzL7N4n5PwJ8Lf6APBw8Gv+nvnj/d5L9n2KXq8Lsp3qFu4FxjudcuMf2XOAJlzruN8fy2m3kz/NghMf2trOMLfxf43dea/poJwXHsr+qx/ByJW57qVS53snu44wZvZ+Okz6E+9LUw2se28NXjmNYXuvkJXnzxPGjMdPX03Ox40zfNGBF7i1Ezfpge22bSR895R6mquC+smfRlhjk3fmeGt1b1ONanpM/vT0xWXtS8kdHLOQ6WS8arEtdg74fxHY2aHOOmUu6AlEXGCldHWPS5yHuv982kGkYqx/sh6b/fxdUxPosJ7IHESX9l+hobl3oCe4UvLTLD3vPGGjvdgfHdcIvwqe7nL4X/HuZeCPr9jqAMHa/nURVlHctWluf+RzIODhVoc/5i2t5jeY9K/vEybnXNcZM+qBOfynEKjFsBxspaBgyrUscFaaS9j2A21MRzaYYzUNY+6V/cc88+qHKnveynpW5OB/cddVlLHY/4ErnX00zyXu4w/dXhXyp9tt/y/b4TSuVelMQ5sWf8uPOwc4DRyZ1r3Odp6atDfrlF2nZRQrIqcV7rbGJsc8W4dvuWGkNi33TUJK/cJXkMSPpUPWJscDjUWmdbT5fYx1ypbNN1t0j5noHqOr3Hs0HqfXvaS8bylMDdsqukrC1GQC6Mk3bcH1PPeMAb4JPXpP1PeuoYp1wBPukq8/s3hguSLpt84pMxO+D1KCdWcIM8hz1xug/jhB/66Xl6XOb+B1o+XCvzdlvc9WpBbGqAhyS/T7yPqLWeYD920fPvSeHv9rFe9bbxpbHDeMLZxGF4uhvDvc2NR3y/1TJ1t9DNw/z7yhXvHu2eE9vfeDNulJ53JcLzc3yDjWRPF59LZbMPN4uMbJw418g1kpwNPO/HYH+affmj8Eyca7Xq7QjsJdeXNjzjvUgd9wT2vUol7KTee9kvbWrqe1F5PH/3erV83SN1bJ241hjkyvEO8AT6dI2M2dK0j9Q93rUxV3guT27rtK4RUtmGY5K+D/w=
*/