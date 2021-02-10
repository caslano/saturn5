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
d19vwqw8NPAQ9rPqw9jErgKolGqGOTlYoqEAaG7X+VTGXOtGS21JQaC+nBLs7QLbi2YqMTt6ICOYJR+WZkTSWoV/8wgO7GjncCntJKBFtsOylVWKUdq3qJNAxQSTZ2EPxY4PD8cMUOPDr07mY7t/8iJNMZcIOzOctHKFkd5XipcuTPPcsnPV8kxgRRf1YvTyecwnnR3zr3OeEfPK2CsXS32HKoT9nbANdbYKbfRg86Yii8T+ndmg3gtxRJr2OIiTSa/dyRJw4r428e+2sVma8DGooSo0oqpOCl52abNUJJNBKQyJB4vdp/q2pMYJmWmKNdHBmW9SwsN5Nut+44oYOK+RDiPvTzMD5rfHJ98gRiNKiwDUpe7v7Q3sr1nle7ERfL0ot8wYFjYrQpyNSdtZkJ2jNpb2O7vEyV3GPldk10Fr7oJ2W0+rc5fqKoZKbk+kfR1Ua270GWcVqIktlj0GX1d/LdkrECzSBzt2YyI1/nV8W0OSFIPl+TrrCEWg+69xO92OctbetdR3oiW0J05hhAcyMINA2DpWr9KOYsiPrOLEw6R8rv0mg274zsOnoxeXjI+V3BKIM6xenRodlXhCEsWMV3INaOSA2s0FrXYzVe4GbPaejDXuxVYk8RR9FiWNKJk45MlLN5MFnGDq
*/