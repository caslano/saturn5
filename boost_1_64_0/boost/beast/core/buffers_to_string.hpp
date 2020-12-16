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
G4s3mLm0ibXKjCtzd4ms5H+88D5pm46/y2w2jntWmolK3vT57jqzH0n4AttRH/vvPE9GwiOUfD4m7km2Fz3SbFgPxWQ1B8qabfLcCfcidWZNk/jFGU7EKTH7l/Z+AoeyFVEym+dNcBw/Iff7mzEX/yw7QgfF7xEjA35bwWvKSRxkKwTznDja2gjXbG18xLmKxTe8p5pPb4P1ccX3kBdfMfjiTb5erX9xBMUpvlLyxZKvBXzhwnfJEDX3Jo9luwByqejDaN2tzuwS7E+bqey33u94ql22SB2kdzrftvp7nvCvRW9P7bS/O/lcqJKx3S3jTj4bqsXfLb9OPh9Wib+STY++v0/+Ym7Jvr8TlGbax5/j2c8aq9eug/ag97ivbOO0Cv+ZCA9ln7PSiA405jN8tPfYrt7NHpHw5ZCmSP/jNceiTRgrapCnPpSxCE3GHrPmzOTbHm3J2AJv+VI8R6Ktd7blRlfe2V6e4/nO9jtxR2lj/8m9g33XjI87dzY3v2KO26Zm/lf0nDDnC+/N0d7VNH3w7TxbYQhlJxV0JXjyCkR2OAXlfBF1d2iY73wBvEqf62u6zqkKi1Vj5nxxx3f6HLHeRXA/q7xK7/Rr2rxoeYE2D9J0not7q7Px5MK9RJ+ngeXSp9a6HY4wV78YUWao8jFOnB4+0gqfI+Gd2lqe6qurI/fw0tWRdD30nRPilD6tXPGgN1DWdj/lQDMFaiPyO7U5fZWmj6TCu1wGvV1YBs5hJV2PtngvzlcnuM3UCS6wdILdrzxYBVTneBT40wVmPiNZTiVrWpgaN05CD7jAV7+ZZazyKMv+eN+yXIK4x3zKQvMFHZTlmNYmF/vaL0D4qdsvKPCj13yxZr9A19l+0elbpqvAG32O/zKJc/rcKQUFgcuGuKps27N83zn1cPRn73d8Fa7exb5k2ZEHj3euPDWO4L5e8lrTx7c+NoE327c+YGZvXWNHbZztVY7WtFMrhz4mhCT45u8K8Bb55s+cMATKG/hP3daEnjddlvb4ydsW8Db45m2Vrv7fUR02eOXzki9Rh1YbtyT65rMZvG0++aRJjA7yhzhqTGrUn38Sduo2MfyNSY1+bGLkJ/mWZQf42n3LglctVzmu9WMTo13rkzf42sRA+KnbxLjWj02MGwLYxDia5F+GDvqWBzP3strm6rVNRkfPDK98X3Ya5Gd/X//PtGM+eVRmOwLlD3ECPtMQduo2Ozp6pul99rpk37JchrjRhT5laepqn0Xcjmx2IPzUbXYUdMFmh9U3svsZcqWxXEmgUsTPdpVNm8DLUCn5LZHyNGi248iPVNzvAp2vhVj5LZH8Ij0vGYroz/3lJi9xM3jLmTe+LEjOOJtQ71k2fgNj/hhnsLIVd6W4Q1V+nekgj/df9Y1Svfe2SJzeXS6XayySfHi8Uxwe4GK+GtQbtAV0PXh3Fio7ClLvmHZrMl9Bm8PQoxC+euwf7IE3xzCWyYrfl3E0mwAqLEGd9bhf3BuwnhhirMQv3zUa2q4XvtVIdbo6V++E+I1FzAzX9yOznQZY75zDfN85yVM8wHrnHNOld87XCvV3Tt6XZ7J19T3z+cKufevr6fE+VeE1HqyQd6njZlpcg9D7UAPPYljG73kloG+acjrXsz1pQs+jTZX9POE928jR7efN1e3n+bbNHRLeFznppc40uU38EtE2MdI2b6HOb02x2qa/b9uQ51iK1TZDu9Q2l8/1bJt7xd1DXw+AHb2urwdsnHuq7TQ+5iYzLteM9OfkkYG+4/Yt4DniapemNa4xe+bCwmkLXKcOrccQoq/ddT7m6uNVa6rv/Vqy8KfI935qTQ31u0HGq6Y12vOBcZzu9upCXqxxZ4M=
*/