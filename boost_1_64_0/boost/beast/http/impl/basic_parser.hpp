//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_BASIC_PARSER_HPP
#define BOOST_BEAST_HTTP_IMPL_BASIC_PARSER_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/make_unique.hpp>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest>
template<class ConstBufferSequence>
std::size_t
basic_parser<isRequest>::
put(ConstBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    auto const p = net::buffer_sequence_begin(buffers);
    auto const last = net::buffer_sequence_end(buffers);
    if(p == last)
    {
        ec = {};
        return 0;
    }
    if(std::next(p) == last)
    {
        // single buffer
        return put(net::const_buffer(*p), ec);
    }
    auto const size = buffer_bytes(buffers);
    if(size <= max_stack_buffer)
        return put_from_stack(size, buffers, ec);
    if(size > buf_len_)
    {
        // reallocate
        buf_ = boost::make_unique_noinit<char[]>(size);
        buf_len_ = size;
    }
    // flatten
    net::buffer_copy(net::buffer(
        buf_.get(), size), buffers);
    return put(net::const_buffer{
        buf_.get(), size}, ec);
}

template<bool isRequest>
boost::optional<std::uint64_t>
basic_parser<isRequest>::
content_length_unchecked() const
{
    if(f_ & flagContentLength)
        return len0_;
    return boost::none;
}

template<bool isRequest>
template<class ConstBufferSequence>
std::size_t
basic_parser<isRequest>::
put_from_stack(std::size_t size,
    ConstBufferSequence const& buffers,
        error_code& ec)
{
    char buf[max_stack_buffer];
    net::buffer_copy(net::mutable_buffer(
        buf, sizeof(buf)), buffers);
    return put(net::const_buffer{
        buf, size}, ec);
}

} // http
} // beast
} // boost

#endif

/* basic_parser.hpp
yX8VtFzi/yZy7GvKS+L/RD4m/gZuLe5dwL/AAvBvsA70kd58MA48FowHTwO7gGeBieBycCPwDjAJbAW7gq+ByeDXYCq4u49xFmwCe4EngRngUrAfeDPYH7wbzATvB7PAh8Ah4HvgCClfmbVnCbxI5NMVnCbl28OsD3ASuD04GdzR9AcngFPAvcB9wZniXgROBZsl3PdgviF7eoDbJZ8u4BjJ5wTk1B1cBI4ETwS3EvdN4rb62xpJJ94X2t8WEy4TPAXcDjwVLBD3Z+L+Wty/iFv4k/0VtBlfKH9nEG4EeCaYDzaDU8Q9wqfcIk/ZewDOc5Hn5XJ/1lXgFuDV4JbgjeC24DJwD/A6kef1YCV4g/S7G0WeLYbsBwDvlHzSwNMkn5Mkn1Mkn1Mln0sln9PAieAZ4D7gmeBssBmcC54DHgcuAU8BzwWbJf654AXgZeCF4HXgJeCt4i9ywLbfu13lSbvaSdrVztKuxkm72k3a1VhwprgXgbsLH+MknzpDbN/FJt7MJ0WtTMu9ez6/HLqDW4Bp4JZgP3BbMB28AewJDjD7E3gW2Bs8D8wAe5FuX7Af2E+3F7FhBSe4tOccwvUFNwM3AbcEc8AtJF/cko7YoYLjXdI5R/hfAg4HzwVHiTtf3Fa/aJJ0rnR5D7WY/IMXSL+6ENxZ3MeI+xRxt4jbf7+i2A+KvWRh0P2Klwo/l4GvgEt1ucS2DhzjUq4rfdIPpF9dDY5WbukXtnK1SjqnupRrmZTrOol3PbiDuKvFXSfuY8Ut5RLbJt5dLuW6Wcp1C/gwuFziLYCw43G8V1P5u1bi/RDnH8d+BvuAv4KTwd/AR8HfwafBP8DvQDJV7z0fGAcmgElgHJgKxoM95Hdp72K/or5NQtr7VJHjbHBr8BBwT7AWnAXOEXnMBevBeeCFYB14HXgoeB9YD/4BNki5F1t2IeBXIq9u4ELJd6b05/2kP5dIf66R/lwBTgHLwGlgOXig/H4OWAm2gNXgFWAVeI24W8GDwPclve/BbMvuAIwXfuJs640LCWfi0bbwS9cR/jAJfzhotbvlEn6JS7u7Rb6bbgdHgXfI+HonuDN4D1gH3gsuAO+XdIsMWeOWte/CoHPeP5Vx+wuR51fgMPBrcATYBo4Gv5Fx/VtwjPyu77OU9K+W9O33SI6RcWkb6SfbgjuBu4N7gHngVHB7sBTcAawCdwRrwJ3AeeDO4OHifwqYD54r6ciZpazfdt558y3QSknvCZf33b0SfyXYD3wYHAI+Am4q6W4m7u3AJ8Ay8BlwNvgceDT4PNgEvgieBLaCp0j4FuHzAUnvYXHLeCfrrIztLuPd38IfAZoyTAAHgHFgDhgvcssyZP0U2EbS8YG9JJ2/dH746XCh+SXK+LqRjI9J4HCwK5gLJoPSHmW9kjp1aY+HyHhWK+PZHHAgWCft/lBwM7Ae3Erc24nb+v5uk/QzXb6/j5P2fjyYAZ4A9lduSx6yngiOcJFHk+5X+Em4g1zKMUHksYe8JyaCO4KTpN3vJePj3uD+4q4Qt9WvWiX9s1361UDpV4PAYeBgkXMmOBHcBNwHHAJOA4eCReAw6WfDwYPFfyGYDZ4AbgqeLm55b8maEvXt8t660LpKFkwAL7a1l6USb2eX9tIs8c4B48AlYH/wXHAn8DxD5GytWciaTWHQfcR3yPf7vSLn+8E88AFwHPigyPshcG9wJVgIPgwWg4+I/B8FDwIfA2eDT4AN4NMil2fAJeCzYAv4gry/WsEbwZfA+8GXwUfAV8DHwdfBF8E3wNXgKvAT8C2ZH7wNfgGulnnCu+DP4AegWegPwS7gR+BW4CdgHvgpuDP4GbgH+Dm4L/gFOBX8EpwOfg0=
*/