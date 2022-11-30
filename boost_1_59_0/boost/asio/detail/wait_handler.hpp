//
// detail/wait_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP
#define BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/wait_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class wait_handler : public wait_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(wait_handler);

  wait_handler(Handler& h, const IoExecutor& io_ex)
    : wait_op(&wait_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    wait_handler* h(static_cast<wait_handler*>(base));
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
    detail::binder1<Handler, boost::system::error_code>
      handler(h->handler_, h->ec_);
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

#endif // BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP

/* wait_handler.hpp
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
*/