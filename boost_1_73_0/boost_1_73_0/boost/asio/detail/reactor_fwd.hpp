//
// detail/reactor_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_FWD_HPP
#define BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class null_reactor reactor;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class select_reactor reactor;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor reactor;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor reactor;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor reactor;
#else
typedef class select_reactor reactor;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

/* reactor_fwd.hpp
CbitW/pJNorukKZD4V9DIzygRyjUJTAof+3KymCoQtmtLM+OuAy4NFIB5yffLR0IS60S5l/44OuIV9iKKENxIRUkJ4ka8Ra0+iBP1FbRQYaKwRjcZ1n4CpUH+WKqdEnCmajvPwMtwUPD2eVH5PI3onDyl64W0fwc/wx5BE1q5CGTECNgDZMfjMqSQxPSo1pd0ymwMHBQtvm29CgBTdXRYPZq/guZY79ZNFUElyAcjKrpekhKvkay7qPibs34ALMMilWY8OnvfvctZtwnCTgoptJQUVSDJr8cnekaKFNE0VmeIJ4H8wRAwdPf/vo3yAnulQnM0g3IubLTNLnVmpyEEvIa3ppisoiBHt7FT8KiqJH4rryu9UUhAAy4lZAVL6A4YwlBz1XdqBdv+EsXYyiDI2sy3vSM8GHAy0Z2CR7w31G1wj9UlseaBhLXi1qRPHEcFbFO+qAq5jLIffrQ/8UxJuGWlajESoFY3ZBNTbXZELUgLlHgpWi4B7YwN+9KVTlqG6TBQCVKvCIyo+U/RGvfV+AahHC/z/+NFVmQgQUe+zJ4UPlfxGr+VVPtTP0Lc8MTYDxDM2nJTfAshJ5RCwLJYgyZZ8UOUXLv+hFeOYviBN+ns3IPwk+tNQTXwzQ0A/9ZWIx9pzh2qutsMGoT
*/