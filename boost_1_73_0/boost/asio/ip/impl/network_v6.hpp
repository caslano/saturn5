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
+fW0Nn6nEQ1ejcO+O5T54totuIdxOOuD8BoivhTtwQBbxMNysnP6GOw0UzA9jWfmHiUIjo7uQ51AIRXr60PC5Kw6IYfoautly1tqMCVDSfSmS9u4xJsOKjPx4R6ATjP9TPv9Ajy0F3AzgNFBllsMWvjRqxUd256QwYNGBmjKtFY5yTIVLd7y0ASIpY528nnVCZ7mC96ocZhCfjS7u2SGF54zX5Uif3i2IkvP7V2xMiPf8N3c
*/