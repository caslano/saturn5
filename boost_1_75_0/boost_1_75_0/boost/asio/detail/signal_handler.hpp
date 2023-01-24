//
// detail/signal_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_invoke_helpers.hpp>
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
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    signal_handler* h(static_cast<signal_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };
    handler_work<Handler, IoExecutor> w(h->handler_, h->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*h));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SIGNAL_HANDLER_HPP

/* signal_handler.hpp
YntmUtLW6swkCB8VEyPlT6nOnyT6M6DgXfQu9nqf85eAw3uhXcVi+bscOwsuO2sQ08Pw1SLltODRMGcT8tzm/aymzREIXUtaOxBUY3pfhKE80ZvhIQfmhIFuq0KPkDKNhtTyFan8BKxb5bxmxyWb7z2MuxWmaH6h2NXF527nXjLwOS9ZhH4woc/BXs1DE7opcoM/GCF3iF8N938VaZpEL5GXhDOyEdV8Tdu56ixzyfN4u3eWFZriAmJVsmBGaJZzWrJZhRkAPVqp5jUHHpWsr2MBBoo32Uw/NPQl9UTftWgLHMEWQ9GtkXjDUMEJ8YrJ5tuPTfkewZusQifeofADxDu6+H6wZDRbKwDIVrSnqc8yVwJTi/C2LwzEAF0iNxFr/gOAT0Jj5KCoKLwT1pGZHoYDQMBt0h2jFLqANgoWWlpGoA/IUUI0/bD02v7ACJYSIhsicbzt4gsYk5TNOxsy7Bg0o3UaPDXzPHqFJLpGB7p9OYta5mnjdnMPu7yvgMTdnnexqfIdAOztvscoBoNlI8QGq7gVXUgB/Pdii/qJDRmVfoz2ZV90+EvPKbeRJZM6cA8/X6w3V3YtB7LevH/Z0jrv6pKal2Hs1P8FhNUCi1SwDYQK5GTPpNVofHQQ+fKRDkVKJR+u0Nhpa3+80DPJ7SHlk9j0eqUL0r3D0v2BpovGdN/i3eN5rwXRsX/15+jV5bStug7dtNyItGAT
*/