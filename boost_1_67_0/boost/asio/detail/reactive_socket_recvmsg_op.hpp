//
// detail/reactive_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP

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
#include <boost/asio/socket_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class reactive_socket_recvmsg_op_base : public reactor_op
{
public:
  reactive_socket_recvmsg_op_base(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvmsg_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      in_flags_(in_flags),
      out_flags_(out_flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recvmsg_op_base* o(
        static_cast<reactive_socket_recvmsg_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_recvmsg(o->socket_,
        bufs.buffers(), bufs.count(),
        o->in_flags_, o->out_flags_,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recvmsg",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  MutableBufferSequence buffers_;
  socket_base::message_flags in_flags_;
  socket_base::message_flags& out_flags_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class reactive_socket_recvmsg_op :
  public reactive_socket_recvmsg_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recvmsg_op);

  reactive_socket_recvmsg_op(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvmsg_op_base<MutableBufferSequence>(socket, buffers,
        in_flags, out_flags, &reactive_socket_recvmsg_op::do_complete),
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
    reactive_socket_recvmsg_op* o(
        static_cast<reactive_socket_recvmsg_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP

/* reactive_socket_recvmsg_op.hpp
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
*/