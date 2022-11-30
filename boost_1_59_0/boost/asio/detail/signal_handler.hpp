//
// detail/signal_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_HANDLER_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/signal_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class signal_handler : public signal_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(signal_handler);

  signal_handler(Handler& h, const IoExecutor& io_ex)
    : signal_op(&signal_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    signal_handler* h(static_cast<signal_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };

    BOOST_ASIO_HANDLER_COMPLETION((*h));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          h->work_));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, int>
      handler(h->handler_, h->ec_, h->signal_number_);
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

#endif // BOOST_ASIO_DETAIL_SIGNAL_HANDLER_HPP

/* signal_handler.hpp
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
*/