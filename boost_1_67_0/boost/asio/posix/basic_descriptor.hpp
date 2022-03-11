//
// posix/basic_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/reactive_descriptor_service.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/posix/descriptor_base.hpp>

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
template <typename Executor = executor>
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
#else
  typedef detail::reactive_descriptor_service::native_handle_type
    native_handle_type;
#endif

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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
   * enter a ready to read, write or error condition state.
   *
   * @param w Specifies the desired descriptor state.
   *
   * @param handler The handler to be called when the wait operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
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
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitHandler,
      void (boost::system::error_code))
  async_wait(wait_type w,
      BOOST_ASIO_MOVE_ARG(WaitHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitHandler, void (boost::system::error_code)>(
        initiate_async_wait(this), handler, w);
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

  detail::io_object_impl<detail::reactive_descriptor_service, Executor> impl_;

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
          self_->impl_.get_implementation(), w, handler2.value,
          self_->impl_.get_implementation_executor());
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
iqVupaA3uX293VuxK/GrPS/9sQPVQM8Dwkmwr58pjsF23ENQDBC/urx/BcaicAxxyaiJ6PDqK+17aLBxliYz8Jv5IbAqiDaZMzB4sD6w4oNI169m5N6+usm5B11YNvjeH+qgQjv79FxOyg48YTq7spxPZN7zgvml8ndWinDQsP0Q+GBeA2YOfoRw/crbyneHciG0q88GYYARv9IXHBo8ApoL94cTWKqtYeZsoinnB2kicqYyKOlKcn3eGzunVmn4bTNsFxroVxcLyYyPUZDwjI13dodd8C3lTeBxVwVDpurgpvotOl8IqO8nty6cP9Qw6dJiQ4BECSOvgB0uqV4sCiCtXbi330zJtW8tdioX1ibOi6uY4xkgaH4DMnRtk2cKf2m3JTutuTwYyYO+j1nfvU2YVt5hC8phR+eF2xeFD+2t1+6tO++tg7ucSrk4yrc0Eeouf2Bk/BxOnIeG2muk9WUtxKTuM6buA4vuA5iujgy2e044SH3UpTo6CIGjJupnEDSByvrny8Crz5A+y2+/CKSWk0vWke/6SHyB0/5xx/O2SwrzLal+kcnaLKHNsqVvtNCgS7afmusa6hUi3w2iSzerCed7KMILxOIJVoVBVgUhSh0Y8AzEL5gGxG8h3gZNZn5eS+ade9d09QoHyoHlKzfYPZhJEfc9GE5JH6XAJls5E4dXXabR2NdVuZNG8p8a4wJlumpj5aQPZ25stZCE30knPgRKhWN9iqGMnOnDt+wj7zR/OPWGnoBnd8NtzagLjmqCON36+WST3R6r11k5ZLwQOLLnmh8ApSWRl48w8oqAtF6OJ7tO2ZbgzeE83tfZFrf4H9XDrrpepvaFkQdFRINPtd/NF/QblwbeP5R+N144vuWQdtG9chvQPJe84j1kHPUrORbHdCI6romFWDxwDrOzwh70+2FatNvssNHnumC+tBt7ULuINJo1N9qsmNXmqMSQD89S2++amsYPtR9enx6rq4DgKhDHX/xdagEyruDs0JxocDSA8uJdHP/n6u9L3O+cebgw5RDt853hvWjoEgaBFhT5GtJMBXlxFXXqi7Qj05RWSYuS7Kq6qqqaiSqF6PULfT1ZH7OgWipTM0zJNWuq4kTMAffw2P27iomxhvk5NMSjQdFMud34DaNvus1v8Pzws2tj942LOEIyyBbHTbhwBXKKSSedb8QpAJWky84eASzbnwatadpt4Dc5vhTg06Qye5LLzmtiN9haKPF5vs6pOw1Mbqh3bERgymQJrLOqdlAoE5KF5ojqM5ZoftdvPdbtr0Uo1GivAfB52AyaOSxi0+CItRA09eie2fCdorTPFZwgljZK343mSGPxfE0s6U+La75z/qGaRjnIPj8+w6lHwv+T02eAIM+WSkrKoVNPkZtkUitAkxE7K9gp0xZqiy1yk2fLiX2EhkqxdXlxcZSiuj6Tl9dU606yQrmwoWBMe3tLhzo+/WeCZXVK20GCZ3OvUeu77rdFkq1uCvkivEWwtiKL3GKLExxysVLB4Re9ZNitYoxuXI5eTe9aTVIj+EtYcL0/vxt7vpL3VBzLcvF9pmEtSkzYSXg3RkMDk7LiMNjFXYGHNXZyOzuaYbR6wn7COGU+nGG8MXkWRMO9VR2Uyg1YXXyainLyTvNt9ZezYUhVYzE8W7R8tVXt+ohwl7yZ0FdYTsxHiSPwca6XsepHSp4KR18lvcU5HoEA8PCLr/eXETqbc/ilNmhsRDcPNIn+/nd6ZXG5NL1TcR78rC7jc3u2vHI0VrH1Bp/z2h55G3haD81O1I4oxMdokMzkFEWg3/uWuRseC99jRdDcq5EPjPZoV4werVYfmnkxrQA/HvRxi+Wb6/ra8luqKqHJPJUFCsaoqtsj8Hkeat7L+//QkxIRsixviIpZQ+LvQ7HHYXPb36wPg2ieOlS32k0GskbERYZWDA4LxCyMjW4uM1jsIH05Z0NCeGp//omGvZRnAPC24WfYfftT8hBjZdzwBgq60KBLxWPOUpnKHlofmEVkVfQVYXYyq45DFYaj1Vw+7t3r+0xlBfVoDGAusuOZlEc+BwX6dTRDeVZlz77X1YM/WDKQc9/UzsTZxcnU0BYelLI3soJnYSZhJnlJ8PExiYAyXCzt7UQNXUxJqEV5WJiZuQEsLFwAVjYOFjYGZnYqZmYqml/V7J1IqEmEQFWYkihY2LvYO1vYO5CIKLORyBoaW9q98DRMsvYmf1QFYGbmYmYHcLFyswEYmNl+rUrByd7E1dgUVNdfqzIDNfBHVQICf+sv4I/+Klt6mZKwsDAp2du7kLzIlZik7MzsSX4ZEygtqs3HyinGCWAGADhAo2ATAQhxc4mIshTdQ3AoyhYF0Ni2nRvbtm3btm3bNl9s27Zt2/z5g1U97K7ag7PPqKGc7KEdGhsjwiMAQcTfAIiotQuvqK0Lq3CmBgqpB65wDAW3iAyviKq2tKm1tbWBOqQpc+FKpbEkS02lLzYAkNCQ/GkXuZS4nNChkeRbAL7s5FBgnAOCCvzpl5jYMXahoQtf9Pf2zPX34rPzP0FgcCaQYXA8YWBwaHFgcAhRYXA0EGBwXKBhcHQgYb5cgDDYQwEx2P+Jxx6DgeXKQXSI9f3s53B0YnC2u7NnZPY31gO0te1TkA8dDQuhHpHE793regaQkFJUghSS0LFRM0NweXno+ENkBxWXMmFgDFymYeNQ0wCDw8AgCUoqi4sA38jL6ClqIIrN/ZJnEdZCFGKl5ooiUpL9I0ELQXnBhoxB977SUqc+t0UK3tsKjvO3ViAEkvj35J0Mb6y4w3x2dJu+HMJA7ruxgnOh0DmLJ6cmSj3dVANKf59L3R7X4Zb96Zr7WcMqlr5syTkMgpDJvtcS6Sv7lg+So5/c/RIrVRas2tHcoNxSIo+Ko6aakiQjrQQ46Mxj+NwOQNZJC2pi+BYmYG9xTpxATUdk6Xxspayo3t5qAFc0gZjEt8f5vYkyp1fgQe1be+f8rKIkR//IHDpRmtsRzCLwFQHoFWTELaZjn+4f6Z3Vf/FiTki8iE5hId7PLShJofmpsJnBfFlacmwe4D9e/j2yHgEaiA0o+I1aIQ41Bf6jb3XGS2NjFUaKAslbWKS2FzCDv9t+hri3x56LmA9y6PcihqWeKeXo1nioOXeUwSRnEDeXa3pygCMgldgJ9qtc3uT6fR12E68cdqYWqT7upu9eDvzfjEX1GYlAbEDbnJUAgJoceoscn3e/IxibXOSOLx5WU3G0TID/934XO+tq9A9aZssQEo9MjSU9QQY1mkrkA8eMvr2Td03BvgZjcSHQ6fXn26Yd5mZKA0VmZrEUYv1/iGG06AFeXoeSuVuR7HzoQ1ZUSyqyL2KiH8t92d9fH2Zk8BQu+7LCq/cJy6tXYW3g7EkPgdxvF3sx3Ftvo+/N0cQn+oAkq4benvfNr/X31XdOZ7erBB+4Dqo97mld/4IC73x+TR84WrBMkT68I7TcNmprB6fZIKrt8EGrRcnGugCmK4QohZtZdppnqch4WUJxDDn2XYYKUSvmnQwugeV7sPikEk4vDo8AhfsrexJXYiEddHFf+lr2v/bMS5gGw2SKuXWVh6PsYoG1lkasYhCv+l7qIWbhD97h2ckgGFAo4sWEemKsNBGEdiEWEPBH+d6uB5oUBrMFERKUhycXkM2er/eWvVWNwfA1C7FxiYnB5YSnU5Os/YAdorLzspBSYJnbK613Ckuhypj3rrlZUQ9+HaWvp0ViRG2gGIX6zVAC0Bjx0+bS8qqS07PNS+r6xaBAFRzAAIjJuIc/RtZQvvJKcUGFnJTMkFb0TtL1TMEQhdCFsL0e+f5RrPBNV7zUuOaPR0iMLAxpZH2XTNktjtM1fykEf8cRCcrSDrzgbdAlYVChQ7Kl0ZYjcaErcaGbIcXqYaWwsNQzf0VFBhYgix+26lJkcG52cmIGAAAs/9N5jr+L0elhfRXxxPJtfNpQGoHW0UdobbSlczJEbPqX2igoGXkhL/KVssWJbLLrdtqaKiu813aRIcSqzXopvdNGxMsoFiuTxZ0/oQBDItoRZnIzi4ol2FEXfv5z5EwtSt1QcFEv77fsoHDWbdxq1aL3kyDcUMlUpbQTqJC691VCDFjRHyaCh+xcPUuls5XQMaKQD4QjVyrQ1zsPCeXeVnYOTm0H7KFxyR6XzwBJPijJceuCjB0/goalHrOslYnDw0T1x/4tHPKiq6RGuWCD0RhYDE/gcXff+3etwfxUcLj533eUtxYMez3or93I9mIt5mDcTqMAyinTfxaj2HipqlalJAT75OVy4qBIwS/vghXg5KGJ0yvhCEiC2X6wGzNl10yLvux+iVGuuaVecTkymGl+rTOR9dmFp0YrcKcto1hGwdAy11Yj7X3fyeNv1Hfqe5vqLizNRO7ctGetynyHdpe1DPFUL/CLbKf4cbpTgyKC66BPdQIWkCYAEEHaeVFJVGf10BBd7mJGJkroNv/iKRgr0j3b6CXWA3UL72qFj9SISiaLCe2MTSyvgChpTCalB54fJvQmfnfwVvGvvy/GfFXMFF1ZHD32/SpCJdYWhjX6lySGdlb6d26Gk9v4Tc2Mbouv9M2tJ0gsL0wtrCtJCL86I8Ijy78sCXqz4CHH/NsylmhkdKUjoiQWlha2BkCNM/0w5h6/HuHplS0cKBzipbwdUgieukD+AYFBw8ICf0OhgYGBwcGh4SH+ZQ0IiIj+zQIFRojHgEiIBwg4ji1KicTo6QgEZCmL5WkKgI2NzYDKxocOjU9MhT0pRbpnb28fDhHOLi7OTl0MUkz9O7j6qEbPrE5PTC8pbs9ID8FsL858d4pHP6XX8eGGziweHfChRoEhHgkK96N2rdZrXvRd9EKEQUTCXo4rzkwvUAd0B8FR5+f1zkf3FYTr8Ns5Bnvn6ACkrpEBmP2rcjQiW2gLWbm6/V7rgH1maABYV9/Y4PBbXeiH3/qtO4//D0L/R2oJDOBLaGnkuzVfRjk9SkYbow8OamwtmH0NQHsgvy1BKjtDSV04OgS1Dwxqo02kbb1dZEigngT8P/YoCPCycHZ/kWAtjD5KapKhacoPuyBW1pZfInNgLVDgsDmgbX75uVRosB/Jl11QQwBV1xm9w7pf2G+wR78n7OqW7SkMQ2W+eBdx0dvvbnYLZ5l+dgvWAlVOcL1NSZJ8yR74AG4ejqhO10Yygi38q937wqBCz83fmz4BdXfzrTjZKG0P1mQFGDbCRYJWNpDl8AwV6tz4L5ojNT4t1cVHN/zA2aLBs7b/Hv7tXmkMH/fiDi1KD98Zp8qPYsYU+9jZn+q7xXLQWWVTiwTZZnzjpl7RMLL5dS8SVXA0Gky7OD2NbysPr4l/dl1uabAT22VWYuLLUMktgf53YeZeQ5EvPLAxS2xSEG/lCYNb8sPl/TJBHqp/2uWTmJ2nYayonVoq2k4NLliAr2tldmAUWfDZ5hz7JueOdELNm6g4b5FK4ES1EHUz3DWDT3pRhtj2mh+kku5cNZOZ4FL3eIt1ofzausRX9WzTFTvSy55mV/1oyDmU2zab8f3bPfJ7y/LTu8ey9vO0v+dXvbpneIx2vIcG+KyTHKQRHiMEccQztM6uoT6csd4mHKLXFdqGwMQEPVYG0dgAHWUfZV9fR+8E0WgPKCySsb6+1hb8Q+YBCzvHA/CAlSegK3TC5w778gvuAQvANjr5ffs9spv8U+sFh9bye8ZhCOCwTRJu+JDngRpJwhdAqK1JiUoryErzRAPDW/ra0U3KdHcjVfQgcnZk/cna9GPy3rB9s8z5mUnsluX8OEondVfqafMg0ViSFxgn+rq93EMib/fR1chIvGJ6YmFTvV/bN31E9Tlv5taoXjBgQfpj/WIffd7aAty/NDS770hzth+GkIq6JiMEixsVpM6n1ANilkL/zlBiMQbwZpHZVioqbGDOple9Elupfu/lcGGBXZctjPCoBLaEFnqWX58RTvMp1xrnjqKQydtJvYQRySvduT0mCONxr0lMk5E3rPM49TFjYcV3Y1hurMDDL0qtmv29y3gapOi/6yfSQuBl9tM7iRhfFzS1ryYH0FC7qwNI/v5LqzcHvPKY5w249BtP5/9u5y0wReUAXfcbU+t3e/aDvklDdfqL5wr9SHeNBvyVJ/mbtOza87u7bqrwEzH/w3H0rmfVrG2N84vfpEld55fOb/DbvH4Q6Ez4q4t/gcoMQ0IedTHsSrhHSEDwmxpCCAIaQ2po/kV4uolFskHlrMjYt5v1eMGW64rPUzojq39dmsc+Mdv5eUncO0Nv2d6l4S29uVWwDARDGZKfyylzG7Ul91n+KLEv7QsJlTHwdoZcOppkUBslEt10tnmLEqJjYGM8lMhVUnHs+P37+wtEDAAA/AfkD+gfsD/gfyD+QP6B+gP9B+YP7B+4P/B/EP4g/kH6g/wH5Q/qH7Q/6H8w/mD+wfqD/QfnD+4fvD/4fwj+EP4h+kP8h+QP6Z9/f8j+kP+h+EP5h+oP9R+aP7R/6P7Q/2H4w/iH6Q/zH5Y/rH/Y/rD/4fjD+YfrD/cfnj+8f/j+8P8R+CP4R+iP8B+RP6J/xP6I/5H4I/lH6o/0H5k/sn/k/sj/Ufij+Efpj/IflT+qf9T+qP/R+KP5R+uP9h+dP7p/9P7o/zH4Y/jH6I/xH5M/pn/M/pj/sfhj+cfqj/Ufmz+2f+z+2P9x+OP4x+mP8x+XP65/3P64//H44/nH64/3H58/vn/8//w/+3hBGsua16G9Uon/MOue8Cqc3Hkd5L/+q9SnKmdSSdYueTRenFjulu1DCv19AC76ibZIEy6JTKhQ5jZRDW1fABPtl3x4pbxbqm2CFjQbKleWXEeT9Nr+r29vB/arG0oYo20jN+G/wiUYG5Iwleab2VqECWo/j472WxUt5p/Xq+h+v9M8AP/fNqRDwxPDQ1OwLz29iHoggKsta+3fUzVDaj+diPqfQUkYgDejVRX14KSYqIwsGWnx9JyQmBwpCIKpcaIZoqHhgRk4zZKAVMOpgStDw8IpADRbWwY0VThTeXQOdsB8b1tVeTTsz16dyPrGLzapetg5RhhmfP7ioFSDCf29ujr9PYhT/b3w9V9biRGoi7HeLXkfj03gXutyVXNl0+8oWBWkujRYFfi7Qek2Vtz6oVMvKEX2hXQ6jyU7oJ0khoWk5oGBgRPBtZC53X77gzYqzoPIKCd9wzbOLpZFQGA3FCQiZf/jyoCSE8NQUmCdgcd7Boas2Vf1uBUjk5vRMKnd/1S79ytBGl5TsJOS3RjdXU27J/QTMVzQHbbY5hwSd1WFFAzFhV/FxjHO+MWxyA2clUgu85G1wFlrPrattk1FSlRb9Gh0X3S1cvaLCIgeKLjafI38WNKWZul2GYBpaJA/mc9cvimv1tOe6yQ3Pq81yQagcsTegEmSTvOnEnQMnPmxOkKN6P7lOAHrIk5mhykAJu+aZPiCDq5ElufVV8gdw9/XFtRWYPk3UExxgMZNF7tQV9KjBa05GB6EDvOBBIGdPH2/g3Ocx7L3VA9Uz/G2qjJT30Dnv57f5B/aj0RnzlBG59zNb02Ut415Yxcky/xn1CR/d790fsAA+k/fVrFn8siherw8QYZ4XCoF5LJkirnQoWeWNv6U65rQCaHYYqkuawwVG2cS7YlMJflFrWGvr+nQiFlaW4uWXYAzq0hntNPYyrqq4TDIwwJ21urLf4lmfTz2C9Mn7r9OhA5coFxbqs62hSgROU5NfO6vanl3rQzZpCBCb21EeYb0PpUV21QmliHHSvsATS2B7Co4wCyFwyiBK6G003dWISALEdTZKt+YcX1MWBX/ghCt4cHHvka43ztL8vpOCNBG3Ihwi+z5pmjYEgt4F6HAeJnkeSLIx7LuCiIPncnAoQHDV5R9okQab2ThEosChpJcuex+FKbxAyL66AGd3SPozxhrjK7kTfeFCunz4/eakxjE8C98Wb364mU/RsNM86IODHp92YYdY0UuV0VaFvf8RMa3yKWyKUw/gTNWu7XolmHeMiWtxLq88qV4bn14s+jHyF5wcbXh08zySlbCw+5yRYJNocT/1h6HUXgH7o5YUzLmd+NWbNIgsViYsrzbsoBdvpPthK7KEG/2gkASysaVdJsA4nj9hG0VxQMlZnGq5QzT8l9zo30nGX3b8EoM28XTutiMqww5vlPNPoWOM1jJSo83b77mGOcuXfuvjaCpE5uikYGUvIkXWARsyceslB40/ZDbciNy0FLrA5jJGflCqQ0S1HRgWRcl8ZV4rnweYEPdbVdLNw6blc1Rt/8zuybTRaNujiDRleVCgtLYuPEgzTeSFrQ/Q4V3qVJLR5FSP6CdzipF6mriHLKbS6LElDDnOSm5hI4WCKZ/2p/PLdE51MwS9c4PZeqg2SHQcnPpsQFv6Ufw+ALQDyjj8S5zr1TsmTeV6IPfXVXaPBPyNJqO2UQn3byejzZ4cb0WovzPg9SlNbTUKZ10lGzN+XzcXQQ5KUqM+ZBuhh1rs4VkL5oJs5RqcnpmaIfNqp+LUfiMSDZwgi28ra8Swm86H/ZMAvsHal5ootrjm0zpYo7Ep3LiQ4Omg9C0Wb3EjfYldJuhyUWXXEctb9ymrrPoblChEQ4yf7gIVw6C6MFJN4R/9HMPaPw771atNy0EB41EqiIDnpK+oSa9UMfH77Llag1ev69nqEJx+jL5cXFkMrRTt6nmAJ4AKeIIGP7t4O3dH35hPZdROS88/+S/9KOvSHf0/9zVrhk5aes2f30tUiAqOiX1Eh3BlUk13KZZtbzes05wK7hgX9IbKmM7pf6z2D2vTb2EEbxtmmLSmaZuW3NJaApNP89q9awIO04ARODM48054I+Lkvs4Ox7gOaknEZ8yC4fKrri14+CZttzkA0PgtnrDbfZlN1dvYILzOnHdaaFAOF2MsLbwc/cDrTiZH80ERfDw6TJ7Rt2iMl5VJJtEi8zi92BHgvEHHiePhh/1ph2kPfNQOP59a9SCbtHqF9BhlPLrbyBvRMLfkngcnE1kZjvLNMGGIXBSjXgzgtmB/BQT57bhoHm9rblgoob5mvuu0hTYtSTmY0TOkJoZhGZDxGd4350IH0tmkA46EbdLuCnWUL2TihNXcdn2nLJ6P4X2APKQ+rFaeX1i2CvP3ALnCuEI7+xuNtDViihdmt/1qe0tUi8pta8VJr383N4B6uYjytyAvMG1xzM=
*/