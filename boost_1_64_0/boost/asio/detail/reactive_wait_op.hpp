//
// detail/reactive_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
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

  reactive_wait_op(Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&reactive_wait_op::do_perform,
        &reactive_wait_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP

/* reactive_wait_op.hpp
zI/TtxOYdawPYd9pcNS5MHdJTI7tIe/uNrBITTgS5nrHhzmKc4EVjnwd9e+NX0mOOYdezJVQcBm8wO6VmPhyrorUeOHep2H1tWvXeQyR1/cDN+cdPBCUC3tEhJqKGOZGKBz9dRX4QxK3rq142IaLHpHx3wAPzGlAnjwC3LYuY5eCVRtt3G9VTLZxYk28j1XzVm3l4ePEXAjI5RoPUf6PQx5sv7n3Yc7vEnJ48iWn9Qlw1LJX+68nLbjwLZ6x24pjaif2JHjK58TFOnrc80H1YW7VxFwITc56jVhDDzk22oX5iRsAMR8igEvsWR2DN+xpDkw9n/55yLjZjIa1cxf+AAxfu0IFQD68oGNC2eakUUGHRd/7oo3DMN56bz6EzhOMld4oruS9nIgHgTeO9EpC3uqG8ire29tvD/4IrjoQrJ7/vjeIIyxODcfr1UQc+bki5kTYedg1xSdzmK9ZuMhA5J0o09fBEwWHeRCQmXOD/gK5Md1XnDGsYwRgLT7kaJughgnsTWBQM4SVAv7eAsa12mgX3lYxQ/d5R2JKf4UzhiVmbbvfkzjaYG772e9fJWZtn99XcKRVrLeXcmvb+zeJW9vODyUemAu2H5iYB4XzhSEz50D9HXKl/Q43VNeJdfZBDLUB6+yBa/FT1gR8GsTRqGGOgh1Ho4c5CpJTV1dbH48osy69OvaFx/FbfKy7N+XKOZBfAcO8L57n5WFfA4MKieqHtfcaFvHPjvwGcnzVsexbyNT1aP/QZZgPgzkDFkzbMQrx+x688rg6WxbnDFswdd3ojxYcuhbj1NFY8TjmpoUkrsxcFc9uJrGV3tp2hM15l6Th7JH9NTflMsqMtwjiCFbgyUFcWydyGPA1vLeF3JO6pSavZxCWN8ZbWfA6Ktwo1jq0tuD15TUrIyiLNgZeUV5TWxM90W9X2uq4iHxllP22C2Ja2O0NHPH2x4I7mHgMj1d05o4Gh17DWARj4Ck65p/7w60b+sPURJz6iDhuyG2cEJ9OCjcWDXunR9TWi1RxmjrrnEB5dNFxNT8Z76rjgTw5XMetedLN4Kh50l3HrHnSI8gJ5gme1VNyFesE9mOXmLaPem8pt+6j3seKy3nwfQN4cB/1fgGOrhv0J3yJsa/gAMjUfQUHurLcfHEkOWSDXJnclJBlg1kGz0jnEJLR4sRyWptYlpVdJM/MRf4MJbx8rDiMB2tlOE/TWB4V8uy8kgXZhRnF2VmMDQOmHmbhn5usYDgKjv2MgHxOdh6FlMvLljw/I4HlFGRkZRVmFxWhXEeZ8rK8TC/9owlbQVjBovnu1pEczhGQycOeRTjpATl7YT9jgPkHPePZY025sq/zkYSFCaPDPihSbrZm0tHUxbQWV4Q5zsOLcsL59YX+e3mUIie1mRXdzFW1Ue88sfEWPIb4TGAM+Torp1jN24katqAAEGOTgBnlyHV4soqhYHKWZGcV51DZIK1TLBw1/KkqnpNxlIpNA2arJ9NVLK8kNxfyGZAr9ZHjMRPywEGDyJ8MFeezHzJm5WZjTNqK6ecUZqqcouyFJdl5mdllGXmLEX6WjhczBCxbxYrHj0HInJ7ZKsYZK+RzNPnigmyENVeVlyDT0ObkaFheDg0RFHml4a+d1zjFmfxIYPN1bPZE4ZXTn6tii3KKcmQO8fu2wMe5PnN88jxZCW3FUphTvJgXJOG1wDPzAxwy8MFWVeBhDfFa+W5i3BnYLHoZMt2jTCgyGZQdRSivQoHzFjc5s3MyqVLzqryc7CIOu8jD6dDzzNqaOL1POd6+68UKVhipiETr4oXiOAKMQUvc3692kZDxtghZ7rmSBflubLgsjwaWNReHjKKMS335WgEgTxZ78pw=
*/