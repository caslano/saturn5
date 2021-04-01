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
Za81spJF1YPYbyrQMzhwfb0CjEczBbp8zuUfrjW6rcwa6qDE7PESazSc/IsNOjct353eg2oBiZqpZfYV9NTgfOwJLtUEAoyRMcZOA0PTV2isIQEXYkTJPVIJ/DMc7p47ZdJavaE01175HtjeVEy1rdU+dAJoH2Dp0/reXfAMKgG8Eq+EVG579VO7BFCnw/Ara/gDnYNRVK5T3tbgHWeVDiSgMv5BehzH3lkdJB0PrmK9gugCE7qIJ+Q5hxFBAmA6LJsSK7GbN5m1azj8HaMsPBNJEgawMJJA0dxq9b79U8aTjrVkLjrLo2Sqa6b6h4OEWOqeWxrXolu/gEOIWuj4f4+3oQRXrUE1wplFaUXo9Cz5TJCovbthL8kuGRXuc7nomCZhLmWlwfca5rbEgCt/ChnuowFunycGjePtyTffEfTiqi1JLWI02oTtd7gQCfhQVND0Rln+0qnwarDCA6bZ5fSxKtHg+JHCeOfWEJ/k8aAktPy7VbOVyYvaiR2feWX4LHDr13mU8IYczEAWcsrjIuFkvC4hMF3HafZpgyjt/3PS4SImBQV9nreh7g==
*/