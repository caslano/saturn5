//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_READ_SIZE_HPP
#define BOOST_BEAST_IMPL_READ_SIZE_HPP

#include <boost/asio/buffer.hpp>
#include <boost/assert.hpp>
#include <stdexcept>
#include <type_traits>

namespace boost {
namespace beast {

namespace detail {

template<class T, class = void>
struct has_read_size_helper : std::false_type {};

template<class T>
struct has_read_size_helper<T, decltype(
    read_size_helper(std::declval<T&>(), 512),
    (void)0)> : std::true_type
{
};

template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer,
    std::size_t max_size, std::true_type)
{
    return read_size_helper(buffer, max_size);
}

template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer,
    std::size_t max_size, std::false_type)
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    auto const size = buffer.size();
    auto const limit = buffer.max_size() - size;
    BOOST_ASSERT(size <= buffer.max_size());
    return std::min<std::size_t>(
        std::max<std::size_t>(512, buffer.capacity() - size),
        std::min<std::size_t>(max_size, limit));
}

} // detail

template<class DynamicBuffer>
std::size_t
read_size(
    DynamicBuffer& buffer, std::size_t max_size)
{
    return detail::read_size(buffer, max_size,
        detail::has_read_size_helper<DynamicBuffer>{});
}

template<class DynamicBuffer>
std::size_t
read_size_or_throw(
    DynamicBuffer& buffer, std::size_t max_size)
{
    auto const n = read_size(buffer, max_size);
    if(n == 0)
        BOOST_THROW_EXCEPTION(std::length_error{
            "buffer overflow"});
    return n;
}

} // beast
} // boost

#endif

/* read_size.hpp
W1ijatOUcW9Drr9MMvNLIF9kNCcGGdxjrlhCu50/c3cDQZP36BQsJROBuFUnPqhgiNoL7lZz8/DULM2OR5wk/jfK3QN2RiEb/Azr4KIg+wgZML1PMaapxE2ZoGBh62jtzhhrc3t9Y5jJHX97VE+wt9fRuw45M07+LONh+u/Hj8JMOV5YkVamGNnahZ2D0pcTl7ReEjRickdvIOSEB5FGAIbEjLJqCpZ0nlc6Nwp9nkmj+5AVzsvDBrcNItpWM0Xj4V8DMwRLAO3Q00KVsU2e+t8bJ8uPGjIbduzCSbHGkAmKVrUjthtWhuxqXBGJrBkQhqVfZB1/cw+G8p0dHHHA7Wgafm3miBeqpvBkBfc52C9+0aBFx+f49ZuVchD+6Fkv53ZdHycPffh1qKwSc+Ov/h6n2t708gzopKTF7TajulTwqp2d1Sw6sSd9S+GmMqDgc8gjcmk/A97LGHpmuXZi4wAYpalFsGXUtoe6Y4TPdX+MAF1xyO46EEXEgzq8/CPQiuxZwThGPKyRX+FFGkjOWFjRGFyoniEQL8lHNAb2n4HmmGNw61ZX/rsPEA==
*/