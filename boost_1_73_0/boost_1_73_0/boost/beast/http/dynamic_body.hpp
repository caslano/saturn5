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
zWQp6mNLVOpEV+oA0atApN2KLysUBaKwEFmMa0+QuDYIDsD1JkhcD6RI6Kb4BIlr+MQEPORf6W+i64R4VrQZ8UXYasOoLd8CSe31FnyC4kqSOHYSyV76+BbqruBnaVvOMBzt/H+X+MnTChPqIaYyu47ZCmY3MruP2f3MMBigWY50mBWfURaYvL1YmB+It8rfqLGPWfZOyz4SHRkJNJRYdqFl79OJcpTStnX2jQHLnlFWYbXuLq7dVdnuiuC912E=
*/