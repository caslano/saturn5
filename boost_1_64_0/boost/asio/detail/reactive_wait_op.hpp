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
3PFQOyZPtdU46QVHmiPnIs4O+agnwm2Q5rAcsvt19jJMdibVuJsIv5QIsaSpvLBbfVlGgBcSNZO7nbaQwMzh9uC3l6wRq5a/rlLj4IaymDK3umoDmR/fLV3emwR7P42sxoE/syNJG+7pf5NWa16Bf27MmPVPsTUpnz2ZARhXwRD9FL8knDrQTUZYY+4ajrH/6Y/ym0ml6yFkTzlt1+5Wy5k/uuXaezYSh8/OdfIqAZoJGFwl5Z1I1LBQtWIRUe6JDUhOyJh+dJnirpp2a747O6ziVsCQVOMtY7IwDqJqGvY9cCPYzUo34UOo4mpANCiA9IobfzwujqQzvrGlUPf94fgpI29OWqF+DEVSjmm8kAa7LLutBqXS8kPaNGfIalhd7q1oMg30jRKuzxazKw8owYVKWO1TE0ifr0RuTRjmNoiRUEme7sYlkk6IFdnz604ohSSCEdVLDy+rmbw0XbKyn5oPv8GjmFUBuC44NTXbM20oJYcTa1+dZXj5yIXc7oHNoW4tQb3+oib56rCmXbbJdmx5YW2bbZ11UzYtShh8aaQsSXTJyIqOczav6A==
*/