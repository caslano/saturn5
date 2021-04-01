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
NJGQ7tSQfuUK1tfbZ2B4akR0eS9SJKPizGtFIud4w4LJq6EBbQuscE/Pjmk8Oqh6kE0Z7HBcoo4p92OAfz2AWmipkaIwK2nK6xQpUDal23uuLCApaWYDtrIfFGOxA5ZuIv3qjEt/bzmIJseE4Zb0+hdoHBxWSfgLAJacJvXhKyhPRjGfuRldB+oRxmJtpHmHHbmm/DlwaaBqSpLCag0r53ZKyBM+2m9nDGBA1EGCJss5pbOP245qszVijjo3y8AhbG8zcYxZLxOgbsG0V3ILMUG7Na9HwXeZM2406rLvNYELpl6PUm675kqeU5F6JEpMe2wLEXjkF2oAkdGrAzElAnxxM/QwJvgkc5KtXkRVh1AR8u2c9TeEv7LOPAaJfBaa8OEHJAO+pvqtCx2eY9Q3Z7WcaPacSjZNpIOVMW5LaRbJ7lNM5RF7irJlreuw8HSlw5Ox8t4Hp830VPlo2ZQRpGmOyA4Xy8Wq7N4rgCnbO2dIePMsdpghV0iu2JwdRFb5jPjH6yObD0Jz+mXFyxAqXxicb38XRDkEm08dwGpnUBGP91BcAUScSVD6Lw==
*/