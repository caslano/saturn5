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
nE8y411UvPQds9ZYPbe+8CiRZp8Z6+/uDwt+21DVQ1OIfFwTvoDQQ8/6TmFCYhOGqKdQWiCi5u4IRDI6T1RqVJFq8kpYnhCE1uAlQqjUfhx9ptT4qB0cac5FLJTFP1iUyZyCb4h+ohhQ6VMAOhLQNJsf5cH0oWaVjfgM3MOyiNmaCpbmumkKhRdolhNcHKqXA9ILEIbmZuNIUCRYoxHiBOqfKgxosYtKTzhloWwlq3TFrQyL90pdV9TDwhoSvY3AL2WtgYqyoRk6pPNXpjAJCRMZFDcoS8IOe5KnpNlagnOqBj8L++1q+abgpozTrwIoIwHugMXheXaD86OnMVMc350boWFi/TELplL9w2JwBnEoaod36hvfse7AaFLiJlk5SBYPcChmcUNhnSqFDGArOY4IPGIpOMh2kOSm/rxGxpb+31Wy6Lv8nlI+V9sV0jIRAZiqZOGq6A8r9EqUhDK468yHnoiLlFlmTSTZwAEPhEBHD8rcP3/z5N0P8s/R5yACkAXQJEA3g0UmM1Bp7dR45yEVcCXEEBWWADDPPk1lWJrSqazI18tGlLBaBSuUMO6+E49IfaZCx8dk4cxHhv0g5/f2I3zaCiy9h7AKC0uoJUPZVJOh9pkx81A0IWlq5gQRlA/hZLlKpD9MLTMm
*/