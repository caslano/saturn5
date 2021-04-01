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
hjyeH68tN31cWTaD7WPCQ9cFQpVzoScoAMbN1cePxQdHZMVqo0PGG0U+grOj8tgk2tmY2AFGVfgNZHHv2BYhOJxgsk8PsamsFsilwgGqxNAB2Op2OqJDbOJKQcieHIjxD/QY1lKJVvcKXfe79C2dY1AuqqVMb7VTdghHDGruKJ2hgjr/SeTCCN57OwZtfaCvMLSpWH5JyP7d7vVctbFUArWanx8AvK3E0t+7FJZBxIcx3llhCn5J9uKUgCZ60SOZuUBtkn7oIC8EDnY/FKDkDCHx8KjutcQxo2PHgMjuLIxsRYWuaT2zRWGMT8USzI8VCqf/Fh7Ch4IxZ5/Q08TAdRcKDpYvqrLpS3ZH2CRi1ZX39b8ivGBAMoQJuaQR2aZEO7FVS0As3lARvHi7DFLt4jlvYQVRZhTTSuhFtTtUy7/u8GsZYCPL9LJ/BsfhsVG6L3mrXeghTYxVuC75gLaZ9kJye1zCh399cBnsdRWhjYEeg7C0+tfCYli+A3xJUeYjoD7ihyNC4l40QUiGGB4aAci9aC9IJuYOazPbUVun4DgqNHhfMkwCIGZVXg==
*/