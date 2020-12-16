//
// detail/reactive_socket_accept_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
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
  reactive_socket_accept_op_base(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, func_type complete_func)
    : reactor_op(&reactive_socket_accept_op_base::do_perform, complete_func),
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

  reactive_socket_accept_op(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_accept_op_base<Socket, Protocol>(socket, state, peer,
        protocol, peer_endpoint, &reactive_socket_accept_op::do_complete),
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
    reactive_socket_accept_op* o(static_cast<reactive_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
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

  reactive_socket_move_accept_op(const PeerIoExecutor& peer_io_ex,
      socket_type socket, socket_ops::state_type state,
      const Protocol& protocol, typename Protocol::endpoint* peer_endpoint,
      Handler& handler, const IoExecutor& io_ex)
    : peer_socket_type(peer_io_ex),
      reactive_socket_accept_op_base<peer_socket_type, Protocol>(
        socket, state, *this, protocol, peer_endpoint,
        &reactive_socket_move_accept_op::do_complete),
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
    reactive_socket_move_accept_op* o(
        static_cast<reactive_socket_move_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    // On success, assign new connection to peer socket object.
    if (owner)
      o->do_assign();

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_ACCEPT_OP_HPP

/* reactive_socket_accept_op.hpp
/Px6VpswRwn0jM6a0cP6+p6em2Rw2jeAXsPdL67BQ942THAqLPCNpuHmf8RfPQ2fjec3TnAqVPBNEpw8AP6aBCdvgL824mg4wDdNcsnfZkku+Xtdkkv+Nk9yyd8WCa7z9/oE1/nbMuR4SS3fKsklf29Icsnf1kku+dsmySV/b0xwnb9tE5zyh3dnO8fzzizKGOvba51fFdJ30DpHRPqOWqcIWN/J6sur5r+e/Wy63hTolanWxOoZM/ebhfdxZ/B6lrt+aBfRrItJ31V0Tin03URnlyLs3UUvckDam7VWz+j5PXzN3X+0Z6BTAsH2ChglFGzvgHFime2TYLPx3L4Bo0SD7Rcwcj3YjIBRwwnf9PisyAI9MzPQtT/395nrA2b5ukkC+/QA0Y3GtgeKtgp+I30263R4VbM74eZ4D4IuC5JHV9NGPfCDhWOMCQ4fHKL41AnmF1Vr0t2n9BawRj2r6rS8VensANbfpnTKPOzfrnX4fxOjHwp9sr4//d3r/p5Fz82Rv+2QgPzW53RyBWn9Tqv12HhL0Nq1nsr++0kfN1fpB+xPOoUxT3T3Ts0XDVll2wHR3TtymGhFNilPhzttf7JZIH+bNHEZLBSNxjbkAJTPoGVZtW4KCJscuGwXJVllstHkfA5Z3pjKJuvFrUKsH8E6HQepy3VY6WiDSS8rXZfriNL1e7XY6rpOwW9LwHR5HimaueKItaWsYZjH2jLRZs6G3TtEc2ONo6CdsLzRnphqteyc9tGFvnSkNNhf6qeT0BaXe+eV5L7xY9LczTe8M83NFxJOS8XwuQND5eLHn/09fKzWCo/AR1WjzysNloZ7F9AFJGU19zcaMfnGXIuY3MNaDxjNQYFlAdPz9WMB0/P14wHD2cQd09AM2jNLlydtVlYnutxPNEKOdW/HBbqe+14RMP7Ww2maCFnu0tS0aZqMbZAm5k3Fy4vnjAyX/PtjWglu1wZORYySTu/78YbNX9jb586Xxt9upR30XOl6bqqjdD5Jsk56V+l6b89K6LIqDvOFWjeqPh9llWX0+YK11VajjyAc9omiYUUi277L6rwakbSToOm9CCcbbaC/1FtJ3OP3bjD/LkNmp4B5lyQiTaeCheGdBj11t+F7wNwFgHif3wtdf6bW99K8T/OsKRx+eH/BB0dm9lDNYO0DrJkkkMb7TQttqLdeN+WT9y1vNWqZV9c+FHNX1z4cM7cv7SOaza1ONiZWe+F+NOYu3I/FzIX7cc0WtYerzXEkGPN7Kd7o8N7SBNPv9emaS8jEzoiYnJP/qYjJOflnGlbsrSv2vgV3NxE/K8mlXT87ySl8eqc/bfiCRXzJ1Ybm73PM3wv7uT//DP/bvkqknQtNf088D9qI2RGV0wGmbHs+dLxKFP4FpM0ifiH/2wv/Img6/ItZi8L/LOsIn/NzCWl97p7Hz+Fv3R5cCo0jYe3z0Dgw9u1lRqP21ewNL48M9xrHlfW5/ZdPyyt9g/D/FQkbXd+uTHHUty8kmD7/76qC0771IwcGZ/aQr662mhzXQvo1oncnpyqjjRbrX/T1sSmEfa3T5X6N67TGO3gpD9c7fZy3jo1m7Qr6+xs8lmd8CAezL2lmR3+I/8uW0Y5njv9GT5M83OTpkoebnS5zhbcUWmmk3Nc7VOLNpOXSEYvNavuS7Jv8yvQ2jQ7C+eq0NrLm+2vapjx0eG+ftAdfj5i0B9+ImJyndWvABipFl1CnXSNr2b2WSZusSTaI4/bQhpKGeaaIjfMaJDVP9q3IRsZx346YjOO+EzIe/FC8341YHsV7R2zTGMd85p0hC84f/17BF40MmOIq6Xp9l6dLu3O31tW9MfcY3SzXoLGXPjP4+0qX6Wc=
*/