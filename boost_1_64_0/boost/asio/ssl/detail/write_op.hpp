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
akP5Gn23ds23ls1sAygjZZBSvFrrVryhqq5S/8v7A8VjSKO6FAzcg13F29bDEn+8XGfQh9q9z4jnfUatz7Z4nXGp9WUsI3mTFC/KxXNp5vpUa6maI5z3rv6V7G1cm7Fi+LlJcSdmXn2i8P6K537mvFfxqTT9fMSvU2uee/wrg6tOfuX1CfmvFzrtme20N7bTnspOe3I7r/m6WNZMDUn6feSXF/3ivYrEe47cf6ZuU/etBbPfS7vja7Ls98Z2XiPGPQF5nw39uTcd9wS0zLulco9kn1wL5aJt5D4PPt+ekr2BCCi5o5RLspG7mvldA4wDbjHMW7RRLlnkzPMWJZQrBQ7gfONAhtV8le++yUZ+JecLVgGTuBdxpmG+Pw/kpvx5lO8FusCw7gOAayDyZTiRezincN55kvCrvTh5D4P/kp55L86B1COB85yDuBfkEOAFnF+/FDgUuITzgJdxHvCzDFNv3Ev455WOO827s9yZ1H+EYS9dN+XLRN68l+7FlFvAeZaF3It4BXAcw5O5d7TM8QKnA5dxvucyYB7587n+aBlwKedh8oFXMJ72g+urs72WU5/P0V4rje2f5lwP4yk3gfpMZD1MMs5XWuWt86qUH0P5scb5esrH2chfT/vZDowB3gB0cR5rB4SaguyNuH065lIQVwRqmQ6+liiZO1oBeh6EPQyxT6F1T8IW0FHQaRDmZ9TegU0g7Rm84wWeAWVNQByohHv6HQelTJT9+dSefJng9+3Jtxe0YgbSB54FzUVcLPfL4954pj3xihB/AXAFqBbk27/umB4/BXmAtnJeoQW0/9vWfeV2I78k7h3XAPK999+KtN8Duri/2y6EPcB60D78Pw7SnsX7a1ABaCtoL+gI6DQo5RDeuYPKQA2Hwu+xw0f4CB/hI3yEj/ARPsJH+Agf4SN8tH9EgSo//fl/j/dP19cA6HP8p/Bi47Ssv3V6j/jpfyvb0fegeIen3n/kWd9xqHcaeI+h3le0gPBOgu8hgIb3DUk55nWE4SN8hI/wET7CR/gIH+EjfISP8BE+wgeOf/f6/8qqylL94b/Lz/5t4Wf/8LN/+Agf4SN8hI/wET7CR/gIH+EjfISPDh+f8vM/HGyvWe/97Z65/99kIQ3fni2R9A8bgVSIB6fgfLx8G3epe97i/PyFhTXrC0tKSz34at5ztXy3tidBQ3zNeoOvesoM05IRXo7wryQ8OSIWX5PdB4qMiJTv5qZ6v69GUoVr6yrXiPwCJZ8i8pchfELC50b0Qw3fD+oREWX4Plv/xlnkhX8x+F8X/mkRA/G7D9QnIkLSdqu0h3h9zaPsmnyT5//eNWagHt8r4irU5E9Bsk8CvzzpT7/mvxGe/hIejPDTEnYxPkLrmSB+AVBGxONfo8RfhBrJRD6fjYuCTKHL/11ybnz73yb7/L+jvvFtnre+E+n/HfWIc6oe5bxbfVuu6ke+jXxQyiIyEv4bw+A1fSvZSn8A1fwuuwL0JhwzehIs9gBjrS1FtKpT2AOqzP9N9jaRKdQu8/uPZzrx3CuA3z5SZqDGeOS+SPajwDmEXpBzLpHJcqm2k/hFSPN+iR8frC7nG78bvcdbl7XK5776TlLKIvVzWNLEdzsB3xwX8bv12/md9ZdBBen4GWRfP1i1Ux2sjoaKXK2W7f/GmmkNFRvsJbbuYR/xxV3BcIT2RQn3N9lrPO31HIlbiW++YpSN3iDnemoZ8Mn/Lto6uifaORnfvPXusSimPGZ4r8gerl5RsZH4ts2xvosljZEM+8rQT/z4h2LPAW2g9p+Arjjnkfq/bpCqf/O+Rr3oB5L2+SDopgno39b6p18F01il+vsvhH+P1ge/W/32yXQGWcY=
*/