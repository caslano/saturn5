//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_ROLE_HPP
#define BOOST_BEAST_WEBSOCKET_ROLE_HPP

#include <boost/beast/core/detail/config.hpp>

#ifndef BOOST_BEAST_ALLOW_DEPRECATED

#error This file is deprecated interface, #define BOOST_BEAST_ALLOW_DEPRECATED to allow it

#else

#include <boost/beast/core/role.hpp>

namespace boost {
namespace beast {
namespace websocket {

using role_type = beast::role_type;

} // websocket
} // beast
} // boost

#endif

#endif

/* role.hpp
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
*/