//
// detail/reactor.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/reactor_fwd.hpp>

#if defined(BOOST_ASIO_HAS_EPOLL)
# include <boost/asio/detail/epoll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_KQUEUE)
# include <boost/asio/detail/kqueue_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
# include <boost/asio/detail/dev_poll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/null_reactor.hpp>
#else
# include <boost/asio/detail/select_reactor.hpp>
#endif

#endif // BOOST_ASIO_DETAIL_REACTOR_HPP

/* reactor.hpp
bL52bTEUzlJpcrrxAhK9GdgKLFKxH0Zs2C89OarOOjBcBWxMiqZ5qqTpCldkddfXVdfon0CpoAJ6LAZ0dKjIjEq5If+YtL20IPYiOw1SEhLg4KjiPoe4WlJ+p7WR7Rm62Ejnj0MNqdHVs006FPP2xpsipJckifpFvtfEwpX+bQYRj8Z8jUZuOFinhm5nN93C+Rf24XsvAg7i/L/Vf4l0A/JBMpzIU7xVrd+eLIcUKB/baA8M
*/