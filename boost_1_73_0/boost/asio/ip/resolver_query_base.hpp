//
// ip/resolver_query_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/resolver_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_query_base class is used as a base for the
/// basic_resolver_query class templates to provide a common place to define
/// the flag constants.
class resolver_query_base : public resolver_base
{
protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_query_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

/* resolver_query_base.hpp
gS8q9Xf6JMri3TS5MD45qzC+JAu9gOlSqhC8ACN4chZq4Z+cs2LIHJNUGdWoiJVUXJOSuFTRWMwvLGCYWv4titWXoFjXtSZpjPyhMj/L+VmnUu/rncjp1IZL+y8aTlWKIucpuX0rmZu2Fo1ilu6HQ2h8R4Z4ckblpDMuGX/+2ufw3SzBkHfDtWS5fNMGuHzq+5nS6fthiabLRf1ZzHVf+fOZGPCymEezAeU/OLyH2OfCVzVP
*/