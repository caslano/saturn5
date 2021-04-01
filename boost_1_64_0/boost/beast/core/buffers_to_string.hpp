//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_TO_STRING_HPP
#define BOOST_BEAST_BUFFERS_TO_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/asio/buffer.hpp>
#include <string>

namespace boost {
namespace beast {

/** Return a string representing the contents of a buffer sequence.

    This function returns a string representing an entire buffer
    sequence. Nulls and unprintable characters in the buffer
    sequence are inserted to the resulting string as-is. No
    character conversions are performed.

    @param buffers The buffer sequence to convert

    @par Example

    This function writes a buffer sequence converted to a string
    to `std::cout`.

    @code
    template<class ConstBufferSequence>
    void print(ConstBufferSequence const& buffers)
    {
        std::cout << buffers_to_string(buffers) << std::endl;
    }
    @endcode
*/
template<class ConstBufferSequence>
std::string
buffers_to_string(ConstBufferSequence const& buffers)
{
    static_assert(
        net::is_const_buffer_sequence<ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    std::string result;
    result.reserve(buffer_bytes(buffers));
    for(auto const buffer : buffers_range_ref(buffers))
        result.append(static_cast<char const*>(
            buffer.data()), buffer.size());
    return result;
}

} // beast
} // boost

#endif

/* buffers_to_string.hpp
1I6K+ladZXGs8DiLyrfsunCZPzeX1WRWw0a/zI9uUSXU62Wvi9km1bqpoLa1ogV5aJJX4PCyfkuOLB/Bekx4imZ2diLHhldnsKqkx+4HoppY2v5zyfM3lQQu967YnDtRcRlV7fLPC6jExdnVpN72+TbwuL4KDDVEuhDo1hdBQwY6JYgBwIdn7x2X7XFiohGbOy2P0MsiV+J9WBoP4SPJn72bcCmbhZq2BZ5Tu6SPDQMk3/epGdZDV20GpGNbGUumtuT2t1JKuxBZ7hEUnpM+mruq1y7KBFZf8H0KZjagZvqRHcW3FahFel0aeUIbhLowjZJs6haAGpF5TyPboIF4MTvVwjq0rPVbfoxGoPLQJ8b98nD3KFIq++9P2chzpvshzo6r4l6EUkNeowzjo6w1BruqQvSHoeXxeTMmRNicJkNFHT+f9Ajbj63sdPcMXvONyuyU3lvCUbNGyRdumcWKOk5SMJoTghvEdy8SeGXy/Y6VGOmuMmhK8kHjq7i7X/Lrmn1OjPH172mQ+hHxnHkgUQo4WnpmGCw+iWedJFKltoOxQpfadNnpDEYJhQ==
*/