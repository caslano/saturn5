//
// windows/basic_overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/win_iocp_handle_service.hpp>
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

/// Provides Windows handle functionality for objects that support
/// overlapped I/O.
/**
 * The windows::overlapped_handle class provides the ability to wrap a Windows
 * handle. The underlying object referred to by the handle must support
 * overlapped I/O.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor = executor>
class basic_overlapped_handle
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the handle type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The handle type when rebound to the specified executor.
    typedef basic_overlapped_handle<Executor1> other;
  };

  /// The native representation of a handle.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef boost::asio::detail::win_iocp_handle_service::native_handle_type
    native_handle_type;
#endif

  /// An overlapped_handle is always the lowest layer.
  typedef basic_overlapped_handle lowest_layer_type;

  /// Construct an overlapped handle without opening it.
  /**
   * This constructor creates an overlapped handle without opening it.
   *
   * @param ex The I/O executor that the overlapped handle will use, by default,
   * to dispatch handlers for any asynchronous operations performed on the
   * overlapped handle.
   */
  explicit basic_overlapped_handle(const executor_type& ex)
    : impl_(ex)
  {
  }

  /// Construct an overlapped handle without opening it.
  /**
   * This constructor creates an overlapped handle without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the overlapped handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the overlapped handle.
   */
  template <typename ExecutionContext>
  explicit basic_overlapped_handle(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value,
        basic_overlapped_handle
      >::type* = 0)
    : impl_(context)
  {
  }

  /// Construct an overlapped handle on an existing native handle.
  /**
   * This constructor creates an overlapped handle object to hold an existing
   * native handle.
   *
   * @param ex The I/O executor that the overlapped handle will use, by default,
   * to dispatch handlers for any asynchronous operations performed on the
   * overlapped handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_overlapped_handle(const executor_type& ex,
      const native_handle_type& native_handle)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(impl_.get_implementation(), native_handle, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct an overlapped handle on an existing native handle.
  /**
   * This constructor creates an overlapped handle object to hold an existing
   * native handle.
   *
   * @param context An execution context which provides the I/O executor that
   * the overlapped handle will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the overlapped handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_overlapped_handle(ExecutionContext& context,
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
  /// Move-construct an overlapped handle from another.
  /**
   * This constructor moves a handle from one object to another.
   *
   * @param other The other overlapped handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c overlapped_handle(const executor_type&)
   * constructor.
   */
  basic_overlapped_handle(basic_overlapped_handle&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign an overlapped handle from another.
  /**
   * This assignment operator moves a handle from one object to another.
   *
   * @param other The other overlapped handle object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c overlapped_handle(const executor_type&)
   * constructor.
   */
  basic_overlapped_handle& operator=(basic_overlapped_handle&& other)
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
   * layers. Since an overlapped_handle cannot contain any further layers, it
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
   * layers. Since an overlapped_handle cannot contain any further layers, it
   * simply returns a reference to itself.
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

protected:
  /// Protected destructor to prevent deletion through this type.
  /**
   * This function destroys the handle, cancelling any outstanding asynchronous
   * wait operations associated with the handle as if by calling @c cancel.
   */
  ~basic_overlapped_handle()
  {
  }

  boost::asio::detail::io_object_impl<
    boost::asio::detail::win_iocp_handle_service, Executor> impl_;

private:
  // Disallow copying and assignment.
  basic_overlapped_handle(const basic_overlapped_handle&) BOOST_ASIO_DELETED;
  basic_overlapped_handle& operator=(
      const basic_overlapped_handle&) BOOST_ASIO_DELETED;
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_BASIC_OVERLAPPED_HANDLE_HPP

/* basic_overlapped_handle.hpp
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
*/