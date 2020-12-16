//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BASE64_HPP
#define BOOST_BEAST_DETAIL_BASE64_HPP

#include <boost/beast/core/string.hpp>
#include <cctype>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

namespace base64 {

BOOST_BEAST_DECL
char const*
get_alphabet();

BOOST_BEAST_DECL
signed char const*
get_inverse();

/// Returns max chars needed to encode a base64 string
BOOST_BEAST_DECL
std::size_t constexpr
encoded_size(std::size_t n)
{
    return 4 * ((n + 2) / 3);
}

/// Returns max bytes needed to decode a base64 string
inline
std::size_t constexpr
decoded_size(std::size_t n)
{
    return n / 4 * 3; // requires n&3==0, smaller
}

/** Encode a series of octets as a padded, base64 string.

    The resulting string will not be null terminated.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `encoded_size(len)` bytes.

    @return The number of characters written to `out`. This
    will exclude any null termination.
*/
BOOST_BEAST_DECL
std::size_t
encode(void* dest, void const* src, std::size_t len);

/** Decode a padded base64 string into a series of octets.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `decoded_size(len)` bytes.

    @return The number of octets written to `out`, and
    the number of characters read from the input string,
    expressed as a pair.
*/
BOOST_BEAST_DECL
std::pair<std::size_t, std::size_t>
decode(void* dest, char const* src, std::size_t len);

} // base64

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/base64.ipp>
#endif

#endif

/* base64.hpp
++CruA++mfvgD3L/exuwEPgU978Pcv/7n8AS5ns6MAFYChwCLANeBCwHlgErgIuBM4CrgDNZrvGK6zjAPLZ/BHA0yzWH7T4X2BR4FW0zFnBffhH3x+cBZwLnA2fzOeWL6yO0EdMPPheJ47lIB56LdOL5R3eej/TmuchZlnORND3HxwMHiPOYZO63bWI+7wIOAG6mnG6hbc5W4HTg/czvAzxPeJDy9UfgRuA27sc/TPl5BPgX4HbagjxO248dwGTgU8ABwGeB2cDngFcCXwDeBHwRuBn4CvBZ4B7gbuDrwA8Y7xvgLuAx4N+BDRw+G5TWwHf4bZCDwG7Ad4F9ge8BBwHfB54D/AA4HngImAn8UJ9f8Deec7LKoPOLz2gD9DnPRY7Qxuso8C7g18AtwH8D3wN+CwSJzVK84bM5agNUwO4GAHgu/dPpv57+LfQ/CXQA/wp0Ag8C3UDMFSW9KuCsUm+tzjA29cNePGgfKNRZxuj+vvOMG4B3g3aDYjsjTaD/fCNzQOgzjkV4vhGkzzoGgIDj5zlrnHncffbxzz2GDgQ/MA84FrgJ6D8DOYqPrcxFmsFnIVV4dmxg9ZnIrEH25yLNBvvORgYCPwE+gLh5gxEOOgb/bvhxXnLSZyWfDEH9DUX4fKecm4wfiuegW0DbQdZzlH3wxw7znadkAIPPVPYMC32u0ng48v97lBmYDgp1zvLJ8JpnLS2Rp5YjUC8jan/ukpleffZyC2RuB+hdUHSZV6WBxoLKy/6/zl/CLuzCLuzCLux+DvcTnP+DzEuPT/7+/0QV3XBnJ6xPJpt3G4waOtw8X80y78gSnX4JPzMR68OA8FJkq7gIDKI/MMny/YA8g5vJPBscoBDWBOsq39nVsDFj5L7ALKaEvJTpM+mnkMLTQif+Brx/HyriB9yvE3qfwn4/okmO+fzbPXujd2W+lNv62iNfPjHg4aft9kHqfo/OqdoPov4d61raAGJB/TvL+jWG69dWXL92BKYC+3LdOoDr1hXA9HKvKgDptckPtMHP883Tf7D9/bLy8Bw27MIu7MIu7MIu7MIu7MIu7H55zgWa9OOu/wum5p0a3f/Mdlj7UfcpmbrY91PnYy3oMdP2ukjW7ulYs6s4rfOUP6Mka1pegB208C2ino0/XherLlJOYTl1nnR4FvWO/OHVOo8ZFh6mEaAffEGNNBjuS0Lrs/5deHpa9JYYj3pDUE2xpD+laFJxte7j+8J3pY6bFhT3EPx8N+PKyzV/nyD+w4E6UlOnWe5X/lL4inTcgUFxj+p3MS7L6edPD+IHqGodyJLSqVYdSEmHz4N0W9sX+2wREszv/uB5tBP6AvINs97RbWI8nmh3F60b3KKdL60KRZ0oi14j8i/f1fDzZlHfaUMt9Q9NXaUdWveJ8ka9pF1ar0lkSnhf1rpKWo6E9w3yWnWw92teygvTPaR5RQ6E97Dm1e1LvUetL4V2DNZ71O0TpKOI+g7SOUyn/fNuxO0IvBP4JPpdVbHud1nDeJl8qP7H/kb+4Vp294r/GurQGbDJMv1f497T1Gp5p1ywTzKNAdV3JYh/Nv24HXy62CRY5LCG/DCN3lqn9hnxr6Ef2taSxsCafY76sq8K/3KDfZzpnRuqn+l3jJey7bD2ccSz1Y1mvxsseqIvCN9qwz9ePC3+BF2vH0jazQPGAKZN3emQ/VLrO78nvNMMPSYExU8K6qf5M9hPtT4jvwHH/B2WuCmQN7elH+dNmcz3+nW+PxK+K4yA+zx4J/8IKdN++gPblekVF+WzjqnD+Yakt1B0WPd3lBsNoERbPf63kDQTJdwZ69OvLuVYkAbsgnGgHnWcS6FEVUaaYaGZoHKSOVZsqeU=
*/