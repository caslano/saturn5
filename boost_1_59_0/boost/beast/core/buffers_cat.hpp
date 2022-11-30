//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_CAT_HPP
#define BOOST_BEAST_BUFFERS_CAT_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/tuple.hpp>
#include <boost/beast/core/detail/type_traits.hpp>

namespace boost {
namespace beast {

/** A buffer sequence representing a concatenation of buffer sequences.
    @see buffers_cat
*/
template<class... Buffers>
class buffers_cat_view
{
    detail::tuple<Buffers...> bn_;

public:
    /** The type of buffer returned when dereferencing an iterator.
        If every buffer sequence in the view is a <em>MutableBufferSequence</em>,
        then `value_type` will be `net::mutable_buffer`.
        Otherwise, `value_type` will be `net::const_buffer`.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<Buffers...>;
#endif

    /// The type of iterator used by the concatenated sequence
    class const_iterator;

    /// Copy Constructor
    buffers_cat_view(buffers_cat_view const&) = default;

    /// Copy Assignment
    buffers_cat_view& operator=(buffers_cat_view const&) = default;

    /** Constructor
        @param buffers The list of buffer sequences to concatenate.
        Copies of the arguments will be maintained for the lifetime
        of the concatenated sequence; however, the ownership of the
        memory buffers themselves is not transferred.
    */
    explicit
    buffers_cat_view(Buffers const&... buffers);

    /// Returns an iterator to the first buffer in the sequence
    const_iterator
    begin() const;

    /// Returns an iterator to one past the last buffer in the sequence
    const_iterator
    end() const;
};

/** Concatenate 1 or more buffer sequences.

    This function returns a constant or mutable buffer sequence which,
    when iterated, efficiently concatenates the input buffer sequences.
    Copies of the arguments passed will be made; however, the returned
    object does not take ownership of the underlying memory. The
    application is still responsible for managing the lifetime of the
    referenced memory.
    @param buffers The list of buffer sequences to concatenate.
    @return A new buffer sequence that represents the concatenation of
    the input buffer sequences. This buffer sequence will be a
    <em>MutableBufferSequence</em> if each of the passed buffer sequences is
    also a <em>MutableBufferSequence</em>; otherwise the returned buffer
    sequence will be a <em>ConstBufferSequence</em>.
    @see buffers_cat_view
*/
#if BOOST_BEAST_DOXYGEN
template<class... BufferSequence>
buffers_cat_view<BufferSequence...>
buffers_cat(BufferSequence const&... buffers)
#else
template<class B1, class... Bn>
buffers_cat_view<B1, Bn...>
buffers_cat(B1 const& b1, Bn const&... bn)
#endif
{
    static_assert(
        is_const_buffer_sequence<B1, Bn...>::value,
        "BufferSequence type requirements not met");
    return buffers_cat_view<B1, Bn...>{b1, bn...};
}

} // beast
} // boost

#include <boost/beast/core/impl/buffers_cat.hpp>

#endif

/* buffers_cat.hpp
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
*/