//
// windows/basic_stream_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
template <typename Executor = any_io_executor>
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
   * needs to be opened or assigned before data can be written to or read from
   * it.
   *
   * @param context An execution context which provides the I/O executor that
   * the stream handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the stream handle.
   */
  template <typename ExecutionContext>
  explicit basic_stream_handle(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be written to the handle.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the write completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * This asynchronous operation supports cancellation for the following
   * boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some(this), token, buffers);
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
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the read completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
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
   *
   * @par Per-Operation Cancellation
   * This asynchronous operation supports cancellation for the following
   * boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some(this), token, buffers);
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
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
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
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
*/