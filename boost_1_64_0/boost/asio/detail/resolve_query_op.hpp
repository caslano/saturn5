//
// detail/resolve_query_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_QUERY_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_QUERY_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol, typename Handler, typename IoExecutor>
class resolve_query_op : public resolve_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(resolve_query_op);

  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif

  resolve_query_op(socket_ops::weak_cancel_token_type cancel_token,
      const query_type& query, scheduler_impl& sched,
      Handler& handler, const IoExecutor& io_ex)
    : resolve_op(&resolve_query_op::do_complete),
      cancel_token_(cancel_token),
      query_(query),
      scheduler_(sched),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex),
      addrinfo_(0)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  ~resolve_query_op()
  {
    if (addrinfo_)
      socket_ops::freeaddrinfo(addrinfo_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the operation object.
    resolve_query_op* o(static_cast<resolve_query_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner && owner != &o->scheduler_)
    {
      // The operation is being run on the worker io_context. Time to perform
      // the resolver operation.
    
      // Perform the blocking host resolution operation.
      socket_ops::background_getaddrinfo(o->cancel_token_,
          o->query_.host_name().c_str(), o->query_.service_name().c_str(),
          o->query_.hints(), &o->addrinfo_, o->ec_);

      // Pass operation back to main io_context for completion.
      o->scheduler_.post_deferred_completion(o);
      p.v = p.p = 0;
    }
    else
    {
      // The operation has been returned to the main io_context. The completion
      // handler is ready to be delivered.

      // Take ownership of the operation's outstanding work.
      handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

      BOOST_ASIO_HANDLER_COMPLETION((*o));

      // Make a copy of the handler so that the memory can be deallocated
      // before the upcall is made. Even if we're not about to make an upcall,
      // a sub-object of the handler may be the true owner of the memory
      // associated with the handler. Consequently, a local copy of the handler
      // is required to ensure that any owning sub-object remains valid until
      // after we have deallocated the memory here.
      detail::binder2<Handler, boost::system::error_code, results_type>
        handler(o->handler_, o->ec_, results_type());
      p.h = boost::asio::detail::addressof(handler.handler_);
      if (o->addrinfo_)
      {
        handler.arg2_ = results_type::create(o->addrinfo_,
            o->query_.host_name(), o->query_.service_name());
      }
      p.reset();

      if (owner)
      {
        fenced_block b(fenced_block::half);
        BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
        w.complete(handler, handler.handler_);
        BOOST_ASIO_HANDLER_INVOCATION_END;
      }
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  query_type query_;
  scheduler_impl& scheduler_;
  Handler handler_;
  IoExecutor io_executor_;
  boost::asio::detail::addrinfo_type* addrinfo_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_QUERY_OP_HPP

/* resolve_query_op.hpp
tPbqzhP/AmMaKJQuL68E5YiKGaXuMgt15pzc1gmmkWaHSRMYkRBqkxAYBi2ilw4xhfT7QD9a0bfJTQhAWI7UIzKs3I9yRueWz/WdurnT2NegPOHW4KrTrAvdb66qb41Ve/QcdVqLp2CKAWUVOK/kvU5D+oCMn3Gx1mQi6BJJ10PiEn0327abLtVo/o1Xlce4CL1loofeUtbghUa+5+ob91wYfWb8dXTQR3VZOB42sdZOKUPZfUWrS/R+igz8a7b9fRgfO6JSHkhq/ky11A33T25Zpj3mMz2zeC9+7iVR7+Fyf2+d6JKeRj7yEXasmje0w0aGyeihWsUlhBLYR9lpispHitnnyTdGiUyVBePsy57tqvNS04I7Xpzle7xMe5QyPwUwa9Q5AZ0fjIslBXVVSygLy/kwuGs7+Yy0aRafvCb20Y75HJ6gsPmN9B3FvgD2P4g9h/Mx0pvyN/P+stDMp9xnxpHslgk5tv2TfubYdlTs8fY9bKdwjh75BV/q/FI+oNwheYp4/4Tpjpg/bblIR5wC05bmcaV3Xi1lXLu8IP/MrLMK5oyfPbmgsr5Cyu3nMsbXLneUM+lTXP1c7PsYM1z5+LmMQYgvYvwoWR6dtl+AttAjbSuLyutlHPROH8OkxLzHk/52f/oV0x99v2bEvZkeeXoHld3ozpOoj9nXReaFtHZac5JbnlbEx7S6+aCkPDpdNyJd293pwhXNYIPycuvbn7SgnFz59/jOEXxnj+s7wmqS//czovO/52vwGuJj/iPeqamITtc20B5yp6u6vnZZzHo5ZPMYZRERiuyxLCLd+aeQbme9JbvGZ3wjoi63VUbn5aMM1Xm68sImE6ucSR+7zcD/q7eZ9zNa3mZ2VnP/Is8QXq3GGzUH0flZhS2LGAcKimqLJS+8V2KVzIaYF9ImWzLeULGv8yXgX3uvrwSx1xKE5ufMP/fJFWRZOolS8f8rVhNuc9DUXuLcY/xtoQlYZ8CuFHsX2T98c6Vav+K8oKL5+b+i32/SNz7X7Pxc0QerSb9uXJP0plvBKeirU8z3uCRPf8KsIw8rWOXNvi1A/R/vZFD1xPODEg90EAO1PWetabff5N/uj/V2fey36HPlLfo7f3TbpA3BwBcTikfcVfnGiCLI3QOV+8urf/+bLz+95vjF3z2j0882nx+O9Ub9f/7N/6dDyv2pl/M/uLO8y+Evr9s+6bUePzuGtWBJ/5Q5xWlv5h8f0Lo6/dBlZ574JfYdCf2uN8/tdmPhXW0uj9/nS/nsjkchb8ub+Xefe0n+kfDVt126s/2hfbdf+zT2/fqU+9EJc9PrM6/e/IvUMVe3PvTF+9iT21q5P5PQ/vGC7Oynzg71P2tF18ldoEeV8kl7cs3mkz3yn7iiYcb9337sp/sMaDqV+7iM0s/WLr6wf2DlhfFr3iv9vWHcIO6vXPvmbyaUlv1o3d8uWfJA9zuRxp90V+4/vv+mJ19+bsWJ1cmPdOgf9/ns2G/7t5X6zcq6Le+dl/+ZOv/A6vT5P0yHkuRdKQf/T8q697z0s7PSTqQldXxoyWvQYUi9rDijb8buTlvv/8fFD2964cpj88E34j734Z1z/vLlvdM/vuv729rc3esWzNZ7Kfd+jbcX3ztn3BmT9ny468hdk7AQ8i+px5MHfxV346Xrtkx99bOisvN7HcJdr5LOurQrP10376bzLu93zg8Ts1u/hXniEOU+elXdNRs2pYYnvHr0kxN9npyGc57qHUoyfFJn0KFcilRaHL/Pc/w+3/E73/F7VJb8lve7Rtu/5V2zTfitRLcO/L1WtSv+3mxoWT4Hv6fB9OLvZTAp/J2DPKXzdzF+p/J3d9RXH/7uibbQRX4=
*/