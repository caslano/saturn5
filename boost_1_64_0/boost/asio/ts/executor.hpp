//
// ts/executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_EXECUTOR_HPP
#define BOOST_ASIO_TS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/async_result.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/defer.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/packaged_task.hpp>
#include <boost/asio/use_future.hpp>

#endif // BOOST_ASIO_TS_EXECUTOR_HPP

/* executor.hpp
GKhMgxCdUZtQU+EsWkx6w8YKqzOCUUal0qqdV7nY8mX7PGYs08NcX9OT71t01kbuL/hATCE5hsxYI1uCwoXbWP89I0LrQeSlONktqHudc8QHt+z4s7HsrsUifCQrZFJO+99530pi+mlA81SVy5db8FdVAYIFpRLYCzFooingTzPGM7JvU0R0Uu8mq8Zm/Qhkn+PrR9DXpPLYFctvCwP2GLQT2X9cPYNcM9QGoXXmrjEnjAvKRVXxZFwSjRSHUvQjZgELAZhPfAOzILtuIzBZffuv/PgRwmBr+tn7QhqwNvD08J6ns/Zrpi7vG6vhbH4QTZGwSm4dw1lg0b4xa9fa4cu+iGZ99h8/Um0tClb7u0MF6ozWvMuHi7m7BmnEXzyz19zobdopcLSvuBQf3AOQMtxMu9YymTK0hBxBH9rfbwTHqzQR0dY830tzFhUtP/JzxSQx/AdaWBmr3JlFmHX7J8jDQnloq7UMXviLRMPu1IOvT2J7rqZJCeWU/KCa75NBals7uNRvpH07i9h3H4szt2UB+CLNiues3IoVsHuaMkOYiWoQUMHZREB1Dg==
*/