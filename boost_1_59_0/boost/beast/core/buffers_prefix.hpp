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
#include <boost/type_traits/is_convertible.hpp>
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