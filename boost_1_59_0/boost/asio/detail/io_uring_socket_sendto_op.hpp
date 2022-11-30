//
// detail/io_uring_socket_sendto_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_SENDTO_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_SENDTO_OP_HPP

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

template <typename ConstBufferSequence, typename Endpoint>
class io_uring_socket_sendto_op_base : public io_uring_operation
{
public:
  io_uring_socket_sendto_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_sendto_op_base::do_prepare,
        &io_uring_socket_sendto_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      destination_(endpoint),
      flags_(flags),
      bufs_(buffers),
      msghdr_()
  {
    msghdr_.msg_iov = bufs_.buffers();
    msghdr_.msg_iovlen = static_cast<int>(bufs_.count());
    msghdr_.msg_name = static_cast<sockaddr*>(
        static_cast<void*>(destination_.data()));
    msghdr_.msg_namelen = destination_.size();
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_sendto_op_base* o(
        static_cast<io_uring_socket_sendto_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->socket_, POLLOUT);
    }
    else
    {
      ::io_uring_prep_sendmsg(sqe, o->socket_, &o->msghdr_, o->flags_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_socket_sendto_op_base* o(
        static_cast<io_uring_socket_sendto_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      if (o->bufs_.is_single_buffer)
      {
        return socket_ops::non_blocking_sendto1(o->socket_,
            o->bufs_.first(o->buffers_).data(),
            o->bufs_.first(o->buffers_).size(), o->flags_,
            o->destination_.data(), o->destination_.size(),
            o->ec_, o->bytes_transferred_);
      }
      else
      {
        return socket_ops::non_blocking_sendto(o->socket_,
            o->bufs_.buffers(), o->bufs_.count(), o->flags_,
            o->destination_.data(), o->destination_.size(),
            o->ec_, o->bytes_transferred_);
      }
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
  ConstBufferSequence buffers_;
  Endpoint destination_;
  socket_base::message_flags flags_;
  buffer_sequence_adapter<boost::asio::const_buffer, ConstBufferSequence> bufs_;
  msghdr msghdr_;
};

template <typename ConstBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class io_uring_socket_sendto_op
  : public io_uring_socket_sendto_op_base<ConstBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_sendto_op);

  io_uring_socket_sendto_op(const boost::system::error_code& success_ec,
      int socket, socket_ops::state_type state,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_sendto_op_base<ConstBufferSequence, Endpoint>(
        success_ec, socket, state, buffers, endpoint, flags,
        &io_uring_socket_sendto_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_sendto_op* o
      (static_cast<io_uring_socket_sendto_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_SENDTO_OP_HPP

/* io_uring_socket_sendto_op.hpp
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
*/