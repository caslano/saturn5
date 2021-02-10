//
// ip/impl/network_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

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
    std::basic_ostream<Elem, Traits>& os, const network_v4& addr)
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

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

/* network_v4.hpp
OhbASIakLPXfj5bdLB2wi2RSj+/xkd46eyig8y663KM2Xjx4TvxKmdpRuBePSF0Ba6veCGfahOGG8mW336122wqchVSIdRQPWqMu4E4u5nIhViriwfm+gNpZy++GsfXJk8jzXOyRKKQQogMyRxPh3KoIF2ngzFH1cAp4rSKhvCA0WoMa3nqmTHWgPIJ1Edxv9N5wP5ZfIbYmgOuGDiRUiPABb5yH1p2vRJlAeOw8BrQRtRRi/a6OHWEGioihzlIPj/t9Ccrq9PFpCIUQo6tJYhwr5FyctTF26QgwnMVshiO3rN1RiGXPhhp1ojgynA3RJDrIZKNYBptJe/OPNHy5kz++y8VXKXak0QPPILBltt6MjImMB8b3leVrCnyvsYsQkGsViWnfOg0qIJOY2DNaBaYtoDK2Rt73zU95C5un7Tr1Va3KtIeP4mzIijBhb+dyDtXzcoQ+L6uEVRTcpYB31GFtmt7YA7w2T9zua1MCt8DBtzESmP7I8H8vGbAinfRAElsX/jb0yY0UfwBQSwMECgAAAAgALWdKUilcCQWpAgAAMwUAACUACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm90by5kVVQFAAG2SCRgfVRRb9MwEH73r7gntokkwBBCqhjS
*/