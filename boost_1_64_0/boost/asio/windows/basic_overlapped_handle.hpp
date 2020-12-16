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
i7PAe8ALqvrv1fsSuBa4Pxvz02wPcAPwK+BGYAwGYjOwIXAL8BvgVuApQ8nZlxfgijFpop19GY5wnHcJO+vyNZx5tiUHrhVchPMsPMcS6QzLmc+v5ML1h+OZldDzKnJOpTFc4GxKMZz1TMphuE/grOdPiuD6h5w/gbCo8BmU6+CsZ00Ow9nPl0Q+WxJ+liT0HEnFz44Ezo3cgXpvhtsD9wGcOoJ7NOBawRXAlcAtOVJ5VqTyV/mr/FX+Kn+Vv8pf5a/yV/mr/P26v/+M/n+L1m1+Jf3/3tgESF4q+v/I1K//f69F//9S6qKfpN7YbuoRd7w3oP/XokWY/j/3bUqFZgP17QJpWkbSK2ZcM60jWCL+B6PpGZO+s+S1oZFdz7gpzwdsB10+6hqf3BZaxL4085+4uCZxuYH/EBDns+sW9wF9V7iAbvGas9gNW6aCusW7lE23GHWw6xYfVJF1i1F/rVt8UUvUOYJucbIzXJf9IaQbviI4Dmc+E0BangnY1MimS8w4raeOPji7LumZ9HKRf5he7jq2YQxcEu3BPAy6MmsbqJdrqyP5qVzoLmN7AumyqBt5dnt+yC9MT3dNhDMCj4BOrbTWya7fynqxHqSNfkaA8dHPCDBe932fCvR9sE0//4xArify3M7RbYdIiDK3+620zW2kiTq3EWef2wUrzzi3SR99bq/DmC1zY3D/x+b2bdgEGce5HUlfvarTn+dPDv/c7rjKMg5nOTdQKrQHHRwPpm0ZPtcZZ5O14n/bYTs3QJ2usRL3hcOm68wyMlebcW6d76tC21HrO08U/wipcx3Jt7g4YEs1FXippD9kNERv1DAcki4N4TXv858TSBU6WEAWuixHHKyyCQ18FwpNjsU26WStT5wJ7LGatsXFzzxgA9ynThsBflidKw78cHb96nOVdct8kWVdzlrrmEaXdXlrbbIO6X65rBscE34moYN5JsFWJ30mIZKsI230MwmM17Js9TmcSdjUqGJnEqbF+RPXpz50KtCU2bus7TizzCZtba3T/0fTDxK7DC+kPjrpseNYajmTsPR+M+wK0KSibu5w+c75dULSxgnvFui8qtnPCHDcl0meeVq/xRB/V3ByAmmgjSxhbraF9aBeb3pg75lhsXp+QHZw3n0h5SeHn2+gPs87Ev93FWnOPyn5Juo5Xk38U2nDX+rC+ibyDAPn2TmcYYj+TCs86xmGzeyAD5CmMbGdaS97nfCGf+0c+QwDeYR6M6jSYOBjku7K5JyYWI5JIK/Xkw+py5L0XUs7EIb/opxvYJo15CdIavF3Sa6raiXbzjewbMgLTeNh2fnIZ5SEbU1eoNZI2QXMW991Y62LxGu/jOfK6iIJ5HmK/XYLfxRpu85LHvDzVyr55ZtNkt7jhm59NuXregk75IMeHO4HO6Wudu12mPNivLnP/ogZl264VU/sGU+QfCYivMfv5X4qTxMH9HMpl089ZIYdlTbn2ttsqdtYyUN0HySPIS63KnAFniP3PCw25A3oZGGP+HGVQRvGv3tQbBjHuqED19Xl8QTqd73Qf+t0qUzw0UinmXexqdslZW9z+VS8zNUsXb8UqZ8rav3G6fpNlPr1dLlUJ1dgvu3fwvnJerURmqGubFVLwsah7FVS1yagSlfZrOc4SedzedUI7M/3xDNylyNQ11obRecw9nFnvEfCNE+1jUlSRoxZXxVSXz4rtU50BuvcUuqT43DDKuN16k6jHuudJ+HfuL3Q6l9khjuuw15pQ8cp11x1pftO1ZnP698I3e88F6mu6P9uqp0xVL1oXKH6OLqr+x0erCxGqqucfdSXzoGqzNVNveHyqDT3CeR8j5rA9t8s7Vkc60MPdEJ/nlQ=
*/