//
// experimental/impl/use_coro.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP
#define BOOST_ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

template <typename Yield, typename Return, typename Executor>
struct coro;

namespace detail {

template <typename Yield, typename Return, typename Executor>
struct coro_promise;

template <typename Executor, typename... Ts>
struct coro_init_handler
{
  struct handler_t
  {
  };

  constexpr static handler_t handler{};

  struct init_helper;

  struct promise_type
  {
    auto initial_suspend() noexcept { return suspend_always{}; }

    auto final_suspend() noexcept { return suspend_always(); }

    void return_void() {}

    void unhandled_exception() { assert(false); }

    auto await_transform(handler_t)
    {
      assert(executor);
      assert(h);
      return init_helper{this};
    }

    std::optional<Executor> executor;
    std::optional<std::tuple<Ts...>> result;
    coroutine_handle<> h;

    coro_init_handler get_return_object() { return coro_init_handler{this}; }

    cancellation_slot cancel_slot;
  };

  struct init_helper
  {
    promise_type *self_;

    constexpr static bool await_ready() noexcept { return true; }

    constexpr static void await_suspend(coroutine_handle<>) noexcept {}

    auto await_resume() const noexcept
    {
      assert(self_);
      return bind_cancellation_slot(self_->cancel_slot,
          bind_executor(*self_->executor, [self = self_](Ts... ts)
          {
            self->cancel_slot.clear();
            self->result.emplace(std::move(ts)...);
            self->h.resume();
          }));
    }
  };

  promise_type* promise;

  void unhandled_exception() noexcept
  {
    throw;
  }

  struct noexcept_version
  {
    promise_type *promise;

    constexpr static bool await_ready() noexcept { return false; }

    template <typename Yield, typename Return,
        convertible_to<Executor> Executor1>
    auto await_suspend(
        coroutine_handle<coro_promise<Yield, Return, Executor1> > h) noexcept
    {
      promise->executor = h.promise().get_executor();
      promise->h = h;
      return coroutine_handle<promise_type>::from_promise(*promise);
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<Args...>&& tup)
    {
      return std::move(tup);
    }

    template <typename Arg>
    static auto resume_impl(std::tuple<Arg>&& tup)
    {
      return get<0>(std::move(tup));
    }

    static void resume_impl(std::tuple<>&&) {}

    auto await_resume() const noexcept
    {
      auto res = std::move(promise->result.value());
      coroutine_handle<promise_type>::from_promise(*promise).destroy();
      return resume_impl(std::move(res));
    }
  };

  struct throwing_version
  {
    promise_type *promise;

    constexpr static bool await_ready() noexcept { return false; }

    template <typename Yield, typename Return,
        convertible_to<Executor> Executor1>
    auto await_suspend(
        coroutine_handle<coro_promise<Yield, Return, Executor1> > h) noexcept
    {
      promise->executor = h.promise().get_executor();
      promise->h = h;
      return coroutine_handle<promise_type>::from_promise(*promise);
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<Args...>&& tup)
    {
      return std::move(tup);
    }

    static void resume_impl(std::tuple<>&&) {}

    template <typename Arg>
    static auto resume_impl(std::tuple<Arg>&& tup)
    {
      return get<0>(std::move(tup));
    }

    template <typename... Args>
    static auto resume_impl(std::tuple<std::exception_ptr, Args...>&& tup)
    {
      auto ex = get<0>(std::move(tup));
      if (ex)
        std::rethrow_exception(ex);

      if constexpr (sizeof...(Args) == 0u)
        return;
      else if constexpr (sizeof...(Args) == 1u)
        return get<1>(std::move(tup));
      else
      {
        return
          [&]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            return std::make_tuple(std::get<Idx + 1>(std::move(tup))...);
          }(std::make_index_sequence<sizeof...(Args) - 1>{});
      }
    }

    template <typename... Args>
    static auto resume_impl(
        std::tuple<boost::system::error_code, Args...>&& tup)
    {
      auto ec = get<0>(std::move(tup));
      if (ec)
        boost::asio::detail::throw_exception(
            boost::system::system_error(ec, "error_code in use_coro"));

      if constexpr (sizeof...(Args) == 0u)
        return;
      else if constexpr (sizeof...(Args) == 1u)
        return get<1>(std::move(tup));
      else
        return
          [&]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            return std::make_tuple(std::get<Idx + 1>(std::move(tup))...);
          }(std::make_index_sequence<sizeof...(Args) - 1>{});
    }

    static auto resume_impl(std::tuple<std::exception_ptr>&& tup)
    {
      auto ex = get<0>(std::move(tup));
      if (ex)
        std::rethrow_exception(ex);
    }

    static auto resume_impl(
        std::tuple<boost::system::error_code>&& tup)
    {
      auto ec = get<0>(std::move(tup));
      if (ec)
        boost::asio::detail::throw_error(ec, "error_code in use_coro");
    }

    auto await_resume() const
    {
      auto res = std::move(promise->result.value());
      coroutine_handle<promise_type>::from_promise(*promise).destroy();
      return resume_impl(std::move(res));
    }
  };

  auto as_noexcept(cancellation_slot&& sl) && noexcept
  {
    promise->cancel_slot = std::move(sl);
    return noexcept_version{promise};
  }

  auto as_throwing(cancellation_slot&& sl) && noexcept
  {
    promise->cancel_slot = std::move(sl);
    return throwing_version{promise};
  }
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename Executor, typename R, typename... Args>
struct async_result<experimental::use_coro_t<Executor>, R(Args...)>
{
  using return_type = experimental::detail::coro_init_handler<
    Executor, typename decay<Args>::type...>;

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(Initiation initiation,
      experimental::use_coro_t<Executor>, InitArgs... args)
  {
    std::move(initiation)(co_await return_type::handler, std::move(args)...);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_IMPL_USE_CORO_HPP

/* use_coro.hpp
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
*/