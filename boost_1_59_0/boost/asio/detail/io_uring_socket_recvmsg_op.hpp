//
// detail/io_uring_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVMSG_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class io_uring_socket_recvmsg_op_base : public io_uring_operation
{
public:
  io_uring_socket_recvmsg_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_recvmsg_op_base::do_prepare,
        &io_uring_socket_recvmsg_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      in_flags_(in_flags),
      out_flags_(out_flags),
      bufs_(buffers),
      msghdr_()
  {
    msghdr_.msg_iov = bufs_.buffers();
    msghdr_.msg_iovlen = static_cast<int>(bufs_.count());
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_recvmsg_op_base* o(
        static_cast<io_uring_socket_recvmsg_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->in_flags_ & socket_base::message_out_of_band) != 0;
      ::io_uring_prep_poll_add(sqe, o->socket_, except_op ? POLLPRI : POLLIN);
    }
    else
    {
      ::io_uring_prep_recvmsg(sqe, o->socket_, &o->msghdr_, o->in_flags_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_socket_recvmsg_op_base* o(
        static_cast<io_uring_socket_recvmsg_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->in_flags_ & socket_base::message_out_of_band) != 0;
      if (after_completion || !except_op)
      {
        return socket_ops::non_blocking_recvmsg(o->socket_,
            o->bufs_.buffers(), o->bufs_.count(), o->in_flags_,
            o->out_flags_, o->ec_, o->bytes_transferred_);
      }
    }
    else if (after_completion)
    {
      if (!o->ec_)
        o->out_flags_ = o->msghdr_.msg_flags;
      else
        o->out_flags_ = 0;
    }

    if (o->ec_ && o->ec_ == boost::asio::error::would_block)
    {
      o->state_ |= socket_ops::internal_non_blocking;
      return false;
    }

    return after_completion;
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  MutableBufferSequence buffers_;
  socket_base::message_flags in_flags_;
  socket_base::message_flags& out_flags_;
  buffer_sequence_adapter<boost::asio::mutable_buffer,
      MutableBufferSequence> bufs_;
  msghdr msghdr_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class io_uring_socket_recvmsg_op
  : public io_uring_socket_recvmsg_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_recvmsg_op);

  io_uring_socket_recvmsg_op(const boost::system::error_code& success_ec,
      int socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_recvmsg_op_base<MutableBufferSequence>(success_ec,
        socket, state, buffers, in_flags, out_flags,
        &io_uring_socket_recvmsg_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_recvmsg_op* o
      (static_cast<io_uring_socket_recvmsg_op*>(base));
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

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVMSG_OP_HPP

/* io_uring_socket_recvmsg_op.hpp
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
*/