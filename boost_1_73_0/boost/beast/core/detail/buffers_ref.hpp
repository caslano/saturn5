//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_REF_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_REF_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <iterator>
#include <memory>

namespace boost {
namespace beast {
namespace detail {

// A very lightweight reference to a buffer sequence
template<class BufferSequence>
class buffers_ref
{
    BufferSequence const* buffers_;

public:
    using const_iterator =
        buffers_iterator_type<BufferSequence>;

    using value_type = typename
        std::iterator_traits<const_iterator>::value_type;

    buffers_ref(buffers_ref const&) = default;
    buffers_ref& operator=(buffers_ref const&) = default;

    explicit
    buffers_ref(BufferSequence const& buffers)
        : buffers_(std::addressof(buffers))
    {
    }

    const_iterator
    begin() const
    {
        return net::buffer_sequence_begin(*buffers_);
    }

    const_iterator
    end() const
    {
        return net::buffer_sequence_end(*buffers_);
    }
};

// Return a reference to a buffer sequence
template<class BufferSequence>
buffers_ref<BufferSequence>
make_buffers_ref(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return buffers_ref<BufferSequence>(buffers);
}

} // detail
} // beast
} // boost

#endif

/* buffers_ref.hpp
oSaBewrvRMffddvrfHfCXQFnyxQHAXOthrPDmf6wFd6EPJWg5vgO7vDK23V5IsPg/S3Kl4jGUvlE/oDIb6AdfILUJoGhBcVDHsWMxVIT6Sg6BAgJZLNA+b44eo/jkgyaPaUh3ULKwEpnyt99SWPYLTu3kI3J+Eik3GhsIj2VIcnhYM+lJ/P7ItlYK/Je1bq6ddUq9WxrXYMQ8uws4HelEpdjhJlSTBkuJ1KrEVdQOAQQcMRU
*/