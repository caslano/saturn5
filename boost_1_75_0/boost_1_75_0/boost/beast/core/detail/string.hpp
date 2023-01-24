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
kv21hcG+RDMsEQKgdu8bvMGTGIEeyLBwCBl0sa8tS4ELbwUy/zR7hAqe3YGof+DKXiqTKuaFHWDKXqL22GN3qElDnC8mj4VKmupkRdTRw1gffNmX2YxJw1FLvBoP84/yi2lwiS3mUiKILWZT+CYImbIb6qj03dOOZAtr2RQVyhw/lPTd34cTbcf6E8z076fqv+vvbxLEZUxuEoRlGHawwTHp1bLhMbU5lSRmTG4QlNH4OFo2Wt4NK1dX6fCAE5uagkqcnV55zpeX4yq3HqL6r+AWAjsUxT3SZXXBJi/dyV09sTcXa+9kAGB4F4R4Z6XWxwa1k2XAh+7u+gRxgvx3X0SKLoLsJqAi2gEai4FtR1KbNviGMgB9/92r0wkwY3WTtB/AHQDE2mlYfed4KRjeLhzwCemCoO4AzRkerQCZa+8VL2C6ACDpDnrtM89dIE/ATuyN1uWnE2BndNtn/93/CczcLdK//bz7TvQEFn4E4lSlk7zaAkmi/evq1zd00r4MpdK8VTRQbOhx03Ls7Deac6at5thia49XjCDKdi82vZx768Zlp5Zfa3ABmJ6IpKidyWcy0S2csqG5jq6G7WYwS5lFbQfHw7YZJIFdlPRLpYmh4Xvdy+PnAe/RKqstyjBY0HLXeyed1my8bBvnol8yr9BhAtP+1jXUGXjvJsCVYQLjtEqrlCU4JDwnPCa8JiyV1i2xGc5dmDu54Tmu
*/