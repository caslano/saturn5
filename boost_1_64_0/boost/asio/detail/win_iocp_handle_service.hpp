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
75z6OpU0T65Hv23f44S3gs93CJ5r03J1zXFI2YV9zzXlE3JfO6uSjjwS1QpOgmvsNvat8PuqQ83a76uGO95K1m9x74p9iLcTfdMEKybaHBThdE2Q3t+3xX6KtzOlPNGKi7hnI8uEayPhsu37JfYzvemEmRJlr4a+J2rYE8PvvWnTUt+2/b+izfQH98Xmu+4z4n+16pnhnr5j2+PNmsI3Jf6PrJ60YedLLSMczBa5R4gzXts7x22L7WbeJfa9o+/Lbt035rvl3+Qa6RHXsneV8Olqd67R3iVbZPdj4jdO7R7Ls8u2p8qawp3U5zQUc8XKGubKW/yxSa6678hljdfno9FYe/ms+xlRuYrxRhdAhnlGwt53k3WfqN0mTlUz2Tb1mqeITaL8Qp6bLNdzU/89dzLOirbfRZ8l/8RAAjbpvrtHMXfYz9Iu8yzphuOcstm6PSrK+4GGSYm2F0r9W1nJ+m75mtjvlXo21Roe9T1B43Xv69Dv3I3flW/1pq9vJ3a7v0pQGd52xS0hbB+46jGS+G+xzqJcVmHs+51GwRdMsKwT5Dvg2ZbrXB2VWYhMT1um8cUh7lXqTnu6JPy7sGNvdBjr9xrSPwaPp9dmByL9jgsfq3zcvs9SLpWzA/oWi8rmlhTkTCsM3WMek2jaPr3XTrjuZsz7sdhf8XTz+DVMaLs3xoTpZNqq98W+wzPAE2V/mt6fXSL3pqe/p5E+605cqeFtnPg1ey8w5xTcZnTVtueP4ney2beWiGmN6YDpgnHq6skid77RG+Z737b71F/tqq9P7h955Yu1CX+thPdpvanfPktnHmiIHXeQvT12Z17o0/fc8zi733PP47z1nnseZ/sht/6O20uH3Po5bpsPufV13J4+5NYneBwUkxjaBg1Ut+A2KLOONmjkpMhnRmbuPvwzIzN3//PPjGx/TuQzI3N3H/6ZkRIm+pmR+P9rz4x02oOaCHn6o/1ubPIUrn6wYG65FX19RmVYuid0qX+6iS/iuZGrz3Wn8Slkq6KmcToTQmZ9XHgaNVyyrpdyn+VYFZaH8YdR9lwvvOz1OxDXCMvXkMnufD1gt8XR84WOmqj5IlzDz+wkvohlvydCGj+w5w2ipFHVU0o7/m5gzXbZTHupbVA6d4Wlc1I9ytcZOxAn6dQ4w9K64jx3Wu8fbCc4WlppRKLXZcI1vA0xdTlMd1z5+e40vjOI0FHTWF5WXvt917DJUubTpT7b8tPnluYHfZMNy8s5h5EXUzeCzgTmOriZ64Tch5EXRH5eM6PnkaNXo+ePcNGfV/Fv+Nmrh/O8Zk9x52uzvVY4Wr5kE0rUfBGujj6glnxnBYU/tEbvyPJt+gjzHukuizOctutCd1mst/uN2srC1iabI/UlWplo+OSo7ceYIJlD79MNy7fU5TralF0XRm6jq6Lns2x2RS19T1jab2xgXQ1O44ap7jQ+YvcjUdMoLydR272a2usl/g1/N7lvcN3vJqc77XmOO1/X232PyZdLrWcB2uorgvRsuvK2y6Td5M3ky/gZ3X31z1dg74heKzRfIXmyct15etfuoz6MlqeGn4Pt1I/bIlzz14ORjHpN6Rj1u6arDAnX8H7xqijveAvz3Gm83e4zoqZROo1o91nDJev8WIQ+48OG9xlcz1WHuUbEPmP5NHe+fmP3GVHzJZ1GtHwRro4+o5Z8Z0n4hvcZvZPr12dw3Yh9Rnl+hPPp7T4jelkEdxpRy4Twps/4oFWUPuPDhvcZXNPVZ3CdqH1GywJ3Pi+3+4yo+ZROI1r+CNfwPsOkPaxt3RchjdfafUb0NOqINnq7UFN73cS/4f3GVfXoN/o4z1yhO297U2nfTd7srcOH2rhPUiM=
*/