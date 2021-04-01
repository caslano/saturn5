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
wN/mxfU7S6zWDTJhufE2aSWvNPPKusZx7a0sA/RYN6flsVe8jZPzLr08bX7TeXYm4zkY47IdjjTXcgGUnu1vK3PFahQsKDl2pmsKGUK6K8AhX1RYLrMLhPcIW7PjSx+sswaFHnyWGfPjUnlZb1/PH68bbUOb5LHtAfNQcBkNMscOHaMAFwVlEfBg+cHQqurXOdZDa3XQcg/IDllYlatsjmQKwnEx57WRbNpGiWjLeK5CmcZqJBe+aCdAYSzv76m9atmC6T9/HcygBFLR2Ao4xRgZlrp5zTFdB+4IZ3fDcolJgdFa+vBxNv7iBe9Hz5rKGDixfZXV2GJUBMxLDtFzkoJONnpilfnQOkqf6HGRlk6p+dbQjB+jJq8IJXe9P59yx+HBsSrtj1qjI/H/t2r46WfS4TQnul9BR7i9rbhyJluZn09x/kSFpNu3lGE/2pIvtDWEYm1AN0ifnNW4kqmm1jF2NNrDEAvHaQGtX2NR8d4Ypi2DuCn0ZM8gcKT8RIqYiBtu/8PZoleGSEPnt2Feqj5fpJPeXFEAkv3bTJaKWt3cVxUs9/zn1db1cw==
*/