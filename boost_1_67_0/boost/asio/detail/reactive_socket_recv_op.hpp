//
// detail/reactive_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class reactive_socket_recv_op_base : public reactor_op
{
public:
  reactive_socket_recv_op_base(socket_type socket,
      socket_ops::state_type state, const MutableBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recv_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recv_op_base* o(
        static_cast<reactive_socket_recv_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_recv(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        (o->state_ & socket_ops::stream_oriented) != 0,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    if (result == done)
      if ((o->state_ & socket_ops::stream_oriented) != 0)
        if (o->bytes_transferred_ == 0)
          result = done_and_exhausted;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recv",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  MutableBufferSequence buffers_;
  socket_base::message_flags flags_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class reactive_socket_recv_op :
  public reactive_socket_recv_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recv_op);

  reactive_socket_recv_op(socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_recv_op_base<MutableBufferSequence>(socket, state,
        buffers, flags, &reactive_socket_recv_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recv_op* o(static_cast<reactive_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP

/* reactive_socket_recv_op.hpp
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
*/