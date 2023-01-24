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
tldFbTHRFbVPkPYfO/9ritH9eqkLiHgy0qy3765/UjVZ63Hg8UADVg/Qc553upvMXM4M3Pih8oGUo1Sz7PiofEkGTCkbbu+g6uWyuW5CJoEkudHgNXjI8vO09XQTy7ZtI72fwUV+O5kKp4EtmnI6HXJ7ctG2asLtdJUFw6vM7GgojSOySYfrT2cUpXUS7lKVW8Qao6nBa3BhniuBdm2vzrYtFusAZLnIxMm4gO/MrTdHTQeqzYYpGz5NDS4yiNYfj7ZsBhfJH41YhVb1F2EZbtuGhqOK0Nn6Pk7405PcwHts22pVzYUXhAcXvflE3y/cCEuogSwuF1bCmophRbYpiDuJBSp0uKR8GHcS3fJkTEJN7E5C4ATIn4ndW4r2Fnh51/RFxVJsJt7tBcsqnzkTS9aS49U+FuI/gSrBtUbEzc10p8vntKBR1sH/ZhuSfCwabTCbpidOqJuQuJ21eCk98rwzEqgs8GU79Uln1fxnDjNq68Q7TuM6kfT7CugKiGrIV+3qppZq4oSSBK0nirQaehxMxCsKArWMGiO/+vH9lUcjKT3SdU7IiCqCqmTs6jpvnKH7Os9KrxOKhQEuVZ3vogZfbvl7ydfchZZnpIvanOHz2TP4fL0NntSax2HQmrj4U7pQ/g6dfR7nv6o6KJir4wOfTRksDK6OJwMMiFtU5xMLNjC+FW/J9JArHHxMyVVex5rIMf4qVZmSFgiW
*/