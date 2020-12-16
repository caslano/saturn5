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
owfiJwVcRlXMTw65O4UUc5gRl70Ap0Ss4dbKnRox2b9zWsgozbLn8z0pzmnmc3P/y951gFdRZeF5BCIdEor0XkI1INJbSAIEQhJSMBQNIe8FnqaR94KgKGDFXWwr9l5QXFGx7NpXVl1FZdW1La7uinV1xbUrupY9c+4/c8vcF3DL9+1+Xx7fZTLn/++d2+beM+c2K46S987ytHJiNJQaYfwMxrE5Q+6cfMXawfE/k3F+7QM6+FkuVlpcljUL6oA4UIz74M0+Jr+jzpYyGDmZz+/IzySGPTwxzunL2bjM3C1SxsZgr98/h+Ql3sGkkJ0L2fhxUnYey7zJexi7FLKS4pxc71xpzp8LgnKM9GAMk3GuTLzXMUDGLpQY61qAONytKlbXQLlRW+tWOC9vLzJwNdyLJcbmUnV97SUSgxqhj0tdKnBS+0jeUBHHKdWMXSYwlCVGuzE2cTljvPiHuVeI+3CEgqld55MZuxJYQ10wT66SWCBPrpaYNU+uMXB4Zr/XSsxIN87+ZFzaSK7ne8yMY9Od74HxGxS8tiHOTwMuxjcVvD4S48M0+VzQgBz+kIabJM5j+mre3CwxWbCIz3ZggWkNiM8twOW0BvG8X0o55xmaDzHG6WMIC8/aIeWcBN4YnSclCPy2IB6tYRzjmz6O1CljuHcwhucRhb/geKhD4DtNnCLcEJNri+4M4LX0GjPM+u5dJo4KLmt8rf+su00uv+EyLveYODc3Ev+VhscCafm1jgfScq+OB9JyXwBPnJb7dW4gLQ8EcKQF78eDjMs9DB7y7+EHbefDLOetQiPevga/EbJYorr5CHBZN7G/rpRr/N9C7tcvyB915bTuWJy7KdfLPKbLox7/cVWunFf/O1dePJuXHlUgXU94sroGX/YkyY6em1OYW5Cf783x3q3KymZF4xhR5TNBVUyZR/+0Klfm0T+jyREQymsPYW6nvOhId1mJuy+S26bzFujc9//ejtcwAWE8q3NgM5VhPGfHEQb23tU5hIuw/xCQl9GMiHLftv6CgeO5jL0YxGh8Ji7WNWpYME0vJ8DLYseLcVwdhxIn0vJHDZPx2RuU86wSHtPVMGk//ZMup5qEtY0BOQclxnF1LDo2jHWNmlxP718smAgR47k6LlQ/YPsMDNMAGXtTxXg6C+FYF/6WxLDzdW21P8CFevG2z+E1epyYIe44rirnM05qwuX1YXV6ED//XY2HvcWR5vcsGOsC3lrHRHiZzLf3bRzOG6x1tOEN7hb/GPeVOGe5arv6UGIyWch6XvMoce6vx0Yx9qvLkaMY+zUwVRf5WMdkeoF/YsOVevCpxHlvGH7bgH0mMcRH6kifq1hc5EMVHwuBfXoNPL4W+/TqctRngX3lY0ijsrf51wLDh0iRPJtUk/MG7Sz/RpPLsZ1vNbnsJ/6hyVnPYvl3mlz2H99rctk3/qDJeWqcGNsNyMuqPZ3KaSsw3i4lZ1ZJcTZMLcBDARx6OOadNUuEy2Elsc4xMQ9WIqxzbIwXl7a8FgGetDsmBzC5F9thQUw9Vpk5Le0cHPAsOK3sHKFRIo6tAxy5tqpNAJO2yLYBTExLVOPYzs5BHMUz2oMjloJmlKi2gQ4BTK5r6xjA5NrgFB/L0c7ZT1Xk6nnknVS5Mh+ksy8vzJVWS4F1CWAybl0DmLRbHK5iC7KL52JVtOe3WwCXc3G6K5jYEqQ+sqb2eH+NZw8VVw8cRNg9Fdw897WXgmESU6yBlNwVyKPeGl7tz4fvo8qlsZj99FUwPhkGYfVT5Bi5YXl/Ra6u0xqgyNV1WgMVOddsttTKM0wGWXB1r4jBAVztabFfboBTVR6D4upxhgY4NRSQrpOmmRw5jMH4MAM=
*/