//
// basic_writable_pipe.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_WRITABLE_PIPE_HPP
#define BOOST_ASIO_BASIC_WRITABLE_PIPE_HPP

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
 * The basic_writable_pipe class provides a wrapper over pipe
 * functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = any_io_executor>
class basic_writable_pipe
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the pipe type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The pipe type when rebound to the specified executor.
    typedef basic_writable_pipe<Executor1> other;
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

  /// A basic_writable_pipe is always the lowest layer.
  typedef basic_writable_pipe lowest_layer_type;

  /// Construct a basic_writable_pipe without opening it.
  /**
   * This constructor creates a pipe without opening it.
   *
   * @param ex The I/O executor that the pipe will use, by default, to dispatch
   * handlers for any asynchronous operations performed on the pipe.
   */
  explicit basic_writable_pipe(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct a basic_writable_pipe without opening it.
  /**
   * This constructor creates a pipe without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the pipe will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the pipe.
   */
  template <typename ExecutionContext>
  explicit basic_writable_pipe(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct a basic_writable_pipe on an existing native pipe.
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
  basic_writable_pipe(const executor_type& ex,
      const native_handle_type& native_pipe)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_pipe, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_writable_pipe on an existing native pipe.
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
  basic_writable_pipe(ExecutionContext& context,
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
  /// Move-construct a basic_writable_pipe from another.
  /**
   * This constructor moves a pipe from one object to another.
   *
   * @param other The other basic_writable_pipe object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_writable_pipe(const executor_type&)
   * constructor.
   */
  basic_writable_pipe(basic_writable_pipe&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_writable_pipe from another.
  /**
   * This assignment operator moves a pipe from one object to another.
   *
   * @param other The other basic_writable_pipe object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_writable_pipe(const executor_type&)
   * constructor.
   */
  basic_writable_pipe& operator=(basic_writable_pipe&& other)
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
  ~basic_writable_pipe()
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
   * layers. Since a basic_writable_pipe cannot contain any further layers, it
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
   * layers. Since a basic_writable_pipe cannot contain any further layers, it
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
   * This function is used to close the pipe. Any asynchronous write operations
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
   * This function is used to close the pipe. Any asynchronous write operations
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
   * This function causes all outstanding asynchronous write operations to
   * finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
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
   * This function causes all outstanding asynchronous write operations to
   * finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Write some data to the pipe.
  /**
   * This function is used to write data to the pipe. The function call will
   * block until one or more bytes of the data has been written successfully,
   * or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the pipe.
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
   * pipe.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().write_some(
        impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  /// Write some data to the pipe.
  /**
   * This function is used to write data to the pipe. The function call will
   * block until one or more bytes of the data has been written successfully,
   * or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the pipe.
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
    return impl_.get_service().write_some(
        impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the pipe. It is an
   * initiating function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param buffers One or more data buffers to be written to the pipe.
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
   * pipe.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
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

private:
  // Disallow copying and assignment.
  basic_writable_pipe(const basic_writable_pipe&) BOOST_ASIO_DELETED;
  basic_writable_pipe& operator=(const basic_writable_pipe&) BOOST_ASIO_DELETED;

  class initiate_async_write_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some(basic_writable_pipe* self)
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
    basic_writable_pipe* self_;
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

#endif // BOOST_ASIO_BASIC_WRITABLE_PIPE_HPP

/* basic_writable_pipe.hpp
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
*/