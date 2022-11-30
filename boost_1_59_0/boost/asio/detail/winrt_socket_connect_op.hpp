//
// detail/winrt_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_work.hpp>
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
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_connect_op* o(static_cast<winrt_socket_connect_op*>(base));
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
  handler_work<Handler, IoExecutor> executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP

/* winrt_socket_connect_op.hpp
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
*/