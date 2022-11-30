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
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
*/