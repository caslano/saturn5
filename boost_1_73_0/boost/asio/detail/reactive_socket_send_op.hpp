//
// detail/reactive_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  reactive_socket_send_op_base(socket_type socket,
      socket_ops::state_type state, const ConstBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_send_op_base::do_perform, complete_func),
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

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_send(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->ec_, o->bytes_transferred_) ? done : not_done;

    if (result == done)
      if ((o->state_ & socket_ops::stream_oriented) != 0)
        if (o->bytes_transferred_ < bufs.total_size())
          result = done_and_exhausted;

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

  reactive_socket_send_op(socket_type socket, socket_ops::state_type state,
      const ConstBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_send_op_base<ConstBufferSequence>(socket,
        state, buffers, flags, &reactive_socket_send_op::do_complete),
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
    reactive_socket_send_op* o(static_cast<reactive_socket_send_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SEND_OP_HPP

/* reactive_socket_send_op.hpp
ssDYq29cKobHjI2nmU7YoUegAkuOceou0an9qtYu5z28Ps91bKE7r4vqFvmZkgrPDB5OpQUwZ6DA513Neq39yuwmw4QyfdK232VMVdsrozFtgdFGpO/1itQikU6PRRppZdG+JgUQoKN5tWwZl0mxXvZF4XgmM3auow7cC3BKeeQhX5S2/2wYYAk3T6WZenYUWHZqvo8mBtUWX6Zv47PsjG8MME8Pm8MF0JgO5PphMF509GH/
*/