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
8ItBWqk9gskizVA/ozYfERAqEAH2qAAwL2wUdoBxJhguS5wEJfwfTIBzZMvKmkWC0wX9qlqngG7WQz/v9JU4JfhweOgLsO2v1b3yqEV+3CvmO/HnCSDLjcDUiPJGOMaJXobuEKxMHannyasV+O5piBVkBtdLCvqMSyaInF2IlMJLfj2c70OoRhtV/ZClbQQ9wHwYyd1fn1zJVw3Wl0lA4hbCCnGePvDCt2+Wa29DZcTTY/YrQ9MK0mZxMTfH024litnSA1G4o1ifqUi1LC4iyB03mEaoOvupKNQadieGC2sJJn2cf8/yvqz1ho4YdV3zplzyAtp/To4zw9ut24cZNCNOmpBI6SYEt2OIsmRoaslb/WeB4OOpxo5KjeFVW0UEnGyJmSlg2VjtCbMk1EYhYtZqeo7EUc1e8qeTcPK6XEL+ds6ZwaG3LUwsa7lK4yZU0U9FE7uX2oA5uSZCUF+xu6B1RolUJOraq6gUAuZPrq8xk5qg5SW1uvLrecQIPNRcM+Obw/UaLaHvBpdzFTG9D/jklfd2sndiDxb/K0tTj6N/FlxTq+HBAbH/fA==
*/