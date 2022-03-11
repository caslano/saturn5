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