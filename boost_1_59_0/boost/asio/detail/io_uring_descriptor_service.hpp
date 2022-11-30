//
// detail/io_uring_descriptor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/cancellation_type.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/io_uring_descriptor_read_at_op.hpp>
#include <boost/asio/detail/io_uring_descriptor_read_op.hpp>
#include <boost/asio/detail/io_uring_descriptor_write_at_op.hpp>
#include <boost/asio/detail/io_uring_descriptor_write_op.hpp>
#include <boost/asio/detail/io_uring_null_buffers_op.hpp>
#include <boost/asio/detail/io_uring_service.hpp>
#include <boost/asio/detail/io_uring_wait_op.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/posix/descriptor_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class io_uring_descriptor_service :
  public execution_context_service_base<io_uring_descriptor_service>
{
public:
  // The native type of a descriptor.
  typedef int native_handle_type;

  // The implementation type of the descriptor.
  class implementation_type
    : private boost::asio::detail::noncopyable
  {
  public:
    // Default constructor.
    implementation_type()
      : descriptor_(-1),
        state_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class io_uring_descriptor_service;

    // The native descriptor representation.
    int descriptor_;

    // The current state of the descriptor.
    descriptor_ops::state_type state_;

    // Per I/O object data used by the io_uring_service.
    io_uring_service::per_io_object_data io_object_data_;
  };

  // Constructor.
  BOOST_ASIO_DECL io_uring_descriptor_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new descriptor implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Move-construct a new descriptor implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another descriptor implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      io_uring_descriptor_service& other_service,
      implementation_type& other_impl);

  // Destroy a descriptor implementation.
  BOOST_ASIO_DECL void destroy(implementation_type& impl);

  // Assign a native descriptor to a descriptor implementation.
  BOOST_ASIO_DECL boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& native_descriptor,
      boost::system::error_code& ec);

  // Determine whether the descriptor is open.
  bool is_open(const implementation_type& impl) const
  {
    return impl.descriptor_ != -1;
  }

  // Destroy a descriptor implementation.
  BOOST_ASIO_DECL boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec);

  // Get the native descriptor representation.
  native_handle_type native_handle(const implementation_type& impl) const
  {
    return impl.descriptor_;
  }

  // Release ownership of the native descriptor representation.
  BOOST_ASIO_DECL native_handle_type release(implementation_type& impl);

  // Cancel all operations associated with the descriptor.
  BOOST_ASIO_DECL boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec);

  // Perform an IO control command on the descriptor.
  template <typename IO_Control_Command>
  boost::system::error_code io_control(implementation_type& impl,
      IO_Control_Command& command, boost::system::error_code& ec)
  {
    descriptor_ops::ioctl(impl.descriptor_, impl.state_,
        command.name(), static_cast<ioctl_arg_type*>(command.data()), ec);
    return ec;
  }

  // Gets the non-blocking mode of the descriptor.
  bool non_blocking(const implementation_type& impl) const
  {
    return (impl.state_ & descriptor_ops::user_set_non_blocking) != 0;
  }

  // Sets the non-blocking mode of the descriptor.
  boost::system::error_code non_blocking(implementation_type& impl,
      bool mode, boost::system::error_code& ec)
  {
    descriptor_ops::set_user_non_blocking(
        impl.descriptor_, impl.state_, mode, ec);
    return ec;
  }

  // Gets the non-blocking mode of the native descriptor implementation.
  bool native_non_blocking(const implementation_type& impl) const
  {
    return (impl.state_ & descriptor_ops::internal_non_blocking) != 0;
  }

  // Sets the non-blocking mode of the native descriptor implementation.
  boost::system::error_code native_non_blocking(implementation_type& impl,
      bool mode, boost::system::error_code& ec)
  {
    descriptor_ops::set_internal_non_blocking(
        impl.descriptor_, impl.state_, mode, ec);
    return ec;
  }

  // Wait for the descriptor to become ready to read, ready to write, or to have
  // pending error conditions.
  boost::system::error_code wait(implementation_type& impl,
      posix::descriptor_base::wait_type w, boost::system::error_code& ec)
  {
    switch (w)
    {
    case posix::descriptor_base::wait_read:
      descriptor_ops::poll_read(impl.descriptor_, impl.state_, ec);
      break;
    case posix::descriptor_base::wait_write:
      descriptor_ops::poll_write(impl.descriptor_, impl.state_, ec);
      break;
    case posix::descriptor_base::wait_error:
      descriptor_ops::poll_error(impl.descriptor_, impl.state_, ec);
      break;
    default:
      ec = boost::asio::error::invalid_argument;
      break;
    }

    return ec;
  }

  // Asynchronously wait for the descriptor to become ready to read, ready to
  // write, or to have pending error conditions.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      posix::descriptor_base::wait_type w,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    int op_type;
    int poll_flags;
    switch (w)
    {
    case posix::descriptor_base::wait_read:
      op_type = io_uring_service::read_op;
      poll_flags = POLLIN;
      break;
    case posix::descriptor_base::wait_write:
      op_type = io_uring_service::write_op;
      poll_flags = POLLOUT;
      break;
    case posix::descriptor_base::wait_error:
      op_type = io_uring_service::except_op;
      poll_flags = POLLPRI | POLLERR | POLLHUP;
      break;
    default:
      op_type = -1;
      poll_flags = -1;
      return;
    }

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_,
        poll_flags, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected() && op_type != -1)
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(
            &io_uring_service_, &impl.io_object_data_, op_type);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "descriptor", &impl, impl.descriptor_, "async_wait"));

    start_op(impl, op_type, p.p, is_continuation, op_type == -1);
    p.v = p.p = 0;
  }

  // Write some data to the descriptor.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return descriptor_ops::sync_write1(impl.descriptor_,
          impl.state_, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), ec);
    }
    else
    {
      bufs_type bufs(buffers);

      return descriptor_ops::sync_write(impl.descriptor_, impl.state_,
          bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
    }
  }

  // Wait until data can be written without blocking.
  size_t write_some(implementation_type& impl,
      const null_buffers&, boost::system::error_code& ec)
  {
    // Wait for descriptor to become ready.
    descriptor_ops::poll_write(impl.descriptor_, impl.state_, ec);

    return 0;
  }

  // Start an asynchronous write. The data being sent must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_descriptor_write_op<
      ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_,
        impl.state_, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "descriptor", &impl, impl.descriptor_, "async_write_some"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be written without blocking.
  template <typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const null_buffers&, Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_, POLLOUT, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(),
          *p.p, "descriptor", &impl, impl.descriptor_,
          "async_write_some(null_buffers)"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation, false);
    p.v = p.p = 0;
  }

  // Write some data to the descriptor at the specified offset.
  template <typename ConstBufferSequence>
  size_t write_some_at(implementation_type& impl, uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return descriptor_ops::sync_write_at1(impl.descriptor_,
          impl.state_, offset, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), ec);
    }
    else
    {
      bufs_type bufs(buffers);

      return descriptor_ops::sync_write_at(impl.descriptor_, impl.state_,
          offset, bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
    }
  }

  // Wait until data can be written without blocking.
  size_t write_some_at(implementation_type& impl, uint64_t,
      const null_buffers& buffers, boost::system::error_code& ec)
  {
    return write_some(impl, buffers, ec);
  }

  // Start an asynchronous write at the specified offset. The data being sent
  // must be valid for the lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl, uint64_t offset,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_descriptor_write_at_op<
      ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_,
        impl.state_, offset, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "descriptor", &impl, impl.descriptor_, "async_write_some"));

    start_op(impl, io_uring_service::write_op, p.p, is_continuation,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }

  // Start an asynchronous wait until data can be written without blocking.
  template <typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl,
      const null_buffers& buffers, Handler& handler, const IoExecutor& io_ex)
  {
    return async_write_some(impl, buffers, handler, io_ex);
  }

  // Read some data from the stream. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return descriptor_ops::sync_read1(impl.descriptor_,
          impl.state_, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), ec);
    }
    else
    {
      bufs_type bufs(buffers);

      return descriptor_ops::sync_read(impl.descriptor_, impl.state_,
          bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
    }
  }

  // Wait until data can be read without blocking.
  size_t read_some(implementation_type& impl,
      const null_buffers&, boost::system::error_code& ec)
  {
    // Wait for descriptor to become ready.
    descriptor_ops::poll_read(impl.descriptor_, impl.state_, ec);

    return 0;
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_descriptor_read_op<
      MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_,
        impl.state_, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "descriptor", &impl, impl.descriptor_, "async_read_some"));

    start_op(impl, io_uring_service::read_op, p.p, is_continuation,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }

  // Wait until data can be read without blocking.
  template <typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const null_buffers&, Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_, POLLIN, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(),
          *p.p, "descriptor", &impl, impl.descriptor_,
          "async_read_some(null_buffers)"));

    start_op(impl, io_uring_service::read_op, p.p, is_continuation, false);
    p.v = p.p = 0;
  }

  // Read some data at the specified offset. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some_at(implementation_type& impl, uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    if (bufs_type::is_single_buffer)
    {
      return descriptor_ops::sync_read_at1(impl.descriptor_,
          impl.state_, offset, bufs_type::first(buffers).data(),
          bufs_type::first(buffers).size(), ec);
    }
    else
    {
      bufs_type bufs(buffers);

      return descriptor_ops::sync_read_at(impl.descriptor_, impl.state_,
          offset, bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
    }
  }

  // Wait until data can be read without blocking.
  size_t read_some_at(implementation_type& impl, uint64_t,
      const null_buffers& buffers, boost::system::error_code& ec)
  {
    return read_some(impl, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl,
      uint64_t offset, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef io_uring_descriptor_read_at_op<
      MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_,
        impl.state_, offset, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<io_uring_op_cancellation>(&io_uring_service_,
            &impl.io_object_data_, io_uring_service::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((io_uring_service_.context(), *p.p,
          "descriptor", &impl, impl.descriptor_, "async_read_some"));

    start_op(impl, io_uring_service::read_op, p.p, is_continuation,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }

  // Wait until data can be read without blocking.
  template <typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl, uint64_t,
      const null_buffers& buffers, Handler& handler, const IoExecutor& io_ex)
  {
    return async_read_some(impl, buffers, handler, io_ex);
  }

private:
  // Start the asynchronous operation.
  BOOST_ASIO_DECL void start_op(implementation_type& impl, int op_type,
      io_uring_operation* op, bool is_continuation, bool noop);

  // Helper class used to implement per-operation cancellation
  class io_uring_op_cancellation
  {
  public:
    io_uring_op_cancellation(io_uring_service* s,
        io_uring_service::per_io_object_data* p, int o)
      : io_uring_service_(s),
        io_object_data_(p),
        op_type_(o)
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        io_uring_service_->cancel_ops_by_key(*io_object_data_, op_type_, this);
      }
    }

  private:
    io_uring_service* io_uring_service_;
    io_uring_service::per_io_object_data* io_object_data_;
    int op_type_;
  };

  // The io_uring_service that performs event demultiplexing for the service.
  io_uring_service& io_uring_service_;

  // Cached success value to avoid accessing category singleton.
  const boost::system::error_code success_ec_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/io_uring_descriptor_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_SERVICE_HPP

/* io_uring_descriptor_service.hpp
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
*/