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
SCIIOxmqo1uU1yGo/ZVTzGPdky3xfslquMi5m8gZIeGvDgstOeaxqGO43gYWY2498AXBX1623NUZ0fczlgQTMep7OQq0k9r2Hh40hH2nL3Wb35DiWLeF87b5niRoYKstscZzLzDEfpkJ/DLqf5uC9vHeWGzRjm0gkvsOkF0wTV4oENxJM4UnvJnNS/+lzWP77tW/mWU4ltbEB1PZ6GA1mW4F/nswixJoB5KRj+CFu/abqI9y59h3VnjLLOgDhmadBhlDZcGL7tXAgyxxWOc50+JLNatzwiubBCHmMfEZJvrxSfFDa5b8jyY74XwEiZloyuWhbYR6TTbUqr2OOtYiH6w5btsUOBmKmgEhgnhh/IdBlgC+sLeJVHd2nMhZFl1HGNO8pxTHQSGqkkIl4br9VUOKiy/1cYx5RKBSBSBFVFBGJQoUhuma1JUAkx+Pvql9oywpDwoyx2oJcXE+4fYGICWKAvy/19Oh9P14PL0h27eUWkL9EGBEabsyg+zeALPNJwzZci4t/2jWdFaVViG5TztrCYKapLUcuBlikTIsowJynRi9SIoQLWsKzg==
*/