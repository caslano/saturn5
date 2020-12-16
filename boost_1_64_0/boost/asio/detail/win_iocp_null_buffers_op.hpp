//
// detail/win_iocp_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_null_buffers_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_null_buffers_op);

  win_iocp_null_buffers_op(socket_ops::weak_cancel_token_type cancel_token,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&win_iocp_null_buffers_op::do_perform,
        &win_iocp_null_buffers_op::do_complete),
      cancel_token_(cancel_token),
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
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_null_buffers_op* o(static_cast<win_iocp_null_buffers_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // The reactor may have stored a result in the operation object.
    if (o->ec_)
      ec = o->ec_;

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_NETNAME_DELETED)
    {
      if (o->cancel_token_.expired())
        ec = boost::asio::error::operation_aborted;
      else
        ec = boost::asio::error::connection_reset;
    }
    else if (ec.value() == ERROR_PORT_UNREACHABLE)
    {
      ec = boost::asio::error::connection_refused;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
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
  socket_ops::weak_cancel_token_type cancel_token_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_NULL_BUFFERS_OP_HPP

/* win_iocp_null_buffers_op.hpp
fd6n8ZRFaJ+Xkd9W8JfwRHg5zIFXwTy4Es6AV8BitWv56PkA5ClC+fSNsSpbwP6wNTwJtoWnwM5wAMyAA+FgOAgOU/cJcAicrPJT4WBYJHatd0a3vlxDrt/drnfaHt3lDbTTD8KecD0cCx+FufAxeBF8HM5Se4XaF8CNcK3KPwmfhbvgJvgJ/ANsZusphK2gbR8A/wzPgi/AXPg6LIBvwAq4E66Eb8HfwrfhbWq/Q+33wV22v5exCvwA7oNxPt4PYAf4DTwZ7oQToEW9OQ964RS156h9BvTBWTAG3gvj4HZo5+tTmIg9hXJMgr3hFr3PGyzV26w6oylnaYPW6X0u0vt6ETwBlsBzYCm8CJbBSlgOfwVnwZVqv0btq+EceCusgHfDedDrCYRvCX8GO8GFMB3OhX3gTNhP3U+DP4HD1W6nf6ClOn5hqtbTGNhT08+GtsqmMA62ho1gO7U77U6mhr80QrvTHDnRIQu7wiTYHbaGg2ALeCZsCc+FyTBH/UvVPse26/WqLdXpqnppV6ue7tv0esPJVw84Cg6BY+BQOBZmwfH63IyDOWovh1nwG5gNG3loP+Bl8Dx4Mzwb3g4vgBuhHW4rzIMfwWnQIj2TYAycCBvD0dBpD0Q3JrwjQntQYAXa50J4EpwBB8MieAYshuPgRfBCCRd4LkthBZwFL4Oz4Uo4HV4N52g7R1mpvkjRiSnXt1V6kFb5u4F0toG/hSlwDewKb9Zyq4KXwnu0nq6DV6j9WngvfBDeB5+FD8CX4IPwB7geNuWaD8Fj4cPwFLgBngkfhaK3FI6Dt8CZcC2cB++EF8O74CXwbrgYPg2r4DPwXvgs3AI3wZ3wD7A5efwjbAf/BDPgZjgYPgeHqfsE+DU8Bz4PL4MvwivhVngDfAVWw1fh43Ab/IPaN6v9BfgafBv+BX4Ed8D98A3Y0xdIdyb8G5wK98FS+DmshF/Y14Vfwdvh1/B19d8H34E/wPcgddX6CC6BH8BfQzudlJWEux9+B5+EB+30wu+hvkehX63ucYy8l22re3wg441tdb8vI0ch1f3+NhKToXLrVS4ODlG5Wd5Afzlb39sq9L1tgfbP8+DV8BJoxm3b65ffrO31y2/l9vrlt3p73fmdbPS3SB8rcml2+6X99h+R6wafgz3U3lftWfB5bR/+DJfALfBSuA1er/Y1ar8Xvgwfgq/AR+CL8Fn4F/gS3AG/h29Av71/ECbBt2AqfBt2hLtgb/gu7Avfh6fD3XA4/BCeDT+Ck+DHsAB+AqfDvXAu/Az+FP4NLoP74HL4hZ1++A28HR600w2/h1uhx8M4BH6L/V34HPwSxuJ+AMZB7a9VFwdlHqG/vlPL927YQ+0Zas+05eBoeA+cqvY8tU+H98K58CFtfx+Bt8h1aS/gY/B5+DjcAqvhe/ABSFrlOq3hk7A9fAr2h/dr/dhsdExw7zT9yXZd0fRX8v9xcCnsCS+Fp8NlWj9ugLnwt/AquAbeDa/Q9FwF34Ur4V/hr6HHPtsKDoGr4FB4LRwLr4NZ8Hp4AVwNL4TL4Xx4GVwIfwXvhDfDJ2CVU98dXQiwrT4X8XCs5udM5GyOhE3gOOiHWbCpLQdbqP0YOBq2se0a/1ZHTwEcquXVWvdD2n/veQLye2AK/BimwU9gL/ipzmPshYPhZ3AI/Cs8A34OJ8Av4FT4JVwE98Mb1f9u+C18Cn4H34Q/wL9CjzfwHueDSTAOJsOv8W8HG2PvAZvAnjAB6jyM7iWX/e+ueZglhO8El8JR8FI4Gf4SXgh/BefDK+Dl8AZ4A/wtvAleBW+HK+G98NfwAXg1fBFeA3fC6+A78Hq4G67R5yzD7GWWsaakz05PZ23Hbkc=
*/