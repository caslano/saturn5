//
// impl/post.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/execution/allocator.hpp>
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/execution/relationship.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/require.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class initiate_post
{
public:
  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        execution::is_executor<
          typename associated_executor<
            typename decay<CompletionHandler>::type
          >::type
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typename associated_executor<handler_t>::type ex(
        (get_associated_executor)(handler));

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    execution::execute(
        boost::asio::prefer(
          boost::asio::require(ex, execution::blocking.never),
          execution::relationship.fork,
          execution::allocator(alloc)),
        boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)));
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        !execution::is_executor<
          typename associated_executor<
            typename decay<CompletionHandler>::type
          >::type
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typename associated_executor<handler_t>::type ex(
        (get_associated_executor)(handler));

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    ex.post(boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
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
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        execution::is_executor<
          typename conditional<true, executor_type, CompletionHandler>::type
        >::value
      >::type* = 0,
      typename enable_if<
        !detail::is_work_dispatcher_required<
          typename decay<CompletionHandler>::type,
          Executor
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    execution::execute(
        boost::asio::prefer(
          boost::asio::require(ex_, execution::blocking.never),
          execution::relationship.fork,
          execution::allocator(alloc)),
        boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)));
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        execution::is_executor<
          typename conditional<true, executor_type, CompletionHandler>::type
        >::value
      >::type* = 0,
      typename enable_if<
        detail::is_work_dispatcher_required<
          typename decay<CompletionHandler>::type,
          Executor
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typedef typename associated_executor<
      handler_t, Executor>::type handler_ex_t;
    handler_ex_t handler_ex((get_associated_executor)(handler, ex_));

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    execution::execute(
        boost::asio::prefer(
          boost::asio::require(ex_, execution::blocking.never),
          execution::relationship.fork,
          execution::allocator(alloc)),
        detail::work_dispatcher<handler_t, handler_ex_t>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), handler_ex));
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        !execution::is_executor<
          typename conditional<true, executor_type, CompletionHandler>::type
        >::value
      >::type* = 0,
      typename enable_if<
        !detail::is_work_dispatcher_required<
          typename decay<CompletionHandler>::type,
          Executor
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    ex_.post(boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      typename enable_if<
        !execution::is_executor<
          typename conditional<true, executor_type, CompletionHandler>::type
        >::value
      >::type* = 0,
      typename enable_if<
        detail::is_work_dispatcher_required<
          typename decay<CompletionHandler>::type,
          Executor
        >::value
      >::type* = 0) const
  {
    typedef typename decay<CompletionHandler>::type handler_t;

    typedef typename associated_executor<
      handler_t, Executor>::type handler_ex_t;
    handler_ex_t handler_ex((get_associated_executor)(handler, ex_));

    typename associated_allocator<handler_t>::type alloc(
        (get_associated_allocator)(handler));

    ex_.post(detail::work_dispatcher<handler_t, handler_ex_t>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler),
          handler_ex), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_post(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<
      execution::is_executor<Executor>::value || is_executor<Executor>::value
    >::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_post_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_post_with_executor<
        typename ExecutionContext::executor_type>(
          ctx.get_executor()), token);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_POST_HPP

/* post.hpp
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
*/