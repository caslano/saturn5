//
// detail/io_uring_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_SOCKET_ACCEPT_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_SOCKET_ACCEPT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Socket, typename Protocol>
class io_uring_socket_accept_op_base : public io_uring_operation
{
public:
  io_uring_socket_accept_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state, Socket& peer,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_socket_accept_op_base::do_prepare,
        &io_uring_socket_accept_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      peer_(peer),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint),
      addrlen_(peer_endpoint ? peer_endpoint->capacity() : 0)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_socket_accept_op_base* o(
        static_cast<io_uring_socket_accept_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->socket_, POLLIN);
    }
    else
    {
      ::io_uring_prep_accept(sqe, o->socket_,
          o->peer_endpoint_ ? o->peer_endpoint_->data() : 0,
          o->peer_endpoint_ ? &o->addrlen_ : 0, 0);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_socket_accept_op_base* o(
        static_cast<io_uring_socket_accept_op_base*>(base));

    if ((o->state_ & socket_ops::internal_non_blocking) != 0)
    {
      socket_type new_socket = invalid_socket;
      std::size_t addrlen = static_cast<std::size_t>(o->addrlen_);
      bool result = socket_ops::non_blocking_accept(o->socket_,
          o->state_, o->peer_endpoint_ ? o->peer_endpoint_->data() : 0,
          o->peer_endpoint_ ? &addrlen : 0, o->ec_, new_socket);
      o->new_socket_.reset(new_socket);
      o->addrlen_ = static_cast<socklen_t>(addrlen);
      return result;
    }

    if (o->ec_ && o->ec_ == boost::asio::error::would_block)
    {
      o->state_ |= socket_ops::internal_non_blocking;
      return false;
    }

    if (after_completion && !o->ec_)
      o->new_socket_.reset(static_cast<int>(o->bytes_transferred_));

    return after_completion;
  }

  void do_assign()
  {
    if (new_socket_.get() != invalid_socket)
    {
      if (peer_endpoint_)
        peer_endpoint_->resize(addrlen_);
      peer_.assign(protocol_, new_socket_.get(), ec_);
      if (!ec_)
        new_socket_.release();
    }
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  socket_holder new_socket_;
  Socket& peer_;
  Protocol protocol_;
  typename Protocol::endpoint* peer_endpoint_;
  socklen_t addrlen_;
};

template <typename Socket, typename Protocol,
    typename Handler, typename IoExecutor>
class io_uring_socket_accept_op :
  public io_uring_socket_accept_op_base<Socket, Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_accept_op);

  io_uring_socket_accept_op(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state, Socket& peer,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_socket_accept_op_base<Socket, Protocol>(
        success_ec, socket, state, peer, protocol, peer_endpoint,
        &io_uring_socket_accept_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_accept_op* o(static_cast<io_uring_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

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
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, o->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Protocol, typename PeerIoExecutor,
    typename Handler, typename IoExecutor>
class io_uring_socket_move_accept_op :
  private Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
  public io_uring_socket_accept_op_base<
    typename Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
    Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_socket_move_accept_op);

  io_uring_socket_move_accept_op(const boost::system::error_code& success_ec,
      const PeerIoExecutor& peer_io_ex, socket_type socket,
      socket_ops::state_type state, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, Handler& handler,
      const IoExecutor& io_ex)
    : peer_socket_type(peer_io_ex),
      io_uring_socket_accept_op_base<peer_socket_type, Protocol>(
        success_ec, socket, state, *this, protocol, peer_endpoint,
        &io_uring_socket_move_accept_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_socket_move_accept_op* o(
        static_cast<io_uring_socket_move_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

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
    detail::move_binder2<Handler,
      boost::system::error_code, peer_socket_type>
        handler(0, BOOST_ASIO_MOVE_CAST(Handler)(o->handler_), o->ec_,
          BOOST_ASIO_MOVE_CAST(peer_socket_type)(*o));
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  typedef typename Protocol::socket::template
    rebind_executor<PeerIoExecutor>::other peer_socket_type;

  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_SOCKET_ACCEPT_OP_HPP

/* io_uring_socket_accept_op.hpp
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
*/