//
// impl/co_spawn.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Executor, typename = void>
class co_spawn_work_guard
{
public:
  typedef typename decay<
      typename prefer_result<Executor,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type executor_type;

  co_spawn_work_guard(const Executor& ex)
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

private:
  executor_type executor_;
};

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
struct co_spawn_work_guard<Executor,
    typename enable_if<
      !execution::is_executor<Executor>::value
    >::type> : executor_work_guard<Executor>
{
  co_spawn_work_guard(const Executor& ex)
    : executor_work_guard<Executor>(ex)
  {
  }
};

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
inline co_spawn_work_guard<Executor>
make_co_spawn_work_guard(const Executor& ex)
{
  return co_spawn_work_guard<Executor>(ex);
}

template <typename T, typename Executor, typename F, typename Handler>
awaitable<awaitable_thread_entry_point, Executor> co_spawn_entry_point(
    awaitable<T, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_co_spawn_work_guard(ex);
  auto handler_work = make_co_spawn_work_guard(
      boost::asio::get_associated_executor(handler, ex));

  (void) co_await (dispatch)(
      use_awaitable_t<Executor>{__FILE__, __LINE__, "co_spawn_entry_point"});

  (co_await awaitable_thread_has_context_switched{}) = false;
  std::exception_ptr e = nullptr;
  bool done = false;
  try
  {
    T t = co_await f();

    done = true;

    if (co_await awaitable_thread_has_context_switched{})
    {
      (dispatch)(handler_work.get_executor(),
          [handler = std::move(handler), t = std::move(t)]() mutable
          {
            std::move(handler)(std::exception_ptr(), std::move(t));
          });
    }
    else
    {
      (post)(handler_work.get_executor(),
          [handler = std::move(handler), t = std::move(t)]() mutable
          {
            std::move(handler)(std::exception_ptr(), std::move(t));
          });
    }

    co_return;
  }
  catch (...)
  {
    if (done)
      throw;

    e = std::current_exception();
  }

  if (co_await awaitable_thread_has_context_switched{})
  {
    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), e]() mutable
        {
          std::move(handler)(e, T());
        });
  }
  else
  {
    (post)(handler_work.get_executor(),
        [handler = std::move(handler), e]() mutable
        {
          std::move(handler)(e, T());
        });
  }
}

template <typename Executor, typename F, typename Handler>
awaitable<awaitable_thread_entry_point, Executor> co_spawn_entry_point(
    awaitable<void, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_co_spawn_work_guard(ex);
  auto handler_work = make_co_spawn_work_guard(
      boost::asio::get_associated_executor(handler, ex));

  (void) co_await (dispatch)(
      use_awaitable_t<Executor>{__FILE__, __LINE__, "co_spawn_entry_point"});

  (co_await awaitable_thread_has_context_switched{}) = false;
  std::exception_ptr e = nullptr;
  try
  {
    co_await f();
  }
  catch (...)
  {
    e = std::current_exception();
  }

  if (co_await awaitable_thread_has_context_switched{})
  {
    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), e]() mutable
        {
          std::move(handler)(e);
        });
  }
  else
  {
    (post)(handler_work.get_executor(),
        [handler = std::move(handler), e]() mutable
        {
          std::move(handler)(e);
        });
  }
}

template <typename T, typename Executor>
class awaitable_as_function
{
public:
  explicit awaitable_as_function(awaitable<T, Executor>&& a)
    : awaitable_(std::move(a))
  {
  }

  awaitable<T, Executor> operator()()
  {
    return std::move(awaitable_);
  }

private:
  awaitable<T, Executor> awaitable_;
};

template <typename Handler, typename Executor, typename = void>
class co_spawn_cancellation_handler
{
public:
  co_spawn_cancellation_handler(const Handler& handler, const Executor& ex)
    : ex_(boost::asio::get_associated_executor(handler, ex))
  {
  }

  cancellation_slot slot()
  {
    return signal_.slot();
  }

  void operator()(cancellation_type_t type)
  {
    cancellation_signal* sig = &signal_;
    boost::asio::dispatch(ex_, [sig, type]{ sig->emit(type); });
  }

private:
  cancellation_signal signal_;
  typename associated_executor<Handler, Executor>::type ex_;
};


template <typename Handler, typename Executor>
class co_spawn_cancellation_handler<Handler, Executor,
    typename enable_if<
      is_same<
        typename associated_executor<Handler,
          Executor>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type>
{
public:
  co_spawn_cancellation_handler(const Handler&, const Executor&)
  {
  }

  cancellation_slot slot()
  {
    return signal_.slot();
  }

  void operator()(cancellation_type_t type)
  {
    signal_.emit(type);
  }

private:
  cancellation_signal signal_;
};

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
    typedef typename decay<Handler>::type handler_type;
    typedef co_spawn_cancellation_handler<
      handler_type, Executor> cancel_handler_type;

    auto slot = boost::asio::get_associated_cancellation_slot(handler);
    cancel_handler_type* cancel_handler = slot.is_connected()
      ? &slot.template emplace<cancel_handler_type>(handler, ex_)
      : nullptr;

    cancellation_slot proxy_slot(
        cancel_handler
          ? cancel_handler->slot()
          : cancellation_slot());

    cancellation_state cancel_state(proxy_slot);

    auto a = (co_spawn_entry_point)(static_cast<awaitable_type*>(nullptr),
        ex_, std::forward<F>(f), std::forward<Handler>(handler));
    awaitable_handler<executor_type, void>(std::move(a),
        ex_, proxy_slot, cancel_state).launch();
  }

private:
  Executor ex_;
};

} // namespace detail

template <typename Executor, typename T, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr, T)) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(const Executor& ex,
    awaitable<T, AwaitableExecutor> a, CompletionToken&& token,
    typename constraint<
      (is_executor<Executor>::value || execution::is_executor<Executor>::value)
        && is_convertible<Executor, AwaitableExecutor>::value
    >::type)
{
  return async_initiate<CompletionToken, void(std::exception_ptr, T)>(
      detail::initiate_co_spawn<AwaitableExecutor>(AwaitableExecutor(ex)),
      token, detail::awaitable_as_function<T, AwaitableExecutor>(std::move(a)));
}

template <typename Executor, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr)) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(const Executor& ex,
    awaitable<void, AwaitableExecutor> a, CompletionToken&& token,
    typename constraint<
      (is_executor<Executor>::value || execution::is_executor<Executor>::value)
        && is_convertible<Executor, AwaitableExecutor>::value
    >::type)
{
  return async_initiate<CompletionToken, void(std::exception_ptr)>(
      detail::initiate_co_spawn<AwaitableExecutor>(AwaitableExecutor(ex)),
      token, detail::awaitable_as_function<
        void, AwaitableExecutor>(std::move(a)));
}

template <typename ExecutionContext, typename T, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr, T)) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(ExecutionContext& ctx,
    awaitable<T, AwaitableExecutor> a, CompletionToken&& token,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
        && is_convertible<typename ExecutionContext::executor_type,
          AwaitableExecutor>::value
    >::type)
{
  return (co_spawn)(ctx.get_executor(), std::move(a),
      std::forward<CompletionToken>(token));
}

template <typename ExecutionContext, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr)) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(ExecutionContext& ctx,
    awaitable<void, AwaitableExecutor> a, CompletionToken&& token,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
        && is_convertible<typename ExecutionContext::executor_type,
          AwaitableExecutor>::value
    >::type)
{
  return (co_spawn)(ctx.get_executor(), std::move(a),
      std::forward<CompletionToken>(token));
}

template <typename Executor, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(const Executor& ex, F&& f, CompletionToken&& token,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type)
{
  return async_initiate<CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type>(
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
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type)
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