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
HKTTM7/I6MSEVMv3vDICiGRh3sOT1Bdp0qdRtBSNFdTS6skiEQDV34J9hFK6+/exRVZAG67ZN5F56q4/qFNcw4u9eH4HXOAXr+gVbuOtIGnFIQDENrgpUQ8VgdV3OE00eiEstOLKXQwIObrHZmo7jeGbyW0xJR66WqOoSTlH6TI3AaD/wErKs8x66U9Tj+7FJN3N25z/kw0AKk0OFAQuNuuPYU5ZviQg+99Ib+6B1UImR4fvlhEdcp9B0s06njGY8w0CPHuJ2uPY30l68pAfKcJeYELRFD9BGg04TR+tED/i+b38xHc+M4azopNgmkT1WVy66UbkVddtA8Vq7LZ6KKWDyRSvDKor4Z1WSM6hllS4O9ETE//ONXbG+A2+W0tgzFuNIQN8ubSEgvlqRbcghfVTRzrGDVYNixZMN8zq8JTK2QVF/DU1cJDDOis5dVSM+YQ15PKi8Da7/yI7kz5hUrO0yrm1D8bwoggSDN3HIXl11CcnADI7HVIQ6Plk8pTT9O3bxjZMQw2w2I+9qPNq6Ps0pkoqSXqecrhXMuyj3oKjE7e6jCFlePFgZA==
*/