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
bZyiHeKLCfGC9LGaM/soNPxgnBPvhRm3URSrDMwWrIU4RB/s9WdlUwYZcBHmbb72LiSMWcE5m/XLO/cg3ZQwfi0jAiFoa/VgUYDBYUwg6+zoyzNNpnmmJhY9IvtMaIjG0YrO0eH+mQtduXeaXNuFq3QTsKuv8ceNOl9W7qrozcccRHwWEDNMt9D0ws+Ndu34Pqg1fUBnmm0ifOz3p/RIQR5gotriko9I507lp7zbTbnLgb6OhHPFZ52oUeFAM7rCia63qxp3LMTBIkVw6OZiIuJ8hqq2TFCAt+AZzb8bOh5KgaqHMXDJLk420AXhtaCw25UN18CUct9pvBdsiiBota6xan8R5HQvj0XLIwC6eMKHzCpnFNGxkYcB8o+V66KIfJkD32pBy14GsD+KNOkzgaZ6rkW5cAbzP8fR5w+Z857cuUV74rR5vuW2CwiRv+AoEifWYZXiBq1NrBijq+ZCVgQyJimiJKXiuUqJjR9a47ouFh0LqFgxoClOx0vxYoieNBr2O4T+OO15421EI5GCmTPiX4/Pv+WLOli6bH6/MAjpFb5o59u9sHUgBw==
*/