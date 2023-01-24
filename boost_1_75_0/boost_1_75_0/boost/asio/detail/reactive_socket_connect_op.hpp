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
zpExHjPN9Ep01TvN1W0EhqLbtxbR3/7SXD36T6a5Quh9LPI+5bumuSqlCFp2LjskzVWp79vSXG196bumuSr1BdNcbc3G3DwUZP3Pp7lChKMJfkWgU98nzRViRpm449Hpsf9qmqvbfAOluTqiprmqDqS5WkHjuKdXmqv1PL9VGT/dF5rmqqhPmqu83mmubg5ZgEXBJammucIl+d+V5oomwkL2syxtDny/NFfqsNP5ABQs69P7p7l6YGjAXP43THM17KMAHU3ar+NprjC1lRbYeoVPCUtz9ZcPfb3TXBX5BkhzRTlZeJor/BmW5oqe/UtprlQ03mTrD43fPc3VQOj8Dmmupg75j6a5sv7XpbnCTwdgHC1+OB7jaNHtD+No0eUF42gxZhTjaNFiR44DPi2OljZGJ26MwTRXG7p9PJZ2eiDKn5Il8txV0+Lw8w87+bj2k+0qvTsk80DIex0j/ErvDAE8AQDaRFQPhvR/b9Krm33/StKrsv9PJr16kpj6fy3p1bHY8KRX8zu/Q9KrZf/zvZNetYfnpPr3J73a+s8nvVrqGzjpFe1toUmvsmP/l5NePfsvJb1avpPrR4p/wKRXnv9w0qtj7/uCSa9u8X2vpFeUV6ffpFezeye9oqJkig9SWmXfzb5+kl5h0VwbG7Vq4KRX9HouMxj6SXqlPrNH/puTXnFp6rxJr5Cv6y/p1bU+5QdLevXGD5j0avEP
*/