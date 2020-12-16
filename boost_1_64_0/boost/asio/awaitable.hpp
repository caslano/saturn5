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
ObcQGt/BMnbPpIwPiznqPSn2vQtf2S1EX/YtxuDofho23YN5y5+lYtXlbJRlBiW988beCCWEDxqT4nlzml6oyFMDtmC8Rw82hCjQIfkJ3EnAFbQzm3E4pgrz4rRx8fY/eiI1iuqi45E0o59ZSIyh+AJHqj78DL2u99meoQco9aclBjecQcXGOWzAQBcrezexg3v7ScNnGftmXEUjl1shwWgjSZ2bx5emvMJjzUe0YVUJ3Ukp5Sl6CuQ3sYJfcMsl0Z2b6VbBXihVlbHOvsU0ZUYDRNx1qcHNjF91HIulv+1Yy/xVuGFyk32uboH88WBaMkIJg6yPHbKKJ73Dh/iiYYuxKzWcDT3uit7hO5n9gAb4ZUO2cZQULf22i5l/aqGvaip8/4UbcCmRZ6MlH2P9WD16IraX5s33gHR3OTZ+9YDtxkJorLXE69pBzKkpJM/zb7C0JZR17smj0HUzuHXeWKQblMNwvw/1W9+j6VIrMEbPnt+6rY9r3WNxcfYtWuYyiQzSvNDq4o3kMiv0nMihpJtFVOkwnyZbayG2Pp2NdB5HVTP/gH9qQkZ8HnnmzKeTpUfgnLIVImUubH5SNl6s8WI+7xci3TiQL7i+lmY49cEusxHLfeXId24c2e9fwUdUhVOs6FHkHlhLH846INXAhAoGqrjp82ycwXRemXWJfKTGYuzeLagsvknN39bhkt5Q3NpeQ1eyPHHTYx19N/BEasVmFKyN489vxdPIG6/5FBTS6rXG7KbePuTPIeQebYSWTCk1v9sD2e4JJNquCVfRVDZBPhnO718z5bgckrw1h24uzcOkCRPIPb6VBq33QKPZBcuc/AR+U4okptvxnZK3SKH0IGa8qcGsQ3u5ULc9zdrfwPtP2WBlwjI69z2IhkftgMe6KJjtDKWWxaE0QvkuGSQyOpb5i4xWnaX/Pv9DSfYqipy0mSk/WoztlZ9BFuvgMa2TqWltwmDyFQxLU6COG6bcNOUf5elsx+dD82j35HLSzLLH3I4RlJjyCzJHfNGcPpOexZvxvr219HSHBb00241D38T4IvceMmN7MS9sCL05eRKB4nUkcVPQQxrswpWBkzh0IRTpEm9pkkYC1UaM4B/OKCO/BWzJ6u0wfWrJ7QdH0tSDJmxCSSDJlkjwcarzkXnBARVKX0hheiy/UT4H2jIWSK8egT5HX2i9UKX14lv4poAbJBIvz5psGumH1C42Xq2ShD6Jw79nKYkLfGJ/xlNUPdVBy6ggYi9ewi9JBatWHmKSidUoSVZnO9Z5It0zgO6PHI+wR4sg2hiD4+96sW5jO1375s+Wr24n3cF3bPajy5haYEehYf9o+94jbK6hJ3oFHNEsog3LTWdiR9gHgUOUYFNV/iJ6jD1MD8+Ek2QFe+xchsb3p/iOg18RayMD+Zs2MP76EVodDmQ7ppeLtk+gqRlCfMjTn1R3dRGfvUIXt77akstjd3wLKsESdzX64FHKNxUK3JFMCK+bZY1Tb29QgcDhDYkiUrDIwrMFenRkGJFtgig3rvNGgdZdhOc20Jt/Qkje50JFT21oUe4w2jxLmc/YFwxx6zxITmzD3zWZ7J6NPQUNdWRHNwbRmKuvmInKX1rUJs0Wj+6keTOy8bXSg4ZYlPL8b6+xXODtQ5VaKbdWDUM/iZPf4lS+tbOE2kqm0wI1Vdw8uhOiyu+geXcS2cb3k9MxY5w2WkEJIQW0XaKHpKc0sftHQ+Fxu4X/veyB81+USLd1OE4cdOfb+i/ARiGSlw01Ju3zmtQkGY8lH//w1HJj2hLawHVCM8m0/ACXHH+XWjMVKftEAAYl7HDQxpQG196mZzKfIDv0Lfti2kSXw17zI7el6ffefqQ=
*/