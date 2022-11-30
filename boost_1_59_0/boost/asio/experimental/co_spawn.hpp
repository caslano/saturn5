//
// experimental/co_spawn.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_ASIO_EXPERIMENTAL_CO_SPAWN_HPP
#define BOOST_ASIO_EXPERIMENTAL_CO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <utility>
#include <boost/asio/compose.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/experimental/coro.hpp>
#include <boost/asio/experimental/deferred.hpp>
#include <boost/asio/experimental/prepend.hpp>
#include <boost/asio/redirect_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename T, typename U, typename Executor>
struct coro_spawn_op
{
  coro<T, U, Executor> c;

  void operator()(auto& self)
  {
    auto op = c.async_resume(deferred);
    std::move(op)((prepend)(std::move(self), 0));
  }

  void operator()(auto& self, int, auto... res)
  {
    self.complete(std::move(res)...);
  }
};

} // namespace detail

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename T, typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(coro<void, T, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void(std::exception_ptr, T)>(
      detail::coro_spawn_op<void, T, Executor>{std::move(c)},
      token, exec);
}

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename T, typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(coro<void(), T, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void(std::exception_ptr, T)>(
      detail::coro_spawn_op<void(), T, Executor>{std::move(c)},
      token, exec);
}

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename T, typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void(T))
co_spawn(coro<void() noexcept, T, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void(T)>(
      detail::coro_spawn_op<void() noexcept, T, Executor>{std::move(c)},
      token, exec);
}

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(coro<void, void, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void(std::exception_ptr)>(
      detail::coro_spawn_op<void, void, Executor>{std::move(c)},
      token, exec);
}

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(coro<void(), void, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void(std::exception_ptr)>(
      detail::coro_spawn_op<void(), void, Executor>{std::move(c)},
      token, exec);
}

/// Spawn a resumable coroutine.
/**
 * This function spawns the coroutine for execution on its executor. It binds
 * the lifetime of the coroutine to the executor.
 *
 * @param c The coroutine
 *
 * @param token The completion token
 *
 * @returns Implementation defined
 */
template <typename Executor, typename CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void())
co_spawn(coro<void() noexcept, void, Executor> c, CompletionToken&& token)
{
  auto exec = c.get_executor();
  return async_compose<CompletionToken, void()>(
      detail::coro_spawn_op<void() noexcept, void, Executor>{std::move(c)},
      token, exec);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif //BOOST_ASIO_EXPERIMENTAL_CO_SPAWN_HPP

/* co_spawn.hpp
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
*/