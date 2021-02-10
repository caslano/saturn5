//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STRING_HPP
#define BOOST_BEAST_DETAIL_STRING_HPP

#include <boost/beast/core/string_type.hpp>

namespace boost {
namespace beast {

namespace detail {

// Pulling in the UDL directly breaks in some places on MSVC,
// so introduce a namespace for this purprose.
namespace string_literals {

inline
string_view
operator"" _sv(char const* p, std::size_t n)
{
    return string_view{p, n};
}

} // string_literals

inline
char
ascii_tolower(char c)
{
    return ((static_cast<unsigned>(c) - 65U) < 26) ?
        c + 'a' - 'A' : c;
}
} // detail
} // beast
} // boost

#endif

/* string.hpp
E611+uPxaOxMBv/q/0wiG+KvEliHnS2yTvCklJXhSc11cl4090829kCadPlw6C6MKcBB13HBev4wGJ1rZO94y+o45P1zW34SRgi1p4sA+DsXDwgXlBQijfDVEXNEJcx9YETHbshNsb37OADu0GMnTh0/kBYMCEiltM2z7RoJ+tXeoQ0Hc4uHndFH8eZUPWBNCFGnkJ3wUAa1ekurMctFVKMfReb73oXzQ294cdU/LpPmTJyK1vrj1kn5fIZg8uXkOWr93uRTneQatdpjRfJ5akARZ3TpXPevR+NPxxuyNR4b8Z6nNhhO++NhT5vn8Tq15mNN7vd3Ohmdf+xPn9Wbevwivd0OPw5Hd0NndDMdjIYbsjUff1O2q96kJtWGbPS4JtWGbHA2F8B0XF9TRF8iRLuWmvHEvzXQWy2t0F0KlTly9QyXn6MWFTZsx1lbLZNfg1zZIt0/7Tyx85wvJYCWkByIilyMk6/UjTLE8kyVCiki6T1H5SBtZi5rHuURLZWuOATWVsN7lQcpB0FC6mhQ4x1mC8BxtjBogcvMCeWcAaJExw6h/Ca80B27KWIHAKGmmXH/ujcYoiCBdnxWyWL/rIHprApOOiwLTKHxKuPiLTiU4llYxkO22CtFa7eNTwMUMIopROBUbQgiXIyG
*/