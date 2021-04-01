//
// ssl/detail/write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename ConstBufferSequence>
class write_op
{
public:
  write_op(const ConstBufferSequence& buffers)
    : buffers_(buffers)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::const_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence>::first(buffers_);

    return eng.write(buffer, ec, bytes_transferred);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

private:
  ConstBufferSequence buffers_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_WRITE_OP_HPP

/* write_op.hpp
hgcYcgfCJQfKjjD34ZLHO0ldBsSGII0h/58tY7QZezb8ER4a+7tSleXJpRiSzg3bYkK3q3JQI5Fiu9erjOey1rbgZ376erRs7RLqnLjUyaF1Xeq76I6jmNvz7FemC1ryedSjcB297SYV3ijPEo45YNDrLpOapb+Hn8NptNZTkimcrk/GTh3297RCxT/0s7X8jbUOkzw64ohi/X1/5Vqy164XqHpT6ZuXaG4eZBPBmIJCKqAM4Ji7xMe12wgiHjzZEotjIu74lxcKkcOkPYpGbhp8LbfgG2QUkikceFH3k3A6U+m7JutCLw5xeMURVLFtevf+rax35IEz7I7H8mRNwOlVg9AdTyRdaHhnXu7mkutpn5Hot0Wak6UybX5zDVMheb0W4doGOzUPjAzAGi09F3vVyERvnFwhrdoEPtSYLL4TPufScShdYMVugnwGGRaZhcwf3zMAIp3q5ntng/BeohdLrpXoqafNk2iAGqA2SQGsNYKEOa84bXGVQtpTCg8lyyTQJIzmVjJvof65AJr2pR68PM9v5ijzHUWP1QQEAqj0du8rVyJRT4817Q==
*/