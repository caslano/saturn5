//
// basic_readable_pipe.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_READABLE_PIPE_HPP
#define BOOST_ASIO_BASIC_READABLE_PIPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PIPE) \
  || defined(GENERATING_DOCUMENTATION)

#include <string>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_handle_service.hpp>
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/io_uring_descriptor_service.hpp>
#else
# include <boost/asio/detail/reactive_descriptor_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides pipe functionality.
/**
 * The basic_readable_pipe class provides a wrapper over pipe
 * functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = any_io_executor>
class basic_readable_pipe
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the pipe type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The pipe type when rebound to the specified executor.
    typedef basic_readable_pipe<Executor1> other;
  };

  /// The native representation of a pipe.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_HAS_IOCP)
  typedef detail::win_iocp_handle_service::native_handle_type
    native_handle_type;
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef detail::io_uring_descriptor_service::native_handle_type
    native_handle_type;
#else
  typedef detail::reactive_descriptor_service::native_handle_type
    native_handle_type;
#endif

  /// A basic_readable_pipe is always the lowest layer.
  typedef basic_readable_pipe lowest_layer_type;

  /// Construct a basic_readable_pipe without opening it.
  /**
   * This constructor creates a pipe without opening it.
   *
   * @param ex The I/O executor that the pipe will use, by default, to dispatch
   * handlers for any asynchronous operations performed on the pipe.
   */
  explicit basic_readable_pipe(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct a basic_readable_pipe without opening it.
  /**
   * This constructor creates a pipe without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the pipe will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the pipe.
   */
  template <typename ExecutionContext>
  explicit basic_readable_pipe(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct a basic_readable_pipe on an existing native pipe.
  /**
   * This constructor creates a pipe object to hold an existing native
   * pipe.
   *
   * @param ex The I/O executor that the pipe will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * pipe.
   *
   * @param native_pipe A native pipe.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_readable_pipe(const executor_type& ex,
      const native_handle_type& native_pipe)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_pipe, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_readable_pipe on an existing native pipe.
  /**
   * This constructor creates a pipe object to hold an existing native
   * pipe.
   *
   * @param context An execution context which provides the I/O executor that
   * the pipe will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the pipe.
   *
   * @param native_pipe A native pipe.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_readable_pipe(ExecutionContext& context,
      const native_handle_type& native_pipe,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_pipe, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_readable_pipe from another.
  /**
   * This constructor moves a pipe from one object to another.
   *
   * @param other The other basic_readable_pipe object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_readable_pipe(const executor_type&)
   * constructor.
   */
  basic_readable_pipe(basic_readable_pipe&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_readable_pipe from another.
  /**
   * This assignment operator moves a pipe from one object to another.
   *
   * @param other The other basic_readable_pipe object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_readable_pipe(const executor_type&)
   * constructor.
   */
  basic_readable_pipe& operator=(basic_readable_pipe&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the pipe.
  /**
   * This function destroys the pipe, cancelling any outstanding
   * asynchronous wait operations associated with the pipe as if by
   * calling @c cancel.
   */
  ~basic_readable_pipe()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since a basic_readable_pipe cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A reference to the lowest layer in the stack of layers. Ownership
   * is not transferred to the caller.
   */
  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  /// Get a const reference to the lowest layer.
  /**
   * This function returns a const reference to the lowest layer in a stack of
   * layers. Since a basic_readable_pipe cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  /// Assign an existing native pipe to the pipe.
  /*
   * This function opens the pipe to hold an existing native pipe.
   *
   * @param native_pipe A native pipe.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& native_pipe)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_pipe, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native pipe to the pipe.
  /*
   * This function opens the pipe to hold an existing native pipe.
   *
   * @param native_pipe A native pipe.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& native_pipe,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(), native_pipe, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the pipe is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the pipe.
  /**
   * This function is used to close the pipe. Any asynchronous read operations
   * will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the pipe.
  /**
   * This function is used to close the pipe. Any asynchronous read operations
   * will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the native pipe representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * pipe. This is intended to allow access to native pipe
   * functionality that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the pipe.
  /**
   * This function causes all outstanding asynchronous read operations to finish
   * immediately, and the handlers for cancelled operations will be passed the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the pipe.
  /**
   * This function causes all outstanding asynchronous read operations to finish
   * immediately, and the handlers for cancelled operations will be passed the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Read some data from the pipe.
  /**
   * This function is used to read data from the pipe. The function call will
   * block until one or more bytes of data has been read successfully, or until
   * an error occurs.
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
   * basic_readable_pipe.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().read_some(
        impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return s;
  }

  /// Read some data from the pipe.
  /**
   * This function is used to read data from the pipe. The function call will
   * block until one or more bytes of data has been read successfully, or until
   * an error occurs.
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
    return impl_.get_service().read_some(
        impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the pipe. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
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
   * basic_readable_pipe.async_read_some(
   *     boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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
  // Disallow copying and assignment.
  basic_readable_pipe(const basic_readable_pipe&) BOOST_ASIO_DELETED;
  basic_readable_pipe& operator=(const basic_readable_pipe&) BOOST_ASIO_DELETED;

  class initiate_async_read_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some(basic_readable_pipe* self)
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
    basic_readable_pipe* self_;
  };

#if defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<detail::win_iocp_handle_service, Executor> impl_;
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  detail::io_object_impl<detail::io_uring_descriptor_service, Executor> impl_;
#else
  detail::io_object_impl<detail::reactive_descriptor_service, Executor> impl_;
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PIPE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_READABLE_PIPE_HPP

/* basic_readable_pipe.hpp
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
*/