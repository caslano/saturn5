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
SehAdorcOuATF76MYfv4s1rn7zY+WCw4RfdSEa2xjwSBRpeSHjgT1Lf8hngZWW7n9DGzfzN2xMWYHgn4v/RJ+n/P69m+cbL909hRywxkYm9r9o9OOB+aw/fBWEHltpfrGjhCk1vvn0wxotn6sl8YhWb8EqikfvuCPmyUrF2PZaVfpr9/DkRLvTVLDMxQ32f6bfRPhF1jcCQMEr0kG9vGRruxbdu2bWuSiY0vdrJJNpnsxrZt2zY3xsyx6n5dXdWr6qr+2/2nX71+79BdZ1ufQVQR1xH2S/9gSi0MElQIkzl2K8bOmpzspYf5yF+bIXc2NSd/tCuW4OWUjUi1sn8FcbiU2bSDOkAgnyej0+xb5Ym99yAYOTvYn70ndSiySrZU0Lrj0IO7N4Uj5mxdfE/PnjKlMxjUixvURTJUGZondghnCIQI2QgWGMOU8RIELK6pGk8UV0AVCHCB/9ZsWRROwLdOs4huDRclmzaMrfvkVwJAwIHRAZjuk/ltP6P7bq9e5B0oh6KLvj21Ea8KC1U+cmnZqPMV3yCZKr3Jdne43Qfh7Y/o+YFH5IAHXShjTPsBMYORVRxjHOmAsXshJx61uI7i85jrmc5XxQU/t0rGNmemZtLmpBxw9EoPQRFvNzidgfiKbOOAQd8pTvprWKXabKES+TD1G43O1XNSonCRcMz6ouvZQiO9EQgSuLF5L5VhwxTlJJVxZtXTMk2M
*/