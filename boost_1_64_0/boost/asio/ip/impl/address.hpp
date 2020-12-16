//
// ip/impl/address.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_ADDRESS_HPP
#define BOOST_ASIO_IP_IMPL_ADDRESS_HPP

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

inline address address::from_string(const char* str)
{
  return boost::asio::ip::make_address(str);
}

inline address address::from_string(
    const char* str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address(str, ec);
}

inline address address::from_string(const std::string& str)
{
  return boost::asio::ip::make_address(str);
}

inline address address::from_string(
    const std::string& str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address(str, ec);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address& addr)
{
  return os << addr.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_ADDRESS_HPP

/* address.hpp
HqnbxNj82GRPfebZNEblL7F+bBw/4hLrN4rN8zSI7eqpnzArNtbTLOEUfD3ehI4JGYgmJ5ySUBTb2pOQMD2hY2zzRLc7oYPxmAqTEgbhUbU7sX5MQjexd0voQuCpCV0ThuHj9aTg2iyhXUI7mAoHxXbh5PQXtD1vaF8Tei/Sa/Uhydchl9hNWdYPey/aL35p5j727Ec+e0tt/5+I/8X0irey7lFnvv2V4oesifcDVwbyP+Jrf3NX7feiv38UfC8qc9GuJI6vyCN2E+dBVxPchlLftd1Ddojs31zjXV10LoQ/fGzoPUV1YfeK/16X2APtzKrtHnP0o2PfY+y+LEnk7rKy6C+qVF+3xNGW8/HrRs7KXS2s9bDmPaa5fd1LHNfzLbyBPLv5x3rX1GGuxQncP+zrx4z9xrmOf0wv0hjdPQNlrHj00wPuvzT15sbJPa995MtfPhxp7C7S2GOksdPjH4s+3jFhx16a8iydA7O1HnJgAUbHZPS5nHcHtTvHZPCoOgPEwuGwHpwE42ARrA9LYDyU+Nz67KjPwTlwKGaAvp9M0bGiAtgFToXd9Btrrn5jHQdLYaF+S62AlboG2v1wNbxNxxRud6xx9TP4S/iAyj2nY3D74K/gn3QM7i24U8cWHtKxhYd1bOERHVvYBRu4aIswScfoUmA1TNOxuS7wJdgDvgz76NhaFnwaZsNn4Hgdg7tAx+Dy4V5YDJ+DF+lY3hIdy7sM/gYug/vgDfC38CY93216vvXwLngv3ADvh/fAnXAT3A03wz26htc+XcPrgK7h9Yau3fUOnA8/1rXP3NTVQpgEF8E0uBi2hRfBU+AS2B1eCvvAKv4GwKVwNLwCzoDLYAm8Es6Cy+EVcAW8Eq6EK+DV8Fo4H94EX9FvrIcsfQ7TZ8Ic2ALzMsY/BtxCx4A76h6hp8KD2r4OwTN1jOocHaMapGNTOTo2NRK+DYt1jOoi+K6OYb2v7e5v8KfwCNwGP9a1vz6Bn+qYVSzp+xwmwKOwIfyHtot/wv46NjVUx6pybLsZy9RnH31+yqkxljlExzKzYUs4FLaBwzQ8adfnB+pIr7t4zGT/QxNyTRxjlufBfDgWNtW9YbvA8XAMnAgnwklabxfAcjgZci3Kd+iJ+s05R78Hf4rx6jffo5gM/SZrf0PdgKnG8C2T75aE7Qkd3wVTewd/s0sc6LXaY3IwxZiVA6PfwqJH9Ige0SN6RI/oET2iR/SIHtEjepz84cXM+37G/6eWlk2b5VsF8OTWAUxmLLqNvRbT9hi+gQ5eZOnaf6sce//l6pjMFj4GZMCbYTphrNdlLGRhcYkvYb5U8Q3WjIWYNUD4jq7yxLLTGsUn/SGMlYfXIxhhZAeZ7/Uu/V6fF/BTO7/EvsmnA4C/rB1C+uIY50phOH+46ujniVx/1yK+4CXj/kMXMrifK+5DxG20uj0lbq3EbQxuJNG6Q9y6i1sObql2ut603bxynvPUbazITYi/1OpSP0Vl03EfKu7Pe9tbG7zqLuVZIe6PeOtZ24x7Ju4r1D3NusGr55RvPNvEvaOm1yXpPSRuyS5JB26kQ8tlNWPHq2RNpT7zl1oZxPFjce/jscvLMnsnudyLLC1batjnttRdFeLm8qwMlfOsDnVzbXa4BepkjCk/+9j1lpRfUH28Km4vSJnmatnfI/F44j3WWVKm47WsLxD3YUz/uVrcJ2hZ/1Dcx8S3sFaI+1gt6wXinhkfZ1WI+zgt66vFvSXu08T9XC3rneI+ihUZ2oq77NFoyvbduDjrJk2ny0oy7r+Pm2b1tySdQXVRHdeCr5iSTtzTjfuWuATGOySduGcY92vievNV25dOUm3ck+rnWOOlzGQ9HlM=
*/