//
// ssl/detail/handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

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

class handshake_op
{
public:
  handshake_op(stream_base::handshake_type type)
    : type_(type)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.handshake(type_, ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

private:
  stream_base::handshake_type type_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

/* handshake_op.hpp
Rw0zDDqDwWg0csZiY4nxaeMK40qjybjKyBtXG0uNfzc+YywzPmt8zvi8cY1xrfEF44vGdcZ/GP9pzDPMNeQbomEQ95ZMy30oC+Y2y0K4j2Sh3NuyMO5jWTj3jiyC2yabzL0ri+S2y6Zwn8incp/Kp3E75NO5nfJo7jN5DPe5PI7bJU/gdsuTuD3ymdxe+SyuXP44VyGfw30gm8tVytO4fXIdt18+j/tClsUdkGVzB2XzuSpZDndItoA77JHLHfF4gjvqwXJfeizijnks5b6SLeeOy57kvpYVcSdkBu6kzMhtkXHcKVkx956shPtG9jT3vmwFd1q2kvtWZuKqZau4GhnPnZGt5s7KSrlz8r9DOcqA9me5N2XPcedlz0N51nCfyNZyO2UvcG/JXjV+KNtg3CzbaPxI9prxbdnrxo9lm4zvyN4wbpO9aXxX9pZxu2yz8RP528ZP5e8ad8jfM+6Uf2D8TP6h8XP5x8Zd8u3G3fJPjXvkO4175Z8by+W7jRXyvcYPZBXGSnmlcZ98v3G//IDxC1mV8YDskPGg7LCxSnbEeEh21HjY40vjEY/jxqMeJ41fepw2HvOoMX4lO2c8Ljtv/Fp2wXhC9p3xpKzWuEV20XhKdsn4nux74zeyOuP7sn8ZT8t+MH4r+9FYLTMba2QW4xnZT8azMqvxnLweynEZaP/F+KbMZjwv+9XoL9MaNspCDK/J9IbXZQsN
*/