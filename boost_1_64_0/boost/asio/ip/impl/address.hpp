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
qImA78DyAF1UVm3i5SV04T/RrHa9fvQaUO6speWzrgJodZp8imG+DAD+yS751K05MLrl2j69QFgh5bew7saAwnQxqKvpsbaq+hvt7AH6dEm0ajYnUGWe9Yv6D70yiBqAJ/LNSYwfkkT9NKDcucyedRWUwDEMQ6pK5HCrhgpKptPcTBzv5tUBY/rnOCyY97CvXDDmeDbjxB0xTFYqV/iTpPjGBNfi0QWEkoB7OqfZQW+AESeX35/kn2OgzFh1xDZJK0YOG5dDtN/e0sgKS6EuRgGk0fFNN7xAGUJfmacmT7250sLcqlwFdAouQHoYn/JZrkK/AKl57v1vyVEaapxrhtxygD3qxvPuyC3XKujgqyB7S0GOM+SkSNIXuardZsETZgC65FSAk51sKnRLSG45U/PkCUH0J3gmY6I/EB5wNcRMXLjeW1/MVe//zm+6bIz4KJhv+5oTFYcIhtuAvu8whG0KZFUtKSXlRsiGDAEhPjFXcfZNG2ek66iUrn3Fh6IfKfLDxeEUz3bgNDTlzcBdFHQil+2CAGR8ijBcaYebk+4w119q9HS10rZ1VQ==
*/