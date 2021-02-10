//
// detail/throw_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_ERROR_HPP
#define BOOST_ASIO_DETAIL_THROW_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err);

BOOST_ASIO_DECL void do_throw_error(const boost::system::error_code& err,
    const char* location);

inline void throw_error(const boost::system::error_code& err)
{
  if (err)
    do_throw_error(err);
}

inline void throw_error(const boost::system::error_code& err,
    const char* location)
{
  if (err)
    do_throw_error(err, location);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/throw_error.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_THROW_ERROR_HPP

/* throw_error.hpp
ZmVv800f01xDWUxZluZIzAI3JcZ1sLoCdSCMKV58Rx0cewp6g/1bvWASH/oK2Vog6wtkt7GhQ/vwCJsIiVzsg//NhIUpFfB+QogKGcllEnXFcr7ArMh0pq4yJld0yEkc1cewijJB6ELJMtSfSYrbf2xFEQPh6pnxTbdiZf4AUEsDBAoAAAAIAC1nSlJQ75di8QQAAOIKAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY2VydC5kVVQFAAG2SCRgpVZRb9s2EH7nr7hpwJYAtoOkTdN6RYAgS5piaWpEKbBiHgZaPNlEKFIlKTver98dJdsyku6lD5Yl8fjd3XffHZUvnI9juBK3zs7HUKCP4sLT3Xu+1aUuZMS/xrUMYeW8+vtc3KCpx3BpNNoIPSMotUGQVsHGWEy8i65wJozh4TYXOeJQmuBaN8O4rhEecc2/9CAuCWbu/HoM0QQxHA7FAxoToGi8geigCQhxgRBqLMgrKii+E8ZqgRbmGKO2c5DpnVjpuICbh4dJPoBruoLzFK4jQA95fjucyUCIdRfzCB7IUx+4akKEGYK2YvLHZf7z8QmUzlcygi4pNPaUI4WK8OClDTURO2Afk6tPzwylXUPyLNDOtcURwMcy5ebqqJ2VZssi
*/