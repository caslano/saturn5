//
// detail/win_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_static_mutex
{
  typedef boost::asio::detail::scoped_lock<win_static_mutex> scoped_lock;

  // Initialise the mutex.
  BOOST_ASIO_DECL void init();

  // Initialisation must be performed in a separate function to the "public"
  // init() function since the compiler does not support the use of structured
  // exceptions and C++ exceptions in the same function.
  BOOST_ASIO_DECL int do_init();

  // Lock the mutex.
  void lock()
  {
    ::EnterCriticalSection(&crit_section_);
  }

  // Unlock the mutex.
  void unlock()
  {
    ::LeaveCriticalSection(&crit_section_);
  }

  bool initialised_;
  ::CRITICAL_SECTION crit_section_;
};

#if defined(UNDER_CE)
# define BOOST_ASIO_WIN_STATIC_MUTEX_INIT { false, { 0, 0, 0, 0, 0 } }
#else // defined(UNDER_CE)
# define BOOST_ASIO_WIN_STATIC_MUTEX_INIT { false, { 0, 0, 0, 0, 0, 0 } }
#endif // defined(UNDER_CE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_static_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP

/* win_static_mutex.hpp
dnw7OD4/aGmOfhNeXfYgwoux3aKtes3rRzC/vf9cOOnq50T08d4m5P+gj9/CO8fwT4Gzvpb6QzXn19S+fKmuZcwG1/FHjrueKD7r9KzYx1JDpK2I2s4dKX2vUIbalF0j8bxwFv/O0D2q7mkic9z6GvNNg+6dQpeq8mSV04O42RtdUVSlZwtMepZ1DkDmWFTmwErz7fuHhOYZ0qz97VLzve1jkpZsy1dl9iM/IWk/saWtCGWo7doSSRsa7sjIX04YQH+3h+KZoY3nCe7RwN/sp4FxnA+JfdN+zGKzn2b20uhfxkH61+yl0Xdck76Ta/lmz1P6x6k71T/fakIXQhHhM1nI6mLnmMqpHtUH3+8vurPcrg/aLIGeLwDO5F8dZy0jza5DtE2Mn0lfzbwZbvagJ0o5nU2ekGUHprrgIknvI/N+1wXwRftTLorZxl3oOM/zAZ33aUq3B7ol2dB1GXtWn8bpI9HSDfBNHyrfqhtoo+lr+15wXiedxLpOORF8ibkSlfbXFlWVjyzk8AXPnYUri8rZhNa+zXPZIpBf83SXfltEfJvE3xEeHkqSPBPVXs4+HtuF5rpQtmWLY8rJNLaGDy2V8XHIfprK/gNCmxRuF/qozgeLvqv9+/MV9j36X0ieFDNW3YQem2Od5xMlvljbGA6dFPqBzOB2moeTgULT1lbHqsqK9Wf3qdtL+gfIsSx0IxLby1HWd6Ssm+ire8SmUvmy2Qr2AH8otMfM2c1/0H9VhOyuzdsCWfMuz9h0mHlH6cZuUPaw/yL1IHfdGuNDlzrjc1zxSld8iy3u8Lvd2avvd8fO/C0z9pZm3oq+N3PWPFtA27S9JenB9paSnpC9peowax4lbm851uLd5xv8d8F7npd3fa5t5P9MrstGvmn+SW/GR/M58H8mN3H+deyxDffy/+fRzO1ldtsnHfuA50pog22fJL3ltk/1XePzU9zgw8cexrHO8OEZR993Neib9rmcGC8+75jBvIxWXX9Qv2G/Q/nZQLh7DDwaXuQd3ij6tNhzkfjMLuQ5KZZkdL3mudg8n/xJ4tcpfx45VfoBEp9F/JTSu59n5F1Y0hba9SLmfo1lxRi59DrzfEWcUxIS7y5lXS+cbjTn389IWdf76thM8PeSvjYUs5N/nj4fRB8tRY9Fki+OJI2LJPM8ZOzkH+1KsOw3lX4m9KUx+o45djtPUp32myu66bNTk8/Q+qwkvsFNn7vsDLVflfZ6ubZRxnmqjnO0m9eX8Q7mXq30U23jwzkejX0XGvT+npwhz0HEzZhr/gw5d3AIvnOpZ+7wWF91Nc8nQ+J4PqFs2kzZKp/XaLtzvPb50u66ZtodrYg223Ypg5Jj41ZNu98izJezCp0iySmhc2q/9SzVkO7T7z253th+Wj5x3qyRhQsnzlzAO86G9VZ7t4v/gap1tvZqngwjT4/G4Vvaah/l0T7Kc7Xvge7e9tVBe9KvfVgXbigJbJ/mybC905QW12g6XWvSzXxoYftVp+l7AXW4ZCYrw8vTJ2LPGNdbPM2bP/HqGYWzp7rFxnjwTth/tzXPjvjU/UnqzomjbkZf+u6+MZ6+JX/Lx57ytO+c/XSwh7etD0Kb33xbzfSS92Rve7WMDLlfvH90LD1GvmpD+UrbmoqLp4UJ8PQxG08ZKg/UwzVTj2Nc9mR6eX2IMqJx8Lqhak0Qn5o/w6ZjotWV9ucRF48FLeRRZV71DHW4xnJzTy9/D5N/V/P86awOlD3KaHJek97yeX3fmObn9QRrXvfyv4ftVx4D7l46Nl6+9rvanZcWf7spz7Tb/s2A3T5tfAQeG0wbg1RO4t8MsPolt7e3zseuQN8G17nB8pWRP9pHj5+DrqE=
*/