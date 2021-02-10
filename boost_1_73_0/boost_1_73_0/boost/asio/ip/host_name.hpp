//
// ip/host_name.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_HOST_NAME_HPP
#define BOOST_ASIO_IP_HOST_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name();

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name(boost::system::error_code& ec);

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/host_name.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_HOST_NAME_HPP

/* host_name.hpp
Y68X+s3u9z3+sqSpF76pfwBQSwMECgAAAAgALWdKUqX9mKulDgAA+SAAACkACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wYWdlLWhlYWRlclVUBQABtkgkYK1Za3PbOLL9zl+BVdXe2FuUbCczmUlqa+8mtpO4rh9aS6lUKkm5IBGScM3XEKBlz+O/7zkNkJKczM58WKdCiRTQaPTj9Glw9Hmg/vZf+0tGFKf+8O9G/t/gD5/dpHFT/b+Z+29PuLn5VYV/mPgZn39iqQO1mfXrzb76U7N+VXsy6yau9Xd+v7n5E8t9ppK8HHDy5xt+xZMwM84/ruqHxi5XXu0d76ujFy9+VEP19PDpYapOdGlNribelDPTLFP190ye/HOl7+9HzvwjVcYrnY92BE5X1ilXLfxaN0bhe27npnQmU9qpzLh5Y2e4saXyK6MWNjfq+Gr88ezybarWKztfRTkPVavcqmrzTK30nVGNmRt7F8TUuvGqWkAC5GfWechsva3KEZY3ypumcFEMldC5q5S+0zbXMyynvVp5X7uXBwfztsmxk4OsmruDeWeK0coXj3b1EdoU+kFVtVe+Uq0zqeL4VBVVZhf8hInwsG5nuXWrdKMWFiyzg6pRzuR5FIep1riwBaMm0Vop
*/