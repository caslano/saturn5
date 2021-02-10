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
wfZxElrvT/dH5jkNgBmTvIP9l+evVBg2NEak4SoaQNIELehKG+lJcu+W1l28s+50fvLTON7L6YRS1pBTjrsWmtQZTepFYxW9ZvBsll2+i84XH8GTb/PRcp5Cb6hUEyxxlX7+mp6fEfLkbvg+b774APkIEa7Sy/MWcXH3Dyf44j+I49E0Y64P89unE+QvDfKkON5coK8mNgHpv0ibE3WFlBkempE0UUe7d5yvVPwBUEsDBAoAAAAIAC1nSlKO+Drt7gIAADQGAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcmVzb2x2ZS5kVVQFAAG2SCRgdVRLT9tAEL7vr5hboJCltEDUqKpEuRSpqhCl6gFx2NhjsmK96+6uE/LvOzMbOwHExUrG8/oe45/BP84hYgpuheoy0p+v90cPy5DyvAsxz01dx/tjfj5orb+pH+i6OdyWAshLBM494lzIgQI2AWdjSuqyrrGew0x/OtWf1ZXJ+BjiZg5V8B6rbINX0+lU3cSwsjWCgapPObRDPTQhUjB1WNnGVjIIjK9BhnXGRg1/kvWPMvUYNqFXlfHQmqeyWdVHR9j+9ZhyOkiH0CfcNcR6HCRNI67QZy5UgR5xbSnbh9ga5zYDRbsaArtA7lhruAo+
*/