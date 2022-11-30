//
// detail/reactive_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
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
  reactive_socket_recv_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_recv_op_base::do_perform, complete_func),
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

    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    status result;
    if (bufs_type::is_single_buffer)
    {
      result = socket_ops::non_blocking_recv1(o->socket_,
          bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(), o->flags_,
          (o->state_ & socket_ops::stream_oriented) != 0,
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = socket_ops::non_blocking_recv(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          (o->state_ & socket_ops::stream_oriented) != 0,
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }

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

  reactive_socket_recv_op(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_recv_op_base<MutableBufferSequence>(success_ec, socket,
        state, buffers, flags, &reactive_socket_recv_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recv_op* o(static_cast<reactive_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP

/* reactive_socket_recv_op.hpp
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
*/