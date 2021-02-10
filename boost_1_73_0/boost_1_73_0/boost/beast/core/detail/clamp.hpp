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
xCRYFg7+k0ryDbsRdM9YmH1kCNLofLM8RLYTe+OlQuhXmFUbx9C4RhdlyshOXQneLOXH2icd+UmHqMU1B56XPOr8D1BLAwQKAAAACAAtZ0pSPByJ/WgGAAA5DwAALAAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZnRwdXBsb2FkZnJvbW1lbS5jVVQFAAG2SCRgrVZtc9u4Ef6uX7FVpx1JZaTkPvXil6nOllPNqZJryZdJmw4HIkEJPRLgAaBkt8l/77MgKct2LvF0jh6ZErD7PPuGXYwGv93ToQF984nDJ8aDd9C4tubfMvFflo7jT1T/Qesj3t8iGdGDyqe4T99W+US9oBI3LKf8PY6/RfSRbeN/I9b8GPNXrECNNS9MeW/VZuupd9GnN99//2d6Rd+9/u51RJdCK5nT0ku9lnYT0WkaVv6yFXd3QyfPI5KeRD5soFZb5ciZzO+FlYTvuUqkdjIl4SiVLrFqjR9Kk99KylQu6WJx/WE6fxfRfquSLYPcm4rc1lR5Sluxk2RlItWuxiiF9WQyqAM8Vc4DsPLK6CG4JXlpC8cYTC9yZ0jshMrFGkTC09b70r0djZLK5rB+lJrEjZLW/eHWFwdPPsCIQtyTKT15Q5WTEbFkRIVJVcZvBASLZbXO
*/