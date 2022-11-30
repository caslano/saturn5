//
// experimental/awaitable_operators.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_AWAITABLE_OPERATORS_HPP
#define BOOST_ASIO_EXPERIMENTAL_AWAITABLE_OPERATORS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <variant>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/experimental/deferred.hpp>
#include <boost/asio/experimental/parallel_group.hpp>
#include <boost/asio/multiple_exceptions.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace awaitable_operators {
namespace detail {

template <typename T, typename Executor>
awaitable<T, Executor> awaitable_wrap(awaitable<T, Executor> a,
    typename constraint<is_constructible<T>::value>::type* = 0)
{
  return a;
}

template <typename T, typename Executor>
awaitable<std::optional<T>, Executor> awaitable_wrap(awaitable<T, Executor> a,
    typename constraint<!is_constructible<T>::value>::type* = 0)
{
  co_return std::optional<T>(co_await std::move(a));
}

template <typename T>
T& awaitable_unwrap(typename conditional<true, T, void>::type& r,
    typename constraint<is_constructible<T>::value>::type* = 0)
{
  return r;
}

template <typename T>
T& awaitable_unwrap(std::optional<typename conditional<true, T, void>::type>& r,
    typename constraint<!is_constructible<T>::value>::type* = 0)
{
  return *r;
}

} // namespace detail

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename Executor>
awaitable<void, Executor> operator&&(
    awaitable<void, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, std::move(t), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return;
}

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename U, typename Executor>
awaitable<U, Executor> operator&&(
    awaitable<void, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, std::move(t), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return std::move(detail::awaitable_unwrap<U>(r1));
}

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename T, typename Executor>
awaitable<T, Executor> operator&&(
    awaitable<T, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return std::move(detail::awaitable_unwrap<T>(r0));
}

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename T, typename U, typename Executor>
awaitable<std::tuple<T, U>, Executor> operator&&(
    awaitable<T, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return std::make_tuple(
      std::move(detail::awaitable_unwrap<T>(r0)),
      std::move(detail::awaitable_unwrap<U>(r1)));
}

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename... T, typename Executor>
awaitable<std::tuple<T..., std::monostate>, Executor> operator&&(
    awaitable<std::tuple<T...>, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return std::move(detail::awaitable_unwrap<std::tuple<T...>>(r0));
}

/// Wait for both operations to succeed.
/**
 * If one operations fails, the other is cancelled as the AND-condition can no
 * longer be satisfied.
 */
template <typename... T, typename U, typename Executor>
awaitable<std::tuple<T..., U>, Executor> operator&&(
    awaitable<std::tuple<T...>, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_error(),
      use_awaitable_t<Executor>{}
    );

  if (ex0 && ex1)
    throw multiple_exceptions(ex0);
  if (ex0)
    std::rethrow_exception(ex0);
  if (ex1)
    std::rethrow_exception(ex1);
  co_return std::tuple_cat(
      std::move(detail::awaitable_unwrap<std::tuple<T...>>(r0)),
      std::make_tuple(std::move(detail::awaitable_unwrap<U>(r1))));
}

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename Executor>
awaitable<std::variant<std::monostate, std::monostate>, Executor> operator||(
    awaitable<void, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, std::move(t), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  if (order[0] == 0)
  {
    if (!ex0)
      co_return std::variant<std::monostate, std::monostate>{
          std::in_place_index<0>};
    if (!ex1)
      co_return std::variant<std::monostate, std::monostate>{
          std::in_place_index<1>};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<std::monostate, std::monostate>{
          std::in_place_index<1>};
    if (!ex0)
      co_return std::variant<std::monostate, std::monostate>{
          std::in_place_index<0>};
    throw multiple_exceptions(ex1);
  }
}

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename U, typename Executor>
awaitable<std::variant<std::monostate, U>, Executor> operator||(
    awaitable<void, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, std::move(t), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  if (order[0] == 0)
  {
    if (!ex0)
      co_return std::variant<std::monostate, U>{
          std::in_place_index<0>};
    if (!ex1)
      co_return std::variant<std::monostate, U>{
          std::in_place_index<1>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<std::monostate, U>{
          std::in_place_index<1>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    if (!ex0)
      co_return std::variant<std::monostate, U>{
          std::in_place_index<0>};
    throw multiple_exceptions(ex1);
  }
}

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename T, typename Executor>
awaitable<std::variant<T, std::monostate>, Executor> operator||(
    awaitable<T, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  if (order[0] == 0)
  {
    if (!ex0)
      co_return std::variant<T, std::monostate>{
          std::in_place_index<0>,
          std::move(detail::awaitable_unwrap<T>(r0))};
    if (!ex1)
      co_return std::variant<T, std::monostate>{
          std::in_place_index<1>};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<T, std::monostate>{
          std::in_place_index<1>};
    if (!ex0)
      co_return std::variant<T, std::monostate>{
          std::in_place_index<0>,
          std::move(detail::awaitable_unwrap<T>(r0))};
    throw multiple_exceptions(ex1);
  }
}

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename T, typename U, typename Executor>
awaitable<std::variant<T, U>, Executor> operator||(
    awaitable<T, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  if (order[0] == 0)
  {
    if (!ex0)
      co_return std::variant<T, U>{
          std::in_place_index<0>,
          std::move(detail::awaitable_unwrap<T>(r0))};
    if (!ex1)
      co_return std::variant<T, U>{
          std::in_place_index<1>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<T, U>{
          std::in_place_index<1>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    if (!ex0)
      co_return std::variant<T, U>{
          std::in_place_index<0>,
          std::move(detail::awaitable_unwrap<T>(r0))};
    throw multiple_exceptions(ex1);
  }
}

namespace detail {

template <typename... T>
struct widen_variant
{
  template <std::size_t I, typename SourceVariant>
  static std::variant<T...> call(SourceVariant& source)
  {
    if (source.index() == I)
      return std::variant<T...>{
          std::in_place_index<I>, std::move(std::get<I>(source))};
    else if constexpr (I + 1 < std::variant_size_v<SourceVariant>)
      return call<I + 1>(source);
    else
      throw std::logic_error("empty variant");
  }
};

} // namespace detail

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename... T, typename Executor>
awaitable<std::variant<T..., std::monostate>, Executor> operator||(
    awaitable<std::variant<T...>, Executor> t, awaitable<void, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, std::move(u), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  using widen = detail::widen_variant<T..., std::monostate>;
  if (order[0] == 0)
  {
    if (!ex0)
      co_return widen::template call<0>(
          detail::awaitable_unwrap<std::variant<T...>>(r0));
    if (!ex1)
      co_return std::variant<T..., std::monostate>{
          std::in_place_index<sizeof...(T)>};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<T..., std::monostate>{
          std::in_place_index<sizeof...(T)>};
    if (!ex0)
      co_return widen::template call<0>(
          detail::awaitable_unwrap<std::variant<T...>>(r0));
    throw multiple_exceptions(ex1);
  }
}

/// Wait for one operation to succeed.
/**
 * If one operations succeeds, the other is cancelled as the OR-condition is
 * already satisfied.
 */
template <typename... T, typename U, typename Executor>
awaitable<std::variant<T..., U>, Executor> operator||(
    awaitable<std::variant<T...>, Executor> t, awaitable<U, Executor> u)
{
  auto ex = co_await this_coro::executor;

  auto [order, ex0, r0, ex1, r1] =
    co_await make_parallel_group(
      co_spawn(ex, detail::awaitable_wrap(std::move(t)), deferred),
      co_spawn(ex, detail::awaitable_wrap(std::move(u)), deferred)
    ).async_wait(
      wait_for_one_success(),
      use_awaitable_t<Executor>{}
    );

  using widen = detail::widen_variant<T..., U>;
  if (order[0] == 0)
  {
    if (!ex0)
      co_return widen::template call<0>(
          detail::awaitable_unwrap<std::variant<T...>>(r0));
    if (!ex1)
      co_return std::variant<T..., U>{
          std::in_place_index<sizeof...(T)>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    throw multiple_exceptions(ex0);
  }
  else
  {
    if (!ex1)
      co_return std::variant<T..., U>{
          std::in_place_index<sizeof...(T)>,
          std::move(detail::awaitable_unwrap<U>(r1))};
    if (!ex0)
      co_return widen::template call<0>(
          detail::awaitable_unwrap<std::variant<T...>>(r0));
    throw multiple_exceptions(ex1);
  }
}

} // namespace awaitable_operators
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_AWAITABLE_OPERATORS_HPP

/* awaitable_operators.hpp
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
*/