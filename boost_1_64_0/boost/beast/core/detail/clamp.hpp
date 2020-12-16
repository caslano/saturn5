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
8aUrjueBFzM+BzDFoq/oDCwCduUZ/UEmn16f5hiZMinxW5++hHqt8Qw/EdgDeCn1KJOo/7iM+p5sYDFwCuNfrTjeBG5l/G1Efm4ziPkbyvX2sVz3Pg94ATAdeDHwfJb7AmAeMANYAhwOXAQcBVzJ8OuAY3gHxMXAn9Kddxlw3IRxIfNjvctgNe8WWMM7DW5heTcBk4FbmL87Kce7gNPoPoPr9XO4Pr+Y6/VL6b+C+sJV1IutoTvlxHECxjQB5LSV7WIb2+XDbB872D63U04/B15K98m0X0E9mgv4qJkv+i+jfSX1aqvpTv0r/96jLTM/Vv1rF7aLrmwH3SiP7vwukqhX7MH20ZN60F5sJynUOyVTXv2B8+n+lbRP/n0FTmL6rYC5TH8a9ZvTmY8cvg14JeWRD+zFuykGAq+iHu1q6k/ygFnka3Q0T49yD9a6J87Hejv0KGUgj17l2HyvbsUxHOSEbgHUc7hX17IR9jqQR+dywOnWu5T56V5OOpvqX6JGAE1agPV+UBEoDe6ZIxAOv7eAcvF7FzCYjub9BV49TXSFW1ezD/bjoDTYJ4LKQLWmH6gRlD4S+QcdB+9SYEIl9DT4o5kDMvU7a+GWDBxT6avn2TMSWOnW9xwAngQdhttW2B2ZSN8FvQbIowdKgVsDMNMFXmA+0E8nhMaL9ALphuBeD/tB0MkPHWrpMjv1RbC74A6MrkI8IFN3lAmsBc8p8OdXoUyjQKmIB78zRiF+0H78Pgby6Jc6LYTOBOTRM01d6NU1rcfvteCpA22B/QDQX/e0HzxHQY2m+7VoU0i/CO6rQKmwbwHuBTVSN7UP/iVwjxoEHhNHo+0Bk2GvBwbSWR2F+x5gymiv7ipzNPhAVh3WUth7AlOqUQbQKlAG7OvhvhW0HfYc2A8DXcC9cDtZjbwBkxe59V2O5XbReaWNObPe6zh1XzmL3Pqv5Iu9OjAncD1oJygW9qWLfHVijQH0YnsXeXVjhxch7EOQ6WKEAaXAbSowkL6sGu5lcF8LqgPtAwXSoalxKAN4a/G7HpiAsibA7Sh+pwOjliCPoHz8rgFlLQE/sAxo1bfthFvdErfebS/wfdgbgdFL4YbfqUCrPi4L9kygExibBbkAPfq5XfidkYU4gLlAF/V1UdeBLwvpgGphHwP7bvRRB0EnQbE3R6g00FSQC7QRtOvmkL4uZEImZEImZELmn+xdDXyVVRk/dx9sbAPGgDHG2MYYMGDAwIGgCONLJ19OvpxGbmMbbDK26zZsJOpQyi/UhVSaSEtR0ahmaWFZraLEslyFRWayUosKFQsJFbP/+9z/Pfe8733vPhj28Wvv7/fc/z3nPM95z3nOx3ve95zznP+m6980/19yNuf/I0cpfosN2GfM47fY80B3Wd9is31zwfwMq/fZOr+16m+x2c45jJo6cy4/aqLPbn+qitTflH821LdG/8Yu7G/kt1Hnd1Cdj/1cx5BEoaGgHchH3sRAPiwpzhuFygf5k2QfDb6pGHM/NV7z3DjySXiChJfUrqcN+wpHPEgT54PIN5XrFQJ8Xd6ba+af9jo5B4P0kS/JQvGTNIlfup6Xkfvb5mV2cj3AbM41TAZV40+xU3feTWurKjE9s9Er6ysqB0l+qDvyG/O214h7lMG7VsIWa95Usy4IRXShLvRnXUCcVn7EPUO719rm9rM4t9+HEUSCGsHXbtRvvR+G6XTUCfL28deJLpcV4nKtq82RnNvh/qQNoJvA2+LTd01VmW/6o6y8tKasPGRdJf9Yre9fi3uF8Nf7+MvQ5KlzP3+mtpN+SNxrDLsbYOe6Er/d5Z8Lz0rWa38cI53tXM/FH5HwuXr9xpMJ0L3Mf3StnVs=
*/