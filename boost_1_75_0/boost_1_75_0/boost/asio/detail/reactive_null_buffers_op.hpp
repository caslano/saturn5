//
// detail/reactive_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

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
class reactive_null_buffers_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_null_buffers_op);

  reactive_null_buffers_op(Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&reactive_null_buffers_op::do_perform,
        &reactive_null_buffers_op::do_complete),
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
    reactive_null_buffers_op* o(static_cast<reactive_null_buffers_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

/* reactive_null_buffers_op.hpp
sHktEYMSzfN2MN2/U3jkwW7VyvmUauW8gqycXpJNcIoaVeH6FyGutzSpnaGut4SV9V3ey0Ow4usIYEWo/LwntNfTma6aK1VOkGdtZVu4UoW3nlOlwPh4bu8MWTG8dUH9ilCJYUcoxqBBl7QrBGOBX17S5UGFD2A/xpPVoS0D1bsWB9q1la9j9K7FR+Rdex+m1KQdl9QynIlCR9udbf042uLNXo62+R0+1M9satM44FBH27XUBXzrqQBvAdgcHWz4XL/LOUOdbBNC0LpT87StVj1tqRB62qYGZ7+ybzatd2w/SJK4Rg9Vo68tFs61sSd+1keZs7NNVeYQgFzmnhBU5iAYTZmjPm65JKDM2dAdVObg0MzxrOzWehemzEFNEtKWVE2ZUwldIGVOfmBENWXOZaTMWULKnINLAzMalujtgb2GFlY3Gf4C6NngO+9aJHd1VH3BbIgkB9zIassJbV7mGzyFQZfb2SiavBgO/pIQ8H/qC57cei/m4A2epE7VyxaTveLOia6Mw4Nk8/W5XZ6ndWF0vrY9ZNHUngulea/rvA/1JbslIS87Q192ngsnmN4bsQXpfQhZ6JKdHQpg9rkwQoX6sA8sJ7xpah8sJ7QV1iV/4E0MgdLTFgKlpyMcxR/IRtmJs4T8ZT8gf9k3Vg/zvT/iA99J1V+WCw24+LnXrJFfwLsqbxjqO4uFQ31nawbXoVqtlKYMvube90ef
*/