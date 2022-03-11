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