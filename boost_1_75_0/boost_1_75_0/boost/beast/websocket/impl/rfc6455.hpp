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
eUNLtMYoAzqovX69KIMmGxH7ymdwp5020lIfaJb27nVcX7PUhzttzCh4ptLXALhPYwfYJuR/C90UjaOfGE3kAgxxSPUcVdNtjF1j67b0gAcUHgUctjFulEp9ge3STY+fYJSiS/gyupEbC8P+6PvV+DRVrTNVNXUfIzlu159BiIgmhRBLPuc2zBl4VeCQWOS/ABYsgSi9kOFIhhuFpcl/YoN21wobcE55qJi00RrRWlE35TwClt9znWnSIXDR4EKe8RrLjMOd9vsNlsqlWiNWxgibqowggYFbBOF5SyGYq36Vp736eYD/0MVz0iFIaEt4fJJpssWUncWBEZqIIhqr8lB3RQk/AJ7Hpknva1nAIq56LVS9Cqvy6oEMzoUF8Ubjm43G0+GN3qJCzjLcoI6qx8SeFJuiiH5JuIeo/2JWsugCeSbEUDacKYYSfCsDIy+EnF3WCl6IQz9qs7YkAQZOgwJ4rkVaGF5l0CdxZrg1Gd5wfrnG9OINsS++38aLZ9OLu2tNL54a++KjbbwYTkpRJPQoQEFDVVhZHIzffMYmFqYZwIVmWaxiqo1IUJk7CPrY085MQXCiUBOzcFag4R6cis+lfqmf6/e1MXWiiSWWJtjbPBWAuLS9/cOxgLCSx8QHFOulxab9VMZ9OkPXxV+4zrOuOc4T6lENUkZtyIM2iunQJHde1LkjMUWRqE4/1HWGpjmOicCLoTQYwBm9
*/