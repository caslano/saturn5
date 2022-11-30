//
// detail/winrt_resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_work.hpp>
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
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_resolve_op* o(static_cast<winrt_resolve_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> executor_;
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