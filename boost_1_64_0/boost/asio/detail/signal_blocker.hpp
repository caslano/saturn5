//
// detail/signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/null_signal_blocker.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_signal_blocker.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef null_signal_blocker signal_blocker;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_signal_blocker signal_blocker;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

/* signal_blocker.hpp
ItWIzrleqzLsQafSmncIcQ049a27lQgENP/J4dJj87dKCGaJ0NHZwY92me5hh+ZP+bGsTab9ccyl3c6dY5IKG+RIfaRbepoxSdcfcBnZeljHQx/Hrn7IbwAM4vwCRvaAZdI3rUgqxxa4vSIWyoZLkdn7dVXVXBAH6zx2C2kp0dn4rg4MedZ+Xyz3w+dRneZMkzUAwITDYhtwAeA8Eg4WRdEHUkPPzCLr4b3epW5WgGFLqCcsDkWwsm2bwthbqHGY5jy3tAq8aPSEGp0Pud+h+LDnW0owu+kL+lWNHPVrahYFj7yXBFaB6Lv5JPKnzBbhA4psMg+TMQNbv0Y6FizzIR2kg2E/bQNmTcWNYcH3lJJwrueY0GDv6TEL4xrxusoe0AM9QftwmkJoJCkegu/72tbkBgXhI4/WSrSOgfbrU79C9iY/2NlLijjC4dYkvC7PGEt0CU7pjdkEob+4P5VnC3EGHHkRd6TMae2v7XUxpCMwB0l1snj4saw+lwfZr0br5tQdqZB3APt4pKO2HbiXLfoe9/k3cr8ZexTvdOfPmXZaBl4C5wY+Gr/rGQ==
*/