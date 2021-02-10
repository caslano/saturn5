//
// awaitable.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_AWAITABLE_HPP
#define BOOST_ASIO_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#include <experimental/coroutine>
#include <boost/asio/executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

using std::experimental::coroutine_handle;
using std::experimental::suspend_always;

template <typename> class awaitable_thread;
template <typename, typename> class awaitable_frame;

} // namespace detail

/// The return type of a coroutine or asynchronous operation.
template <typename T, typename Executor = executor>
class awaitable
{
public:
  /// The type of the awaited value.
  typedef T value_type;

  /// The executor type that will be used for the coroutine.
  typedef Executor executor_type;

  /// Default constructor.
  constexpr awaitable() noexcept
    : frame_(nullptr)
  {
  }

  /// Move constructor.
  awaitable(awaitable&& other) noexcept
    : frame_(std::exchange(other.frame_, nullptr))
  {
  }

  /// Destructor
  ~awaitable()
  {
    if (frame_)
      frame_->destroy();
  }

  /// Checks if the awaitable refers to a future result.
  bool valid() const noexcept
  {
    return !!frame_;
  }

#if !defined(GENERATING_DOCUMENTATION)

  // Support for co_await keyword.
  bool await_ready() const noexcept
  {
    return false;
  }

  // Support for co_await keyword.
  template <class U>
  void await_suspend(
      detail::coroutine_handle<detail::awaitable_frame<U, Executor>> h)
  {
    frame_->push_frame(&h.promise());
  }

  // Support for co_await keyword.
  T await_resume()
  {
    return frame_->get();
  }

#endif // !defined(GENERATING_DOCUMENTATION)

private:
  template <typename> friend class detail::awaitable_thread;
  template <typename, typename> friend class detail::awaitable_frame;

  // Not copy constructible or copy assignable.
  awaitable(const awaitable&) = delete;
  awaitable& operator=(const awaitable&) = delete;

  // Construct the awaitable from a coroutine's frame object.
  explicit awaitable(detail::awaitable_frame<T, Executor>* a)
    : frame_(a)
  {
  }

  detail::awaitable_frame<T, Executor>* frame_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/awaitable.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_AWAITABLE_HPP

/* awaitable.hpp
szbiM4JWKDdVOLKpqdJeRzuTF0L9H+/O3/5j94Ma8PL4cy6SrLs3tbFxG4lfO/yPedv+7brojrZClRo/HAUqeYme3i1XjRbSbjnMNeFHQ4e7riFF4iwcspbbqTC7zhS+OXbfWoPzrZBncqgZD7Xf8XcyGszTnA3eO44JPrDlluC1HbcJR9I8Y7U0+pCXwHtuCx8HL3OIXKUJRsH3LFTx9TR4Z0apx0PINqVBYC5I60Dj3VRT85SA6E2hX7d+2qymenh/pdrPkfL0kYT7k+398hT6hAb+YI+0DIXuSzToIyqHAGh/qh+OFWMKMt1CCBA40X3BX3L3BoeCxU30wI7WxgpzUSU7ywO87pPDFnhqk1DDcWgobgedB2jv2TZ+cBZar9qxhnztOGZZxtOucK6Pd9k2xE1xi28i0yvBrXAthBfqkU8Jt1M/lUUdBNCacxaOa2dSMdPEGDpJdKe9ROcYE6ziOJOppjzchaqP+1Eyz1Zyk7UH27s1PjnvW2r2UyAbgU72/uGHH3J2zv3hVM846atwusTsdLsTyGQxrJbZ+0d/8iU0abRXHqevaMnqovj8GW9m758kN3HIQz+pq2E+abubU7x92s1n3z96/E1+YE1lvjnI3n/7h3P4QsMGm8x3e97luRpiZKyLm4qP
*/