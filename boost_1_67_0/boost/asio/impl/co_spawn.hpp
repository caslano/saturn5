//
// impl/co_spawn.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_CO_SPAWN_HPP
#define BOOST_ASIO_IMPL_CO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T, typename Executor, typename F, typename Handler>
awaitable<void, Executor> co_spawn_entry_point(
    awaitable<T, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_work_guard(ex);
  auto handler_work = make_work_guard(handler, ex);

  (void) co_await (post)(spawn_work.get_executor(),
      use_awaitable_t<Executor>{});

  bool done = false;
  try
  {
    T t = co_await f();

    done = true;

    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), t = std::move(t)]() mutable
        {
          handler(std::exception_ptr(), std::move(t));
        });
  }
  catch (...)
  {
    if (done)
      throw;

    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), e = std::current_exception()]() mutable
        {
          handler(e, T());
        });
  }
}

template <typename Executor, typename F, typename Handler>
awaitable<void, Executor> co_spawn_entry_point(
    awaitable<void, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_work_guard(ex);
  auto handler_work = make_work_guard(handler, ex);

  (void) co_await (post)(spawn_work.get_executor(),
      use_awaitable_t<Executor>{});

  std::exception_ptr e = nullptr;
  try
  {
    co_await f();
  }
  catch (...)
  {
    e = std::current_exception();
  }

  (dispatch)(handler_work.get_executor(),
      [handler = std::move(handler), e]() mutable
      {
        handler(e);
      });
}

template <typename Executor>
class initiate_co_spawn
{
public:
  typedef Executor executor_type;

  template <typename OtherExecutor>
  explicit initiate_co_spawn(const OtherExecutor& ex)
    : ex_(ex)
  {
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return ex_;
  }

  template <typename Handler, typename F>
  void operator()(Handler&& handler, F&& f) const
  {
    typedef typename result_of<F()>::type awaitable_type;

    auto a = (co_spawn_entry_point)(static_cast<awaitable_type*>(nullptr),
        ex_, std::forward<F>(f), std::forward<Handler>(handler));
    awaitable_handler<executor_type, void>(std::move(a), ex_).launch();
  }

private:
  Executor ex_;
};

} // namespace detail

template <typename Executor, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(const Executor& ex, F&& f, CompletionToken&& token,
    typename enable_if<
      is_executor<Executor>::value
    >::type*)
{
  return async_initiate<CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>>(
      detail::initiate_co_spawn<
        typename result_of<F()>::type::executor_type>(ex),
      token, std::forward<F>(f));
}

template <typename ExecutionContext, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(ExecutionContext& ctx, F&& f, CompletionToken&& token,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type*)
{
  return (co_spawn)(ctx.get_executor(), std::forward<F>(f),
      std::forward<CompletionToken>(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CO_SPAWN_HPP

/* co_spawn.hpp
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
*/