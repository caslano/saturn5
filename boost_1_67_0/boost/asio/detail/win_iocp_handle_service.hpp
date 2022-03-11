//
// detail/win_iocp_handle_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/win_iocp_handle_read_op.hpp>
#include <boost/asio/detail/win_iocp_handle_write_op.hpp>
#include <boost/asio/detail/win_iocp_io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_handle_service :
  public execution_context_service_base<win_iocp_handle_service>
{
public:
  // The native type of a stream handle.
  typedef HANDLE native_handle_type;

  // The implementation type of the stream handle.
  class implementation_type
  {
  public:
    // Default constructor.
    implementation_type()
      : handle_(INVALID_HANDLE_VALUE),
        safe_cancellation_thread_id_(0),
        next_(0),
        prev_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class win_iocp_handle_service;

    // The native stream handle representation.
    native_handle_type handle_;

    // The ID of the thread from which it is safe to cancel asynchronous
    // operations. 0 means no asynchronous operations have been started yet.
    // ~0 means asynchronous operations have been started from more than one
    // thread, and cancellation is not supported for the handle.
    DWORD safe_cancellation_thread_id_;

    // Pointers to adjacent handle implementations in linked list.
    implementation_type* next_;
    implementation_type* prev_;
  };

  BOOST_ASIO_DECL win_iocp_handle_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new handle implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Move-construct a new handle implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl);

  // Move-assign from another handle implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      win_iocp_handle_service& other_service,
      implementation_type& other_impl);

  // Destroy a handle implementation.
  BOOST_ASIO_DECL void destroy(implementation_type& impl);

  // Assign a native handle to a handle implementation.
  BOOST_ASIO_DECL boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& handle, boost::system::error_code& ec);

  // Determine whether the handle is open.
  bool is_open(const implementation_type& impl) const
  {
    return impl.handle_ != INVALID_HANDLE_VALUE;
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

  // Write the given data. Returns the number of bytes written.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return write_some_at(impl, 0, buffers, ec);
  }

  // Write the given data at the specified offset. Returns the number of bytes
  // written.
  template <typename ConstBufferSequence>
  size_t write_some_at(implementation_type& impl, uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    boost::asio::const_buffer buffer =
      buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence>::first(buffers);

    return do_write(impl, offset, buffer, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_write_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_write_some"));

    start_write_op(impl, 0,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers), p.p);
    p.v = p.p = 0;
  }

  // Start an asynchronous write at a specified offset. The data being written
  // must be valid for the lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl,
      uint64_t offset, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_write_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_write_some_at"));

    start_write_op(impl, offset,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers), p.p);
    p.v = p.p = 0;
  }

  // Read some data. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return read_some_at(impl, 0, buffers, ec);
  }

  // Read some data at a specified offset. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t read_some_at(implementation_type& impl, uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    boost::asio::mutable_buffer buffer =
      buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence>::first(buffers);

    return do_read(impl, offset, buffer, ec);
  }

  // Start an asynchronous read. The buffer for the data being received must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_read_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_read_some"));

    start_read_op(impl, 0,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers), p.p);
    p.v = p.p = 0;
  }

  // Start an asynchronous read at a specified offset. The buffer for the data
  // being received must be valid for the lifetime of the asynchronous
  // operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl,
      uint64_t offset, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_read_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_read_some_at"));

    start_read_op(impl, offset,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers), p.p);
    p.v = p.p = 0;
  }

private:
  // Prevent the use of the null_buffers type with this service.
  size_t write_some(implementation_type& impl,
      const null_buffers& buffers, boost::system::error_code& ec);
  size_t write_some_at(implementation_type& impl, uint64_t offset,
      const null_buffers& buffers, boost::system::error_code& ec);
  template <typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const null_buffers& buffers, Handler& handler,
      const IoExecutor& io_ex);
  template <typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl, uint64_t offset,
      const null_buffers& buffers, Handler& handler, const IoExecutor& io_ex);
  size_t read_some(implementation_type& impl,
      const null_buffers& buffers, boost::system::error_code& ec);
  size_t read_some_at(implementation_type& impl, uint64_t offset,
      const null_buffers& buffers, boost::system::error_code& ec);
  template <typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const null_buffers& buffers, Handler& handler,
      const IoExecutor& io_ex);
  template <typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl, uint64_t offset,
      const null_buffers& buffers, Handler& handler, const IoExecutor& io_ex);

  // Helper class for waiting for synchronous operations to complete.
  class overlapped_wrapper;

  // Helper function to perform a synchronous write operation.
  BOOST_ASIO_DECL size_t do_write(implementation_type& impl,
      uint64_t offset, const boost::asio::const_buffer& buffer,
      boost::system::error_code& ec);

  // Helper function to start a write operation.
  BOOST_ASIO_DECL void start_write_op(implementation_type& impl,
      uint64_t offset, const boost::asio::const_buffer& buffer,
      operation* op);

  // Helper function to perform a synchronous write operation.
  BOOST_ASIO_DECL size_t do_read(implementation_type& impl,
      uint64_t offset, const boost::asio::mutable_buffer& buffer,
      boost::system::error_code& ec);

  // Helper function to start a read operation.
  BOOST_ASIO_DECL void start_read_op(implementation_type& impl,
      uint64_t offset, const boost::asio::mutable_buffer& buffer,
      operation* op);

  // Update the ID of the thread from which cancellation is safe.
  BOOST_ASIO_DECL void update_cancellation_thread_id(implementation_type& impl);

  // Helper function to close a handle when the associated object is being
  // destroyed.
  BOOST_ASIO_DECL void close_for_destruction(implementation_type& impl);

  // The IOCP service used for running asynchronous operations and dispatching
  // handlers.
  win_iocp_io_context& iocp_service_;

  // Mutex to protect access to the linked list of implementations.
  mutex mutex_;

  // The head of a linked list of all implementations.
  implementation_type* impl_list_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_handle_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_SERVICE_HPP

/* win_iocp_handle_service.hpp
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
*/