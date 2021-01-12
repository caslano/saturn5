//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP

#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/http/basic_dynamic_body.hpp>

namespace boost {
namespace beast {
namespace http {

/** A dynamic message body represented by a @ref multi_buffer

    Meets the requirements of <em>Body</em>.
*/
using dynamic_body = basic_dynamic_body<multi_buffer>;

} // http
} // beast
} // boost

#endif

/* dynamic_body.hpp
gkoaXl/aYKmiNos3+alDzjSGBNdGzczJq2bjwXThQo5CZxtq4Y2FYnn4sAvFIEoini2DWSi7FVFv2S124Nel4VKzydC7rBJoV5OmdWHzHY9NULpUeRQv7J5jIyhfF4uaS7TVjnPrv6MeXvbsI+BziveJmfLVbYpY+pE2EKbA09OJaK71X8S3/syYGVtrz3R2889Lo9DnXcbm3TbGaWPue+JBCaPTfYKLq0Lc7djRLUB7hcD1
*/