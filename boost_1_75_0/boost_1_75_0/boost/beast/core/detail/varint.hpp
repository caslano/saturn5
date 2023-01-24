//
// Copyright (c) 2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_VARINT_HPP
#define BOOST_BEAST_DETAIL_VARINT_HPP

#include <boost/static_assert.hpp>
#include <cstdlib>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

// https://developers.google.com/protocol-buffers/docs/encoding#varints

inline
std::size_t
varint_size(std::size_t value)
{
    std::size_t n = 1;
    while(value > 127)
    {
        ++n;
        value /= 128;
    }
    return n;
}

template<class FwdIt>
std::size_t
varint_read(FwdIt& first)
{
    using value_type = typename
        std::iterator_traits<FwdIt>::value_type;
    BOOST_STATIC_ASSERT(
        std::is_integral<value_type>::value &&
        sizeof(value_type) == 1);
    std::size_t value = 0;
    std::size_t factor = 1;
    while((*first & 0x80) != 0)
    {
        value += (*first++ & 0x7f) * factor;
        factor *= 128;
    }
    value += *first++ * factor;
    return value;
}

template<class FwdIt>
void
varint_write(FwdIt& first, std::size_t value)
{
    using value_type = typename
        std::iterator_traits<FwdIt>::value_type;
    BOOST_STATIC_ASSERT(
        std::is_integral<value_type>::value &&
        sizeof(value_type) == 1);
    while(value > 127)
    {
        *first++ = static_cast<value_type>(
            0x80 | value);
        value /= 128;
    }
    *first++ = static_cast<value_type>(value);
}

} // detail
} // beast
} // boost

#endif

/* varint.hpp
dGmAS+bVe4lwAggfk5BZIrXgKn8HUgv6eBeoWBdYhgO+H7EvHbCPERz2ZRoOHXU9X/Hks+Io17olGtSP5VmZtJ1g12id8hLqbqFhc6aGvXf/kw2SFzNGzXItpthwkPxXMO5ypcpdhsfphSVGARbn+xVskfbV47NVP/8j9bjMERkROEfQMOCnbfqFmsMX6lJRehyxM69aLHx8HaEpTLO3nyitrVbJpoYMWLxigvkdR3auXYcLD29TkTkCF7ooN+qR+elchgsVUbhQvZj66Lxb1zc9bjucv4XbF23DmuEH4cQhXJ05pHfB6UPsIQUE6jelw4Qc5VJbQW+kwjT1bskAU5x7urG058HS05+UKu/ZlXU52F0UtsaHEuBvhtbZv23tDOL/9+WxEf+QjzpbrMd/lSBNdWgdzXVL7+EMojaKZANYfqtXcqIEcyrFYX9QXT9jHvJie0D+g7m5O0cDKU3NiYCt+jkOGvcOXPWzoggrfaNCF4vAPWGPxEAPzJ2u5sY5AxyvY+gKHflmCOtICXZkZg2OwPNVJuGfU4TklbBF5i1mPIQmj6ideWhEuDN2qaV9f3xmrGuKWhdwr9Fde36uvmvJ1LVQKkGOGQLJ7frpP2fwqZ1NY531JsB+YtX3qLvWI1iXZaxb0JO5PtQNtetH7fBO9WPtlo77kfp/0w/34Jj9eM4bsx/n7J3qR91bHfdjQtn/ST9WXxazH0cW
*/