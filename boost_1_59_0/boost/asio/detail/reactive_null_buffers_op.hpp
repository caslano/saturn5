//
// detail/reactive_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class reactive_null_buffers_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_null_buffers_op);

  reactive_null_buffers_op(const boost::system::error_code& success_ec,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(success_ec, &reactive_null_buffers_op::do_perform,
        &reactive_null_buffers_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static status do_perform(reactor_op*)
  {
    return done;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_null_buffers_op* o(static_cast<reactive_null_buffers_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

/* reactive_null_buffers_op.hpp
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
*/