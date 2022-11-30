//
// detail/reactive_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_holder.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Socket, typename Protocol>
class reactive_socket_accept_op_base : public reactor_op
{
public:
  reactive_socket_accept_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state, Socket& peer,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_accept_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      peer_(peer),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint),
      addrlen_(peer_endpoint ? peer_endpoint->capacity() : 0)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_accept_op_base* o(
        static_cast<reactive_socket_accept_op_base*>(base));

    socket_type new_socket = invalid_socket;
    status result = socket_ops::non_blocking_accept(o->socket_,
        o->state_, o->peer_endpoint_ ? o->peer_endpoint_->data() : 0,
        o->peer_endpoint_ ? &o->addrlen_ : 0, o->ec_, new_socket)
    ? done : not_done;
    o->new_socket_.reset(new_socket);

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_accept", o->ec_));

    return result;
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
  std::size_t addrlen_;
};

template <typename Socket, typename Protocol,
    typename Handler, typename IoExecutor>
class reactive_socket_accept_op :
  public reactive_socket_accept_op_base<Socket, Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_accept_op);

  reactive_socket_accept_op(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state, Socket& peer,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_accept_op_base<Socket, Protocol>(
        success_ec, socket, state, peer, protocol, peer_endpoint,
        &reactive_socket_accept_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_accept_op* o(static_cast<reactive_socket_accept_op*>(base));
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
class reactive_socket_move_accept_op :
  private Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
  public reactive_socket_accept_op_base<
    typename Protocol::socket::template rebind_executor<PeerIoExecutor>::other,
    Protocol>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_move_accept_op);

  reactive_socket_move_accept_op(const boost::system::error_code& success_ec,
      const PeerIoExecutor& peer_io_ex, socket_type socket,
      socket_ops::state_type state, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, Handler& handler,
      const IoExecutor& io_ex)
    : peer_socket_type(peer_io_ex),
      reactive_socket_accept_op_base<peer_socket_type, Protocol>(
        success_ec, socket, state, *this, protocol, peer_endpoint,
        &reactive_socket_move_accept_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_move_accept_op* o(
        static_cast<reactive_socket_move_accept_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP

/* reactive_socket_accept_op.hpp
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
*/