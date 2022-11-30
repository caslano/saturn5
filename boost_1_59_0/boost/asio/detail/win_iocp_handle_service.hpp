//
// detail/win_iocp_handle_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/associated_cancellation_slot.hpp>
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

  // Release ownership of a handle.
  BOOST_ASIO_DECL native_handle_type release(implementation_type& impl,
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_write_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_write_some"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.handle_, o);

    start_write_op(impl, 0,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers), o);
    p.v = p.p = 0;
  }

  // Start an asynchronous write at a specified offset. The data being written
  // must be valid for the lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl,
      uint64_t offset, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_write_op<
        ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_write_some_at"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.handle_, o);

    start_write_op(impl, offset,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::first(buffers), o);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_read_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_read_some"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.handle_, o);

    start_read_op(impl, 0,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers), o);
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
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_handle_read_op<
        MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    operation* o = p.p = new (p.v) op(buffers, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((iocp_service_.context(), *p.p, "handle", &impl,
          reinterpret_cast<uintmax_t>(impl.handle_), "async_read_some_at"));

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
      o = &slot.template emplace<iocp_op_cancellation>(impl.handle_, o);

    start_read_op(impl, offset,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::first(buffers), o);
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

  // The type of a NtSetInformationFile function pointer.
  typedef LONG (NTAPI *nt_set_info_fn)(HANDLE, ULONG_PTR*, void*, ULONG, ULONG);

  // Helper function to get the NtSetInformationFile function pointer. If no
  // NtSetInformationFile pointer has been obtained yet, one is obtained using
  // GetProcAddress and the pointer is cached. Returns a null pointer if
  // NtSetInformationFile is not available.
  BOOST_ASIO_DECL nt_set_info_fn get_nt_set_info();

  // Helper function to emulate InterlockedCompareExchangePointer functionality
  // for:
  // - very old Platform SDKs; and
  // - platform SDKs where MSVC's /Wp64 option causes spurious warnings.
  BOOST_ASIO_DECL void* interlocked_compare_exchange_pointer(
      void** dest, void* exch, void* cmp);

  // Helper function to emulate InterlockedExchangePointer functionality for:
  // - very old Platform SDKs; and
  // - platform SDKs where MSVC's /Wp64 option causes spurious warnings.
  BOOST_ASIO_DECL void* interlocked_exchange_pointer(void** dest, void* val);

  // Helper class used to implement per operation cancellation.
  class iocp_op_cancellation : public operation
  {
  public:
    iocp_op_cancellation(HANDLE h, operation* target)
      : operation(&iocp_op_cancellation::do_complete),
        handle_(h),
        target_(target)
    {
    }

    static void do_complete(void* owner, operation* base,
        const boost::system::error_code& result_ec,
        std::size_t bytes_transferred)
    {
      iocp_op_cancellation* o = static_cast<iocp_op_cancellation*>(base);
      o->target_->complete(owner, result_ec, bytes_transferred);
    }

    void operator()(cancellation_type_t type)
    {
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        ::CancelIoEx(handle_, this);
      }
#else // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
      (void)type;
#endif // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
    }

  private:
    HANDLE handle_;
    operation* target_;
  };

  // The IOCP service used for running asynchronous operations and dispatching
  // handlers.
  win_iocp_io_context& iocp_service_;

  // Pointer to NtSetInformationFile implementation.
  void* nt_set_info_;

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