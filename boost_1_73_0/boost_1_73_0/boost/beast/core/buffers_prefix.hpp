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
zslNmYtY1ZLRk+gq/unk/vhMBmfdSVcP/3TCX3ujd8NxD+H34ulEfHj07tP5eW+0WWp7Eoe8Xvg8aQdDCxbYUD1D4HWIcSyqPJ/Fv6Pkc0qhP18MT7t68OfoGoTu+LLXO+OtpCP++G/RXvQ/9uEuh0ZpD2UBJoaybyLyA2Q0qOB3a0eV0UwPVuRZ1uTXd9KAq81Sa8m5N3fBFrGO6tmUKnTAyjiv9BAalgZr63KG4rN02li/ModoWRrOZjIVNzK9Q37F1/G0CnI2sfQB4x6/L9cB2rqmcqsvJvGDvQEUKro1ROCr80y+WDRD8La9bu11M3uTKL9qmhdZ+P7HGnxT21NKbozu6uvhwes/fSeV8ukk97qx9TZ6ivNKW5AYWFUFNnMqRv2nyvdirnPyfRJA7Q5dnFI7sc4Bd22BW32Ny8QA7ljs7jLPIlXLQ5DitIUPsPmiA9eYPMHAOUu4DB5mL2yVqcjEDJ/8hP3enJpA1hcnojc8L9L7PHQW1/744qLEkuV1dzLrBBEj4TPgQuPlJJsX46RyZ/C4nJlQxHGpue7AyWzUqTv+5C5bc/ukbku/pE19bYbB0yMHLU3vWxNJZpM9k8SxATTiwVv6EuOuytqVg1R0wM6zozJ3QRF+V4zd/vnHCXein6Pe+9Lp
*/