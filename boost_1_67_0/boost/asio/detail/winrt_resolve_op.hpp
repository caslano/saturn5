//
// detail/winrt_resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol, typename Handler, typename IoExecutor>
class winrt_resolve_op :
  public winrt_async_op<
    Windows::Foundation::Collections::IVectorView<
      Windows::Networking::EndpointPair^>^>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_resolve_op);

  typedef typename Protocol::endpoint endpoint_type;
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  winrt_resolve_op(const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<
        Windows::Foundation::Collections::IVectorView<
          Windows::Networking::EndpointPair^>^>(
            &winrt_resolve_op::do_complete),
      query_(query),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_resolve_op* o(static_cast<winrt_resolve_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    results_type results = results_type();
    if (!o->ec_)
    {
      try
      {
        results = results_type::create(o->result_, o->query_.hints(),
            o->query_.host_name(), o->query_.service_name());
      }
      catch (Platform::Exception^ e)
      {
        o->ec_ = boost::system::error_code(e->HResult,
            boost::system::system_category());
      }
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, results_type>
      handler(o->handler_, o->ec_, results);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  query_type query_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_RESOLVE_OP_HPP

/* winrt_resolve_op.hpp
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
*/