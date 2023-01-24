//
// impl/dispatch.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_DISPATCH_HPP
#define BOOST_ASIO_IMPL_DISPATCH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/work_dispatcher.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class initiate_dispatch
{
public:
  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) const
  {
    typedef typename decay<CompletionHandler>::type DecayedHandler;

    typename associated_executor<DecayedHandler>::type ex(
        (get_associated_executor)(handler));

    typename associated_allocator<DecayedHandler>::type alloc(
        (get_associated_allocator)(handler));

    ex.dispatch(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), alloc);
  }
};

template <typename Executor>
class initiate_dispatch_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_dispatch_with_executor(const Executor& ex)
    : ex_(ex)
  {
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return ex_;
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) const
  {
    typedef typename decay<CompletionHandler>::type DecayedHandler;

    typename associated_allocator<DecayedHandler>::type alloc(
        (get_associated_allocator)(handler));

    ex_.dispatch(detail::work_dispatcher<DecayedHandler>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_dispatch(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_dispatch_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  return (dispatch)(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DISPATCH_HPP

/* dispatch.hpp
9s9st4B7DQMYy0QKne5IH5l73wPpjeccRdIkSosNIvA+I7n6oWh8J9N0UFYkWLjIxM5G9HNcPIOJRBvr9gU1SPMfp41VihIMP/WAzZ6A6Uh+ypV+/u0xv3khlsgjWpRifOG5U1JjD04M4ErmEGg+CrEEkWbFMCwqtzNeuHmvxqoGL+OmcGESZu3EI0QRcXab2k85xKw+3fpEbVMuxKMbONcGqEJIi/lj5f2oPGmKxx57aO6uceYTE0uk/x6IYlG6JXu5RkgZwlZM9BSK4bSAKqG4frEUh6Z5t3HmkxeHUrURnc0mRh1o/sOvBGT/RUhcptNTTvnh4++COLgOZz5VMe3j5RR0GveaA/Fy+G+a4sXGvjVIfAoq8ndVlCclx18+NQhHMeNjS93bvyneL5SgXJfOStAXa4BU7xNiy3e7rus18VGVnP4ExSOx8GbOJUYl+Av/18Xv3rbYUVUn/yaIGufA+Wq0MCk5U0snoEfY1v4QF2ju0ijB2dZS37aoKCGopT+j7d+2mCohnmLoz+i0e1SpMK+LWakxlMSosKgEtkuwEpIDd5zq3UwMTvgtEQs/4FwyUrJmv+RSsuZc63nbchEFUN8V7UO6UB3TFOtSYSTPgJ+iZDR3e6PI2S8d/+gKpkA0k6EpLTEpEI1kYPjpBDVOqod7UObd0sRTYETHFKfFq7WiF6CIjrQoaEQL9SYz9zHibUtJlG4yMOqU
*/