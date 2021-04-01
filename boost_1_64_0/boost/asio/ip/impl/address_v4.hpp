//
// ip/impl/address_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP
#define BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

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

inline address_v4 address_v4::from_string(const char* str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const char* str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

inline address_v4 address_v4::from_string(const std::string& str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const std::string& str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v4& addr)
{
  return os << addr.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

/* address_v4.hpp
pp+vC+gUiiKArLSvs9ASQkyD3fX9ODjp7hfDfTuBsQmtJuTatQ8fp+jis4LO6MbHuErmTf7UEQq3AodBetpjshmUm/JngwY+zQyWHO1MoyGrfOfI+0Nnbqmsqg+4Y76usla8hGGaYe1/lMDPhSA4MceDzbPGO6Z5099MKqZNicQKsUbVWPypNKyFuoDnCgIwUhro4DosUkmnfZkHO72XLOPqNY/hP2jtKueTZr5l4xFHbdE850BxJ2VUwQdATCFWvEdh/0VuhusaOgHwZ5DtABtTB/DJCKqKu86E1ivlpEIUF9OYD0YZJ6J0JRpDBwVZXGWedASr00ZpIf9EWzBcXMEQRd8jLqKqY23rjte5fRGQQZnzqwPzrLGCZQhAokX2mSV8cBI/K/ULQNCTJqujOjL+279uvGPW5m+4pjFD/8oQaG5Z97C8yofN+2LZsOGtkwjqn58cHURUj9/5e/7PEibGiQieMaPmM8H5Ag4Ry09ghT0ooqL7RZsPPAPx1vb0a1NEYZgVyRJq+w9TahZO8+N931/KMhsZuq0aYwo/SjuQ6j7rOSryBbFnEg==
*/