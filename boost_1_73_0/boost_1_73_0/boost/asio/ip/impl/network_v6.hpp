//
// ip/impl/network_v6.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v6& addr)
{
  boost::system::error_code ec;
  std::string s = addr.to_string(ec);
  if (ec)
  {
    if (os.exceptions() & std::basic_ostream<Elem, Traits>::failbit)
      boost::asio::detail::throw_error(ec);
    else
      os.setstate(std::basic_ostream<Elem, Traits>::failbit);
  }
  else
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
      os << os.widen(*i);
  return os;
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

/* network_v6.hpp
GEMgTVq1lTdenPjSGBxfsJ125ddz56ZZGdIe2rr23X3n7/vON+TXCxgCJVKXgZcf8rohFz+qr+iGBVx7XTt8ZWyUX1je3a5ur25v7tU9YqldpCm/DGhsmNYGWz26pC6NQbOA99X56+pcXemEawq7BTTkPTbJkodmDE6VZalW6FzMfyERONvbBNtOJ5hbAt7p9Q7GiGA9pA4hBe1ji6GC5RylAyrcaDcynAGHbZKCwa67VMgho/e9hoiDDhLCm97kA9RNB3oGBK97BArqx4sT7dxJATRIz7zecRC29oEB6h38wUAcBz1xkZ6MbS2GWMHlRluXaZs3BWehqrt7Va2W8FZVn+ClWmKQ26bOxkdwvqE2xmaSuP9HFrQLqA13kLPkjqc500YllEzcg23B0wzMp8KbOasEWGBL9Rn97l/QAgL2tLF+LVy3gfrMsrMxAbXP9TCXvTjchrx7Uh1O7dpTkOpz1f8KnRV8SOO6U3Gsf7JJshtYpzDdpdGZEqadAyL+HtEn4E+wGA+2eKKwEiju8O5aVd+W6gtLhQ+6H9yRFG/eZVLK3CyUbRqiYsIiHHM6E1BAPSaYhiJCjp4IeKzBPim6xEfFS/lRmRH0+xTZycbLEbMoU+6F7O6TlQwZPJvL91Lf/S9PW3+kEa/M
*/