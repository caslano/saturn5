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
GGk8uJut/1hs1nA3Xq3G8/U9LN7DeH7PZB9m82taekliGvCp1GhIXIPMy0xi3Gh+u8vvdPwBjK6nweSK9We34yXpCpJDrpW9LB6BGo4m0ih4DaDAPSQqo4QYMvJbNJF9L4soq2KEkbGxVMP06qSLq6MuEepmXRcdfQUY6RRfopxT3W3VU+OACogGso9Mbpn7R1NPIhKl2MpMWqqQdqnmilhsSgXryrxV0/h3JSnplgJ+Gb6+GF5w7mKrdm6laW6ysCxe9HZKxv3Opw7AZLO6gQFjLpunSMVMaOCde5yGiw+XHXrneN+5JkRhDqEspO31GSaTHnf3gRnp8BpAQHufNoYuRI51MQtj9krH7IPHHGkMWtpJjsBziovlOtwE09V8fDv1oMs0XSdzFrUcB8HdYkX11zVIkVvGtZbapfpYGeu2AvHuKH4XwMtMrW6IWeaipIOCm2GT/zBS+akUz95tttV0vJ7SJs9zzsCUGNH5wGXBb49FCC6ml5mYbIL14nY1/XMzDdZkp9F4v7i5nq5OTSxRJ0rX50VEc6ajg8sEafaNUr3IR72yRtRreSSapBj9RU5pO2uttGnhtOrM8N2xTvqd+kclKTWVWtKjHUQQMvm1Rh8S2gUYv4UfzEPR9Tpf/iydhGC1k2Wt/omr
*/