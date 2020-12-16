//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_CHUNK_ENCODE_HPP
#define BOOST_BEAST_HTTP_IMPL_CHUNK_ENCODE_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/varint.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/detail/rfc7230.hpp>
#include <algorithm>

namespace boost {
namespace beast {
namespace http {

inline
chunk_header::
chunk_header(std::size_t size)
    : view_(
        size,
        net::const_buffer{nullptr, 0},
        chunk_crlf{})
{
    BOOST_ASSERT(size > 0);
}

inline
chunk_header::
chunk_header(
    std::size_t size,
    string_view extensions)
    : view_(
        size,
        net::const_buffer{
            extensions.data(), extensions.size()},
        chunk_crlf{})
{
    BOOST_ASSERT(size > 0);
}

template<class ChunkExtensions, class>
chunk_header::
chunk_header(
    std::size_t size,
    ChunkExtensions&& extensions)
    : exts_(std::make_shared<detail::chunk_extensions_impl<
        typename std::decay<ChunkExtensions>::type>>(
            std::forward<ChunkExtensions>(extensions)))
    , view_(
        size,
        exts_->str(),
        chunk_crlf{})
{
    static_assert(
        detail::is_chunk_extensions<ChunkExtensions>::value,
        "ChunkExtensions requirements not met");
    BOOST_ASSERT(size > 0);
}

template<class ChunkExtensions, class Allocator, class>
chunk_header::
chunk_header(
    std::size_t size,
    ChunkExtensions&& extensions,
    Allocator const& allocator)
    : exts_(std::allocate_shared<detail::chunk_extensions_impl<
        typename std::decay<ChunkExtensions>::type>>(allocator,
            std::forward<ChunkExtensions>(extensions)))
    , view_(
        size,
        exts_->str(),
        chunk_crlf{})
{
    static_assert(
        detail::is_chunk_extensions<ChunkExtensions>::value,
        "ChunkExtensions requirements not met");
    BOOST_ASSERT(size > 0);
}

//------------------------------------------------------------------------------

template<class ConstBufferSequence>
chunk_body<ConstBufferSequence>::
chunk_body(ConstBufferSequence const& buffers)
    : view_(
        buffer_bytes(buffers),
        net::const_buffer{nullptr, 0},
        chunk_crlf{},
        buffers,
        chunk_crlf{})
{
}

template<class ConstBufferSequence>
chunk_body<ConstBufferSequence>::
chunk_body(
    ConstBufferSequence const& buffers,
    string_view extensions)
    : view_(
        buffer_bytes(buffers),
        net::const_buffer{
            extensions.data(), extensions.size()},
        chunk_crlf{},
        buffers,
        chunk_crlf{})
{
}

template<class ConstBufferSequence>
template<class ChunkExtensions, class>
chunk_body<ConstBufferSequence>::
chunk_body(
    ConstBufferSequence const& buffers,
    ChunkExtensions&& extensions)
    : exts_(std::make_shared<detail::chunk_extensions_impl<
        typename std::decay<ChunkExtensions>::type>>(
            std::forward<ChunkExtensions>(extensions)))
    , view_(
        buffer_bytes(buffers),
        exts_->str(),
        chunk_crlf{},
        buffers,
        chunk_crlf{})
{
}

template<class ConstBufferSequence>
template<class ChunkExtensions, class Allocator, class>
chunk_body<ConstBufferSequence>::
chunk_body(
    ConstBufferSequence const& buffers,
    ChunkExtensions&& extensions,
    Allocator const& allocator)
    : exts_(std::allocate_shared<detail::chunk_extensions_impl<
        typename std::decay<ChunkExtensions>::type>>(allocator,
            std::forward<ChunkExtensions>(extensions)))
    , view_(
        buffer_bytes(buffers),
        exts_->str(),
        chunk_crlf{},
        buffers,
        chunk_crlf{})
{
}

//------------------------------------------------------------------------------

template<class Trailer>
template<class Allocator>
auto
chunk_last<Trailer>::
prepare(Trailer const& trailer, Allocator const& allocator) ->
    buffers_type
{
    auto sp = std::allocate_shared<typename
        Trailer::writer>(allocator, trailer);
    sp_ = sp;
    return sp->get();
}

template<class Trailer>
auto
chunk_last<Trailer>::
prepare(Trailer const& trailer, std::true_type) ->
    buffers_type
{
    auto sp = std::make_shared<
        typename Trailer::writer>(trailer);
    sp_ = sp;
    return sp->get();
}

template<class Trailer>
auto
chunk_last<Trailer>::
prepare(Trailer const& trailer, std::false_type) ->
    buffers_type
{
    return trailer;
}

template<class Trailer>
chunk_last<Trailer>::
chunk_last()
    : view_(
        detail::chunk_size0{},
        Trailer{})
{
}

template<class Trailer>
chunk_last<Trailer>::
chunk_last(Trailer const& trailer)
    : view_(
        detail::chunk_size0{},
        prepare(trailer, is_fields<Trailer>{}))
{
}

template<class Trailer>
template<class DeducedTrailer, class Allocator, class>
chunk_last<Trailer>::
chunk_last(
    DeducedTrailer const& trailer, Allocator const& allocator)
    : view_(
        detail::chunk_size0{},
        prepare(trailer, allocator))
{
}

//------------------------------------------------------------------------------

template<class Allocator>
class basic_chunk_extensions<Allocator>::const_iterator
{
    friend class basic_chunk_extensions;

    using iter_type = char const*;

    iter_type it_;
    typename basic_chunk_extensions::value_type value_;

    explicit
    const_iterator(iter_type it)
        : it_(it)
    {
    }

    void
    increment();

public:
    using value_type = typename
        basic_chunk_extensions::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category =
        std::forward_iterator_tag;

    const_iterator() = default;
    const_iterator(const_iterator&& other) = default;
    const_iterator(const_iterator const& other) = default;
    const_iterator& operator=(const_iterator&& other) = default;
    const_iterator& operator=(const_iterator const& other) = default;

    bool
    operator==(const_iterator const& other) const
    {
        return it_ == other.it_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*();

    pointer
    operator->()
    {
        return &(**this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        increment();
        return temp;
    }
};

template<class Allocator>
void
basic_chunk_extensions<Allocator>::
const_iterator::
increment()
{
    using beast::detail::varint_read;
    auto n = varint_read(it_);
    it_ += n;
    n = varint_read(it_);
    it_ += n;
}

template<class Allocator>
auto
basic_chunk_extensions<Allocator>::
const_iterator::
operator*() ->
    reference
{
    using beast::detail::varint_read;
    auto it = it_;
    auto n = varint_read(it);
    value_.first = string_view{it, n};
    it += n;
    n = varint_read(it);
    value_.second = string_view{it, n};
    return value_;
}

//------------------------------------------------------------------------------

template<class Allocator>
template<class FwdIt>
FwdIt
basic_chunk_extensions<Allocator>::
do_parse(FwdIt it, FwdIt last, error_code& ec)
{
/*
    chunk-ext       = *( BWS  ";" BWS chunk-ext-name [ BWS  "=" BWS chunk-ext-val ] )
    BWS             = *( SP / HTAB ) ; "Bad White Space"
    chunk-ext-name  = token
    chunk-ext-val   = token / quoted-string
    token           = 1*tchar
    quoted-string   = DQUOTE *( qdtext / quoted-pair ) DQUOTE
    qdtext          = HTAB / SP / "!" / %x23-5B ; '#'-'[' / %x5D-7E ; ']'-'~' / obs-text
    quoted-pair     = "\" ( HTAB / SP / VCHAR / obs-text )
    obs-text        = %x80-FF

    https://www.rfc-editor.org/errata_search.php?rfc=7230&eid=4667
*/
    using beast::detail::varint_size;
    using beast::detail::varint_write;
    using CharT = char;
    using Traits = std::char_traits<CharT>;
    range_.reserve(static_cast<std::size_t>(
        std::distance(it, last) * 1.2));
    range_.resize(0);
    auto const emit_string =
        [this](FwdIt from, FwdIt to)
        {
            auto const len =
                std::distance(from, to);
            auto const offset = range_.size();
            range_.resize(
                offset +
                varint_size(len) +
                len);
            auto dest = &range_[offset];
            varint_write(dest, len);
            Traits::copy(dest, from, len);
        };
    auto const emit_string_plus_empty =
        [this](FwdIt from, FwdIt to)
        {
            auto const len =
                std::distance(from, to);
            auto const offset = range_.size();
            range_.resize(
                offset +
                varint_size(len) +
                len +
                varint_size(0));
            auto dest = &range_[offset];
            varint_write(dest, len);
            Traits::copy(dest, from, len);
            dest += len;
            varint_write(dest, 0);
        };
    auto const emit_empty_string =
        [this]
        {
            auto const offset = range_.size();
            range_.resize(offset + varint_size(0));
            auto dest = &range_[offset];
            varint_write(dest, 0);
        };
loop:
    if(it == last)
    {
        ec = {};
        return it;
    }
    // BWS
    if(*it == ' ' || *it == '\t')
    {
        for(;;)
        {
            ++it;
            if(it == last)
            {
                ec = error::bad_chunk_extension;
                return it;
            }
            if(*it != ' ' && *it != '\t')
                break;
        }
    }
    // ';'
    if(*it != ';')
    {
        ec = error::bad_chunk_extension;
        return it;
    }
semi:
    ++it; // skip ';'
    // BWS
    for(;;)
    {
        if(it == last)
        {
            ec = error::bad_chunk_extension;
            return it;
        }
        if(*it != ' ' && *it != '\t')
            break;
        ++it;
    }
    // chunk-ext-name
    {
        if(! detail::is_token_char(*it))
        {
            ec = error::bad_chunk_extension;
            return it;
        }
        auto const first = it;
        for(;;)
        {
            ++it;
            if(it == last)
            {
                emit_string_plus_empty(first, it);
                return it;
            }
            if(! detail::is_token_char(*it))
                break;
        }
        emit_string(first, it);
    }
    // BWS [ ";" / "=" ]
    for(;;)
    {
        if(*it != ' ' && *it != '\t')
            break;
        ++it;
        if(it == last)
        {
            ec = error::bad_chunk_extension;
            return it;
        }
    }
    if(*it == ';')
    {
        emit_empty_string();
        goto semi;
    }
    if(*it != '=')
    {
        ec = error::bad_chunk_extension;
        return it;
    }
    ++it; // skip '='
    // BWS
    for(;;)
    {
        if(it == last)
        {
            ec = error::bad_chunk_extension;
            return it;
        }
        if(*it != ' ' && *it != '\t')
            break;
        ++it;
    }
    // chunk-ext-val
    if(*it != '"')
    {
        // token
        if(! detail::is_token_char(*it))
        {
            ec = error::bad_chunk_extension;
            return it;
        }
        auto const first = it;
        for(;;)
        {
            ++it;
            if(it == last)
                break;
            if(! detail::is_token_char(*it))
                break;
        }
        emit_string(first, it);
        if(it == last)
            return it;
    }
    else
    {
        // quoted-string
        auto const first = ++it; // skip DQUOTE
        // first pass, count chars
        std::size_t len = 0;
        for(;;)
        {
            if(it == last)
            {
                ec = error::bad_chunk_extension;
                return it;
            }
            if(*it == '"')
                break;
            if(*it == '\\')
            {
                ++it;
                if(it == last)
                {
                    ec = error::bad_chunk_extension;
                    return it;
                }
            }
            ++len;
            ++it;
        }
        // now build the string
        auto const offset = range_.size();
        range_.resize(
            offset +
            varint_size(len) +
            len);
        auto dest = &range_[offset];
        varint_write(dest, len);
        it = first;
        for(;;)
        {
            BOOST_ASSERT(it != last);
            if(*it == '"')
                break;
            if(*it == '\\')
            {
                ++it;
                BOOST_ASSERT(it != last);
            }
            Traits::assign(*dest++, *it++);
        }
        ++it; // skip DQUOTE
    }
    goto loop;
}

template<class Allocator>
void
basic_chunk_extensions<Allocator>::
do_insert(string_view name, string_view value)
{
/*
    chunk-ext       = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
    chunk-ext-name  = token
    chunk-ext-val   = token / quoted-string
    token           = 1*tchar
    quoted-string   = DQUOTE *( qdtext / quoted-pair ) DQUOTE
    qdtext          = HTAB / SP / "!" / %x23-5B ; '#'-'[' / %x5D-7E ; ']'-'~' / obs-text
    quoted-pair     = "\" ( HTAB / SP / VCHAR / obs-text )
    obs-text        = %x80-FF
*/
    if(value.empty())
    {
        s_.reserve(1 + name.size());
        s_.push_back(';');
        s_.append(name.data(), name.size());
        return;
    }

    bool is_token = true;
    for(auto const c : value)
    {
        if(! detail::is_token_char(c))
        {
            is_token = false;
            break;
        }
    }
    if(is_token)
    {
        // token
        s_.reserve(1 + name.size() + 1 + value.size());
        s_.push_back(';');
        s_.append(name.data(), name.size());
        s_.push_back('=');
        s_.append(value.data(), value.size());
    }
    else
    {
        // quoted-string
        s_.reserve(
            1 + name.size() + 1 +
            1 + value.size() + 20 + 1);
        s_.push_back(';');
        s_.append(name.data(), name.size());
        s_.append("=\"", 2);
        for(auto const c : value)
        {
            if(c == '\\')
                s_.append(R"(\\)", 2);
            else if(c == '\"')
                s_.append(R"(\")", 2);
            else
                s_.push_back(c);
        }
        s_.push_back('"');
    }
}

template<class Allocator>
void
basic_chunk_extensions<Allocator>::
parse(string_view s, error_code& ec)
{
    do_parse(s.data(), s.data() + s.size(), ec);
    if(! ec)
    {
        s_.clear();
        for(auto const& v : *this)
            do_insert(v.first, v.second);
    }
}

template<class Allocator>
void
basic_chunk_extensions<Allocator>::
insert(string_view name)
{
    do_insert(name, {});

    using beast::detail::varint_size;
    using beast::detail::varint_write;
    auto const offset = range_.size();
    range_.resize(
        offset +
        varint_size(name.size()) +
        name.size() +
        varint_size(0));
    auto dest = &range_[offset];
    varint_write(dest, name.size());
    std::memcpy(dest, name.data(), name.size());
    dest += name.size();
    varint_write(dest, 0);
}

template<class Allocator>
void
basic_chunk_extensions<Allocator>::
insert(string_view name, string_view value)
{
    do_insert(name, value);

    using beast::detail::varint_size;
    using beast::detail::varint_write;
    auto const offset = range_.size();
    range_.resize(
        offset +
        varint_size(name.size()) +
        name.size() +
        varint_size(value.size()) +
        value.size());
    auto dest = &range_[offset];
    varint_write(dest, name.size());
    std::memcpy(dest, name.data(), name.size());
    dest += name.size();
    varint_write(dest, value.size());
    std::memcpy(dest, value.data(), value.size());
}

template<class Allocator>
auto
basic_chunk_extensions<Allocator>::
begin() const ->
    const_iterator
{
    return const_iterator{range_.data()};
}

template<class Allocator>
auto
basic_chunk_extensions<Allocator>::
end() const ->
    const_iterator
{
    return const_iterator{
        range_.data() + range_.size()};
}

} // http
} // beast
} // boost

#endif

/* chunk_encode.hpp
VoDfgLXgd+AR4Pe6P4rOH5xuhLbjy+Qe4KVgX/AKcBh4JZgLXgXuCF4N7gFeC04ElxlWfxJ9OJgBpcU5+9MLtnB1EYZrjjDc8gjDtYYJt4LfloxNUneIrABfhX6EUndLMnKgyVAtdBq0Anp1t6Swd41w0Pm/ct/IMNK17hz5ausu//q9I+MeTvhP7x5ZcW1094943T3SQjmC7x/JQ5ZF0EJoKbQSWgMljEsysqFxUA3UDN0PrYL+gLLGcz4zVAYtgm6EWqG10LAJxIPKoMXQMqgV+hFK24M2AU2G6qAl0P3QKsgo4GxuaCeoDGqCroKegj6DkvZMMnKhIqgJWrZn7Hzl2BN7Yk/siT2xJ/bEntgTe2JP7Ik9nf8kQHP/xfP/5x6EWWxJY0VpfUO5/xaAjt0DYJ7TH7cp6zvqbHoSNbc81Var3zdOYz2HBbA4/77O0rmzq9Q59Y9mGnova60v1JZ/Aum1VSp7ufF777Hn3uOVqe2UqWNl79Z7QwP7ntEHEzY6W33iqz22jnMqhY8ssdnrA71DOKMqmI+q6gPL59cKP9ru7qgo9zAukPP5CyW/SVC+eXatI7/66oNmNzRW15uZSdnTVdllP6CEJ5URcG7xMl94yQtj55sPkl6ILHJlA+8cqDt0ELSLuU/BnTfuknTyZ6i6kb1RKs50dSbLwjjWT6H3B9NWzCMlNk208ey0b/6UMJ8NNsLum7bvi/5R+E6WAF2hm7IpT7Wd7wZnW0q3tyUJi086fonE9ak2Pae6sUZsSQNhIm9vIuMM2RtCurh1ug7ZL0lwaxeQswyh7TC0bRAn6raxW9i20SW0n6RTnuUO/ubPdbRcd1lLnD6at2Mj6ENin27x5rC9vUp4GyS89YKW4bPGz5t/7IO3kJZr68d1EfBg2ca2xnnZinrZzHrZonrd1+llExr9PaGddY+n+/2nnWejatQq2974X+NuOHX45tdutnDn+yatesf7nlNfb/P34Y2fj7z2mlvTl92368tvfWN85WVT7GXT6nU/qZdtrJctbfQ2y+421NHb2EZrc+1u++y8i59xWq1jmevdsobJu9Z7DXNXWYvMBxPAsfY756usO/xD15K3lzX2HcA+4I7gAHGLTYK854hrhN6j2l/iDwB7gQPBsWAWOAHMBCeJW6+pSnpzjNA11aFyZ/8IcCg4Epwi7oPAbF0ueReAyS7lGi/ymCDy2APsChZIfJAx2rtco6VcOVKuzaRcW0q5csFJ4hZ+GFO95Zwm6fUA1bgNDhC3tl2W+INc4veW+BnCTx+wr7hXxhtqPa5mIusmEGt861i7c7/HVu6w5e5awsu9tcHrenJPLet7gbtqn4PSNiMvMAu07qpdeCjp4c7n7xLIWgNsgT/7OuAi/K6CZD1Q7qj130mbB60gfCu0FirC/SNhFoJyF61j3VDuoVVrhx+By0Dun9Xrhzn59jVE5/2zp0HTtiAOKGuKcv9s8NoilE/8SeqeWdYZ9T2zar1xAehccwy5W1bfK9t3N9z8nQ/mkh7rkXKfrPMuWdYoWZ+Edl/3GmUO/q+C+aT1EVgCyt2y9nVLfcfs5AXwSxj7vbIrN+/CeiZufm8En+K3ryDulGV903GvrNwpa1/zdN4vy/qnvl/W2Npxx6xeE11BPs57ZkPXR3tNQAZHIH/CGpNZr8ZdAAWvmdbyW/A9s1+BtnVUZZzdDA4E8yDrDtml5u8u98euBVebCAWvt3JnrLXeypqmviuWtdfAXbHNZpyjkQN8F0B10BLofmg1lLAX67B7xdY5N4Rn/c3/y+dWmQqADs7/+8v8v8g//ydRUQDwWDqABS46gPttOoA6Fx3AeNJsLQ/RAYzde5yrDoA=
*/