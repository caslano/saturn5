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
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
*/