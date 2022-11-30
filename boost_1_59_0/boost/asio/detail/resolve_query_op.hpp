//
// detail/resolve_query_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
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
      const query_type& qry, scheduler_impl& sched,
      Handler& handler, const IoExecutor& io_ex)
    : resolve_op(&resolve_query_op::do_complete),
      cancel_token_(cancel_token),
      query_(qry),
      scheduler_(sched),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex),
      addrinfo_(0)
  {
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
  handler_work<Handler, IoExecutor> work_;
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