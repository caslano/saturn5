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
N/p1SJRfXLrECMiI8jyZP6ThZJqJxnlTHP35z38SB+JV51XHERdeHMpIjDIZ38l04og3AY/8dep9+9ZW8tQRMhNe1DasbqehEioZZysvlQLXUejLWMlAeEoEUvlpeIebMBbZVIpxGElxPrj51Ou/dcRqGvpTYvKQLISaJosoEFNvKUUqfRkuNY+5l2YiGYMczINQZWC4yMIkbkO2FJlMZ4p4kHgvUonwll4YeXcQ5GVimmVz9frw0F+kEbQ/DBJfHfp2+e1pNstX8glKzLwHkcwzkSVioaQjaKYjZkkQjukvDILB+eIuCtXUKbSBqDg4TFKhZBQRL9CFUmm1pRgZ8zg0TcyhcZjRH5XEikStpsmsMhF2JC7jRRpDEOyASUECMztiEQcy5cm8civC2JQNvNM1hb6BSGIoI+pnI9Eb1cWdp0LliI+9278N3t+Kj2fD4Vn/9pMYXIqz/idi9q7Xv4DrQwhLhfw2T6WC8FSEs3kUysDI/O1+DmuHLfHmojs6PyXxs0WUhViMf4/oC2Osfez5sEEykazRCooh9O7kkma/ObSEzKb7zYOWcNIcuvoeBQ9YLVIw8JNAwtVhPGEz7hRDXINkFUeJFyBK4ge2tKIQS2K/anJpxI2lly1gJ+asvJlkM/twa+yTDl4U
*/