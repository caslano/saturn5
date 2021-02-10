//
// detail/wait_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
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

  wait_handler(Handler& h, const IoExecutor& ex)
    : wait_op(&wait_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h)),
      io_executor_(ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    wait_handler* h(static_cast<wait_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };
    handler_work<Handler, IoExecutor> w(h->handler_, h->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*h));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP

/* wait_handler.hpp
NmCHPhiELOJEk96/GgZKSR+bQJjCeoRfJZGqulKqOe+J9bp4jRVT1KJrfZ4CrtQeoJ5l24VNo/IcwwpXn31t6RG1NTaXctaFoubSr80TZ2tand7wgEEzlBmfJ9eePQv9pltqNX31pK3iR8rbtAGzQC5/Ja8dj7u4XaABj+4vUEsDBAoAAAAIAC1nSlIl0t1ihQMAAE0HAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY29va2llLmRVVAUAAbZIJGBlVEtv2zgQvvNXDHxJAlgu2qN3u0BQBGiANAiaZO+0OLJYUxyBpOxqsT9+Z0g9HOzJljT8Zr7H8LWlkPZwUE/kj3uoiU4W1X3g/38anfS/jXXodYd/qZdAiWpycQ/f395e1Hd0/R5e0ZvpWIQmUAcxBeuPn+Sg+qYTHimMe2hT6lVVVepFxwipRRB4SJT/CyBEDGcMYH1+9S1jQovaYNjBYwIbIQ59TxGNG9UC0Qc8WxqiGyFgjfaMpgwiFSumhs0rpqrA7jfgrMcdwFuLKsPElgZn4IDzAA2FTifYPN//ePj89e/7p/eHz3+APH0pT182O6UeG/AEN19vII7dgZxMOfCEM4oOx6FDn7ZgMwPrY2JKkAKyNgZ05MlmkRXLEeTr
*/