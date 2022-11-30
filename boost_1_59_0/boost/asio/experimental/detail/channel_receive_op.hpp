//
// experimental/detail/channel_receive_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_RECEIVE_OP_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_RECEIVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/experimental/detail/channel_handler.hpp>
#include <boost/asio/experimental/detail/channel_operation.hpp>
#include <boost/asio/experimental/detail/channel_payload.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Payload>
class channel_receive : public channel_operation
{
public:
  void complete(Payload payload)
  {
    func_(this, complete_op, &payload);
  }

protected:
  channel_receive(func_type func)
    : channel_operation(func)
  {
  }
};

template <typename Payload, typename Handler, typename IoExecutor>
class channel_receive_op : public channel_receive<Payload>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(channel_receive_op);

  template <typename... Args>
  channel_receive_op(Handler& handler, const IoExecutor& io_ex)
    : channel_receive<Payload>(&channel_receive_op::do_action),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_action(channel_operation* base,
      channel_operation::action a, void* v)
  {
    // Take ownership of the operation object.
    channel_receive_op* o(static_cast<channel_receive_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    channel_operation::handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(channel_operation::handler_work<
          Handler, IoExecutor>)(o->work_));

    // Make a copy of the handler so that the memory can be deallocated before
    // the handler is posted. Even if we're not about to post the handler, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    if (a == channel_operation::complete_op)
    {
      Payload* payload = static_cast<Payload*>(v);
      channel_handler<Payload, Handler> handler(
          BOOST_ASIO_MOVE_CAST(Payload)(*payload), o->handler_);
      p.h = boost::asio::detail::addressof(handler.handler_);
      p.reset();
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
    else
    {
      boost::asio::detail::binder0<Handler> handler(o->handler_);
      p.h = boost::asio::detail::addressof(handler.handler_);
      p.reset();
    }
  }

private:
  Handler handler_;
  channel_operation::handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_RECEIVE_OP_HPP

/* channel_receive_op.hpp
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
*/