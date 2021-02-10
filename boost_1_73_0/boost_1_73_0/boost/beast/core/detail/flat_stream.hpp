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
mCPbkTejOtkjpunWuQ1G3eLI19cRdPu9sWnIAtvFozY3G9zYXmjVcnJz/R6Xg27QeosRiEgec83NnlwpE1yiaI/KETrU/u31bDG+rM/DC6mCRkRvZkfoR4joY2QwfM1ehz6KG5RO+K74Qvybyfjy6nZ+sZou5tHjTnxEWBrUIF/CTAgev5n0/yW8HK/GEf2xztMRDRcHWsPawKlUrqsNWHxZYULmAHxpzfw0uflhsZw8idmyKUZc5PjCkrZ3K24JwxciT+dX09lkOf3HJJ6Nb95NfqU0g1Zssiz2/SeN58iga2lRf/Ut2PK9wPko9JPQdDaNuYf+mx7cP+o5wdSyBqrP4EkL/+U+88VO03jx5U7ziOKrreZrzaa1SuR7ce8oQT51VT4Pe7Px4MvnpvW0Ha8VCJsP8/hz539QSwMECgAAAAgALWdKUgbrSUtMBgAA+RAAACsACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2Z0cHVwbG9hZHJlc3VtZS5jVVQFAAG2SCRgrVdtc9pGEP7Or9jQSUYQBZz0S2O7aQjICRMCDOB63PGM5pBO1rWSTqM7GbtJ/nt37yReHDeGTMjEiGNfnn12b3fptn/eqwFtePTlm/8+vvDdaEwL+TcP9MPSvv8F7D/U
*/