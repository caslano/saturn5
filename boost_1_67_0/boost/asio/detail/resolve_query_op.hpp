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
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
*/