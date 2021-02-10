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
L8V8BTtZXO0cnSNcKIuk8AtJsaodmE4HbXgWEYYdi/AVmCBHYb5arxRvxtTEC0iOYywTvvqkpzBYhfokAXMl6UJEjpzpkz1iXBTLTvNsyOMQ8TQG9QdQSwMECgAAAAgALWdKUhN7QwkwAQAABQIAACwACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm9ncmVzcy1iYXIuZFVUBQABtkgkYH2QwWrDMAyG734KQQ/dYOkDBHraGDtsp+0FFEeJTV3LyGpD9vSTM2jZZRBykH7p0+fPwKI97Nw757mHIjwL1doNKO6NUunhJdaScAUVzHUiuWUA7YMWfEalmWXt4UoycCXXdZ37wBOBv0iC8f8VNZ5LonvRVkLMVQlH4Ak0kKuKeUQZn+DMQtadWM6okTMmq5GSHJz7CrH+XTMKLr+IPBsixUxt5X63Bx9Q0Nug9b2wDRgIqheiDEZzNfA2W0g8ZcXZuNs1d48av61Y4ZR5yQd4Zbn1KixRA18U0G3tLfzU5k1giSnBYLiC3v4hFnjojnzsHi2AapZXagb+1E4Bs9UAw0Ud57TCEqLJjKjY4AOZ3I0rZI/U0M2atNlOaW2JgDXYEbNdsp4HThU4O+VycD9QSwMECgAAAAgALWdKUtMXWJU5
*/