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
1Gia5PxE1OHvw2r1VWjGvzRn0oSWIhwBMXh9ZOqB1XlE9T6NrlRUjXIWEQn+qgIcfZZus150xjy+rYLGPH13rK16c6e5MqiY0Vbs/AvPES3VaMbZ/TXZtkAxXIovbdNUvfoBSedPkionUnTMgxK8Lc3eEs2DJ3h+l0uE22jOdGIeiW7SHNYSOJECtfMUZrQLpeWGQTgWBSKcE3EZ7/UZExCSQ6WoWyqC7aDmkd9uOHdw275p6bv8Ujw0ymW7GwwgwZroNDtSr6AfRaKXXFl7L/9UdNwOVDMWmKevEntukDQpwXYt+66Lp7SusZWeqIporRGgRarGcLClGkZS2iUxnGSqj8UIzPY5PE2ajPNNjEk8xC4AnJeajw8WuWLELIi91OglVhA0kWe1iWkFLJdovkjzaaiLJXORV6HWrn30QdtO7P7DFkI1fOtM/p1Z0Yxj7Uf5/rQyXCrrPgzciqxEigqpNY7YiqvqBrkmA/xztdC6oivGgC6pvXlUsvli/aqD2+hYJT65WyCmtYpfvLa82VjZwsAfa1YYltxqHpL9TYUZJDpBNpTJXKD04tFlPiWbMnTffD6ymoWksAZdfz+PbxcfYze6TXmZGeVTQ9W9OugNWUxPsH24Stt1+53DbkoAp3NeGzlvRSru4bWK49YknLnMsmuUIDgCR2ZTaWZimi7rpC6JBklbsOjzXOEgk/Po+h+aZvaZg45LWDEE
*/