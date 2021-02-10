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
pK38WEotxZl0mth1vcPEnXmmw265jQHTYfBknl2hOgeHUaiw/6x2Ka22W327BLXk3AlC1H/XyyPjKyb+E5EppO9SwcUUsLqBpD0p6esXYjo95ubxT6Nnf714OXo2uvrbuEu7BeJALgX0XBoX0zwunz+9Gv34OvbT3ly8vRpdvMRuqEoduqsDIaAO43HzrKYdlzPTm5ZKSyEu0jFq5ios09nRBd6sobAo+qmkHJqQuJiBs2r/rJdCrPsJOYH0tqYEhJu+pmBB4ZeAOxy9fvLjz8ZcCm8/A6WxVQhNlItVNvnMPrbHX37S4bfg9uPjP3KgRu4qtPxMyRkh2z9F5+G3ry5GL0evnz3/+XdwGPxBTaJpnB2JBuyy6ITJqFyp+HIUv+0d+PjsSPl18kf5JTU+09M4skoYnf5ZSZ0efhvt4vHV85+vvkxux0cn93v2k5C5/2eRuX/4bTTLx4hiAP776KgUmTK8fv6uNcovP/w7bP/9kzoj72w/th8YSfbC0tF9pktgJjSTvxMYhwN/Ap/Ln578BUL56uQoAtZ+7YrdeXZdOHWnAriJj8khZ6UoUBpX9PvVPW8s8aTI2JoMSCPY/j87Ql0vnlxGKbd4ci1EkiO/2RbrXOy5faY5byPTbPNaysSLGvk7fHmGROxy
*/