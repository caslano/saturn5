//
// detail/io_uring_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVFROM_OP_HPP

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

template <typename MutableBufferSequence, typename Endpoint>
class io_uring_socket_recvfrom_op_base : public io_uring_operation
{
public:
  io_uring_socket_recvfrom_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_recvfrom_op_base::do_prepare,
        &io_uring_socket_recvfrom_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      sender_endpoint_(endpoint),
      flags_(flags),
      bufs_(buffers),
      msghdr_()
  {
    msghdr_.msg_iov = bufs_.buffers();
    msghdr_.msg_iovlen = static_cast<int>(bufs_.count());
    msghdr_.msg_name = static_cast<sockaddr*>(
        static_cast<void*>(sender_endpoint_.data()));
    msghdr_.msg_namelen = sender_endpoint_.capacity();
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_recvfrom_op_base* o(
        static_cast<io_uring_socket_recvfrom_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->flags_ & socket_base::message_out_of_band) != 0;
      ::io_uring_prep_poll_add(sqe, o->socket_, except_op ? POLLPRI : POLLIN);
    }
    else
    {
      ::io_uring_prep_recvmsg(sqe, o->socket_, &o->msghdr_, o->flags_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_socket_recvfrom_op_base* o(
        static_cast<io_uring_socket_recvfrom_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      bool except_op = (o->flags_ & socket_base::message_out_of_band) != 0;
      if (after_completion || !except_op)
      {
        std::size_t addr_len = o->sender_endpoint_.capacity();
        bool result;
        if (o->bufs_.is_single_buffer)
        {
          result = socket_ops::non_blocking_recvfrom1(o->socket_,
              o->bufs_.first(o->buffers_).data(),
              o->bufs_.first(o->buffers_).size(), o->flags_,
              o->sender_endpoint_.data(), &addr_len,
              o->ec_, o->bytes_transferred_);
        }
        else
        {
          result = socket_ops::non_blocking_recvfrom(o->socket_,
              o->bufs_.buffers(), o->bufs_.count(), o->flags_,
              o->sender_endpoint_.data(), &addr_len,
              o->ec_, o->bytes_transferred_);
        }
        if (result && !o->ec_)
          o->sender_endpoint_.resize(addr_len);
      }
    }
    else if (after_completion && !o->ec_)
      o->sender_endpoint_.resize(o->msghdr_.msg_namelen);

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
  Endpoint& sender_endpoint_;
  socket_base::message_flags flags_;
  buffer_sequence_adapter<boost::asio::mutable_buffer,
      MutableBufferSequence> bufs_;
  msghdr msghdr_;
};

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class io_uring_socket_recvfrom_op
  : public io_uring_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_recvfrom_op);

  io_uring_socket_recvfrom_op(const boost::system::error_code& success_ec,
      int socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>(
        success_ec, socket, state, buffers, endpoint, flags,
        &io_uring_socket_recvfrom_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_recvfrom_op* o
      (static_cast<io_uring_socket_recvfrom_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_RECVFROM_OP_HPP

/* io_uring_socket_recvfrom_op.hpp
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
*/