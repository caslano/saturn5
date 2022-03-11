//
// detail/reactive_descriptor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  && !defined(__CYGWIN__)

#include <boost/asio/buffer.hpp>
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

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_wait_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

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

    start_op(impl, op_type, p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

  // Write some data to the descriptor.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return descriptor_ops::sync_write(impl.descriptor_, impl.state_,
        bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
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

    // Allocate and construct an operation to wrap the handler.
    typedef descriptor_write_op<ConstBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.descriptor_, buffers, handler, io_ex);

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

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

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
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return descriptor_ops::sync_read(impl.descriptor_, impl.state_,
        bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
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

    // Allocate and construct an operation to wrap the handler.
    typedef descriptor_read_op<MutableBufferSequence, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.descriptor_, buffers, handler, io_ex);

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

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_null_buffers_op<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((reactor_.context(), *p.p, "descriptor",
          &impl, impl.descriptor_, "async_read_some(null_buffers)"));

    start_op(impl, reactor::read_op, p.p, is_continuation, false, false);
    p.v = p.p = 0;
  }

private:
  // Start the asynchronous operation.
  BOOST_ASIO_DECL void start_op(implementation_type& impl, int op_type,
      reactor_op* op, bool is_continuation, bool is_non_blocking, bool noop);

  // The selector that performs event demultiplexing for the service.
  reactor& reactor_;
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_DESCRIPTOR_SERVICE_HPP

/* reactive_descriptor_service.hpp
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
*/