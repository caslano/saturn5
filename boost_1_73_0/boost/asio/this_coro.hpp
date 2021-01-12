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
v2JGb9s5LAf9cujiR85z/27QjmhvltxGVBr3Wr5ndCIt6jceENLUzBqO16qMwA8f5PUgV5PkYsJUkjcB4g7Mg3h9uEh9zzJu13IAf1mC2K2UXanT3GKwx1yEomNd8pYX6KuNUuJuNaN+AmAYB028MayJZ5HbaGvBDDBsaAjv6GKMMSEH8MttVAe8OUqjOTOd/uQyYAt9lEMfr1K+NU2usDp+SxXUX9I4GbobE8VXY2q9yXGk
*/