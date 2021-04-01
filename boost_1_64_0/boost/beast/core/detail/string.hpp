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
WumuOEJmvVJK8IfAYh8B3D23MF8aqAEXupWCdEG8Q6IjofM3i6fo+FaUdh2x4T2PaKzzUvNOAzbV4K4iwXq10yNaHAL/jGhhCOVfvGxDByrCHN5VuHrEytdjuAVexe2x0AIu/tVWseGyr8MjAakAZ+JU1d0lZ6BgEIJCDTcmJ/ZqmEWbFxT+05pOvchdu7pj7EDKntAHIVIU12ek6ZGN+zQKWZVTOpVfCFMc0CDxERtIhrr/MNQGRfTtTgDlVFOaUMJGe0uDYz61eOUvz0NrLJ7YXx3cV5fYYdkLKQwC0P5rxw+HOB4wSbYiHDz7eWBCwS8H4YxjHYgHpPuOFuJTLLJXrDwo9jGooGC5BaATK2Cp+/OQjMLnab1m1JCWMsbzpJbipHDSWjByTytfduoz0R4vUmZzNz1wRYJ7WqnOfFFJst26JM1cAJS87UXQlwoA7DtuR7BfAPbeQ4Ym5B0Ig6GIYNafmYKCcKreigE4gYgx/fi4KurTL28pPD+9EECHUJboI0EBrhyrTljDcHWpl7MJ9QcFY2MttbL9vWYyWvCagYjdT58IlMxB1A==
*/