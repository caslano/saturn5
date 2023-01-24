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
/+tR3NciK7hL3hWX5HxJLfj0rfA5zpMiwkTR53hCaUk6tvBE8+rfyY55cTlPfPRy/iDeDa2kd0OPm9bWEnz5pBPuzZfiT21zF2t9DpuIlSd6F6Y+6uKdpCtOL528kWtQqlfgLQGYOfT4kswcOoLBF2+fg6wpsRGOXMHiW85gTUkDLFXE52qTDzjSieOKON5qPZizZ0FfZs9WlxgYepdhGV9S1hS3ZI0jKl8RWIJSDcJofdSZNjv2NvZwGNAcIMMrmMSO5kvWOSJY91GkVhtfktmEHBASPsFUuEpgT6k//L9G8pGxakmWgVV4Ofa2iUSQcPEdwsUkkYt2Ov8aSbn4AOViGZUoPBNmqab8Qy96Z7v4Ki2uxk5YQ8uLcS0fuw1u4hzO1qAPoYt6QvlI9JKcptgoAtZJQs403MG2KP6AsEXbLxJ4KPCcoJAygJYdpm0EL2o5rEdBuPztjjRU3C/epuMQvhJxw4w4lTu4kbMrF92v/mTFVMqfh8Hg3hiFjAHKykm2wwnlx3FBsEKoGWxEpaRZmEpWIu4bMnYYd0PODiwtwaYebd7eHfTAAOCPBEfx1f3Egeit74kxvx0KDb94ezcISuZLsUmaVm8fgOXYRTxl6pK/Ez6iAsATc+24Kn+T4NKgSyO6lOhSii4FuhSiS44uueiSoUtGXbQg0fa1OI9MprNIco98rAw78kzayaNmSTRf+BHPnAKniZty
*/