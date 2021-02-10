//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFER_TRAITS_HPP
#define BOOST_BEAST_DETAIL_BUFFER_TRAITS_HPP

#include <boost/asio/buffer.hpp>
#include <boost/config/workaround.hpp>
#include <boost/type_traits/make_void.hpp>
#include <cstdint>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)

template<class T>
struct buffers_iterator_type_helper
{
    using type = decltype(
        net::buffer_sequence_begin(
            std::declval<T const&>()));
};

template<>
struct buffers_iterator_type_helper<
    net::const_buffer>
{
    using type = net::const_buffer const*;
};

template<>
struct buffers_iterator_type_helper<
    net::mutable_buffer>
{
    using type = net::mutable_buffer const*;
};

#endif

struct buffer_bytes_impl
{
    std::size_t
    operator()(net::const_buffer b) const noexcept
    {
        return net::const_buffer(b).size();
    }

    std::size_t
    operator()(net::mutable_buffer b) const noexcept
    {
        return net::mutable_buffer(b).size();
    }

    template<
        class B,
        class = typename std::enable_if<
            net::is_const_buffer_sequence<B>::value>::type>
    std::size_t
    operator()(B const& b) const noexcept
    {
        using net::buffer_size;
        return buffer_size(b);
    }
};

/** Return `true` if a buffer sequence is empty

    This is sometimes faster than using @ref buffer_bytes
*/
template<class ConstBufferSequence>
bool
buffers_empty(ConstBufferSequence const& buffers)
{
    auto it = net::buffer_sequence_begin(buffers);
    auto end = net::buffer_sequence_end(buffers);
    while(it != end)
    {
        if(net::const_buffer(*it).size() > 0)
            return false;
        ++it;
    }
    return true;
}

} // detail
} // beast
} // boost

#endif

/* buffer_traits.hpp
BHyMClicWn4YlRtWtduo7clBxJGlJKXOoQhxwKFYIcwBlXkstTvsPK9VVDF1Af4uNEd7Y1I5jKH2YEmTZZvWwqQmoA+T1T/mdyv6MFgsBrPVR5qPaTD7yMJ+mcxuAH0KZZrkY6GlgXJN6bbIUhlXOv+4X7/1pzSPsjKWdG1snKre5u3Jkk7ze15rLDLIHunTs3vTt/tCmq+XjRX2dDWJcvvkvtQ6r9QnsUwQpdlfLhv7lW0yM7KxWgI6G/udHPnTavXP6fpmtBy+5XjeSp0oBhAojFe3VBaZErFLEC1zsUX2HArm19Kg5BIAToJMGUWIfVK6RLNa5CaRmuNP1/1afB9hgalpLmk6Hw6m4XgyHXlmaPfttuh7dVxTPfto24fTd7fT+eDGHQ+RG9RGjWbywh/niJ+cXozez1ej8G4xrWQntkCxyUeBrJC9SG37bXois3F5Nng/8surOS57v+MLxOCCT3hdHLYZtLymNHFEsRO59WxQ6XElpPRnzukPaR6rnaEdEhVUtOZsYBYRLZh3M50GTsT7u+XKk0Wh1UMKuASijvBHIsvWIvrs7w/h2Px2FS5Gg5vx3Wy4msxnPRY0BsMgGIeyxPEso3tQlhMvKNLCbMggGVg09DpmyZVlWmFgWcqD0Cnz1JkBs2yV
*/