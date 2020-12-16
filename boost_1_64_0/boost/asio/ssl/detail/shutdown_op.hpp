//
// ssl/detail/shutdown_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class shutdown_op
{
public:
  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.shutdown(ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    if (ec == boost::asio::error::eof)
    {
      // The engine only generates an eof when the shutdown notification has
      // been received from the peer. This indicates that the shutdown has
      // completed successfully, and thus need not be passed on to the handler.
      handler(boost::system::error_code());
    }
    else
    {
      handler(ec);
    }
  }
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP

/* shutdown_op.hpp
9A6LXag6mdjLWid/QfncTnUi1tFx+/B9A/J8L6t9/B351TO/wAEJ5iH1f9ZsG+DvvG2ctbGNkt7WevgH+JodykXTYNnMttHcBds4a2MbJ3rb20arfdnQxqGPGc02Y4byhRJtrRNNXwPpkC9Mo9N2EduXa67oY+okKAJ5pQ2XvNwL5uSfVwjPUoYrsHf9ZLysn6xajx38E7l+crLIfB7hDK0O/9guSIs+Q/jteZ6E08VPUK6UoramFstY18KBFW4dlNz7wpcsbR0lteoRn1+5+DdD4l5DqlIWHKWVG0srcLNTwnxQx8JTbMk3GTLx5nw3VRd7PMa8XxbeFIbhQQ5hn6+qhWifJn3d5GjUX2z9S7F9B6n6rwr4/vwMwqtA6aN0RDiE78/V+lFZI+6t4/48F+X97st0jWnsa+3bvdCG7kxpQ+MNlrr+/97cr8Hb+X6NtKzX/xirDfdGmeqtZVLX/9+b+zN4O9+fkZb1+h9j358b0gLL1LHrf8vXglz/Y631EI16aLbUQ+eu/75+3BRrtYG+yKeV+ZhvJMUMpM7fM9kB+LtgB+/RDozlyu1n1T8mB/UywqZcYgosl9kWwN95W3jPZmw/0M/eFtzpduVCq3bAHtJ2OY/tmf2t9RGbg3qyrQ+YRCeu+ZN9vun6W23Chbw8Ki88lBlsoX+OyRbA13lbQFpiC8byzB1g1T0OfI2m8igbQHnMNtDYBRvwlqfY9I3Q/gH2NnDUWJ4Otv1E61ig9E9yWfWP1/uoMb8utnmTy9rmiXp/G6nywEOu/zqQYG5z8HW+zRNs2nxanFXnweDLNZdHXQMSzG0Ovs63eYJNmzfF2be5x1Sejo3/RXc4t3lsvFX/JP06aMqva2P/3nhrmyfr1xjmYXoxYujvb5jGfvB3oe3fsBn7Lxho1X2obu+25VL9HuUy20BrF2zgDZuxf/9AextoTLMpVwf7f8vtzmN/WoK1PlL0vjnKJt9OjgNTfWN/gtUmUvV+p/JSL9TUWHDCbA/g7bw9nLDeE8I/n1X/Yfr1yFomNR6cMNsCeDtkC/PNZbLeEx4c5GALljJ1bEyYeLvzPWFmorUe0vT+asmzc+OCL5+0wdZ8huv9z5tPyeTyQsP7J68NpJvHX/LSd4t8A0u/f4hfEBCPYQj/K0orGV9miFfPRx2woXSO3+pbafk+Fvn7n5HoPxl5BrwPy0yy6j5S72tZSnfLOxbfe4VMcx1AJngdIN65DiS+83WQ2Yk6UPeaQ6x1MFofA4x1YH6XIPqPCrwGt6N/bjv653ZB/1Gd0F/Zf7JV/2x9vPHrb3j+8rb9mADdPe3o7mlHd08XdB/TCd3VtWaoVfcJSK/Rr7v5WYO2Py7wnrsd/Rvb0b+xC/qP64T+vv7fRv3HUP900CSkd9RJ/8LV5VXg4Z4t4FntMfgCoFy6pY4WqLhkpePaEHSMp47IC+VnXtSTepv0aUmx6jMFfK7RTvqs9WjU52vSbgxTH8g56YM4sz7lHdAHeenftzvpo+6LD5xjtc+p4HOb9MHzEO0yx2yX4Atul4h3tkuJ77xd5nTCLjkm4QMZaztOy8H5QL2D2yP50y11s0Diutceqa/5Xm6YVY/p4Gux6BHcDlsc9UBcN9thjo0d5qZZ7fDCHF0xsx75bq8dzjDbIfiC2yHine1Q4jtvhzO6YIfR6db2+wzSm2jRWwzRyQ7Jn26pmwUS1712OMPGDo/a6DELfB6rHjAGZzv0OOuBuO61Q+phul4fzbDa4VzwNfv1MD8fclycbbJH8Ldjj83t2GNzF+xxdhfs8chwq/5RSK9V6W+aghLdIwOfVYLrjvh2nlU6prvp2TKyE7r72n5XptWGL9Kv7WM=
*/