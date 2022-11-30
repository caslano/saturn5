//
// detail/reactive_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
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
  reactive_socket_connect_op_base(const boost::system::error_code& success_ec,
      socket_type socket, func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_connect_op_base::do_perform, complete_func),
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

  reactive_socket_connect_op(const boost::system::error_code& success_ec,
      socket_type socket, Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_connect_op_base(success_ec, socket,
        &reactive_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_connect_op* o
      (static_cast<reactive_socket_connect_op*>(base));
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

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_CONNECT_OP_HPP

/* reactive_socket_connect_op.hpp
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
*/