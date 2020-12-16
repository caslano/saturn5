//
// detail/win_iocp_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_socket_connect_op_base : public reactor_op
{
public:
  win_iocp_socket_connect_op_base(socket_type socket, func_type complete_func)
    : reactor_op(&win_iocp_socket_connect_op_base::do_perform, complete_func),
      socket_(socket),
      connect_ex_(false)
  {
  }

  static status do_perform(reactor_op* base)
  {
    win_iocp_socket_connect_op_base* o(
        static_cast<win_iocp_socket_connect_op_base*>(base));

    return socket_ops::non_blocking_connect(
        o->socket_, o->ec_) ? done : not_done;
  }

  socket_type socket_;
  bool connect_ex_;
};

template <typename Handler, typename IoExecutor>
class win_iocp_socket_connect_op : public win_iocp_socket_connect_op_base
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_connect_op);

  win_iocp_socket_connect_op(socket_type socket,
      Handler& handler, const IoExecutor& io_ex)
    : win_iocp_socket_connect_op_base(socket,
        &win_iocp_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_connect_op* o(
        static_cast<win_iocp_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    if (owner)
    {
      if (o->connect_ex_)
        socket_ops::complete_iocp_connect(o->socket_, ec);
      else
        ec = o->ec_;
    }

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, ec);
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

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_CONNECT_OP_HPP

/* win_iocp_socket_connect_op.hpp
7AOfgqPg03ASfAYWqP9c9c+Az8LZcDdcAJ+DS+Dz8HL4AlwBfwmvhS/DtfAV+B34KtwAfwM3w9fh4/D38En4B7gHvgV/p+l6F74DP4IH4REpd507g9/SdtuU31dovaT/lveCBbCf+geofxQsg5NhOZyu/hnq76X2Mc+EFfBC+HVYBJfB5bAcXgu/BkkP5a5j/nCPtpNmcKWm56jW049hN/g3mAf/DifAT+F56p+p/tnwn3AZ/BxeqeHWwAbaf8bBh2Ai3AYbwl/AzyzzPNExajnnep4013JqCfNgK30+pcMC9Z+r/hdU7k3YFr4N28E44mxj7LTquJ2OSSZF2Gkdg1x3OE6fH+fAfHiu3ofz4Bz4FbgAzoBL1X+Z+r8Jz4d3qfz34ET4KJwAf6j+ajhJnxuTYRAWajr3WzpeA6dqOtuI/W/+1C5wF7UHPBiuhmfBNfq8u1Gf3zfBC+BauFjtAV+p8mvhBrgB3qbPtdvhk/AOTd+dcBe8C+6D34Vvq/xf4D3w7/BeLef7YCK8H7aDD8BMuEnr7YOwL3wEDuQbEftzJ7RRN3Ght226wow4p306Y5sOu3TYpPv32KP7d9uiq8qIOyX26Opri66udujc9ucibc9Fb3cuGptzam/OZWtud0ZcnezNHZ1NOfePtDdXP1tzfnbmsDFn7MvFt41TG3O2fblTY1vOz65cJtcLty0XnV25k7EplzIn7pTalfOyKZfNNY7blTt5m3L5xFeCW4PbjHsBdxiXzkZZY3CluA24atxBXMtibLPhSnBrcTtwL+MO41pejK033FzcGtxmXDVuHy6ezY6ycPmXxOyzxf5if7G/2F/sL/b33/L35dn/Y879FNn/e6EP429qV+zOOB33V32FD3DnhtYb3ij6CrLYILQYWy4fprcsp1RnwZbPNjoGE8X/up+eosr3NDo/48T/lpV6fP07xVIWpjMzVmR+K/4CE0c3tx6F6k2cL+efEv9UIz/MrdulOi7Fcn6bZduny9L5QbSI1zvWn/navXhUwjcxNtTeE39KmM27wtAYlehqLZfr9MB/IW6vHrOvM131D5xhVyL3q5Bcq8oXnTbCnDKvIbO5Js1POdLsa7NpXxRp/pQ4X5I1dpWPRK6xU90b0dM/FoXeQ0gPX65B8YpJNDHKF7k+XeqWHMuN0L9M41ie0ckxdURk8916Oaaer1X7eRtwXZQXca3ymxz1HGtCWtGlvC5w13OV72bW3n1H/IsY7w1K3Z3vUXcnmHA5Rq+/Svwl1jlWcz/bAxqmp9HPvE38C9HWCXjqQ94r5y+2Jlhpvjr6PxGZ8WibtjfrhbbKsYmE6SH6ilVxsi+h6iv2FJ3cQT76iqkqn5mgOjRN83x1sa9ofuL6YdeDC47XA2PDZr7rnrtsFcg976u6WPlqk6+XbfsL92Aato7Wyj2X6jdnQbmU5aY0WcOs99mWae84N1vvpX2OPtfk68TrwZtqvoiLtBaJP9f4Z0u6bZusuzTd7TXdLdUWU3lNunXxqZ38kB0mS9b4TCRcFU76koZN0DOtKf9a0oY+XHg7KVR7gZ302ulqx7DKdW2xceRny1DlO0Vry3B8rbYMNW0FarPuMU3XFtxXh5Ffd9pE55TTzna8tFSuIenTMOtokYXIaLt1tJUJRmY9mqYzHW1UdDLNevgjInOVdS7pLMFp29WwncPaaZq20wY3h84tZd1AMuE6iMzfh8paMGPf5SMJf5M1nf/zcWlGJ1SzWZMMoxvaVuJMlvY7l3u4M0l1LOOzabnB+B5+7Vfl9yepjmVynp9+JfW8Xm1Yy13bsLm3ke2XDEXYiTncyNt2ZXUor3W0XVl9c/1tHfnZrtzV2Nt25f4=
*/