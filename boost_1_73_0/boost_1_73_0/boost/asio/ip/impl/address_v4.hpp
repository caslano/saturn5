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
OLB302KhhjgbZNljLFp9A1BLAwQKAAAACAAtZ0pStfPhWuMBAACUAwAAKAAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3ByZXByb3h5LmRVVAUAAbZIJGBtUk1v2zAMvetX8FJgAxI321Js8GlFLylWbMOSnooeFJmOhSqip4+k+fcjZXv1gJ1MyY/vPT3ygfyhhj5gH+j1om4Dn564TmTI1dfXzx3F9FT3FNKz2qDra3iMCKmzEUoLtDbEpG6bBpsaPlc3H6uVutMJDxQu9YBRy+VSDW0IsUdjW4sNbH/cfduOLHtsKSAY8h5Nsv4AiUB72Ox2P4FC+W5huSzoCu69itl0oMFo5jU5uMHIxBClX+TmIto3cuffQO9SFygfOlVg76emf1VHzQ16gxLVeKHUrpudIaYgvmNH2TX8oNlLzzaJ11mu0tfaVxEcYBelXcLgdbKniXHCx6qEHsm8xDU3L8ZSv9U3wklBDYdOTkwd8HdGDmWWuxkTOWGIlryg2GqO2FTwnf5Kqrl55+CoX8aYG2x1dkkaC9Oag7hvi4RsCfh83GMA3g9PaZaB9QNmltUCbBKgjjEfGVK8qA+rLyvm5BeHMrGef58pyOh0gqM9dEksM9HJNv8nBs1Tefz1wGYNMUbt
*/