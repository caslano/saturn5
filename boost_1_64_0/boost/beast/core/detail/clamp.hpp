//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_CLAMP_HPP
#define BOOST_BEAST_CORE_DETAIL_CLAMP_HPP

#include <cstdlib>
#include <limits>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

template<class UInt>
static
std::size_t
clamp(UInt x)
{
    if(x >= (std::numeric_limits<std::size_t>::max)())
        return (std::numeric_limits<std::size_t>::max)();
    return static_cast<std::size_t>(x);
}

template<class UInt>
static
std::size_t
clamp(UInt x, std::size_t limit)
{
    if(x >= limit)
        return limit;
    return static_cast<std::size_t>(x);
}

// return `true` if x + y > z, which are unsigned
template<
    class U1, class U2, class U3>
constexpr
bool
sum_exceeds(U1 x, U2 y, U3 z)
{
    static_assert(
        std::is_unsigned<U1>::value &&
        std::is_unsigned<U2>::value &&
        std::is_unsigned<U3>::value, "");
    return y > z || x > z - y;
}

} // detail
} // beast
} // boost

#endif

/* clamp.hpp
jK+vx0qjMoy2/jMd+HpNI0H0ghCaSh/w+BTczGOVhsdeBUp3PMeELMZ1IFt1V6VMajBbbb55+vkXBcCHWD1s30dsG70qYY3xzWwzLCISoxcGWo+rfkrXXqWSBjyIxHOf1E9Ye6F9FHJaysscNYzl2PrXTndlcw9U0d8UAtlsvRVzr1b2fIjbnHoLYFaO90ChFbr27uWocMIbWTVc20azvCnyG+SZSkfEQy5qmU09zgeDHkh209gNr++Ht533z0fhCL+mIv9jRA82bzYoxaEIZDWYgDt6bl3blC2OvE1RfOiuN8v15fGhtUH4BB6FYWBy7VwO/WpXUyvWRcCO1MdYVBh6BPeKaGXYEfcGGLTRuJuOAh990MomXeAlIGQu9/518M6ZdR17jx1tvtcwAJjw7jpaewkIfIMQ7oqq7SHgEhPwsdYUOYceOxGrXZ6Tj38q8EI/7W4MvwGJJhX0UiO/xCtuqPpQIXzRVQ2TWHbLkQiNTAqAJOWSK9d+wLsIeCnK+jhbMpdUimrU6isZfmyXCnA7yFrMRS6eVrskibzK0xRilvhgM2YSKqbpsg==
*/