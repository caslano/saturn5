//
// windows/basic_random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
template <typename Executor = any_io_executor>
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
   * handle needs to be opened or assigned before data can be written to or read
   * from it.
   *
   * @param context An execution context which provides the I/O executor that
   * the random-access handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the random-access handle.
   */
  template <typename ExecutionContext>
  explicit basic_random_access_handle(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
   * handle. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param offset The offset at which the data will be written.
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
  async_write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some_at(this), token, offset, buffers);
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
   * handle. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param offset The offset at which the data will be read.
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
  async_read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some_at(this), token, offset, buffers);
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
          self_->impl_.get_implementation(), offset, buffers,
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), offset, buffers,
          handler2.value, self_->impl_.get_executor());
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