//
// detail/winrt_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class winrt_socket_connect_op :
  public winrt_async_op<void>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_connect_op);

  winrt_socket_connect_op(Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<void>(&winrt_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_connect_op* o(static_cast<winrt_socket_connect_op*>(base));
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

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP

/* winrt_socket_connect_op.hpp
gUsUz47fvHlvxjfsuiU0GLGavCWnuSF14SX2JgXfqiuy4xKutts1rD/dbnMqSCqU3EatPUfWbEPJUrdEFdrABbVAe9ypi0ayl/Cqfvm6fqEuMVLH/rCEPsYRRg4RptEyNqqqKrXtTcjBkAEWEMxgLHqIDLEnYPnxUFW5BI/RsAuwM7HPX2mvKcdU7DFKKIGRb9kPAT5vbqrM3biuVmrLcE9w+f660jyM1qCLiwxS+ocRfYTQ82QbSeyMK2UQ7tprhwPdtWto2VreiRb3B/kQSO5gZA/oGjlrdpGcgIykTWs0JmY1bH+qodElJiOGQI30qXRSeQpCE9hJy22mVWqlYDi4iHsKS1VvblV9vYazudRZ0W9nrIUBvxBkqGPjlIEeaCWSqShkrRKzD5OYIVQ0emonqwLDrOPjrYYpuKcxn1FEQXeAFUjP58JruJdxWADOmJmHXHaZjEowhbuco+5Puyu+agwUhIE0+qQ0tvo3nSXNR0+akvmwUoUqCKLjCMZpO8mQyp+Mk8ypS/3k9F9xyNb+SuQjR8qnrEZCL5mCS3uZk5hHIJnwiCuzZD1hc5g5nbdGFlau/p5Q2qWygq3nIZPqzDcxIV2DZ6XZJEOyztHOGkfh+UL90IjQzRDHDkzi/yBQehBOBPpPCGWX
*/