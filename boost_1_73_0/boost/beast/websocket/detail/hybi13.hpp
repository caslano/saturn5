//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP

#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using sec_ws_key_type = static_string<
    beast::detail::base64::encoded_size(16)>;

using sec_ws_accept_type = static_string<
    beast::detail::base64::encoded_size(20)>;

BOOST_BEAST_DECL
void
make_sec_ws_key(sec_ws_key_type& key);

BOOST_BEAST_DECL
void
make_sec_ws_accept(
    sec_ws_accept_type& accept,
    string_view key);

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/hybi13.ipp>
#endif

#endif

/* hybi13.hpp
unTmXPptCakRJDQXtd5X1oZLrcoKSEQDhgJKRWgBOrFUOykvth/jBkJeeKY7xzg+8eXRT3/pfBIdpx83ff+bdpsZIP3DvB/G6fTaW2u7E+pc5apkKe2mkFcVYk6SRtE8+xXzK6U4/a65xSXFeNI7wfYEZPBBlaADJZDV/35hyarHQcAjwJUw24ieLCzZQXybKDmA52HYEQ0Ak7s95B6UQQYgl5Sm+JTZb6MTdNg8g7CaUhPM
*/