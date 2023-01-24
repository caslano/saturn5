//
// impl/post.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_POST_HPP
#define BOOST_ASIO_IMPL_POST_HPP

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

class initiate_post
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

    ex.post(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), alloc);
  }
};

template <typename Executor>
class initiate_post_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_post_with_executor(const Executor& ex)
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

    ex_.post(detail::work_dispatcher<DecayedHandler>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_post(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_post_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  return (post)(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_POST_HPP

/* post.hpp
sTyJYydewnUXKDgaVjqdSL/Aae6KsRVTx6Ybx608Tu58U3zR9UtntTnRk/nvz4c/bucUbwoUJuC6/uke/Rvmb7Kn6PMr9379GTuiPbyP4lAmBBIaCfD6mhSqX8OiOoovpCNzOD7A52q+DDToujqz2XX6QK5ENbnd72gKFOGJE08yEezByUJ/4B2itS2sqzcBbAJFjy2WFYxmwe3xU97gvEePlhWgJ+Ia35ifcMsyNfWQxb7sC3D2UrstspF/MUbmnyZIT1OHPz9C9UJ9u/2h84h258DN2lmnikIL3sEU9kRAQ+E25cvzvwjmIOwVP7Vu93mr0SopUEjQeLh1KwbrdpxtCNS7ha3WEGfEsuBLGa+Rp2InpBzywhHtTvkzzM+tqnTO5cIPZ4khip9ZFGh8ZINuLN/Iv2TKfrr70JOz6XofRzVUhJ+wSsui0PH+WKTi0RFFzqrYWTJRtnhU6AiimDui+WDHguK3oP1gOmY+GzqXFidgo93XYkonc4l71/MnGWCpMFfFKPFOzid0Sqm3PWy4SBTwdsAGJBPtFbY3/sSqYSYbClT9BnyYqeHX0N7EELHVa+hBZ+MsX//1wn/0/pa7o8lhnvWujbn94PMhAUURTSM7Ee2olpU32fxB7BfZerIcnWOk+RLD/E6sk27zL3YvmbqXzAYvoNwpN28qyF67bUMr70Tz5a+LVjwGD1yWFmIaUu6id+9HVxXG
*/