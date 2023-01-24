//
// ip/host_name.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_HOST_NAME_HPP
#define BOOST_ASIO_IP_HOST_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name();

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name(boost::system::error_code& ec);

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/host_name.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_HOST_NAME_HPP

/* host_name.hpp
lJ0r8Eqb0wFL4YrKVQgcQZRmQtggwEygr+Or4SX47rHLVihKK8C7daxXHueuz2JhDPGwYCwUdczT/d4QbOAolc5iEHy+Uxh0OZxZrSvCTKzJqxBYIUVbXfhhiWmeZD5ruThH1lMNmh7BsB7HeRrMWmxEE8YnJ5XU9kUHa81IOBtHauSjgV1oow6NLGk6fm9kBO2U10bSXTUvs4ddrOQITN3hN0TARMI6zM098aTGaWoUSXq4XA15GE2IusVtOZj5PWFsdkEs8vIkaFVT7LOvGl3iCZmfKnjcuqOkumhTx6JibNFQQ1Q4w8p7SWbB5Bk3fv2KQQ8K1LCyf1P5pDKnyP7tao0yRi6shLztw17MM/zYNmGJvD0aTixtVNSJHYv64EnL8DP4Li3XO2Sk7x6fi8QJAT3AcYG0ul2vxn5zNFhAh2xBXDz/kkMudVvZYIkZdzUQbHx0Or9u+XxiRn7JlE4oUKHn1d6Qdak0HBQxWZ4/Ft0FeS+oXHrNlM0vwPXqyN2ueW6f/VsDKxSdM/2x6WfCfPhWMRvWQn88O8RIfnX61fWYsc/EXv+2SSSV4VuJPQuUgfK8WM/oQwQhh0onopTJP4QKpYlzHy9e1uE22ww6dKtYBI5oVfWNaejp0GT/oMREX2kTg5FIUlfGaTQ1CGROo59HVOCA+BhDH7M4JJnenQfyWFdMUVTK7qriOAZpLyV+mOARhYQJ5Khf
*/