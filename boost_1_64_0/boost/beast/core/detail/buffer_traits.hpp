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
sJokZrsi5hKEYPsEOPFF3YQVDPQ1VUFGBySkHE2p7wLhjVSzNdwHOo4rkGa91f6MstAreF3KXxga+B+INoilkyx9at4z7iymcyeoXSS48RUYm/MlUvI7c7Uk3Vv3SBETFhkZPuJhTJOvSgbe78MZ6hUyl42+E7aD8exP5rBvAL9fNWgoJn40dYJ7Jte8sbPgPukPmDEfyR3OHfRrRIccmEQpTVzbMPESZGLwGqrA6EITPLInsbXZ09c2mXix6KwclYCbg7cuuZ8a/yXe1OkIdPVh+M5qQvFY6Al7T3KYuqeIKH41yFcAQDnc9wuvCOAiBmA2NUtiSKkbmxL4o63QuSA4G9sAb46CG9ElYeE3CkTjk3hWy4ej6gpjSMgyaVTON/pLVKwi89KZBnmtYz+fptVN54eAQw6dPRuTc0QNM+DjwEgyKKIdCqB0KlslMQbJPEKSs2ERTzZUoH9RIgqh6SFEALc7+BM1Q8oRPQMPwpBCHJA4FVBGi9RBsqcGxqU0ayWt/zgJPBB4KbdxsMZOwSZa9SsABPrpG+BInT9rFl3GCj2FciMOEblSdw==
*/