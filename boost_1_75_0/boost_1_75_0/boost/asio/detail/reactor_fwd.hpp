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
96A1evMQer4Od9/fo2kg5rHFvp6U48Km7XCVSp8ohI5K03XCpk+xA9NThM3v68PQrySRLEX4MCD4V2jAUzzZ/GU5Ne6GR/3oo4RO5Dc8NR7rxWQM9iJEVRCSQaoecXd1UWStZwplT7lH2Owkk3kOoe5WoXKrZkjFrz9lcPekDLEkQ7TQdLHp1WZQL6/SB3p5OW9xqlpRpOdoN+9XmUkvbEL3Svg1Xtis6MJ7Vmpi1+LgHo7zjMXzugQcHzFVhomyLg5JCAhtOEaRkYExwmQm0o2YKA6REmNPKIBXil1GKSZCGZqb55mIWFkXLxfG5cGyNVvacxFAbUQAwEaUPq/j1g05Mvh+ZIQi5GV7TvOm01wvy4J5vv7m0Hl7BudtsT44x8umwvxePym0DLqJetI1ZAGlKIuV/IOFR0w9+K2lpwOULrkcmRzytJRYqVD5vk5F/+90hP6fEPoXZTg+YKM7kLAYLe12xQVy1K0MCE6mmffTciL5vgRha61y9Ra31aRcp1hs7L63ezgzJjiPktLC5DZkQvWKPtJSnZpYo4/x/E6bVHE4mkXwDIbmMW1s7EUwdzxPo2WWj0pg1Ygxdr2nDh7YdZ7XutQpSIshAcULPyz20RyYCkvvebVTLUbruYNmH6znFmwQlQH0rB+M+NtzM6DNGytnjlNewOnGTnL5ABrt+QsUz8V/LHEd7EeoYLS0JzvixREatTSyXF7c
*/