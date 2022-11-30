//
// impl/defer.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_DEFER_HPP
#define BOOST_ASIO_IMPL_DEFER_HPP

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

class initiate_defer
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
          execution::relationship.continuation,
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

    ex.defer(boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }
};

template <typename Executor>
class initiate_defer_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_defer_with_executor(const Executor& ex)
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
          execution::relationship.continuation,
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
          execution::relationship.continuation,
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

    ex_.defer(boost::asio::detail::bind_handler(
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

    ex_.defer(detail::work_dispatcher<handler_t, handler_ex_t>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler),
          handler_ex), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_defer(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<
      execution::is_executor<Executor>::value || is_executor<Executor>::value
    >::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_defer_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_defer_with_executor<
        typename ExecutionContext::executor_type>(
          ctx.get_executor()), token);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DEFER_HPP

/* defer.hpp
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
*/