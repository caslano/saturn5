//
// detail/impl/strand_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/completion_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

inline strand_service::strand_impl::strand_impl()
  : operation(&strand_service::do_complete),
    locked_(false)
{
}

template <typename Handler>
void strand_service::dispatch(strand_service::implementation_type& impl,
    Handler& handler)
{
  // If we are already in the strand then the handler can run immediately.
  if (running_in_this_thread(impl))
  {
    fenced_block b(fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(handler, handler);
    return;
  }

  // Allocate and construct an operation to wrap the handler.
  typedef completion_handler<Handler, io_context::executor_type> op;
  typename op::ptr p = { boost::asio::detail::addressof(handler),
    op::ptr::allocate(handler), 0 };
  p.p = new (p.v) op(handler, io_context_.get_executor());

  BOOST_ASIO_HANDLER_CREATION((this->context(),
        *p.p, "strand", impl, 0, "dispatch"));

  operation* o = p.p;
  p.v = p.p = 0;
  do_dispatch(impl, o);
}

// Request the io_context to invoke the given handler and return immediately.
template <typename Handler>
void strand_service::post(strand_service::implementation_type& impl,
    Handler& handler)
{
  bool is_continuation =
    boost_asio_handler_cont_helpers::is_continuation(handler);

  // Allocate and construct an operation to wrap the handler.
  typedef completion_handler<Handler, io_context::executor_type> op;
  typename op::ptr p = { boost::asio::detail::addressof(handler),
    op::ptr::allocate(handler), 0 };
  p.p = new (p.v) op(handler, io_context_.get_executor());

  BOOST_ASIO_HANDLER_CREATION((this->context(),
        *p.p, "strand", impl, 0, "post"));

  do_post(impl, p.p, is_continuation);
  p.v = p.p = 0;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP

/* strand_service.hpp
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
*/