//
// posix/stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_stream_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of a stream-oriented descriptor.
typedef basic_stream_descriptor<> stream_descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

/* stream_descriptor.hpp
iXNql3GMm7lxWWtz4wCvFlRdsWRuvEEyN17XNDdOtuuLUVNUeEmUYLGgBIubKUFhAfV5R+zuTipzmaPJ4o/5bMC5QUMsnk2Iw7MJCe7PJgiULMGSxK+jagtfgo1JNOu8RD32He70RBXPwJgdRCr0HSGO3bOlofpLX4lqscHS8myzJ7aJGumBUjyG0D+SnWANEaWgf4txekTq/XHHApgTEm2aGmftLA7n2/FkL9MUHXdnHZijGh9XYJsmM5uLx1rvBgZbSJiAuSmnNo4tIA6S/rqHMN4XRcXRJfaLthdozB8rRF76Qiit35KmIdkdnmhobb7QDuYLn8Q59YY3hDFF7BA81zATh1SVjmX+DaBrijvqHwAv4MuhL1vni6+5te7x+S9FObD96DzEwMMNQ4ujNuAYbMGXbY7BVv8kWdJzOeAASFqagNADqhvIAVXTdGmrzZO3dMQh2peP1MTMwAl9/AazwkOYCo9OMH95VHIkwFmJY0JIEBkNQ0pTZBwd/8jJ0QabcLSBXrLC4w1KRl1iJHbyw4HeIMKQwUKQvAT9APO8oy1ymHccdNhqefcHqKygo0JvsNkp5hxZcku0bcDOU8mYoqNF8p4gN6s2wwQgVC7K2yQUwrEJ5u+PuC/pBuzGQSoXO7D1lZGjEOSdVZyDNh2F6EcltFck25VIKB6FaC+sPijxNAQuMpSW4HZlNMz6Nyean64ll8quEURK
*/