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
7Z4rveWjdA1llPu5lNfOP13BDYkRXAuHBy8a28bLgeT8nIPGZoBjzJdGNYoj3ThAjlGMPmC5iEx4s4X8
*/