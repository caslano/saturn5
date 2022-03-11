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
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
*/