//
// experimental/coro.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_CORO_HPP
#define BOOST_ASIO_EXPERIMENTAL_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/error.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/experimental/coro_traits.hpp>
#include <boost/asio/experimental/detail/coro_promise_allocator.hpp>
#include <boost/asio/experimental/detail/partial_promise.hpp>
#include <boost/asio/experimental/use_coro.hpp>
#include <boost/asio/post.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename T, typename Coroutine>
struct coro_with_arg;

} // namespace detail

/// The main type of a resumable coroutine.
/**
 * Template parameter @c Yield specifies type or signature used by co_yield,
 * @c Return specifies the type used for co_return, and @c Executor specifies
 * the underlying executor type.
 */
template <typename Yield = void, typename Return = void,
    typename Executor = any_io_executor>
struct coro
{
  /// The traits of the coroutine. See boost::asio::experimental::coro_traits
  /// for details.
  using traits = coro_traits<Yield, Return, Executor>;

  /// The value that can be passed into a symmetrical cororoutine. @c void if
  /// asymmetrical.
  using input_type = typename traits::input_type;

  /// The type that can be passed out through a co_yield.
  using yield_type = typename traits::yield_type;

  /// The type that can be passed out through a co_return.
  using return_type = typename traits::return_type;

  /// The type received by a co_await or async_resume. Its a combination of
  /// yield and return.
  using result_type = typename traits::result_type;

  /// The signature used by the async_resume.
  using signature_type = typename traits::signature_type;

  /// Whether or not the coroutine is noexcept.
  constexpr static bool is_noexcept = traits::is_noexcept;

  /// The error type of the coroutine. Void for noexcept
  using error_type = typename traits::error_type;

  /// Completion handler type used by async_resume.
  using completion_handler = typename traits::completion_handler;

  /// The internal promise-type of the coroutine.
  using promise_type = detail::coro_promise<Yield, Return, Executor>;

#if !defined(GENERATING_DOCUMENTATION)
  template <typename T, typename Coroutine>
  friend struct detail::coro_with_arg;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// The executor type.
  using executor_type = Executor;

#if !defined(GENERATING_DOCUMENTATION)
  friend struct detail::coro_promise<Yield, Return, Executor>;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// The default constructor, gives an invalid coroutine.
  coro() = default;

  /// Move constructor.
  coro(coro&& lhs) noexcept
    : coro_(std::exchange(lhs.coro_, nullptr))
  {
  }

  coro(const coro &) = delete;

  /// Move assignment.
  coro& operator=(coro&& lhs) noexcept
  {
    std::swap(coro_, lhs.coro_);
    return *this;
  }

  coro& operator=(const coro&) = delete;

  /// Destructor. Destroys the coroutine, if it holds a valid one.
  /**
   * @note This does not cancel an active coroutine. Destructing a resumable
   * coroutine, i.e. one with a call to async_resume that has not completed, is
   * undefined behaviour.
   */
  ~coro()
  {
    if (coro_ != nullptr)
    {
      struct destroyer
      {
        detail::coroutine_handle<promise_type> handle;

        destroyer(const detail::coroutine_handle<promise_type>& handle)
          : handle(handle)
        { }

        destroyer(destroyer&& lhs)
          : handle(std::exchange(lhs.handle, nullptr))
        {
        }

        destroyer(const destroyer&) = delete;

        void operator()() {}

        ~destroyer()
        {
          if (handle)
            handle.destroy();
        }
      };

      auto handle =
        detail::coroutine_handle<promise_type>::from_promise(*coro_);
      if (handle)
        boost::asio::dispatch(coro_->get_executor(), destroyer{handle});
    }
  }

  /// Get the used executor.
  executor_type get_executor() const
  {
    if (coro_)
      return coro_->get_executor();

    if constexpr (std::is_default_constructible_v<Executor>)
      return Executor{};
    else
      throw std::logic_error("Coroutine has no executor");
  }

  /// Resume the coroutine.
  /**
   * @param token The completion token of the async resume.
   *
   * @attention Calling an invalid coroutine with a noexcept signature is
   * undefined behaviour.
   *
   * @note This overload is only available for coroutines without an input
   * value.
   */
  template <typename CompletionToken>
    requires std::is_void_v<input_type>
  auto async_resume(CompletionToken&& token) &
  {
    return async_initiate<CompletionToken,
        typename traits::completion_handler>(
          initiate_async_resume(this), token);
  }

  /// Resume the coroutine.
  /**
   * @param token The completion token of the async resume.
   *
   * @attention Calling an invalid coroutine with a noexcept signature is
   * undefined behaviour.
   *
   * @note This overload is only available for coroutines with an input value.
   */
  template <typename CompletionToken, detail::convertible_to<input_type> T>
  auto async_resume(T&& ip, CompletionToken&& token) &
  {
    return async_initiate<CompletionToken,
        typename traits::completion_handler>(
          initiate_async_resume(this), token, std::forward<T>(ip));
  }

  /// Operator used for coroutines without input value.
  auto operator co_await() requires (std::is_void_v<input_type>)
  {
    return awaitable_t{*this};
  }

  /// Operator used for coroutines with input value.
  /**
   * @param ip The input value
   *
   * @returns An awaitable handle.
   *
   * @code
   * coro<void> push_values(coro<double(int)> c)
   * {
   *    std::optional<double> res = co_await c(42);
   * }
   * @endcode
   */
  template <detail::convertible_to<input_type> T>
  auto operator()(T&& ip)
  {
    return detail::coro_with_arg<std::decay_t<T>, coro>{
        std::forward<T>(ip), *this};
  }

  /// Check whether the coroutine is open, i.e. can be resumed.
  bool is_open() const
  {
    if (coro_)
    {
      auto handle =
        detail::coroutine_handle<promise_type>::from_promise(*coro_);
      return handle && !handle.done();
    }
    else
      return false;
  }

  /// Check whether the coroutine is open, i.e. can be resumed.
  explicit operator bool() const { return is_open(); }

private:
  struct awaitable_t;

  struct initiate_async_resume;

  explicit coro(promise_type* const cr) : coro_(cr) {}

  promise_type* coro_{nullptr};
};

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/coro.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_CORO_HPP

/* coro.hpp
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
*/