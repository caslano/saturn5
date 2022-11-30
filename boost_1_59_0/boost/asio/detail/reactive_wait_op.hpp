//
// detail/reactive_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP

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
class reactive_wait_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_wait_op);

  reactive_wait_op(const boost::system::error_code& success_ec,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(success_ec, &reactive_wait_op::do_perform,
        &reactive_wait_op::do_complete),
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
    reactive_wait_op* o(static_cast<reactive_wait_op*>(base));
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
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP

/* reactive_wait_op.hpp
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
*/