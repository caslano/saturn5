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
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
*/