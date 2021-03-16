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
+1kPz7sVYF6q7F8/3gCYPfnr5X3PBr9vfqwXfpf0gpuCv2N6w1VVVeEj938wenssSzB+rZzzIn5ZXKorE42Z98a1dcU728XtcZO79ak1tTPMsZ766ZPx65bx6ORMrDMW0WMGBF4zR1/ETIg/mp7pzkxJtV3BLmKzbew/8NPZ5WwoeyrCzL+eeDST0lMd2aqJgUlVvnQ2nohfGU8urHKkEul4Zywj7hCehB95H2x7pQxJOcfXoPka5iiOkOZVQlo=
*/