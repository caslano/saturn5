//
// windows/basic_object_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_OBJECT_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_OBJECT_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/win_object_handle_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Provides object-oriented handle functionality.
/**
 * The windows::basic_object_handle class provides asynchronous and blocking
 * object-oriented handle functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = executor>
class basic_object_handle
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the handle type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The handle type when rebound to the specified executor.
    typedef basic_object_handle<Executor1> other;
  };

  /// The native representation of a handle.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef boost::asio::detail::win_object_handle_service::native_handle_type
    native_handle_type;
#endif

  /// An object handle is always the lowest layer.
  typedef basic_object_handle lowest_layer_type;

  /// Construct an object handle without opening it.
  /**
   * This constructor creates an object handle without opening it.
   *
   * @param ex The I/O executor that the object handle will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * object handle.
   */
  explicit basic_object_handle(const executor_type& ex)
    : impl_(ex)
  {
  }

  /// Construct an object handle without opening it.
  /**
   * This constructor creates an object handle without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the object handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the object handle.
   */
  template <typename ExecutionContext>
  explicit basic_object_handle(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value,
        basic_object_handle
      >::type* = 0)
    : impl_(context)
  {
  }

  /// Construct an object handle on an existing native handle.
  /**
   * This constructor creates an object handle object to hold an existing native
   * handle.
   *
   * @param ex The I/O executor that the object handle will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * object handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_object_handle(const executor_type& ex,
      const native_handle_type& native_handle)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct an object handle on an existing native handle.
  /**
   * This constructor creates an object handle object to hold an existing native
   * handle.
   *
   * @param context An execution context which provides the I/O executor that
   * the object handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the object handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_object_handle(ExecutionContext& context,
      const native_handle_type& native_handle,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct an object handle from another.
  /**
   * This constructor moves an object handle from one object to another.
   *
   * @param other The other object handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_object_handle(const executor_type&)
   * constructor.
   */
  basic_object_handle(basic_object_handle&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign an object handle from another.
  /**
   * This assignment operator moves an object handle from one object to another.
   *
   * @param other The other object handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_object_handle(const executor_type&)
   * constructor.
   */
  basic_object_handle& operator=(basic_object_handle&& other)
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
   * layers. Since an object handle cannot contain any further layers, it simply
   * returns a reference to itself.
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
   * layers. Since an object handle cannot contain any further layers, it simply
   * returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  /// Assign an existing native handle to the handle.
  /*
   * This function opens the handle to hold an existing native handle.
   *
   * @param handle A native handle.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& handle)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native handle to the handle.
  /*
   * This function opens the handle to hold an existing native handle.
   *
   * @param handle A native handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& handle,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(impl_.get_implementation(), handle, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the handle is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the handle.
  /**
   * This function is used to close the handle. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
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

  /// Close the handle.
  /**
   * This function is used to close the handle. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the native handle representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * handle. This is intended to allow access to native handle functionality
   * that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the handle.
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

  /// Cancel all asynchronous operations associated with the handle.
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

  /// Perform a blocking wait on the object handle.
  /**
   * This function is used to wait for the object handle to be set to the
   * signalled state. This function blocks and does not return until the object
   * handle has been set to the signalled state.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void wait()
  {
    boost::system::error_code ec;
    impl_.get_service().wait(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "wait");
  }

  /// Perform a blocking wait on the object handle.
  /**
   * This function is used to wait for the object handle to be set to the
   * signalled state. This function blocks and does not return until the object
   * handle has been set to the signalled state.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  void wait(boost::system::error_code& ec)
  {
    impl_.get_service().wait(impl_.get_implementation(), ec);
  }

  /// Start an asynchronous wait on the object handle.
  /**
   * This function is be used to initiate an asynchronous wait against the
   * object handle. It always returns immediately.
   *
   * @param handler The handler to be called when the object handle is set to
   * the signalled state. Copies will be made of the handler as required. The
   * function signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitHandler,
      void (boost::system::error_code))
  async_wait(
      BOOST_ASIO_MOVE_ARG(WaitHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitHandler, void (boost::system::error_code)>(
        initiate_async_wait(this), handler);
  }

private:
  // Disallow copying and assignment.
  basic_object_handle(const basic_object_handle&) BOOST_ASIO_DELETED;
  basic_object_handle& operator=(const basic_object_handle&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_object_handle* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WaitHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(WaitHandler) handler) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WaitHandler.
      BOOST_ASIO_WAIT_HANDLER_CHECK(WaitHandler, handler) type_check;

      detail::non_const_lvalue<WaitHandler> handler2(handler);
      self_->impl_.get_service().async_wait(
          self_->impl_.get_implementation(), handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_object_handle* self_;
  };

  boost::asio::detail::io_object_impl<
    boost::asio::detail::win_object_handle_service, Executor> impl_;
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_BASIC_OBJECT_HANDLE_HPP

/* basic_object_handle.hpp
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
*/