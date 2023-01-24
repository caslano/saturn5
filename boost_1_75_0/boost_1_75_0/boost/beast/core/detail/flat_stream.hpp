//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_FLAT_STREAM_HPP
#define BOOST_BEAST_CORE_DETAIL_FLAT_STREAM_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdlib>

namespace boost {
namespace beast {
namespace detail {

class flat_stream_base
{
public:
    // Largest buffer size we will flatten.
    // 16KB is the upper limit on reasonably sized HTTP messages.
    static std::size_t constexpr max_size = 16 * 1024;

    // Largest stack we will use to flatten
    static std::size_t constexpr max_stack = 8 * 1024;

    struct flatten_result
    {
        std::size_t size;
        bool flatten;
    };

    // calculates the flatten settings for a buffer sequence
    template<class BufferSequence>
    static
    flatten_result
    flatten(
        BufferSequence const& buffers, std::size_t limit)
    {
        flatten_result result{0, false};
        auto first = net::buffer_sequence_begin(buffers);
        auto last = net::buffer_sequence_end(buffers);
        if(first != last)
        {
            result.size = buffer_bytes(*first);
            if(result.size < limit)
            {
                auto it = first;
                auto prev = first;
                while(++it != last)
                {
                    auto const n = buffer_bytes(*it);
                    if(result.size + n > limit)
                        break;
                    result.size += n;
                    prev = it;
                }
                result.flatten = prev != first;
            }
        }
        return result;
    }
};

} // detail
} // beast
} // boost

#endif

/* flat_stream.hpp
/tU0/m1u2QfsG09NO7Z8g1yr7q0HHxG5TAGRDhJxyYjY7EUBE9TFadRHNSf+BjI9uBqZtNqdymLoN00BRmEIMjKkuu3+NxaIxAHpK0nLl2qGvB2G2napDCuVmStrFWS/anWWXokOtjyl/ab4545cO9Ji6bOZVa2RSTQvw2L3vQXRisc/6Tiv01j/gW7Oev5aAs6gBU5TIqo37Dt2XRyB+jTm07OYaMVXOalRS8FSZMN+0+/b8XJ/rNBCcpnf4otJFmyYCB0dc2wVBmQFUFd48HZQEfR46fPHGJmEhdlKzdFJC8eWxVmdvxE0YMdvRWVc2C6EU6+B2PTkwkzRC+YfyCOBJWlDjTwAYVqEzY7VmiIBgQTCiI8oecLyfE8z4GIZu7OFgpVoaDT5z0c52xjsOXqNQXBRs7D26jOlNg+FNH3DAuNgWcPMQF32JI+rf8Dd1vfhSaks2vWEyebXIFKGy4/ucGG9+AnxURnfv31Fd/Pq4SArzNOWz2tBcQTibpRZ8Gl1qmA3akQAX/ifFnZ2GOryaNd/KZZRKSbc2MFUaGRvUY278R4bM9L9rDUs+KtHULYax89JfJtVVJsNaHBIXtuJHzR4T37wqq0OlrTESgulEwNzfknoWxR+bDT1Z6XKIiTBJiF26SFldrqIUwgd00wZGbrbYz8vJQHmAhEn5HaDo9TQ4FrJubLC8FjRuXKRK4qgN1ZYK4qOdFTJ
*/