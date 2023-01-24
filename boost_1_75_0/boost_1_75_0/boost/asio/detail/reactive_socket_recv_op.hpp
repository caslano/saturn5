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
NDjrQ+OzNn2H+Czym0eZYXlYfFZeWHzWrO8Vn0UgkaElF8/w+Cx1ULz12qCERzDhqyHxWQggLD6rtI3rRA/0js/CB54nh2gvDRiftZ7is7B0WHwWvV6oxmchij2288dnUdf6xGepvRty/t6dJz5LnWZ0Pn981soONd5BcD6B8Vk7GwIk6PWdaLjbqToPBmgQesbdNaQvWs2urVvauCKVfJBdiyg+iyaaZwHFZ+HvsPgsQtHUb4nPonmA8VmD/g+Oz7rjfPFZEyk+y6vFZ80m+aNLi8/6iRqPtVg9r1LPdorP4i6rveKzDnBy/xc1PuvZ3vFZI3rFZ61tCzHak4M03dKM9heGkZW8LPYabFS8CDH6N7cFvHJ5kUCs1tPHfBqjPx4Z/THhkMiMv5LKmAMRWxTd5/yDGrH1NDr5fRSI1cIN2CbTKRCrlW1jH/2mV6zWktBYLaxLjdh6hFqOsCJ37OIrC4tfh2Faj2u+YX/ThYdpqWFbGKaV0TZwmNZ60iJz3DtXhYdpPdVPmNY1A4ZpjRkoTGsLwVMcUZTQUe0uyHnrY9SEi0RQ1nR5HtfUxbeq6uIoTV2coaqLa/oP26J4ud7xA38jbTHfWWd/t7Ct2wNhW6a2AInJxKxi2zqVgQO28tu4U1pBv6Od3xYSsPXFEx3qHvpdArZwVnn+EhqwFdxWQuLTzgU7OlDA1nAtYOvi7xWwtTdsR/ZknCdg
*/