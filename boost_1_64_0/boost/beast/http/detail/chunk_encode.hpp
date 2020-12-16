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
y6YJv2pp81bY0YH2LXsQpX2L/wirz2LbE55Ha1wZAnFvSNC96tYex1Rl59T8ImOp2Do57MTkbPPfyHS04AHmOO5etlLah1v5JHy53hvb42DT/ZH4+4zrDsFt79/Ci5Rf4s8Xtw4fai8i/eMTFb7UJ/YgEn9b8WfUVvFHib2ITs9mb1aPn3/8+V3F7e4L2IrV6jY0Hf9Rqiyv2G3JtP9M/Mco/4eUf/5wf3xKp8bhlU4bNxVnto/6UXF62PwO1GNRm8kPNUj9yhnjVnmSbHnU6zzy7XZu/M5/epzcSeXzl7itdNJs6Ryo02kSXmX81DZ8PpXGtfBj+VXOq503V9vmHKDS3ETGOp9RqNzFRjd+G8E4tYD+U5BsjVPH7Z4al2yOUxunJALJG5l/p3mNWXGSttcY9bfiLVuNUUPoOxvx28v0nUfwfEXs4wIk+0t967aTI0FlJ4f8aTvO/lWEGxk4bNjKfKH2QytB5Mtvqi3IGGj9Vq9/a9K/qXpQ9m9Fqszs4erp76u7WN8KqYZ6LoJ6Qs3QTNaAcmutvqo+OJ2DkXt/lTi99T7i8co93siVPnK135ZStQvGIHWmxjDGioHw8CpyTd1oQmKX+B4pu/PWyaEGUzc29Bib04c3a4Y/3yL4Q2LadvRUlU++kU56y0ivL+m9Zqa38SF67FvWz1D1aZL12xzSGWxMVd+qlx/CD4kh36q6zZyn8uge0V7ifNv4iVuVlbLjrnK8A0rkPI7b5R1wE3SL6TNHy/6gamGIXxl5eD9TtjzivUH5UronDk7tlpSYnBo3ICU1ZZ+UySkjEoekjt4oNTnP+W4KeZfpb5g+Kq+LqDWfks/gCN5h1jj/WDe/Rzzp9AN/gWpMe2AX/kuVKaafj7HI3Se2syJfiZOpzzb/W7k/NLJlvG5U47tKRMZzK85AfQbVH8rdYmTx/bELsipDTgu6+WUVn6lltQmy2lvJKlGNFPHptLeJKSNShqTsnpiaOrpravLORqTy22iumecTfDttFJH8rG9iZKDtWPXZXYmWzaqzj64Ww6488usPjgAPhpfceR5ylo96D1lLvBH6DIQZyt3dt6kR7yVriTNU7+mfqtzdfNmUO5CPlS/vRx0nS9dpoXL39G1mdAnkI7bb1lkhe6kw/X1j+P8qY7Sc6WWlNciYQb0+RZ3WpEm9jkgcHJ/EYBHXLTEpNS4jJZWrjbqZNdtHanZSylBqdlxiEjcejU9MSI3bLGUEP4+ChvBvKHG7dom4vg9QfCRx8ldcxPVd6FLfRUH1LbbMhHPaPNfocH450S60rcBysc2eJza0B0M7EH9lnaNdcBiDNA5rjk24oHMrtO1590PVnMhvnyxjZE2GGntpMVOJY42VnvN2/T7YWKWVHHaeaB8Tp6XL3m4p061QsXkX4aGOMjU0ljciNXs9qZ/0XOdCFf4gYwJtTb3DpSzH9PKfQXUK+Bx1fTR4Uq/wc1n7uPdcT/d3Zn695hGhhP9+J7zjfTm9Pvz7soiIk3t27H15YX3gfbmK9Ap6dv778pr6zntfWnJP6OuPODhObMZBs72nNWi5K9sY/rDUQMZWlLGV8n1FHa9WMjvuvJRuSmAJ8f1V31evgo1S01IY/FMRh8jQave4RYb6O1La2IpGda6RkmMq6TdD75h59D/uDktmN4kcrTCfQe+aYVKO+8QKc2E/lQdyVeNujd1GfZXKI1V/B3+k3DsyEqbr+tlcyvhcb13GAYEygnvaCxh5+bZXeR2lytcG33W9dfl2CCmfhHmqty5fTSTl2z+ofLOVO8/obyvfKCnfsgyrfE03OMo3O1C6SMv2dEOg7lrxn5xhla3pmZCySZirMqyyNX0fSdm+bnA=
*/