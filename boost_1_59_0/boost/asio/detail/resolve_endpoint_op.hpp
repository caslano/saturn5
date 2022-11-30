//
// detail/resolve_endpoint_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP

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
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>

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
class resolve_endpoint_op : public resolve_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(resolve_endpoint_op);

  typedef typename Protocol::endpoint endpoint_type;
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif

  resolve_endpoint_op(socket_ops::weak_cancel_token_type cancel_token,
      const endpoint_type& endpoint, scheduler_impl& sched,
      Handler& handler, const IoExecutor& io_ex)
    : resolve_op(&resolve_endpoint_op::do_complete),
      cancel_token_(cancel_token),
      endpoint_(endpoint),
      scheduler_(sched),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the operation object.
    resolve_endpoint_op* o(static_cast<resolve_endpoint_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner && owner != &o->scheduler_)
    {
      // The operation is being run on the worker io_context. Time to perform
      // the resolver operation.
    
      // Perform the blocking endpoint resolution operation.
      char host_name[NI_MAXHOST] = "";
      char service_name[NI_MAXSERV] = "";
      socket_ops::background_getnameinfo(o->cancel_token_, o->endpoint_.data(),
          o->endpoint_.size(), host_name, NI_MAXHOST, service_name, NI_MAXSERV,
          o->endpoint_.protocol().type(), o->ec_);
      o->results_ = results_type::create(o->endpoint_, host_name, service_name);

      // Pass operation back to main io_context for completion.
      o->scheduler_.post_deferred_completion(o);
      p.v = p.p = 0;
    }
    else
    {
      // The operation has been returned to the main io_context. The completion
      // handler is ready to be delivered.

      BOOST_ASIO_HANDLER_COMPLETION((*o));

      // Take ownership of the operation's outstanding work.
      handler_work<Handler, IoExecutor> w(
          BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
            o->work_));

      // Make a copy of the handler so that the memory can be deallocated
      // before the upcall is made. Even if we're not about to make an upcall,
      // a sub-object of the handler may be the true owner of the memory
      // associated with the handler. Consequently, a local copy of the handler
      // is required to ensure that any owning sub-object remains valid until
      // after we have deallocated the memory here.
      detail::binder2<Handler, boost::system::error_code, results_type>
        handler(o->handler_, o->ec_, o->results_);
      p.h = boost::asio::detail::addressof(handler.handler_);
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
  endpoint_type endpoint_;
  scheduler_impl& scheduler_;
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
  results_type results_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP

/* resolve_endpoint_op.hpp
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
*/