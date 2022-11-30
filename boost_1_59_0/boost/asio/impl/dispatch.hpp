//
// impl/dispatch.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/execution/allocator.hpp>
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/prefer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class initiate_dispatch
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
        boost::asio::prefer(ex,
          execution::blocking.possibly,
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

    ex.dispatch(boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
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
        boost::asio::prefer(ex_,
          execution::blocking.possibly,
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
        boost::asio::prefer(ex_,
          execution::blocking.possibly,
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

    ex_.dispatch(boost::asio::detail::bind_handler(
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

    ex_.dispatch(detail::work_dispatcher<handler_t, handler_ex_t>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler),
          handler_ex), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_dispatch(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<
      execution::is_executor<Executor>::value || is_executor<Executor>::value
    >::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_dispatch_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(NullaryToken) token,
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type)
{
  return async_initiate<NullaryToken, void()>(
      detail::initiate_dispatch_with_executor<
        typename ExecutionContext::executor_type>(
          ctx.get_executor()), token);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DISPATCH_HPP

/* dispatch.hpp
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
*/