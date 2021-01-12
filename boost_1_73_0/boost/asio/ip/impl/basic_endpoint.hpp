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
fKCgVRSrtFo7MSIoGgiv7f+fO7O7icHa5/c1MDsz9577vnPuOeeee05163G4JK2xtOojZFW0b7+/sgLHPo7ra7BK2duHvET6oB97e7lcHyFBHQY6aFXPddh0XjH4juSJ3V947rYlA8y6tK3qWX8U90Erkiem/GTM6mUuoyJtVUaPQvI83FjiKUG/P3cnbt5h799vbx3y4oK2RHt41XSln0jPExIu9fO1TSGn7HTlGvRydQV2
*/