//
// detail/win_iocp_overlapped_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_overlapped_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_overlapped_op);

  win_iocp_overlapped_op(Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_overlapped_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_overlapped_op* o(static_cast<win_iocp_overlapped_op*>(base));
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
      handler(o->handler_, ec, bytes_transferred);
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

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP

/* win_iocp_overlapped_op.hpp
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
*/