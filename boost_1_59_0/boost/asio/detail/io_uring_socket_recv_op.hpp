//
// detail/io_uring_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECV_OP_HPP

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
class io_uring_socket_recv_op_base : public io_uring_operation
{
public:
  io_uring_socket_recv_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_recv_op_base::do_prepare,
        &io_uring_socket_recv_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      flags_(flags),
      bufs_(buffers),
      msghdr_()
  {
    msghdr_.msg_iov = bufs_.buffers();
    msghdr_.msg_iovlen = static_cast<int>(bufs_.count());
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_recv_op_base* o(
        static_cast<io_uring_socket_recv_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->flags_ & socket_base::message_out_of_band) != 0;
      ::io_uring_prep_poll_add(sqe, o->socket_, except_op ? POLLPRI : POLLIN);
    }
    else if (o->bufs_.is_single_buffer
        && o->bufs_.is_registered_buffer && o->flags_ == 0)
    {
      ::io_uring_prep_read_fixed(sqe, o->socket_,
          o->bufs_.buffers()->iov_base, o->bufs_.buffers()->iov_len,
          0, o->bufs_.registered_id().native_handle());
    }
    else
    {
      ::io_uring_prep_recvmsg(sqe, o->socket_, &o->msghdr_, o->flags_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_socket_recv_op_base* o(
        static_cast<io_uring_socket_recv_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->flags_ & socket_base::message_out_of_band) != 0;
      if (after_completion || !except_op)
      {
        if (o->bufs_.is_single_buffer)
        {
          return socket_ops::non_blocking_recv1(o->socket_,
              o->bufs_.first(o->buffers_).data(),
              o->bufs_.first(o->buffers_).size(), o->flags_,
              (o->state_ & socket_ops::stream_oriented) != 0,
              o->ec_, o->bytes_transferred_);
        }
        else
        {
          return socket_ops::non_blocking_recv(o->socket_,
              o->bufs_.buffers(), o->bufs_.count(), o->flags_,
              (o->state_ & socket_ops::stream_oriented) != 0,
              o->ec_, o->bytes_transferred_);
        }
      }
    }
    else if (after_completion)
    {
      if (!o->ec_ && o->bytes_transferred_ == 0)
        if ((o->state_ & socket_ops::stream_oriented) != 0)
          o->ec_ = boost::asio::error::eof;
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
  socket_base::message_flags flags_;
  buffer_sequence_adapter<boost::asio::mutable_buffer,
      MutableBufferSequence> bufs_;
  msghdr msghdr_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class io_uring_socket_recv_op
  : public io_uring_socket_recv_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_recv_op);

  io_uring_socket_recv_op(const boost::system::error_code& success_ec,
      int socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_recv_op_base<MutableBufferSequence>(success_ec,
        socket, state, buffers, flags, &io_uring_socket_recv_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_recv_op* o
      (static_cast<io_uring_socket_recv_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECV_OP_HPP

/* io_uring_socket_recv_op.hpp
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
*/