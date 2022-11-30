//
// detail/reactive_descriptor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_DESCRIPTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_DESCRIPTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__) \
  && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/cancellation_type.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/descriptor_read_op.hpp>
#include <boost/asio/detail/descriptor_write_op.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/reactive_null_buffers_op.hpp>
#include <boost/asio/detail/reactive_wait_op.hpp>
#include <boost/asio/detail/reactor.hpp>
#include <boost/asio/posix/descriptor_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class reactive_descriptor_service :
  public execution_context_service_base<reactive_descriptor_service>
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
    friend class reactive_descriptor_service;

    // The native descriptor representation.
    int descriptor_;

    // The current state of the descriptor.
    descriptor_ops::state_type state_;

    // Per-descriptor data used by the reactor.
    reactor::per_descriptor_data reactor_data_;
  };

  // Constructor.
  BOOST_ASIO_DECL reactive_descriptor_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new descriptor implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Move-construct a new descriptor implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl) BOOST_ASIO_NOEXCEPT;

  // Move-assign from another descriptor implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      reactive_descriptor_service& other_service,
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

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_wait"));

    int op_type;
    switch (w)
    {
    case posix::descriptor_base::wait_read:
        op_type = reactor::read_op;
        break;
    case posix::descriptor_base::wait_write:
        op_type = reactor::write_op;
        break;
    case posix::descriptor_base::wait_error:
        op_type = reactor::except_op;
        break;
      default:
        p.p->ec_ = boost::asio::error::invalid_argument;
        reactor_.post_immediate_completion(p.p, is_continuation);
        p.v = p.p = 0;
        return;
    }

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_, impl.descriptor_, op_type);
    }

    start_op(impl, op_type, p.p, is_continuation, false, false);
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
    typedef descriptor_write_op<ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_,
            impl.descriptor_, reactor::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_write_some"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true,
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
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_,
            impl.descriptor_, reactor::write_op);
    }

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_write_some(null_buffers)"));

    start_op(impl, reactor::write_op, p.p, is_continuation, false, false);
    p.v = p.p = 0;
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
    typedef descriptor_read_op<MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, impl.descriptor_, buffers, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_,
            impl.descriptor_, reactor::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_read_some"));

    start_op(impl, reactor::read_op, p.p, is_continuation, true,
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
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(success_ec_, handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<reactor_op_cancellation>(
            &reactor_, &impl.reactor_data_,
            impl.descriptor_, reactor::read_op);
    }

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_read_some(null_buffers)"));

    start_op(impl, reactor::read_op, p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

private:
  // Start the asynchronous operation.
  BOOST_ASIO_DECL void start_op(implementation_type& impl, int op_type,
      reactor_op* op, bool is_continuation, bool is_non_blocking, bool noop);

  // Helper class used to implement per-operation cancellation
  class reactor_op_cancellation
  {
  public:
    reactor_op_cancellation(reactor* r,
        reactor::per_descriptor_data* p, int d, int o)
      : reactor_(r),
        reactor_data_(p),
        descriptor_(d),
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
        reactor_->cancel_ops_by_key(descriptor_,
            *reactor_data_, op_type_, this);
      }
    }

  private:
    reactor* reactor_;
    reactor::per_descriptor_data* reactor_data_;
    int descriptor_;
    int op_type_;
  };

  // The selector that performs event demultiplexing for the service.
  reactor& reactor_;

  // Cached success value to avoid accessing category singleton.
  const boost::system::error_code success_ec_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/reactive_descriptor_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_WINDOWS)
       //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
       //   && !defined(__CYGWIN__)
       //   && !defined(BOOST_ASIO_HAS_IO_URING_AS_DEFAULT)

#endif // BOOST_ASIO_DETAIL_REACTIVE_DESCRIPTOR_SERVICE_HPP

/* reactive_descriptor_service.hpp
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
*/