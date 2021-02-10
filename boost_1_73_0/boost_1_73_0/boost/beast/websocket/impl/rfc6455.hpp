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
CSvW8SiqMvt+K28RkWtd+HL2dqO1cjVbbrFYS92uj+1x7WpYZ+GTVroSihv+ZwJY0FvvN19du3NwbFidLRtseT3b/f8VSwvY2BwbWJVEddGt07Szvd4iHG6obKx/XRXla3epQy65WxyuKjxxKu1BuC5hGszcNTTn5BNVkmoXOY15pHI46QNm+IYq3NUQYqFM8vgMn/dvK0f/ujgra4OdmuHu5JfQapK21tM1QKP69l7+zWLe+Os+B/13o/ENLo5vaeJWakTRSJkZjyoKYbV1Ky9zzhC5xG6Kev+LWjcYA/G8WcS1Ha4Y2723LmoeGoI5utigtiXFUXff0vpawIOmIkSuC5SHl1StEGsZ/8ei8IzplfmQ20+xexiKUynycvFkCSlwIVvK57emHcJKgCfZWzXrd7uvqqW7fhls31HcDeC/UEsDBAoAAAAIAC1nSlJBXS+zkAMAAAAIAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9pbWFwLW5vb3AuY1VUBQABtkgkYK1VXY/aRhR996+4JaoKyMXb9KFNlqyKWJKiZIFi0GqllazBvl5PanucmTEs6ua/997BLkRpxD7EfIw9nnPO/ThjB/3vd3jQh7NH5H4RHTQ6xEKrjxjb/18dRU9w+BDq
*/