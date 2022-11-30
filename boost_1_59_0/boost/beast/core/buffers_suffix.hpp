//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_SUFFIX_HPP
#define BOOST_BEAST_BUFFERS_SUFFIX_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <iterator>
#include <utility>

namespace boost {
namespace beast {

/** Adaptor to progressively trim the front of a <em>BufferSequence</em>.

    This adaptor wraps a buffer sequence to create a new sequence
    which may be incrementally consumed. Bytes consumed are removed
    from the front of the buffer. The underlying memory is not changed,
    instead the adaptor efficiently iterates through a subset of
    the buffers wrapped.

    The wrapped buffer is not modified, a copy is made instead.
    Ownership of the underlying memory is not transferred, the application
    is still responsible for managing its lifetime.

    @tparam BufferSequence The buffer sequence to wrap.

    @par Example

    This function writes the entire contents of a buffer sequence
    to the specified stream.

    @code
    template<class SyncWriteStream, class ConstBufferSequence>
    void send(SyncWriteStream& stream, ConstBufferSequence const& buffers)
    {
        buffers_suffix<ConstBufferSequence> bs{buffers};
        while(buffer_bytes(bs) > 0)
            bs.consume(stream.write_some(bs));
    }
    @endcode
*/
template<class BufferSequence>
class buffers_suffix
{
    using iter_type =
        buffers_iterator_type<BufferSequence>;

    BufferSequence bs_;
    iter_type begin_{};
    std::size_t skip_ = 0;

    template<class Deduced>
    buffers_suffix(Deduced&& other, std::size_t dist)
        : bs_(std::forward<Deduced>(other).bs_)
        , begin_(std::next(
            net::buffer_sequence_begin(bs_),
                dist))
        , skip_(other.skip_)
    {
    }

public:
    /** The type for each element in the list of buffers.

        If <em>BufferSequence</em> meets the requirements of
        <em>MutableBufferSequence</em>, then this type will be
        `net::mutable_buffer`, otherwise this type will be
        `net::const_buffer`.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

#if BOOST_BEAST_DOXYGEN
    /// A bidirectional iterator type that may be used to read elements.
    using const_iterator = __implementation_defined__;

#else
    class const_iterator;

#endif

    /// Constructor
    buffers_suffix();

    /// Copy Constructor
    buffers_suffix(buffers_suffix const&);

    /** Constructor

        A copy of the buffer sequence is made. Ownership of the
        underlying memory is not transferred or copied.
    */
    explicit
    buffers_suffix(BufferSequence const& buffers);

    /** Constructor

        This constructs the buffer sequence in-place from
        a list of arguments.

        @param args Arguments forwarded to the buffers constructor.
    */
    template<class... Args>
    explicit
    buffers_suffix(boost::in_place_init_t, Args&&... args);

    /// Copy Assignment
    buffers_suffix& operator=(buffers_suffix const&);

    /// Get a bidirectional iterator to the first element.
    const_iterator
    begin() const;

    /// Get a bidirectional iterator to one past the last element.
    const_iterator
    end() const;

    /** Remove bytes from the beginning of the sequence.

        @param amount The number of bytes to remove. If this is
        larger than the number of bytes remaining, all the
        bytes remaining are removed.
    */
    void
    consume(std::size_t amount);
};

} // beast
} // boost

#include <boost/beast/core/impl/buffers_suffix.hpp>

#endif

/* buffers_suffix.hpp
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
*/