//
// detail/reactive_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
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
  reactive_socket_recvmsg_op_base(const boost::system::error_code& success_ec,
      socket_type socket, const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_recvmsg_op_base::do_perform, complete_func),
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

  reactive_socket_recvmsg_op(const boost::system::error_code& success_ec,
      socket_type socket, const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvmsg_op_base<MutableBufferSequence>(
        success_ec, socket, buffers, in_flags, out_flags,
        &reactive_socket_recvmsg_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recvmsg_op* o(
        static_cast<reactive_socket_recvmsg_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP

/* reactive_socket_recvmsg_op.hpp
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
*/