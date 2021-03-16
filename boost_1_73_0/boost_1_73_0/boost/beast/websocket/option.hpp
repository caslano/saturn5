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
oc2Gp9ILJ6P6UYU1BziLOPRAviGN7a+wF4E7RtjbjB1l7O/C7b0bJ3HXgPji/aVQA1VYH+u6L941FVXL48r0EN0N70/pjokAoA1wvCbcywj7u8r7kLjy/h9Q+DLFQjFBbBJX6rogqbBgscCl+1iah0OdwIJaDXf6s2xFT8VQ4yTLEp3+Uqon6Da7Uyd4dLpxm2G1aY3JCuWG1WYQ0B0a+0qqDSU7pKouYFLQ4qgZQPOBztT6GeweB9v7HKBYRaY=
*/