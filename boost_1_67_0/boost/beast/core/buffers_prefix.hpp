//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_PREFIX_HPP
#define BOOST_BEAST_BUFFERS_PREFIX_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional/optional.hpp> // for in_place_init_t
#include <algorithm>
#include <cstdint>
#include <type_traits>

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
#include <boost/type_traits.hpp>
#endif

namespace boost {
namespace beast {

/** A buffer sequence adaptor that shortens the sequence size.

    The class adapts a buffer sequence to efficiently represent
    a shorter subset of the original list of buffers starting
    with the first byte of the original sequence.

    @tparam BufferSequence The buffer sequence to adapt.
*/
template<class BufferSequence>
class buffers_prefix_view
{
    using iter_type =
        buffers_iterator_type<BufferSequence>;

    BufferSequence bs_;
    std::size_t size_ = 0;
    std::size_t remain_ = 0;
    iter_type end_{};

    void
    setup(std::size_t size);

    buffers_prefix_view(
        buffers_prefix_view const& other,
        std::size_t dist);

public:
    /** The type for each element in the list of buffers.

        If the type `BufferSequence` meets the requirements of
        <em>MutableBufferSequence</em>, then `value_type` is
        `net::mutable_buffer`. Otherwise, `value_type` is
        `net::const_buffer`.

        @see buffers_type
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#elif BOOST_WORKAROUND(BOOST_MSVC, < 1910)
    using value_type = typename std::conditional<
        boost::is_convertible<typename
            std::iterator_traits<iter_type>::value_type,
                net::mutable_buffer>::value,
                    net::mutable_buffer,
                        net::const_buffer>::type;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

#if BOOST_BEAST_DOXYGEN
    /// A bidirectional iterator type that may be used to read elements.
    using const_iterator = __implementation_defined__;

#else
    class const_iterator;

#endif

    /// Copy Constructor
    buffers_prefix_view(buffers_prefix_view const&);

    /// Copy Assignment
    buffers_prefix_view& operator=(buffers_prefix_view const&);

    /** Construct a buffer sequence prefix.

        @param size The maximum number of bytes in the prefix.
        If this is larger than the size of passed buffers,
        the resulting sequence will represent the entire
        input sequence.

        @param buffers The buffer sequence to adapt. A copy of
        the sequence will be made, but ownership of the underlying
        memory is not transferred. The copy is maintained for
        the lifetime of the view.
    */
    buffers_prefix_view(
        std::size_t size,
        BufferSequence const& buffers);

    /** Construct a buffer sequence prefix in-place.

        @param size The maximum number of bytes in the prefix.
        If this is larger than the size of passed buffers,
        the resulting sequence will represent the entire
        input sequence.

        @param args Arguments forwarded to the contained buffer's constructor.
    */
    template<class... Args>
    buffers_prefix_view(
        std::size_t size,
        boost::in_place_init_t,
        Args&&... args);

    /// Returns an iterator to the first buffer in the sequence
    const_iterator
    begin() const;

    /// Returns an iterator to one past the last buffer in the sequence 
    const_iterator
    end() const;

#if ! BOOST_BEAST_DOXYGEN
    std::size_t
    buffer_bytes_impl() const noexcept
    {
        return size_;
    }
#endif
};

//------------------------------------------------------------------------------

/** Returns a prefix of a constant or mutable buffer sequence.

    The returned buffer sequence points to the same memory as the
    passed buffer sequence, but with a size that is equal to or
    smaller. No memory allocations are performed; the resulting
    sequence is calculated as a lazy range.

    @param size The maximum size of the returned buffer sequence
    in bytes. If this is greater than or equal to the size of
    the passed buffer sequence, the result will have the same
    size as the original buffer sequence.

    @param buffers An object whose type meets the requirements
    of <em>BufferSequence</em>. The returned value will
    maintain a copy of the passed buffers for its lifetime;
    however, ownership of the underlying memory is not
    transferred.

    @return A constant buffer sequence that represents the prefix
    of the original buffer sequence. If the original buffer sequence
    also meets the requirements of <em>MutableBufferSequence</em>,
    then the returned value will also be a mutable buffer sequence.
*/
template<class BufferSequence>
buffers_prefix_view<BufferSequence>
buffers_prefix(
    std::size_t size, BufferSequence const& buffers)
{
    static_assert(
        net::is_const_buffer_sequence<BufferSequence>::value,
            "BufferSequence type requirements not met");
    return buffers_prefix_view<BufferSequence>(size, buffers);
}

/** Returns the first buffer in a buffer sequence

    This returns the first buffer in the buffer sequence.
    If the buffer sequence is an empty range, the returned
    buffer will have a zero buffer size.

    @param buffers The buffer sequence. If the sequence is
    mutable, the returned buffer sequence will also be mutable.
    Otherwise, the returned buffer sequence will be constant.
*/
template<class BufferSequence>
buffers_type<BufferSequence>
buffers_front(BufferSequence const& buffers)
{
    auto const first =
        net::buffer_sequence_begin(buffers);
    if(first == net::buffer_sequence_end(buffers))
        return {};
    return *first;
}

} // beast
} // boost

#include <boost/beast/core/impl/buffers_prefix.hpp>

#endif

/* buffers_prefix.hpp
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
*/