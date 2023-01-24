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
eigEHCtHe57CeDwDtHQlCmVFTCoLjYOvQhaZoOLbJ95+ttGbUZrDGLfuiEtCSFQTDLofzhmyn0FK2N+33oxu9KAUhRiOIZjArEBOCrDH15HFDpDLRsd9AAFaDERzeAnUfNRBj4E0H9i1AHdHO+LvrP2DyvYgWi/ydwuTVT/ExEwgAwNotvYv4o6kXZRT6dOoBFjs8NM34JTbIyHzgzC7I40wE9HugZhKSpwQLykYnTYnZnWMr2pg6HIZxOPIVCY2LzXucUdGWUempSgJuId9AbfiI+dHTui+i4g6io50aSdyjZ0cob/B+Ymu5HfXEKSZsFw2ADIxW8YIW8YBHNHIMhZpizgAizgDirBFnPokLmKYPlmKiwiMAVvF8fg5uoyan5yyE7nBHNcv8R9gQaPQFCn7kMTQfoy2wsq8jfjOt1RPJI8heOVEv1JZbRJnq6qcosq43b9EZpI+8wSeD5jmJ3lLmMwU2nRxJ1KeOMGqVs6TWZNEX45tYHf0k/uZUMtOdsfY+jY4M/4GhYDzpfuhmNqRCnLNtBGQVYillrn04AWMKIbZ5StRL7LtfaygE/1q2W1NzOZRyJXexzJXbqMe2pB+w/KZY7uR+ZkIZvi82cDK0jcewOesylvnqNw50w9L8+OAkwBpJ0q6xSn8dkbQuEpd6Go4mhRoOHSVlji+Ug9LQh/ASH6MHVUyV5OEvDxhUl6eeCMBoR/2SmnI
*/