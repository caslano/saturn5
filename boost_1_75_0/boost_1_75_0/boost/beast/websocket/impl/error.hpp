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
FB3r54RFxAGPEeiNdcQtwzdyd+wNEAQlgIqalspM6FB+nSdw+2qJ/NyvBv81W3kgEBOKNAev9oR8dcoqh6qCO/jVKORWnd1SIbgq+5iBYTPKHasd5XMBgXoylfvnAry3sMpXeAJpkrB1sfFwHZq75bM9gTsAs9wBmOUOcLR1Rxr8l8H6NWVFwLdahXCIPtZIfh18HmLNg6YsWuZIWbuVY0tMEsSIzAEvPeDLthMDht2OslyUfvaEgCfgawZUSdlLEMKm3MjafQCeqU1fIO6fmuod6V+dL7zhe+X+rJ9xBfJ7nm51IKN35/7kCD3PcvqGzjzoze2fUnJFQe5+v60gmNP0JEv2hVwtBbJUAEvb22bzdtvoYx+Cl6r3FBNczIK5zQ72zmZrBcxW110xkitwXC0Zxdos6fL/Efcm8FFUWeNoddYOBDoIzeKCUaLG9YvAaGIA09rBDnZDVNCoqFEEo6LGoRujbIlJgLZoiIqCG+KIIzouKChhEYIgCYKAqBAHB+IyWm2jIs5A2NLvnuXW0kkg/r/3/s8fprpu3bp1l3PPOfesrtDQqOx9QoPoY6b+s0zg0J4edaidLQdc0Y3u3P1TLikYIwA84VNRN92omxkRVW+0e3JvTPPP9QSvwM5Enh0AmRJ+vYRXGvJAiAXoBfH6vZz21aXH7A8LGhF+93g0SrYiq3ckodX1D1/Q9Zsvkozcr7AvZVJI8Ogb
*/