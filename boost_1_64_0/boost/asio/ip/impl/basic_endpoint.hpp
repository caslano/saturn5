//
// ip/impl/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits, typename InternetProtocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<InternetProtocol>& endpoint)
{
  boost::asio::ip::detail::endpoint tmp_ep(endpoint.address(), endpoint.port());
  return os << tmp_ep.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
AVnRt65ba9lLiO+CB+0luI52+wllgxlJX9ZbacHHffutV2XBRS59PYvqBePySLkdIrUyC7W2yL4g/xJmCYWJWST0eXudhwKi05wV4srnHzg3Fo+eP6PDjs597uDLaYHs7atU7zNdPD1WlYafBKtO/+XMlzt75bi7ZidFu/xiCQ1i9hrr78cSfEZQcYC6TVz+tOvL0P337S3lmH0onujZ3pr6gToPVRDmSVwDrA6vVNhrfvgtO74gGuELAoXm+lvdqhcM07jaiC4Ih8+8jTHDYYPWs4u3b1Mya4+dk4UzzdHf9B0KQ/XqvesS99gEjHBru3tRvF688nSlMCHL9DYS/CxSrJhP1iuERjhSCWdlNbOCtt2cAB+Q7HWObc8q0dHlT1CHDehdDTn8kn43vO7hIOwPqEoqfYLSe8CUx8HIe48ndzLL7RWuc9fk9jerk06Cl8xbxq5IOFgCwqH6K3TeEKziHKGS1ZGhtz+AQR8JbQTA3Dd/JhxIxvCg4oEeeoscnbxPTkUaEf9DZ5LAtvkqjk6w2WIV6LoWp5/we5XxUI/dyDWlhZdILPhz9w==
*/