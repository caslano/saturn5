//
// detail/reactive_socket_sendto_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

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

template <typename ConstBufferSequence, typename Endpoint>
class reactive_socket_sendto_op_base : public reactor_op
{
public:
  reactive_socket_sendto_op_base(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_sendto_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      destination_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_sendto_op_base* o(
        static_cast<reactive_socket_sendto_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_sendto(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->destination_.data(), o->destination_.size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_sendto",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  ConstBufferSequence buffers_;
  Endpoint destination_;
  socket_base::message_flags flags_;
};

template <typename ConstBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_sendto_op :
  public reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_sendto_op);

  reactive_socket_sendto_op(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>(socket,
        buffers, endpoint, flags, &reactive_socket_sendto_op::do_complete),
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
    reactive_socket_sendto_op* o(static_cast<reactive_socket_sendto_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

/* reactive_socket_sendto_op.hpp
e5Lq0GDEi0Z0MtX0PJ826ntN382h9eBJ6kq3fmk26GNdQn1g0c2uFapcNKLL4fxRqWBE8D9I28lb5UqtqysK2QHdU5elprQN4zRqRd9AOUhEoLsLTAYWQTBxCzMri5eFdbnasgMmwPrDR/JGu3D1DUgOGwj2xDQQhFn+4fWL/Je/++2vTdtl+dLVTQ2Hnyuf5efCCnvv1uQ/3Z8EK05O1PSSrIK+ofz68cMbtRN/FAobqdYgdnh+1+0QSXC/1a2cmXo2L3+8NPFq8zMxNmd4Sbzp0qKQOn8jsUygnupT1x8bA5NHaCRgD3ZYfK+HKauvQEiRoFsv0ybnoY7tm/dxVGUcyL8eAeIH8Rp6sb08L+4Bmvo14g3Ra1Wz1VgvCm3f7rEbeOKp3GJWoarKv7pW0YnL0iXAJ3cJwWSTtW7xrtlVNstdCVPPCEtst7htu8QAq34w6j7OMoSng2IYC7V9macatmmvn/32ybOn3/xm9kT+//QhLSzPqHi/hyVXj0oGfgU9Ej1jFe7ddqsx21bsYe8Zb7moALbD+xNsWxitgfkUVzsDz8hpMWRYuk5e/fhSvO8fyaN23CLYx2In3C05qXc3FoLJUYhfK0q6KwvMS08WEaF8N9iIVmK5Hh5giFRlbXrWtmbR3aaq1TDH
*/