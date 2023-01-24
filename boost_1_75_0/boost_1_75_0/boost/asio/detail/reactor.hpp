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
I3UiNbIOOrH3lNbfRbnsvZPYCbWzSSGlHjmldfWaXPaCVqoAcJOGiRIy/QBa6jCt2kk9b6Gen+mn53+UeM/fHqL2HCdCPMzq3hx0fGHoLBhnOQnzQO50FXbJZ9m+3xEVRC4rudAkmqrikwvNYlRyYRxQd8PvA0tnAlTmqSPqzpDphDqylVKTMjJpp8nssvqhN8OUkXFwYWPXdPgV8liMrLaxUzB/C6BHUINDcfht8H6vt+HJn4CPwcLP41psKYCVMQ8aqvWmi9i/lzBvsh/XjSImUit4J2FJcliTfoOwHILWjOf8qJcuyGWuh2CQHV1sw0O41csfq9Mps4X4i8Vy3SJ1Z4hHDIagr55WU7zK2PV6+LuQh8J+qwmQK/kLhM3JpLnroIQB84TNPTq8PIwDwQxC5VH6jFmsUFlNP+KFyp/Ro3Hi0gxxmsSiuVUPkzSnGjFWaRkFn4wWNudHIslK4EixR9g8uRG8XIbZeVSoSsZyHYOFzUlULl62jsPm7q0aBy3x3GRQy8Zj2SFUNlrYbOhVthEZ84uwbGac/VJZf2uxyyxb4yV9hGL0DDWEtutohNquanQ5MT1W4OsAhiVCPh7SxoWeF8kImMm/+miPLkisESp/o6OQGRscUzME5xbk+YODbbZHIHYxuwXtW0LlSijg+RkiBUSgdLxVdTOqaGu44Rqmz4XuDMUbH3w8VX18KWLoiJw+Dm/Gw8UN
*/