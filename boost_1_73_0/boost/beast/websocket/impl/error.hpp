//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::websocket::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::websocket::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace websocket {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // websocket
} // beast
} // boost

#endif

/* error.hpp
WjhZjt/JbFpIWruh60tZyzl3gDmeByoF8evTVcpSC7CPguiIV7IeZ2FBZFZ1KsQeOvLNa7xKmVpPezNFz0mglaDbqorFbZcWj7KbBpoBegN2b+TZnUrpgueSBcWipLRY7Bb/+W8gg7O7VcUlBTBXJtB++K9A/E9/p0SKcP4rmpi86zvuZe3bFt812ffDz+zy7T3uvdth3VO+3liCLx/sSlNbJSK7ioHOdhXPF4lM89mKiZzG
*/