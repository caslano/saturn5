//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_RANGE_HPP
#define BOOST_BEAST_BUFFERS_RANGE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/buffers_range_adaptor.hpp>

namespace boost {
namespace beast {

/** Returns an iterable range representing a buffer sequence.

    This function returns an iterable range representing the
    passed buffer sequence. The values obtained when iterating
    the range will be `net::const_buffer`, unless the underlying
    buffer sequence is a <em>MutableBufferSequence</em>, in which case
    the value obtained when iterating will be a `net::mutable_buffer`.

    @par Example

    The following function returns the total number of bytes in
    the specified buffer sequence. A copy of the buffer sequence
    is maintained for the lifetime of the range object:

    @code
    template <class BufferSequence>
    std::size_t buffer_sequence_size (BufferSequence const& buffers)
    {
        std::size_t size = 0;
        for (auto const buffer : buffers_range (buffers))
            size += buffer.size();
        return size;
    }
    @endcode

    @param buffers The buffer sequence to adapt into a range. The
    range object returned from this function will contain a copy
    of the passed buffer sequence.

    @return An object of unspecified type which meets the requirements
    of <em>ConstBufferSequence</em>. If `buffers` is a mutable buffer
    sequence, the returned object will also meet the requirements of
    <em>MutableBufferSequence</em>.

    @see buffers_range_ref
*/
template<class BufferSequence>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::buffers_range_adaptor<BufferSequence>
#endif
buffers_range(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return detail::buffers_range_adaptor<
        BufferSequence>(buffers);
}

/** Returns an iterable range representing a buffer sequence.

    This function returns an iterable range representing the
    passed buffer sequence. The values obtained when iterating
    the range will be `net::const_buffer`, unless the underlying
    buffer sequence is a <em>MutableBufferSequence</em>, in which case
    the value obtained when iterating will be a `net::mutable_buffer`.

    @par Example

    The following function returns the total number of bytes in
    the specified buffer sequence. A reference to the original
    buffers is maintained for the lifetime of the range object:

    @code
    template <class BufferSequence>
    std::size_t buffer_sequence_size_ref (BufferSequence const& buffers)
    {
        std::size_t size = 0;
        for (auto const buffer : buffers_range_ref (buffers))
            size += buffer.size();
        return size;
    }
    @endcode

    @param buffers The buffer sequence to adapt into a range. The
    range returned from this function will maintain a reference to
    these buffers. The application is responsible for ensuring that
    the lifetime of the referenced buffers extends until the range
    object is destroyed.

    @return An object of unspecified type which meets the requirements
    of <em>ConstBufferSequence</em>. If `buffers` is a mutable buffer
    sequence, the returned object will also meet the requirements of
    <em>MutableBufferSequence</em>.

    @see buffers_range
*/
template<class BufferSequence>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::buffers_range_adaptor<BufferSequence const&>
#endif
buffers_range_ref(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return detail::buffers_range_adaptor<
        BufferSequence const&>(buffers);
}
/** @} */

} // beast
} // boost

#endif

/* buffers_range.hpp
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
*/