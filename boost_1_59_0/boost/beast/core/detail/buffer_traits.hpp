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
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
*/