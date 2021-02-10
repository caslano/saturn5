//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_OPTION_HPP
#define BOOST_BEAST_WEBSOCKET_OPTION_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {
namespace websocket {

/** permessage-deflate extension options.

    These settings control the permessage-deflate extension,
    which allows messages to be compressed.

    @note Objects of this type are used with
          @ref beast::websocket::stream::set_option.
*/
struct permessage_deflate
{
    /// `true` to offer the extension in the server role
    bool server_enable = false;

    /// `true` to offer the extension in the client role
    bool client_enable = false;

    /** Maximum server window bits to offer

        @note Due to a bug in ZLib, this value must be greater than 8.
    */
    int server_max_window_bits = 15;

    /** Maximum client window bits to offer

        @note Due to a bug in ZLib, this value must be greater than 8.
    */
    int client_max_window_bits = 15;

    /// `true` if server_no_context_takeover desired
    bool server_no_context_takeover = false;

    /// `true` if client_no_context_takeover desired
    bool client_no_context_takeover = false;

    /// Deflate compression level 0..9
    int compLevel = 8;

    /// Deflate memory level, 1..9
    int memLevel = 4;
};

} // websocket
} // beast
} // boost

#endif

/* option.hpp
K/GRTpVnbLMgtx5qAotVDItZFEE0ozLOxt3Oozr4ASM4SsaHXJsDVrBOG0rP6grrUqQIWFpfA9Wl16NR+UVTui7VgLe69LsOTifrSXzJ04Rzq/y0pf4hBaCyHfP2UBRVH2v4X7QRRYu239fc+gBOFiSJZ6hoSH2tjMtVFC8nv8+eUIdPn4VAgTw3+9qSFNo5aKleBJ6jQdJQoa0DJapOGlv66MEIadcWuCJLyvth8kvTV/igq9xjXVVaLRltuK+IbTb8pTspHe+MaKphmdF8KuXGn7CtLEs6nXnDvXmQ9NiP8F5m+5hIOGmB6ceAmuXadw/AanokJih5rFkkFvyfPeGiP+pJW3FYo6Gut5Pe4KcGrQt4xrTR3KLrdhyNffADqONmm8OhUrdA7Tw57eGnnKPXMxqjje29afAwwA+vfbCzZPVu1GYGeW1oGOZDGpnkQvPmWwqqPX2bYvYKfrQ36igYfP0z46Aqznha5hq1w9BHJcqt2FEDShSqqb+tZrexz+XL44nbW7SgXXlOTgdfBn8DUEsDBAoAAAAIAC1nSlLp1sqdpAYAAEsPAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9pbWFwLWFwcGVuZC5jVVQFAAG2SCRgrVbbcuO4EX33V3SU
*/