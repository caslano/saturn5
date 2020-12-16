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
6j5Yd3X1o2nNXnt1MvdqJXIVsh75DbIDiVWwZzsyCpmJ1CLrKpJ2IckjeSSP//1jX37/n7UX1v5z12O4vIh3RvN9X8PBJdU1LD7i9NLaC5Vaj4GBUObvuhdr2EdsHl7qv/9/VtDw/d/RWn0rkXbIpd63pe7+by9zqsrLw/emetb4O1fj+164HOcAxp4/dd9xI/Vjqak50fKMzNRuSKtoUUZWama0X3R/PjF3zPW+K5lvMX/H7+dIMTqUZjv+bzmkcYyZU/qBSWN6/Vh1C9fscb8bdyyofxd/pq/GpVUWV4XsDbiCsq4siP92ONtM0ZyzsDpsL0D87/legPm8Z8fv63gFutQ21qWmqmKX+zkSZvf3czxG+mwI0edK9KmL10dTV5vay7FuD3Ty6mupvql3R9ogucgcdFrbSKfyc+tX5gnVRf5zffP955d5c6xpkrre3c7Fndyx6fnfandWb8191jdDE3+gfLPTw8t3c6O8MCl/fvU8W7wJ8rR5D8rXfktPt/eBOTKQlei0rbFOFaVzQ+8F+W21R3oUZtgyMUcqchV67GykB7Yh4eUhv2m7pYd3T27ICK8jp0cjPVhUYJf3JGH2vH4OaxWnj8olO14fs+hreLlk74EeXrnc1Kpxv3kZVwrj9dCjyKDcaTJN2XIFbAQe0XPqftnPDAqksbD8HCfxupfnG7/HM+4U0fMr4vzSnOvrPYOMPc17aHWqef40zwbN3yeltW68J9v5RZRFYfyebPYZEmaDIv9tTF5iZs1G49ezAeD67u295n3/J07cJs5AXW4O2QNwCX4HBfUPf+4E86AwWebb7NtmvSwTxr/vH352b9+/POWDeHEr3rg+dW1W47ycQ15GBPMS9swKzc8IX36eMfmx4Wx+RuxhfogXt4030LbWRhs/7xaTn+L4/NjnXVg+5D/x807XsZOxa/qVVs3V9WITPvg8nNWS52FO4ueh7Py0ph5pxtVnZSy8PmuD+W/8jExQDrWN6tML19A+a/dKfdp4A/33gDa2jzBHFBnivlPF5UfP17A8yG/MV5fGr+rSXm+x/uonVD8mzoDun0v3UWqLRyMHuu9ejXSfXxZusyW/xNAf/YL2t9a2wvrp7XTw2ht9cstttswaSUEb0kC/t6lteNtyesbnh6psau/MnvHtyoTx93v42RvtysYbfG/TeoajVTcjVDfZwbzovSC0buR3dFzdGP+qG+tnL9eNSSNgL5SpEjpY+RmAHE6fU1mfn7JFJXY579kLTP00rNN9QS5ttUPz1s6xzw2ld6jSG+St55cwvZJF7uKsjtb7jRF+KZLRg3u6TbQfv3LbpTvxOjVvfV5/G83Nqb+wSO9A85Gr3cC9AraFGhPAPM9n3/zTbub5O8u/9mtXE24yb0TparuKi1zkkY912eSdlFuTj1ibk2LpHbVOsa5dxbUsrqUOIYfpeRlpsdQcrx2UcN1Ntwv6GZusM3F79lgmjR5yc3cYd4aJu5fi3krcUTfdzHbRKIMGKdH9o4Ndi/RWjtGtjusvITHXT3p+rBXnvbTfb1+vZ3PGB7x1qigf2h7lE1fmK7RWYIXKfI7KvC5hmRv77YRlfqcJ91VnjK/M63xl3pk6Xoe0dfOVRZnnqMx1zenQqMzbNafMXzFp5Nsy/9hf5oq7uMOuyzyN6+M7fJllXn+/j9eagQNV5r2RHu479H5hZT57loanbN4jXt5V5oNNuE4qby+eHKt7aQvWDCZ+dFb8jCWZuJUX/7taodbYG6E+ZJj6kJmheTBbD5j16IvJ+1rE1EOsjSlT7/zjSHtzvovV/WSVu+f+ooNZ59SMEU5ZxImMwBihLYMao0f7Jt/b/M+VpVpT7zbVy1o=
*/