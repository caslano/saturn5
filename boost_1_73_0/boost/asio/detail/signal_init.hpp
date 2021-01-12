//
// detail/signal_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <csignal>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <int Signal = SIGPIPE>
class signal_init
{
public:
  // Constructor.
  signal_init()
  {
    std::signal(Signal, SIG_IGN);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

/* signal_init.hpp
RMuNi4bif9wrlhQjW4rBGxlamZymGzuSk5eWlnftPaEPWmxR8J/EwB0G+F/jwO+fA9nAwTIn7OQPBKZOrPV9MfYtQ87d1Bftbmo5jcCszjiq7102ZHYrnyh6dmosdWyA3sKQMkvvkK0WSoZ2zXZP29Ur5MQiTO4L8SmnxbV2Qao5p0g9oc+8l2MwoT/nxJHQjL6mwZsFNMl92+/iQUcn4hZTErGkqYkCL00UuBBYb2nZ5+wH
*/