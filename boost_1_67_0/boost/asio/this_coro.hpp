//
// this_coro.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THIS_CORO_HPP
#define BOOST_ASIO_THIS_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace this_coro {

/// Awaitable type that returns the executor of the current coroutine.
struct executor_t
{
  BOOST_ASIO_CONSTEXPR executor_t()
  {
  }
};

/// Awaitable object that returns the executor of the current coroutine.
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr executor_t executor;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) executor_t executor;
#endif

} // namespace this_coro
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_THIS_CORO_HPP

/* this_coro.hpp
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
*/