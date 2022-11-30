//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_CHUNK_ENCODE_HPP
#define BOOST_BEAST_HTTP_DETAIL_CHUNK_ENCODE_HPP

#include <boost/beast/http/type_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>

namespace boost {
namespace beast {
namespace http {
namespace detail {

struct chunk_extensions
{
    virtual ~chunk_extensions() = default;
    virtual net::const_buffer str() = 0;
};

template<class ChunkExtensions>
struct chunk_extensions_impl : chunk_extensions
{
    ChunkExtensions ext_;

    chunk_extensions_impl(ChunkExtensions&& ext) noexcept
        : ext_(std::move(ext))
    {
    }

    chunk_extensions_impl(ChunkExtensions const& ext)
        : ext_(ext)
    {
    }

    net::const_buffer
    str() override
    {
        auto const s = ext_.str();
        return {s.data(), s.size()};
    }
};

template<class T, class = void>
struct is_chunk_extensions : std::false_type {};

template<class T>
struct is_chunk_extensions<T, beast::detail::void_t<decltype(
    std::declval<string_view&>() = std::declval<T&>().str()
        )>> : std::true_type
{
};

//------------------------------------------------------------------------------

/** A buffer sequence containing a chunk-encoding header
*/
class chunk_size
{
    template<class OutIter>
    static
    OutIter
    to_hex(OutIter last, std::size_t n)
    {
        if(n == 0)
        {
            *--last = '0';
            return last;
        }
        while(n)
        {
            *--last = "0123456789abcdef"[n&0xf];
            n>>=4;
        }
        return last;
    }

    struct sequence
    {
        net::const_buffer b;
        char data[1 + 2 * sizeof(std::size_t)];

        explicit
        sequence(std::size_t n)
        {
            char* it0 = data + sizeof(data);
            auto it = to_hex(it0, n);
            b = {it,
                static_cast<std::size_t>(it0 - it)};
        }
    };

    std::shared_ptr<sequence> sp_;

public:
    using value_type = net::const_buffer;

    using const_iterator = value_type const*;

    chunk_size(chunk_size const& other) = default;

    /** Construct a chunk header

        @param n The number of octets in this chunk.
    */
    chunk_size(std::size_t n)
        : sp_(std::make_shared<sequence>(n))
    {
    }

    const_iterator
    begin() const
    {
        return &sp_->b;
    }

    const_iterator
    end() const
    {
        return begin() + 1;
    }
};

//------------------------------------------------------------------------------

/// Returns a buffer sequence holding a CRLF for chunk encoding
inline
net::const_buffer const&
chunk_crlf()
{
    static net::const_buffer const cb{"\r\n", 2};
    return cb;
}

/// Returns a buffer sequence holding a final chunk header
inline
net::const_buffer const&
chunk_last()
{
    static net::const_buffer const cb{"0\r\n", 3};
    return cb;
}

//------------------------------------------------------------------------------

#if 0
template<class = void>
struct chunk_crlf_iter_type
{
    class value_type
    {
        char const s[2] = {'\r', '\n'};

    public:
        value_type() = default;

        operator
        net::const_buffer() const
        {
            return {s, sizeof(s)};
        }
    };
    static value_type value;
};

template<class T>
typename chunk_crlf_iter_type<T>::value_type
chunk_crlf_iter_type<T>::value;

using chunk_crlf_iter = chunk_crlf_iter_type<void>;
#endif

//------------------------------------------------------------------------------

struct chunk_size0
{
    using value_type = net::const_buffer;
    using const_iterator = value_type const*;

    const_iterator
    begin() const
    {
        return &chunk_last();
    }

    const_iterator
    end() const
    {
        return begin() + 1;
    }
};

//------------------------------------------------------------------------------

template<class T,
    bool = is_fields<T>::value>
struct buffers_or_fields
{
    using type = typename
        T::writer::const_buffers_type;
};

template<class T>
struct buffers_or_fields<T, false>
{
    using type = T;
};

} // detail
} // http
} // beast
} // boost

#endif

/* chunk_encode.hpp
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
*/