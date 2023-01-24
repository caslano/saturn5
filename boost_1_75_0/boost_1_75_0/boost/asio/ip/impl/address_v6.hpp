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
M/P/vNz/u75QkMPMFuTwf8oXBvzNAv6Gg5n9H+BzGPA3C/gbDmb2v4nPGbXd/x1o/kL+vf6f5RVhm//TfFte7mQwc2x/Xi9G2HSQfh6k10H65notEvTtgr+gbyNBXy74b6wvU2yDcufYBg1NsfUCs+fQNNtDP6XbBl3TAWB4mm00uAPAHUDcGbZhC+cBZNj6g9l/Yaqtf/ZcW6/sVNswMIdlx27x0bwKYAV46D2YDABEfuijeRbgPMD/9PBM8N8GwID/NIAv8fgd+L8J8Nv/gvBiCDsO4AdhmQCqrTDyA/9KgI4f/c8Pv/SF7H81TNax4bmpc3N06UmxbCqri9ClsvoCXSE+DD1fV5CrywkcOTQ9JwfdENc5UlRq4XwImJaXBp5OQcw54f6d9o+me3hHjvpoLgKgfSuYB46S84Vc/QA8o9VgCr81ztP2kkrDauyjM9erNPZ7FXjqvcrquTNmhreGD/f9DK8iJUyoVD+znrwYyZE90u7qZzyI8wqEZstnDqpUF+MqWaS6+CAYnNlTXfwBda8X3bhUE8lO58zt1CV95biNV41LnAfDz60554On83m9Bs/qk4efmdLw6vOzzdHnvc7Pttm/TsZDXxbI0fzbEPEku6VGRlKXNUsNmBUQoRkSy1syabaY0LoCLOvBYknAvej4atGJT6yBfR3aJziCiHMGDUKqrU9z5h5sRiSbGMlGRrLDOLOvutgT
*/