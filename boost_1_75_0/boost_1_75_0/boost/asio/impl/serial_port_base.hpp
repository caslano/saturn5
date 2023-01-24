//
// impl/serial_port_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP
#define BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline serial_port_base::baud_rate::baud_rate(unsigned int rate)
  : value_(rate)
{
}

inline unsigned int serial_port_base::baud_rate::value() const
{
  return value_;
}

inline serial_port_base::flow_control::type
serial_port_base::flow_control::value() const
{
  return value_;
}

inline serial_port_base::parity::type serial_port_base::parity::value() const
{
  return value_;
}

inline serial_port_base::stop_bits::type
serial_port_base::stop_bits::value() const
{
  return value_;
}

inline unsigned int serial_port_base::character_size::value() const
{
  return value_;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SERIAL_PORT_BASE_HPP

/* serial_port_base.hpp
+q25KuXa86ve5T29X7XyGXZtE1ss4zh5Y0wy7l6BL3LNgkxHUgy6nkq9yfiyOSI4QQh7NrTyrXH8cvgnfs7yC6I9MiKH0eCnEuTpze7XdiU1Bj2vm75UUxnORM+0bR2nBiB2pg3DaRcxkncfpCybePlNr7570c51iuxnSPPqD+RznL1aow79u6KAFOq52ajN5ql13zhEbAQelkzUlT/aEjWoYTISuOIfDbVaufuH9nGGfHV+sFeSoB9OZeiUwhmYGHvRaABd9Cv+8iSoJjal87Z2EaULGtemDaJ9dvZtvp+5fm0y6XPHPxcE6R7wG7fzen6R7aV4A9hOwVYllUOHRwowSfv2ES7o4mwKFvxaZJ+JKRu2nPP3YoAF6WXWXtikefNoRepeuBGNaoSNBtOVqSXVMyC9yk7+6lMytm+CHqrP3OXO2eYLgnXG6Z7eiBfrHsV1wsaeZFryNlUQlpAoo8gF5wXsx4fmgl/bJL7vsNzODYbf/6D8+6XIAT4o4Z02ildUYkDWUfBiRqK93qTpsuZMV5mqstv9PjfFmXDi1HF89nEOuDgAemVFf9NjPK2pT9bSFN1anMpVv4LOL3A9RREig5W3Lhw1ZF7ODNBXKAYkBLDIIslEti0+y1WK/2TsFNJ/qSXLgib68RBwP3qjnZHJM9K9czod1kEA7n2xZODIVn9aZk3tqjAh/mxsqgSIFdkJvlzpFTA/TuY8
*/