//
// windows/basic_random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/windows/basic_overlapped_handle.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Provides random-access handle functionality.
/**
 * The windows::basic_random_access_handle class provides asynchronous and
 * blocking random-access handle functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = executor>
class basic_random_access_handle
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
    typedef basic_random_access_handle<Executor1> other;
  };

  /// The native representation of a handle.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef boost::asio::detail::win_iocp_handle_service::native_handle_type
    native_handle_type;
#endif

  /// Construct a random-access handle without opening it.
  /**
   * This constructor creates a random-access handle without opening it.
   *
   * @param ex The I/O executor that the random-access handle will use, by
   * default, to dispatch handlers for any asynchronous operations performed on
   * the random-access handle.
   */
  explicit basic_random_access_handle(const executor_type& ex)
    : basic_overlapped_handle<Executor>(ex)
  {
  }

  /// Construct a random-access handle without opening it.
  /**
   * This constructor creates a random-access handle without opening it. The
   * handle needs to be opened or assigned before data can be sent or received
   * on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the random-access handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the random-access handle.
   */
  template <typename ExecutionContext>
  explicit basic_random_access_handle(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value,
        basic_random_access_handle
      >::type* = 0)
    : basic_overlapped_handle<Executor>(context)
  {
  }

  /// Construct a random-access handle on an existing native handle.
  /**
   * This constructor creates a random-access handle object to hold an existing
   * native handle.
   *
   * @param ex The I/O executor that the random-access handle will use, by
   * default, to dispatch handlers for any asynchronous operations performed on
   * the random-access handle.
   *
   * @param handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_random_access_handle(const executor_type& ex,
      const native_handle_type& handle)
    : basic_overlapped_handle<Executor>(ex, handle)
  {
  }

  /// Construct a random-access handle on an existing native handle.
  /**
   * This constructor creates a random-access handle object to hold an existing
   * native handle.
   *
   * @param context An execution context which provides the I/O executor that
   * the random-access handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the random-access handle.
   *
   * @param handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_random_access_handle(ExecutionContext& context,
      const native_handle_type& handle,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_overlapped_handle<Executor>(context, handle)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a random-access handle from another.
  /**
   * This constructor moves a random-access handle from one object to another.
   *
   * @param other The other random-access handle object from which the
   * move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_handle(const executor_type&)
   * constructor.
   */
  basic_random_access_handle(basic_random_access_handle&& other)
    : basic_overlapped_handle<Executor>(std::move(other))
  {
  }

  /// Move-assign a random-access handle from another.
  /**
   * This assignment operator moves a random-access handle from one object to
   * another.
   *
   * @param other The other random-access handle object from which the
   * move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_handle(const executor_type&)
   * constructor.
   */
  basic_random_access_handle& operator=(basic_random_access_handle&& other)
  {
    basic_overlapped_handle<Executor>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some_at operation may not write all of the data. Consider
   * using the @ref write_at function if you need to ensure that all data is
   * written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.write_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().write_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some_at");
    return s;
  }

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write_at function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->impl_.get_service().write_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
  }

  /// Start an asynchronous write at the specified offset.
  /**
   * This function is used to asynchronously write data to the random-access
   * handle. The function call always returns immediately.
   *
   * @param offset The offset at which the data will be written.
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
   * Consider using the @ref async_write_at function if you need to ensure that
   * all data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_write_some_at(42, boost::asio::buffer(data, size), handler);
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
  async_write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some_at(this), handler, offset, buffers);
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
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
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.read_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().read_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some_at");
    return s;
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->impl_.get_service().read_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
  }

  /// Start an asynchronous read at the specified offset.
  /**
   * This function is used to asynchronously read data from the random-access
   * handle. The function call always returns immediately.
   *
   * @param offset The offset at which the data will be read.
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
   * Consider using the @ref async_read_at function if you need to ensure that
   * the requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_read_some_at(42, boost::asio::buffer(data, size), handler);
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
  async_read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some_at(this), handler, offset, buffers);
  }

private:
  class initiate_async_write_some_at
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some_at(basic_random_access_handle* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        uint64_t offset, const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_write_some_at(
          self_->impl_.get_implementation(), offset, buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_random_access_handle* self_;
  };

  class initiate_async_read_some_at
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some_at(basic_random_access_handle* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        uint64_t offset, const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_read_some_at(
          self_->impl_.get_implementation(), offset, buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_random_access_handle* self_;
  };
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP

/* basic_random_access_handle.hpp
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
*/