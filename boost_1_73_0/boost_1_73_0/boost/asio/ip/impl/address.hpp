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
YS3w87GFzWq9fHjOn/I12NBMpDWFK0aB/fehVO0lIQuDCzO6+a/0LYb7CKpvXFRzZcuhbFEdQzZ+VGFrr44iOIZUuUtyQomNC9BjBVWknjHyAphmzoaQQdRgxmE1hGqABo82eRljnK0y6TKqYMeCoR5y2FGPql8ojxrqSXXDFEO5tDilmpowvr8V5nlwqltj7zMoMHXjZUQ/ow2a9pg8UPDD3ITEYwOy7DaV3PwCUEsDBAoAAAAIAC1nSlJRUHVkAAEAAIoBAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcG9zdDMwMy5kVVQFAAG2SCRgXZBNbsIwEEb3PsV3gbhAEEjZIfrDolKjkgtYyZBYMp7UnhDl9nVCqaqubI/Hz++bd/ZtgZ6j5Ktcncj1BZ4ZngVxtFJ3EMbbSwVzEQq4sHM8Wt/CYH5QBhau2cUCp6oq1ZkoMy7yA7n5WddwXBux7NWhaagpsNebnV6poxFqOUwFOpF+6VZZlqmKnIuoh+BmgZtllxrx+XrEfpOvn3Z6q7cwvllMa/Y3CoLy41wh0NdAUSKsv6ur38rYkf8TIQVI3Y0NVM9mUeOASCGhcDXTAkp3KenCFU6gq7H+UbhPxPzHaFSdjeB+PiDtrmR8+u4y
*/