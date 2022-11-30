//
// posix/basic_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_BASIC_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_BASIC_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/posix/descriptor_base.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/io_uring_descriptor_service.hpp>
#else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
# include <boost/asio/detail/reactive_descriptor_service.hpp>
#endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Provides POSIX descriptor functionality.
/**
 * The posix::basic_descriptor class template provides the ability to wrap a
 * POSIX descriptor.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = any_io_executor>
class basic_descriptor
  : public descriptor_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the descriptor type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The descriptor type when rebound to the specified executor.
    typedef basic_descriptor<Executor1> other;
  };

  /// The native representation of a descriptor.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef detail::io_uring_descriptor_service::native_handle_type
    native_handle_type;
#else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  typedef detail::reactive_descriptor_service::native_handle_type
    native_handle_type;
#endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

  /// A descriptor is always the lowest layer.
  typedef basic_descriptor lowest_layer_type;

  /// Construct a descriptor without opening it.
  /**
   * This constructor creates a descriptor without opening it.
   *
   * @param ex The I/O executor that the descriptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * descriptor.
   */
  explicit basic_descriptor(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct a descriptor without opening it.
  /**
   * This constructor creates a descriptor without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the descriptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the descriptor.
   */
  template <typename ExecutionContext>
  explicit basic_descriptor(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct a descriptor on an existing native descriptor.
  /**
   * This constructor creates a descriptor object to hold an existing native
   * descriptor.
   *
   * @param ex The I/O executor that the descriptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * descriptor.
   *
   * @param native_descriptor A native descriptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_descriptor(const executor_type& ex,
      const native_handle_type& native_descriptor)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_descriptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a descriptor on an existing native descriptor.
  /**
   * This constructor creates a descriptor object to hold an existing native
   * descriptor.
   *
   * @param context An execution context which provides the I/O executor that
   * the descriptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the descriptor.
   *
   * @param native_descriptor A native descriptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_descriptor(ExecutionContext& context,
      const native_handle_type& native_descriptor,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_descriptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a descriptor from another.
  /**
   * This constructor moves a descriptor from one object to another.
   *
   * @param other The other descriptor object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_descriptor(const executor_type&)
   * constructor.
   */
  basic_descriptor(basic_descriptor&& other) BOOST_ASIO_NOEXCEPT
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a descriptor from another.
  /**
   * This assignment operator moves a descriptor from one object to another.
   *
   * @param other The other descriptor object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_descriptor(const executor_type&)
   * constructor.
   */
  basic_descriptor& operator=(basic_descriptor&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since a descriptor cannot contain any further layers, it
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
   * layers. Since a descriptor cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  /// Assign an existing native descriptor to the descriptor.
  /*
   * This function opens the descriptor to hold an existing native descriptor.
   *
   * @param native_descriptor A native descriptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& native_descriptor)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(),
        native_descriptor, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native descriptor to the descriptor.
  /*
   * This function opens the descriptor to hold an existing native descriptor.
   *
   * @param native_descriptor A native descriptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& native_descriptor,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(
        impl_.get_implementation(), native_descriptor, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the descriptor is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the descriptor.
  /**
   * This function is used to close the descriptor. Any asynchronous read or
   * write operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the descriptor.
  /**
   * This function is used to close the descriptor. Any asynchronous read or
   * write operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the native descriptor representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * descriptor. This is intended to allow access to native descriptor
   * functionality that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Release ownership of the native descriptor implementation.
  /**
   * This function may be used to obtain the underlying representation of the
   * descriptor. After calling this function, @c is_open() returns false. The
   * caller is responsible for closing the descriptor.
   *
   * All outstanding asynchronous read or write operations will finish
   * immediately, and the handlers for cancelled operations will be passed the
   * boost::asio::error::operation_aborted error.
   */
  native_handle_type release()
  {
    return impl_.get_service().release(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the descriptor.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
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

  /// Cancel all asynchronous operations associated with the descriptor.
  /**
   * This function causes all outstanding asynchronous read or write operations
   * to finish immediately, and the handlers for cancelled operations will be
   * passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Perform an IO control command on the descriptor.
  /**
   * This function is used to execute an IO control command on the descriptor.
   *
   * @param command The IO control command to be performed on the descriptor.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @sa IoControlCommand @n
   * boost::asio::posix::descriptor_base::bytes_readable @n
   * boost::asio::posix::descriptor_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::asio::posix::stream_descriptor::bytes_readable command;
   * descriptor.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   */
  template <typename IoControlCommand>
  void io_control(IoControlCommand& command)
  {
    boost::system::error_code ec;
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    boost::asio::detail::throw_error(ec, "io_control");
  }

  /// Perform an IO control command on the descriptor.
  /**
   * This function is used to execute an IO control command on the descriptor.
   *
   * @param command The IO control command to be performed on the descriptor.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @sa IoControlCommand @n
   * boost::asio::posix::descriptor_base::bytes_readable @n
   * boost::asio::posix::descriptor_base::non_blocking_io
   *
   * @par Example
   * Getting the number of bytes ready to read:
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::asio::posix::stream_descriptor::bytes_readable command;
   * boost::system::error_code ec;
   * descriptor.io_control(command, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * std::size_t bytes_readable = command.get();
   * @endcode
   */
  template <typename IoControlCommand>
  BOOST_ASIO_SYNC_OP_VOID io_control(IoControlCommand& command,
      boost::system::error_code& ec)
  {
    impl_.get_service().io_control(impl_.get_implementation(), command, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Gets the non-blocking mode of the descriptor.
  /**
   * @returns @c true if the descriptor's synchronous operations will fail with
   * boost::asio::error::would_block if they are unable to perform the requested
   * operation immediately. If @c false, synchronous operations will block
   * until complete.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  bool non_blocking() const
  {
    return impl_.get_service().non_blocking(impl_.get_implementation());
  }

  /// Sets the non-blocking mode of the descriptor.
  /**
   * @param mode If @c true, the descriptor's synchronous operations will fail
   * with boost::asio::error::would_block if they are unable to perform the
   * requested operation immediately. If @c false, synchronous operations will
   * block until complete.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  void non_blocking(bool mode)
  {
    boost::system::error_code ec;
    impl_.get_service().non_blocking(impl_.get_implementation(), mode, ec);
    boost::asio::detail::throw_error(ec, "non_blocking");
  }

  /// Sets the non-blocking mode of the descriptor.
  /**
   * @param mode If @c true, the descriptor's synchronous operations will fail
   * with boost::asio::error::would_block if they are unable to perform the
   * requested operation immediately. If @c false, synchronous operations will
   * block until complete.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note The non-blocking mode has no effect on the behaviour of asynchronous
   * operations. Asynchronous operations will never fail with the error
   * boost::asio::error::would_block.
   */
  BOOST_ASIO_SYNC_OP_VOID non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    impl_.get_service().non_blocking(impl_.get_implementation(), mode, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Gets the non-blocking mode of the native descriptor implementation.
  /**
   * This function is used to retrieve the non-blocking mode of the underlying
   * native descriptor. This mode has no effect on the behaviour of the
   * descriptor object's synchronous operations.
   *
   * @returns @c true if the underlying descriptor is in non-blocking mode and
   * direct system calls may fail with boost::asio::error::would_block (or the
   * equivalent system error).
   *
   * @note The current non-blocking mode is cached by the descriptor object.
   * Consequently, the return value may be incorrect if the non-blocking mode
   * was set directly on the native descriptor.
   */
  bool native_non_blocking() const
  {
    return impl_.get_service().native_non_blocking(
        impl_.get_implementation());
  }

  /// Sets the non-blocking mode of the native descriptor implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native descriptor. It has no effect on the behaviour of the descriptor
   * object's synchronous operations.
   *
   * @param mode If @c true, the underlying descriptor is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @throws boost::system::system_error Thrown on failure. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   */
  void native_non_blocking(bool mode)
  {
    boost::system::error_code ec;
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    boost::asio::detail::throw_error(ec, "native_non_blocking");
  }

  /// Sets the non-blocking mode of the native descriptor implementation.
  /**
   * This function is used to modify the non-blocking mode of the underlying
   * native descriptor. It has no effect on the behaviour of the descriptor
   * object's synchronous operations.
   *
   * @param mode If @c true, the underlying descriptor is put into non-blocking
   * mode and direct system calls may fail with boost::asio::error::would_block
   * (or the equivalent system error).
   *
   * @param ec Set to indicate what error occurred, if any. If the @c mode is
   * @c false, but the current value of @c non_blocking() is @c true, this
   * function fails with boost::asio::error::invalid_argument, as the
   * combination does not make sense.
   */
  BOOST_ASIO_SYNC_OP_VOID native_non_blocking(
      bool mode, boost::system::error_code& ec)
  {
    impl_.get_service().native_non_blocking(
        impl_.get_implementation(), mode, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Wait for the descriptor to become ready to read, ready to write, or to
  /// have pending error conditions.
  /**
   * This function is used to perform a blocking wait for a descriptor to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired descriptor state.
   *
   * @par Example
   * Waiting for a descriptor to become readable.
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * descriptor.wait(boost::asio::posix::stream_descriptor::wait_read);
   * @endcode
   */
  void wait(wait_type w)
  {
    boost::system::error_code ec;
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    boost::asio::detail::throw_error(ec, "wait");
  }

  /// Wait for the descriptor to become ready to read, ready to write, or to
  /// have pending error conditions.
  /**
   * This function is used to perform a blocking wait for a descriptor to enter
   * a ready to read, write or error condition state.
   *
   * @param w Specifies the desired descriptor state.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * Waiting for a descriptor to become readable.
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::system::error_code ec;
   * descriptor.wait(boost::asio::posix::stream_descriptor::wait_read, ec);
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID wait(wait_type w, boost::system::error_code& ec)
  {
    impl_.get_service().wait(impl_.get_implementation(), w, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Asynchronously wait for the descriptor to become ready to read, ready to
  /// write, or to have pending error conditions.
  /**
   * This function is used to perform an asynchronous wait for a descriptor to
   * enter a ready to read, write or error condition state. It is an initiating
   * function for an @ref asynchronous_operation, and always returns
   * immediately.
   *
   * @param w Specifies the desired descriptor state.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the wait completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
   *
   * @par Example
   * @code
   * void wait_handler(const boost::system::error_code& error)
   * {
   *   if (!error)
   *   {
   *     // Wait succeeded.
   *   }
   * }
   *
   * ...
   *
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * descriptor.async_wait(
   *     boost::asio::posix::stream_descriptor::wait_read,
   *     wait_handler);
   * @endcode
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
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitToken,
      void (boost::system::error_code))
  async_wait(wait_type w,
      BOOST_ASIO_MOVE_ARG(WaitToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitToken, void (boost::system::error_code)>(
        initiate_async_wait(this), token, w);
  }

protected:
  /// Protected destructor to prevent deletion through this type.
  /**
   * This function destroys the descriptor, cancelling any outstanding
   * asynchronous wait operations associated with the descriptor as if by
   * calling @c cancel.
   */
  ~basic_descriptor()
  {
  }

#if defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  detail::io_object_impl<detail::io_uring_descriptor_service, Executor> impl_;
#else // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)
  detail::io_object_impl<detail::reactive_descriptor_service, Executor> impl_;
#endif // defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

private:
  // Disallow copying and assignment.
  basic_descriptor(const basic_descriptor&) BOOST_ASIO_DELETED;
  basic_descriptor& operator=(const basic_descriptor&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_descriptor* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WaitHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(WaitHandler) handler, wait_type w) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WaitHandler.
      BOOST_ASIO_WAIT_HANDLER_CHECK(WaitHandler, handler) type_check;

      detail::non_const_lvalue<WaitHandler> handler2(handler);
      self_->impl_.get_service().async_wait(
          self_->impl_.get_implementation(), w,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_descriptor* self_;
  };
};

} // namespace posix
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_BASIC_DESCRIPTOR_HPP

/* basic_descriptor.hpp
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
*/