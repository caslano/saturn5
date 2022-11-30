//
// experimental/detail/channel_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_OP_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/experimental/channel_error.hpp>
#include <boost/asio/experimental/detail/channel_operation.hpp>
#include <boost/asio/experimental/detail/channel_payload.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Payload>
class channel_send : public channel_operation
{
public:
  Payload get_payload()
  {
    return BOOST_ASIO_MOVE_CAST(Payload)(payload_);
  }

  void complete()
  {
    func_(this, complete_op, 0);
  }

  void cancel()
  {
    func_(this, cancel_op, 0);
  }

  void close()
  {
    func_(this, close_op, 0);
  }

protected:
  channel_send(func_type func, BOOST_ASIO_MOVE_ARG(Payload) payload)
    : channel_operation(func),
      payload_(BOOST_ASIO_MOVE_CAST(Payload)(payload))
  {
  }

private:
  Payload payload_;
};

template <typename Payload, typename Handler, typename IoExecutor>
class channel_send_op : public channel_send<Payload>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(channel_send_op);

  channel_send_op(BOOST_ASIO_MOVE_ARG(Payload) payload,
      Handler& handler, const IoExecutor& io_ex)
    : channel_send<Payload>(&channel_send_op::do_action,
        BOOST_ASIO_MOVE_CAST(Payload)(payload)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_action(channel_operation* base,
      channel_operation::action a, void*)
  {
    // Take ownership of the operation object.
    channel_send_op* o(static_cast<channel_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    channel_operation::handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(channel_operation::handler_work<
          Handler, IoExecutor>)(o->work_));

    boost::system::error_code ec;
    switch (a)
    {
    case channel_operation::cancel_op:
      ec = error::channel_cancelled;
      break;
    case channel_operation::close_op:
      ec = error::channel_closed;
      break;
    default:
      break;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the handler is posted. Even if we're not about to post the handler, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    boost::asio::detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, ec);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Post the completion if required.
    if (a != channel_operation::destroy_op)
    {
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
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

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_OP_HPP

/* channel_send_op.hpp
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
*/