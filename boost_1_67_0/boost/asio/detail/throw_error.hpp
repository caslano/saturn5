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
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
*/