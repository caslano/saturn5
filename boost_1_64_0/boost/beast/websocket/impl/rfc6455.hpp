//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_RFC6455_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_RFC6455_HPP

#include <boost/beast/http/fields.hpp>
#include <boost/beast/http/rfc7230.hpp>

namespace boost {
namespace beast {
namespace websocket {

template<class Allocator>
bool
is_upgrade(http::header<true,
    http::basic_fields<Allocator>> const& req)
{
    if(req.version() < 11)
        return false;
    if(req.method() != http::verb::get)
        return false;
    if(! http::token_list{req[http::field::connection]}.exists("upgrade"))
        return false;
    if(! http::token_list{req[http::field::upgrade]}.exists("websocket"))
        return false;
    return true;
}

} // websocket
} // beast
} // boost

#endif

/* rfc6455.hpp
fvkVQjvLO6AHRBcm3Sj0tCqwZ1Dt1vQJXACLTp3ZX4gxXwZDhP+8LWX29w/88XKSU5B2jrNHceDESVvo9wcJpU+W69guROD2d7DADm9ZA3qZPP5WP7bSzx/2npPCBsfteK1kD1xl74BDYvrJEKX0iwLlwukhDchBbTA2cLwORBYxeNL6kF0M4LXt4j6mRfPt7pI32ZgiWOP6m33pdX8W1UuayNIZf4uzaflcOSc6HguPgIJEWXbTlNUrsH0A/lE5AiMvQ/vjLOh11RJRhDbeWlxl21Vnhjm1z0PkbGFu+4RlChcWRO38khHrZ/SEcmWq6GmOpQJRz4OgD1Gj65wPGGCU3P78CYRipGeRfqNRHkvh2ZSxKh/3/u85jUPggNYMDJAYSXKTh32UgL53Cw1dYl19/A9LmWca8ztLbosWK6VBBpdiitdFUD6XyrMNB/jPJRanMc92NoBrxy2sq7v0i2DzpxsuNbpELSvjCvezZdEH7+++JtseUx7SWUf/Wusmkj9HrsnvJJ5wrV2IcDJUuNyoHX/PBR6x0ZkRQYUBs2aHc0Uf4wYaZN5zpA==
*/