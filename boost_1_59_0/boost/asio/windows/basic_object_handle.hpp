//
// windows/basic_object_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/win_object_handle_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

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
template <typename Executor = any_io_executor>
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
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
   * object handle. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
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
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitToken,
      void (boost::system::error_code))
  async_wait(
      BOOST_ASIO_MOVE_ARG(WaitToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitToken, void (boost::system::error_code)>(
        initiate_async_wait(this), token);
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
          self_->impl_.get_implementation(),
          handler2.value, self_->impl_.get_executor());
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