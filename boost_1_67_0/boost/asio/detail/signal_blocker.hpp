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
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
*/