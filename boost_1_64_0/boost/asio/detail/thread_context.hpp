//
// detail/thread_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <climits>
#include <cstddef>
#include <boost/asio/detail/call_stack.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_info_base;

// Base class for things that manage threads (scheduler, win_iocp_io_context).
class thread_context
{
public:
  // Per-thread call stack to track the state of each thread in the context.
  typedef call_stack<thread_context, thread_info_base> thread_call_stack;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

/* thread_context.hpp
Mqef8/WkZvYWcR728trCwd89NgfWbXHL3kZ3Zjj+ez/uMqK7yVtShnBjBRMxCmds60GAgUQY0u7EBsgGgHm2rvHK8c9uFopqLIdvFj4XeUsism6E6ruEaxWY4dqzX59FDM5tCmTgWQiuY6ufMv78lfsohOpWIR3vAdgrXqeBEiEqGGfjPW+cMKxMQfVwzAr7ExH6lYKWyyz4p4WHDW0/1kFmQcUZheNFdCburuVktdUR11lvMNMOsR/1AzBDsc7ovb8zfszwSIZyu9/WXXAF73CtJjEQBwpB1OdKnCKQHYz/KmtajHI7WzPRUCkNy9kv1ZZTuJs/2Dmuj0eVy3L3R5Uv6eQib1JQ7+wrOJfQjHc4iZK4r2hqzMUMH1dbWhhylw3C9whbqSIXm6rA81wBo+gScUpWWBHj2QQuLpkWK01OvbmF+OLaVbPk73XB0aUppc3Yd9ByyeKF1Jkmh0sde4Puybz++bbythyBi8b+FjrrYbs3RABZjS1rJbELgWJyKZrq9xXprahyQnPr7zVPKyGgtSchiSwSUjaxqk8+o7i8dYE8zdsX4IxeDg==
*/