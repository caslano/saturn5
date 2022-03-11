//
// detail/resolve_endpoint_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/error.hpp>
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
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
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
      char host_name[NI_MAXHOST];
      char service_name[NI_MAXSERV];
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
  IoExecutor io_executor_;
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