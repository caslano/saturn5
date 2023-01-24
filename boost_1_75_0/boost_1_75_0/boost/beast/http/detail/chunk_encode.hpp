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
7hc0ncowX127x7XLV9fTrMK2fHXNXfCX+OoqGhrVV9cyNtpo8aPt44z6C4rbEM03U1Nc+OQru6YFwNLlX/LZhcrhKz/gj0cpYRPi8JxbUkqudMtHvfIdKW62shNOc8kQQnOTMKCvLQieucml1jb/q0Depqg3A0a7JSV4SypU1w8V/AsOfxMhqSu5hcRqrOL83OMT0vLlb/vJ3q8lIUIbkNJPdn8t9Q3Gfg5Vf+xGURvv+Bms44Y4pq1l8ag3cd7NrYNHi5gtMEdf32P0Wt/AfQelSbnXpzoCYBEIk+YCYe5BrrKQxtb3ufmAz3rAajnKA0gw0FL2MZYESLiyxS5h6OL7SZtWr2PofJSzsqx+0fXHo8nGUFPXrAFEn5todDAqVlF881bwRfc8wffP/Pnd85puSyu50jdj2ydXeuuLE8iVph9TVZIrdf2DciW18b8pV/KadYOa6PKllpgo8qUfjsGpIuRLo1rLl5Z8fnL5Uo7ZyJWNIj5KO5H4aMDngoVlMrclPsp94s+LjxadXHz0SeNJxEe6O1Wj4Gj4S9ao8jVd2NQdFbvLcVEiRUsTX7KGC5NGvRQpa2otWkqPEC11ChMtxf2HoqUb1kcRLV23Popoae+dbYiWJn0WRbR022dhoqXBn/0h0dK1n7VftGSUJUnHhCzpaQD1br+gvDkMurd+aoBujcZ481ODhGnFp5qEqemz9kuYltzQloRp
*/