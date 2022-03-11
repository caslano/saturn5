//
// detail/reactive_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_CONNECT_OP_HPP

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

class reactive_socket_connect_op_base : public reactor_op
{
public:
  reactive_socket_connect_op_base(socket_type socket, func_type complete_func)
    : reactor_op(&reactive_socket_connect_op_base::do_perform, complete_func),
      socket_(socket)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_connect_op_base* o(
        static_cast<reactive_socket_connect_op_base*>(base));

    status result = socket_ops::non_blocking_connect(
        o->socket_, o->ec_) ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_connect", o->ec_));

    return result;
  }

private:
  socket_type socket_;
};

template <typename Handler, typename IoExecutor>
class reactive_socket_connect_op : public reactive_socket_connect_op_base
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_connect_op);

  reactive_socket_connect_op(socket_type socket,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_connect_op_base(socket,
        &reactive_socket_connect_op::do_complete),
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
    reactive_socket_connect_op* o
      (static_cast<reactive_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

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

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_CONNECT_OP_HPP

/* reactive_socket_connect_op.hpp
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
*/