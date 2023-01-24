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
dkjiqVh6lVCE4WlFLO1CPY3fxtnpVXp6c6zsxjCPmWjx1pPayqVH934ReljgfeFvnXXvCx75CHhesMP63K8rqHCexXmzEWpGo8cFbzSPCwlUoj96XLjII1vR6cLIPeBDAaLJa64TvjAR75hr39JEfZ3MCEiKff5RMvlS2M2f78NTmyNL4FRjn/djPyCML/Viioy96O6RE4zdv4eSzwOHv93YB2q11p1BJrukzdkI3uYQvc00XBecljNU55tUUQeUFmXTSyx6FOZx67m9n/CH/KHT4A85MLJR8oX6NbAfDaidcYSdKIP88aQm+NZhm0FUkSY8HvdzxeMu56KKtDBRRekpRifYoMvU7CDJiPdh8g7Q2g8y+ypV83g8WBIO54T36+V9uI8OCJqLEj9LilMj3cdhyn6QtrG+uFaDkYPyUZId1WqJDHgYFghiBp8GFzk7srSSZ9qlQ2zuU/yxK0zNMVdUw3bHulgfdqk2MNqExoZu9ISmAxrAOKWpN+r7ojhG0pTBimM0zMd2QpEhpygsp9CQU2jICa3LRHENiJdIAAwRrEkSWK+clQgRkueiShroHSnToX+Bl1P5TVdZkmCL/nGoX4rSCJmynKF93Qu/XpSBX0OJu7AEqVYzIHq6AuBvpE0iNWTSSN+2zS2f4g1ZTh2bDBLCAtnmzungT5V7xua4Yv0pck9bjsvmt8k9E3NciSUdXWpNQaDa5goc
*/