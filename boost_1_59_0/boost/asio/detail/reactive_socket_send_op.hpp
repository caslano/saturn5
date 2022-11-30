//
// detail/reactive_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SEND_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
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

template <typename ConstBufferSequence>
class reactive_socket_send_op_base : public reactor_op
{
public:
  reactive_socket_send_op_base(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_send_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_send_op_base* o(
        static_cast<reactive_socket_send_op_base*>(base));

    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    status result;
    if (bufs_type::is_single_buffer)
    {
      result = socket_ops::non_blocking_send1(o->socket_,
          bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(), o->flags_,
          o->ec_, o->bytes_transferred_) ? done : not_done;

      if (result == done)
        if ((o->state_ & socket_ops::stream_oriented) != 0)
          if (o->bytes_transferred_ < bufs_type::first(o->buffers_).size())
            result = done_and_exhausted;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = socket_ops::non_blocking_send(o->socket_,
            bufs.buffers(), bufs.count(), o->flags_,
            o->ec_, o->bytes_transferred_) ? done : not_done;

      if (result == done)
        if ((o->state_ & socket_ops::stream_oriented) != 0)
          if (o->bytes_transferred_ < bufs.total_size())
            result = done_and_exhausted;
    }

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_send",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  ConstBufferSequence buffers_;
  socket_base::message_flags flags_;
};

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class reactive_socket_send_op :
  public reactive_socket_send_op_base<ConstBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_send_op);

  reactive_socket_send_op(const boost::system::error_code& success_ec,
      socket_type socket, socket_ops::state_type state,
      const ConstBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_send_op_base<ConstBufferSequence>(success_ec, socket,
        state, buffers, flags, &reactive_socket_send_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_send_op* o(static_cast<reactive_socket_send_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SEND_OP_HPP

/* reactive_socket_send_op.hpp
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
*/