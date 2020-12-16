//
// ip/impl/address_v6.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_ADDRESS_V6_HPP
#define BOOST_ASIO_IP_IMPL_ADDRESS_V6_HPP

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

inline address_v6 address_v6::from_string(const char* str)
{
  return boost::asio::ip::make_address_v6(str);
}

inline address_v6 address_v6::from_string(
    const char* str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v6(str, ec);
}

inline address_v6 address_v6::from_string(const std::string& str)
{
  return boost::asio::ip::make_address_v6(str);
}

inline address_v6 address_v6::from_string(
    const std::string& str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v6(str, ec);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v6& addr)
{
  return os << addr.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_ADDRESS_V6_HPP

/* address_v6.hpp
z7C4/5LZwZk/sN1DaUVU/CYN510jEIYzsAuJLdt36XqF8x37GO7ROQ3Jel9aYD5Eb/ae4DvqTBQzrSHGuQzBM6HT9eP/At3z+QzMCYOY8/k70VtcUVldWlhcyU2vKMXLvP/7SAtWM9d2m8ifpO/AwfAZ5kwTzugjj2ZL3m2fZCfQ5J0J86aESY2Q07w3co8E5GLep+s4eYckvnp+3nYJz3t/54D9SbWP6xKwvxDm/3bIX/JuuObdHs276bqv1xTNu9zAPSktLqs0WRct30iLyvZQOzOoxZ4SfD9vdL8vrzSeKXp4N+upZwaqPW20+/7fmBA9DesDaVhW6UqF5ZmO9WHpeP4opWNnWDp+Y9LhvhfX6B6TWzQdd2g6dr0o6bBrXaP3IiDb1pTZMn/s55qHx/tj0cVY5OCAPT6sTHXA7kxXH7W3GR2wT8buDH+GCe8+83FakiW/1Zru5ZjN+BwM3D8O/bIbwMbTYV+jxUuBa2RoHDqF2QeF2SeE2WeG2UuN3R3nIxrnjRrnWzTO60W+zj7Ii0jHFudNYdfcFWZ/Ncz+aZg99WW3vbexu8vXXm14r9b9Fy+BO2h/C3ZLnGVsUAcGw8uX2Utxscie53veOlvLXDC8X9tR9q18AbueX9+uQ0BHdWgNmcp3svy6J1y52Ff6OhF2ACba+G1b2F30pqvdZ70i9lTrOMp6a/wX0dfMwczGnK1/53YP/P1dzDzMGeqGn7rHvleiqR+Oc6pIn7hV6738saSFPR61jmwLs/8Ku7Od/nuYveoFt/12tRt9xt991ldJK0t+c2jPhyrbc/+LXg6/t3REy3jI8G4HNcx0ueenY79D7Knxn8cle91TDXOihDkD+0axt44/HJfi+GZgN8SW2U/uJpHpGN8yPk70lBk9ExzjxXasqwqXVVhmr9NrRCY7vl28T8KVm3AjrRQdz0527Mn55F7d61PL2xev2PafIHuJWUfztsikm/ObD4v9blnjFdzz/wdyjRfiEn2Vvixx94n7daKvW1ylb4H1T/bO6xssvwlFEfneb9y4ouH8U1Ud2nuw56uB546O1gDcdIybMfDq2gpzZnQBzDBnr3Ncq61Z62U7uEjicIQc+KnI56l8B1lZdr4qU11xPLexr+S+ZOpCKntKUQfiF6ROY8vIXmSd7O0X9C/Af5Xtf+EzIjAgKeA/kDrXEtnv6Jh7HazWurVa3d5rL0bqV1FSw+PxBUmh84y3S36k986fMeIYvMUtcD+s3qUrVlSu0PpXnxRZJzcnOeqkum1NCo7NS/mT8fodxs1RvvT5t0ieZe07FJAtMGP4mo3qngd7io7Q/cBd8pd8xz2Y79qOv+zuL99Xe5q2213kHnJ3hwfsQ7E75QvUnqnyb6h9pPaviXvd8r2wO+UvUvtMbVtuwu5sa7aE2XepfUG7gH3qq279p2OP9hwzv7We0YTphlmMOQad618LtUV8La0g06Vt4DlZ1hk7+5l7RfYMawr/aruk4XtImE6j9TuQ2WPc7EHZYDnrD6Wc6f3j2rL2zbknOLpxQ7fet1++5s6332HXfHE9E+zTdLcIAB/Wd3WmTryu6S4OPMekhM5QlLRRVVSmRaPvPa2JYzLU8xFd+f5Om4DgLH0Pyre0fw88P56/orymVBsjr7ZfZTPMM29Ee6/3p1Tkxof6dLF30G9x2hcf5b517YvuvvAH2LW8mu9q6+K8ziL0OuPP6yxCr+9nXmcUep1N6XVWY9PXQzb1DMTo3xGb/v1vjHx3/Py2+WPGVJx0ke/87W9edb7/H0fvTMzoZyx6ndHp9b3w6H2PPFfS27rXxsE3pL7ru3RUdlzZyAfIz49ybff0EZsmjF6WVLz3sQc=
*/