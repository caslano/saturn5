//
// ssl/detail/buffered_handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP

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

template <typename ConstBufferSequence>
class buffered_handshake_op
{
public:
  buffered_handshake_op(stream_base::handshake_type type,
      const ConstBufferSequence& buffers)
    : type_(type),
      buffers_(buffers),
      total_buffer_size_(boost::asio::buffer_size(buffers_))
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    return this->process(eng, ec, bytes_transferred,
        boost::asio::buffer_sequence_begin(buffers_),
        boost::asio::buffer_sequence_end(buffers_));
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

private:
  template <typename Iterator>
  engine::want process(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred,
      Iterator begin, Iterator end) const
  {
    Iterator iter = begin;
    std::size_t accumulated_size = 0;

    for (;;)
    {
      engine::want want = eng.handshake(type_, ec);
      if (want != engine::want_input_and_retry
          || bytes_transferred == total_buffer_size_)
        return want;

      // Find the next buffer piece to be fed to the engine.
      while (iter != end)
      {
        const_buffer buffer(*iter);

        // Skip over any buffers which have already been consumed by the engine.
        if (bytes_transferred >= accumulated_size + buffer.size())
        {
          accumulated_size += buffer.size();
          ++iter;
          continue;
        }

        // The current buffer may have been partially consumed by the engine on
        // a previous iteration. If so, adjust the buffer to point to the
        // unused portion.
        if (bytes_transferred > accumulated_size)
          buffer = buffer + (bytes_transferred - accumulated_size);

        // Pass the buffer to the engine, and update the bytes transferred to
        // reflect the total number of bytes consumed so far.
        bytes_transferred += buffer.size();
        buffer = eng.put_input(buffer);
        bytes_transferred -= buffer.size();
        break;
      }
    }
  }

  stream_base::handshake_type type_;
  ConstBufferSequence buffers_;
  std::size_t total_buffer_size_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP

/* buffered_handshake_op.hpp
4ANgD/BTsA/YiWf0BQeCJ4LjwXxwDjgAXAoOBO10nwY+DJ4BPgmeCf4cLAR3gUPA/eBQ8I/gcPBDcAx4CBwHkhZrPDgcnASOBSeDU0Bc7QxwKlgGnq/1eCtO1qGBOVpfWus7gX39Q+vvQbC7jjM9dXwZBH4Enq/jTjH4CXgp+G9wIXgIXAt+pvXiv+Bd6t+k/sfBkI57STruJYMfg6kqt6bgRDANNO9JC8PpXujznkRe5b37QrCnTQ/2BWfpe8VscBR4CThd718IztNxe74+Z61Z4+NdUOuPPc6v0PpTBV1XcKnGuww8H7xK43savBb8Kfgt8BnwFvBn4B3gc+CT4HLw58r3B/Bq8B3wGvA/4Eow2z6TCOaCq8HjwTVgAXgDWAh+CxwN3ghO1ftl4M1gLXgLuB78HrgB/D54P7gefAa8HXwdvAN8C7wLfB/cCKba7/tgNngP2A+8FywA7wOHgQ+AU8Etdv7BB8HZ4MPgInAr+G3wEfAW8IfgPeBjILTWNhBa6wnwOXA7uBN8EnwRfArU9zJdV6Iv9HkvOyY53L9lgp3AbLAPmAOKvTNwBNgenAR2BEvBLuBCsBu4GOyp86d54FqwO7hO7++hg8buWIO2ybBLlrBJ9iXbJDtwUcrXwi7ZpkUph22brG5mylfSPtn2RSlHbKNsN3G0WyL2A+O2VXZgUcrXxl7ZIfKaexm2FXGVuJtwO3D7cCmLU6gThOFqcOtwu3GHcL0uT7GKcEtxm3F7cNaSFCsfNw1Xi3sMtwv3N1zaFSlWHm4UrhK3CrcVtwd3CJe7FHtouErcOlwd7gAuZRnPwg3DleJW4DbjduE+xGV8k2fixuCKcStwm3A7cQdx2Vdi5ww3/cqErbPElbgSV+JKXInr63J9Yfb/5DCXbQDwyO3/3dbbMrbCtoc8evN597SYPOEbOaoXVJ6uakUje4YJ50Z0vyY8bn35t+KHxhrBb3PVWct5L8JVL5eEf8MaFtWTr3HkWJE99bfxnDt6h/FOGxth/yisD1XTqGc6SQP3Slz6gifrq9t31JZOFfg76HKLIjKYNHnI5CmTZOtqVBReOWi+zhG+cSGVi8bTGxnI3l6RgeZXw3qYMxgjxD/XcwajnT23JmGr1I+26gnhvfdZ5jyRQ0e06pacITz5VnvdC70jJGtK1gZkmZ6yND01LT1lJLuh/fRIdVb6xcnM58h5tYwWJ7bo2aJfk2bpzRzn1c7LoFzU2enep+UcOXvSV9I5Sv0m3UI7RM5xLTJ7vXMlbLnTTmP5/LJqsy9+o+QnJWR0WIV4bjL37fy0qr3bvffanIWTtG3DgcZ1RGi9MwUd94+8jlHG3CtB3umZfyhA1jcgOy2bmfNKKiGRsLcIq/1BKulUm4Qa6Kyb2U30VDCFIzoXwMUF+Cdq3TR7qutto6bNDRK+Q6H0qF0gjat9uOzc9ZMwt47LgeJvlpTNr6mjWn52gidJeJY8v0NYVx/nuqNnSf44Sc49hM970O6mpVLCyD/9mOWvxdoTqsLf0XKX22WU80JcxF/D/9v1//oM/a/ubhPmQ69uE/579N7iRugg9St3ZOfoW1TvSRPv2fdXbF2jkwP1ERndXS97dYzAd/h6B4jPV8/D2qbeNO6H9mBgGlUXlH8a4WtAF9Tkwz+n/3JBw+f0I/mqTPPR60InkjElkq+h48eNmDl1yJgpwx0qybTuevKlfKqTLMdXrwI0h69XgWd6dZLJPfMcV/5qVcH/wzp234k7gHzyp0TOWwwZOnTKxCFDz294/JZxS/hWm/wSj+kXJhe4+gUNyzF9/Ajxr7P6kG87WTWmjcb+Pzp97GQdx51nLHerkZvrcLJ3CvcGdBlTI/I=
*/