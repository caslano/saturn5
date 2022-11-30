//
// detail/win_object_handle_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)

#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/wait_handler.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_object_handle_service :
  public execution_context_service_base<win_object_handle_service>
{
public:
  // The native type of an object handle.
  typedef HANDLE native_handle_type;

  // The implementation type of the object handle.
  class implementation_type
  {
   public:
    // Default constructor.
    implementation_type()
      : handle_(INVALID_HANDLE_VALUE),
        wait_handle_(INVALID_HANDLE_VALUE),
        owner_(0),
        next_(0),
        prev_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class win_object_handle_service;

    // The native object handle representation. May be accessed or modified
    // without locking the mutex.
    native_handle_type handle_;

    // The handle used to unregister the wait operation. The mutex must be
    // locked when accessing or modifying this member.
    HANDLE wait_handle_;

    // The operations waiting on the object handle. If there is a registered
    // wait then the mutex must be locked when accessing or modifying this
    // member
    op_queue<wait_op> op_queue_;

    // The service instance that owns the object handle implementation.
    win_object_handle_service* owner_;

    // Pointers to adjacent handle implementations in linked list. The mutex
    // must be locked when accessing or modifying these members.
    implementation_type* next_;
    implementation_type* prev_;
  };

  // Constructor.
  BOOST_ASIO_DECL win_object_handle_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new handle implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Move-construct a new handle implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl);

  // Move-assign from another handle implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      win_object_handle_service& other_service,
      implementation_type& other_impl);

  // Destroy a handle implementation.
  BOOST_ASIO_DECL void destroy(implementation_type& impl);

  // Assign a native handle to a handle implementation.
  BOOST_ASIO_DECL boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& handle, boost::system::error_code& ec);

  // Determine whether the handle is open.
  bool is_open(const implementation_type& impl) const
  {
    return impl.handle_ != INVALID_HANDLE_VALUE && impl.handle_ != 0;
  }

  // Destroy a handle implementation.
  BOOST_ASIO_DECL boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec);

  // Get the native handle representation.
  native_handle_type native_handle(const implementation_type& impl) const
  {
    return impl.handle_;
  }

  // Cancel all operations associated with the handle.
  BOOST_ASIO_DECL boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec);

  // Perform a synchronous wait for the object to enter a signalled state.
  BOOST_ASIO_DECL void wait(implementation_type& impl,
      boost::system::error_code& ec);

  /// Start an asynchronous wait.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef wait_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(), *p.p, "object_handle",
          &impl, reinterpret_cast<uintmax_t>(impl.wait_handle_), "async_wait"));

    start_wait_op(impl, p.p);
    p.v = p.p = 0;
  }

private:
  // Helper function to start an asynchronous wait operation.
  BOOST_ASIO_DECL void start_wait_op(implementation_type& impl, wait_op* op);

  // Helper function to register a wait operation.
  BOOST_ASIO_DECL void register_wait_callback(
      implementation_type& impl, mutex::scoped_lock& lock);

  // Callback function invoked when the registered wait completes.
  static BOOST_ASIO_DECL VOID CALLBACK wait_callback(
      PVOID param, BOOLEAN timeout);

  // The scheduler used to post completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  // Mutex to protect access to internal state.
  mutex mutex_;

  // The head of a linked list of all implementations.
  implementation_type* impl_list_;

  // Flag to indicate that the dispatcher has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_object_handle_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)

#endif // BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP

/* win_object_handle_service.hpp
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
*/