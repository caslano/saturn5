//
// detail/timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/timer_scheduler_fwd.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_timer_scheduler.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#elif defined(BOOST_ASIO_HAS_EPOLL)
# include <boost/asio/detail/epoll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_KQUEUE)
# include <boost/asio/detail/kqueue_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
# include <boost/asio/detail/dev_poll_reactor.hpp>
#else
# include <boost/asio/detail/select_reactor.hpp>
#endif

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

/* timer_scheduler.hpp
Ryv9wGUT5J2w8ygbJiaAgnifMQJc6SQeKFkwlq9xv11ury5+UsqEtr4nx+juYK1MAs0FbLGeTiV3aW+Sp+N8EgFHs+oGCHa2kgQgCDf9xpUdQtfQlpFx9BYby/sH8QQNgqQEkeJMKUnxmkbLlLo4OzuTdqvIZ42v49lIqa9LCCBjINN2a//ATQ76rHeWY0SRjYm5aRiIRMeYLoM9YCQoRQ23urdJHS8HaQWmUeJgBeTlWdbrYP1klZhYIgIpCWmcesr3zmpheYYYtj40HNDYizHdRs7gvAE63z5c/nMOXa1N8E54RGsdTCkcW4iTUr8dPP59+/7bm8vP7z6+/6UfPZs3ssWR/1X16mX1fKzUy0OkX6f9fUyfvZuil8Zv4kyQoQWnbtObzI3WlDcALT2o2hgIEstvq9QfY+yDI6f5ly9v5zfzfeA/f7gf3V6fX325unz38eL8bt51FlLJ0nmrkx7t3V6NoTAaypkM76yQ54B1WQkZQj2Mxj0prLDtMH2oU5mj9xJMigyET/zIdZ92zMlDbETbdOvM49QaaC9uY+JVzGFlJaiB+ClsBRjrocp9PSLKlCmEvbIC/5t9XZBp5Vp1ArJO6fxRI8ggZfkjcFJ4Y452zE4VXGwrHI8UXmcd3mg4lpQCSbVMKztS
*/