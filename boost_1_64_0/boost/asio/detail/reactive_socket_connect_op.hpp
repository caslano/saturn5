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
zCkphhXxlOYfhrqslOe5Jc3HM5e2Hytd35t1r9ZNkg2r2/0P9ymGzeqk/4R1mqtpjRYHx2L+SPTCy+5u959BH82zaru2vGLT9PNAz1ZVqE2+H7oZstN7+Qv7dztza6Af8DQkI+c2/UFmbi/AL/G3WUmChBm34RyFh2I2upoxzw8xp2E81npSmn7NOjbFsfYbqzXpkFfSHmaNXGtE0n4LzfzdM9Fku0eUZjJD2u+UlsPuUWjGpseG93ulmVWelO7HWOMscd0l28etrtL4BDTzrAvzD6JRemi/ntHoCI45veWBvuGS+RetMC2OkGn01Hm/XtKmMOG24k8Rxyo7MsGcT2Qjbe1TMTNFw2mo9zQoDX9J2hQmPL/89LTcLr5iu2fWaGe8g/UKz67RrtZudBq16gSH+dy0tliwBR88H9u5d/aFiMk9sS+CUR+jznp4ydf9+0Z9JveN+rrcN6r18kjvyOKyf99ozOW+0ZjJfaOODS9AEkn/t6/LfaOeLn3ey1ZfNGha4iP8Soo0rrV+ZFOYUP7W9plUULtHMOB6X/UrA6Yrp417ndimMKHnXxUzXTHJZt20DSol17P1Qpu4QlJY68d2Uhnh5w18G1c/NvR1d7ftRlY34sDg3EX6N/2rQ4bvHxsHur5/ZxPFFpfKI36BYu4pYVOYuLmngEuhcvybBlx/99ksZLpQEf7rEjaFic3D5jHXBUs2W8Q2umCprXl9bBMXLOLcMraVwkUZbhXaoDzeEOj6d+vWAdPfo7ZRjL63UFktz6p1Wef8xsBG+3rbgHHHO5lN0vCdn98utFne6UyBbR8w/c7vELKmCRPlt2OKUfnyszuFXN+VGjBes9TOjsezOwsvD80xdzer+/B2iZi087tGTH4r7KZZf+9Ir/pmunvEZKz95ojJWHsPzYI+Yk+fufZ8r0CfrHZqy/HM3pqp/mOfQM8zqr7uzo99k1zuSdtPc/NTt6TyPiNikveeiEneZ4aMKzWlZ39hSxYdXup3bRqenZXiDX72gATTdedAy8ul4SXml8OCRX1eXzo75s73B8XMtcEHg9FBSKaXHS5JnTskYlLn3hIzEyT3KW8VNjhvQSkaALozdtN2ro97e8xVc8xhHBrbwC/Me2POTQX2hM1Jc2m2EU5f2q4wo3D6Yx423WRXmt4OzTePFefGdqkmnMKcl7aVJhxlNj+2c3VkIGbu7JPDLKvWatkU7UOdajXzLFd7oA53NuYXGt0P0u20xsbcu7wAnG7jq1F14AO+8fzCBG+2mrUMfDDmdBJaF7+/Fvnc7Uka8nT3w53YEWCUEFMh9Ps2rBliquSyv6fs8U7LPE5hjkDn73UuC8QW+8xMrDTqZhUthbcEjOY7+DHSj3R6e4KbRg5rqdJxuBwlbzPDloGZNBW/jcn+HaLJjgek6yjFGnnezdr0GLGjLWs1M9NT2XeH0nYMWLFcOM8qXbvf7Z1WNw90s7xTlBY9BN9WYo7awPzYFGefEK+GvJFTgWc4L2Y04Eg73gW2qUU2kj+bznpgI/eXs2+yiMv64LGA6bvUx4XlU5wq0pdrXe2JbES6q/r03HGaqz2PKyKdnOz2x01EXM5cnozZVNusz61l9Uq1wzbNyIY8YFLWdu1vCzau0bBfZxDPVMip9eW31YZxfGSD7COMdszlfUVec2uTZ826KRMaJoJ1QtaUMWQ3YPwGclu+EgyHLK5y8Qfnc53g7MyH6ImMPIUkUhyrLO8W28VX1iZaNfdbd3XBhkqD5fKCSv/AcMWkgp45MdCNU9349V2KDQwOjOgxyEkB0/k5OWS4PW6sMV5sf3bjqncruwXz0SUj/FMC1qrKuptTE8z0F+NuPtLnOEYT85E=
*/