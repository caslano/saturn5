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