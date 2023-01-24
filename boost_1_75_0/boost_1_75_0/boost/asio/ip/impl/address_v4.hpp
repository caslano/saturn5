//
// ip/impl/address_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP
#define BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

#if !defined(BOOST_ASIO_NO_DEPRECATED)

inline address_v4 address_v4::from_string(const char* str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const char* str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

inline address_v4 address_v4::from_string(const std::string& str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const std::string& str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v4& addr)
{
  return os << addr.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

/* address_v4.hpp
RapTyAVmvpQwC/hEgkuKSW+uFTLOdMgqrk74cvaUgnjOPmfhA5xdt3AsZ5+3KIIn/DJR5vGEXybKPGs/pzBuE/FlrB1Eb1JnlLqICaR/LBxt6XzTbodhQfUfjsIKxSoluhV6EqTI/LlZuO6KHLBvR4Kduh5zp1+IqqNDMS0dA0ygPX/pOtKnkonITVzX342B0BwLkYnbo4kMkW4/UkkHBvyNQQ38gUHCWAdpA9dx6P1b6fe9sN+PIP0+ja2QQb9PrWFK0vsvpL1/vdD7YzEsv6MW200GUU/q/zOE0AUGA1kWKMHBlQed+BC7ifjT8QkdmVhCkMbZdeQgbOAhehRWvaaCr9gHvtburQbxOrNjgMZH2dJNeOiKSU55nI86F/ilefIEx7m4Lw74aGwAFwAYRiaTy+UyWekUxqfKRzMQ4L4qZ/9Bh3w0CwFGHpL4O727G2gb9NMM27Bc5k9+g6IH/TQlf1juMDCjwEyBGVBqbQCTVtuO0dV2YIaA/yPg/xCY8WCOAPNRMEeDGZvflF+gLQDy7/9fyD8A8u8P+QdA/v0hf0/Ivw/k3wnyvxfyD4D8+0P+AZB/f8g/APLvD/kHQP7N8xsXPf+nxPy8P03Hv+sbF62D/Of9x/L/q98k24PZUnewbVDmbNuwzCAwHwNzYvSgzjPzh3WeAGYymP/+/Lu75N8L8u8P+feC/PtD/j0HzswPHDoBzGQwQ0EO
*/