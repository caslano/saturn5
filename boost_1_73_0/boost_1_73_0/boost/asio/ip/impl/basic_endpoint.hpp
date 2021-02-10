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
AQAA6QEAAC0ACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm90by1kZWZhdWx0LmRVVAUAAbZIJGB9kFtLw0AQhd/3V8xjBRMUFCGIUGpBoZhQE3wplDU7udDNzrIX2vrrnURC8aWPA2fO+c7ZkGkzsI4CJQobGXUQb6htBpVHKLZ5ma/yDTTkQJozVNsNDL33vWlBgq87HFAsHVs8Tx416RexVApVBk/pw2N6J1YyYEvunEFNxmAdejJQR6dFkiSiRK39dEIgiJy5a95nq11TXE0GIwdMhVif5GA1ZkL8OSXJv0LQhWA9NMGmA/30WsuUXCvE0kA0B0NHAxwSjY/WkguoYAaAWjKSB3SOnGCyFWOs99XHZ1UU+bZcv+7niUbWxf0N05Rd74Hs1FMRfxsKUHfStAihQ5ipOOR0vkQtRsrx/6sPHcXA2ovPVOtIUSsY5AF5gTai9/AtPeOyYDTuyIdb8Ig8wKjn6YTCIHvtU/ELUEsDBAoAAAAIAC1nSlI+KQQgqwEAAAUDAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJvdG8tcmVkaXIuZFVUBQABtkgkYHVSwW7bMAy96yt43DBbSYNuxYyhQBMkaIEUMeoce1Et
*/