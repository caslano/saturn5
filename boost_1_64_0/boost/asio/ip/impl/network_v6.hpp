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
YL5tUkw7+Q4VbWcc0g7G64k6uQty+eCVju0ec5GVQQsW2pfdknVw5WPqUAD+oRN00uQcDW4WCkmhtY5PXXY3Vw3AOW5rpym9ouODMraNns2Ew0qWRNQ3QhCAdgnsDuZwOJo2NVZnuO4S8bWjrDNEurF88Fbu3Oln2evT8brgu8FuxrjK+l34NnCTfFLzDpg1m9Gwe7/biaAl3Xp/iNoU3iH9PnLDvqlZU4ojOJ+CzPIEI5vL2PBka4DBiRtwHDejigGKzHGS1d9uu6q+tI6AHNKs4JAi8dqHK5450KZhy8dmcJY8HyPH12Hnos0O+XJPJ3I8gFjEjp4up3vcGXGE6h2/PS0BLRHBDrIJvWsCmqzG2+T43z0yL4qUhtfGknoiiq7roMS2otXIDG3DrrXY3U0ete7cPD9lzw0lhH7FOIeFU7cX2XzBzkdnwory9hFMU6VLSBzOoxWilCHJeTaw1zi8FbADIwFeEdqb2rOrCrYH4uizjKKm1rALbSmUbeWgNy9ulVTsbFPqnj8fhZVbuZFpD42FGIQ6lJV+HqLGx/u0C96ztZx5xbSTMQ==
*/