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
LMVDZrhc03x+A83nd9S6GKPPcPWzIte0THcsDpUDOagscyZWKLwlFWaF7+ySBU54qxrZ8qPwSk59+A5O2XL3H4wNmx9yLjzXlUtx15lcYPWD467hlrv+ayw8Y4AXWbmBh1yPVmllTj5Uuo7xpmtVI1u+cVPrI2x5t/G2c9uZh5jbzoqc244Yg9l3juNZns7ezUU1Ii92KC/sDu1D78+WbDd3LuUfVt89zv5szUVYmQHKs5Ab7W3/Py9i3Wn+pOLK+aXeMZqsXnaMxs6LrqEsLSUO+81c5XHdvPuuNRYSd+91eI1BnL3XedF7rzUm0qpX5F7qXqE61GyiUz7UN+ao1tjPsfLVvIRqU6lOjFqjLLkObhwKMmp/VinuRe7BV5gO5MfOI7zVAnk3TLxslRUFhcWVClfMOJtkW7hnbl9h9PiQGGjlPcPQzf/XrHm2x6zCPQv3e9bsukA7W0KCdj13Nem2Oj80JnZaWp209mmdzWhYvfhnGGy27nRzw/Rnqx9EmNrGHSN73Mo0O6wxMiddw2uAv6+8P0v7Kv/i6iPTfX+B49j5GHaC42F7czZIb5vutD9LivKd5TJaV+mt4ySn92OKSTer7x8Mr6mMWEMk+b5Wfwb6JVbfJ+hXl81x5Xtb/VwzXmX1A4NRa3nc8esLrfnxwfAYWVF5VWV4H8JCa94jGHXWpDtefbE17+oxx7SsyB1je9KajyUNk51n6BZlO3MwdewYb9ieCVmVpy1+j7U7w90zd53VdwzWD7xS41h25FrNiqi1muE6dKbPeXJzs6PGRpX364odD8w3pYnY0azb7WPzPrSaLJ8apXBOxJoyffXC5Vx2ztI3Jyyj6l35H5LLQs6Zn8ix+n6sFEoKdA8mRawlm+3xI9fa1flB2vN0Uh8nr5sSq+xggvyW3bDf7hqWQVZ+cSBT84ATXTdbSYaV131t/Y4vQf916iq3c629lODBQL3I9b59Itacxf22h/czRdohwr7rR0uRLbRyGcEvAg3Dewyj7FeH31P+wntvR9l4JbtrrLKsfnKgM88G27VXITtutpti7+4fvdb68bpdO7nF7isN77kqLb8wfy6fvhLPPqdXrXxCoLH2OX1p9fMJEakd65delfB39xor/8O44dW8LWv0arceOnKNnspv7Bq9cJmNWaOn8uizRm92lJ2KOOv6Fhyi7VPt894e6ON5b3V36I4EM14RoBTcfsMtw7+blPjlsMIT7ih74wTq8S/sHZuf73489aeXLl4x6pVPCkrO7rSH82x6m+fvLs/6ec+tZZ8v/nDt5iVrj/kl8kHzvGLH3Ms/3t/5Ny9cfWqbHn8e+Njh3zUa707O86z7+4dNaDO/y4+WP5o55Ed193z5DvtAbPhHji9s9ee8Az3qVrTZc9mAg/i7rKd53urXC5d/3iHvkSsWjLn78ofu2v713e35T+v+jIcuWZvxUvPbxizZd07pwbwbGGvuaJ5ffvLafgtOCJx3zZAuex/Izjw1/l2p/neiHv6drvHuUB1kw/n8JS/85p8fX3Xgoh8c0+Le5WenxL9D9Sc2f9u+VJhWOmPsd/9Q9/KKjl1zb2I9Q3fz/JbrZk/amPTe64/cfNw/f7Zy2c3x74b1vwM23l2s8e9ufcvmb8LNJe07XvrJia0OtmrU7P5Zr3InTqJ5fuO0p5LqX/7Zr9pvfKl9l+vHnMwckel/aX+qaR8f5PeiVKedNZDfrwScu2Wqg07b/2PP79LG4d8bWoZ/rwr/tmsRcxKcdUmPeH6XdEIOmdsDlNXwb3te8AZ+Tw7YtYH2+S3mPQ3/tudmmG/S7kTnLDc9Z71i2P2/hX+zBtCRfwb1V/1+A/Wxfr+POqDfvbA=
*/