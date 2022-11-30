//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFER_TRAITS_HPP
#define BOOST_BEAST_BUFFER_TRAITS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/buffer_traits.hpp>
#include <boost/beast/core/detail/static_const.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/config/workaround.hpp>
#include <boost/mp11/function.hpp>
#include <type_traits>

namespace boost {
namespace beast {

/** Determine if a list of types satisfy the <em>ConstBufferSequence</em> requirements.

    This metafunction is used to determine if all of the specified types
    meet the requirements for constant buffer sequences. This type alias
    will be `std::true_type` if each specified type meets the requirements,
    otherwise, this type alias will be `std::false_type`.

    @tparam BufferSequence A list of zero or more types to check. If this
    list is empty, the resulting type alias will be `std::true_type`.
*/
template<class... BufferSequence>
#if BOOST_BEAST_DOXYGEN
using is_const_buffer_sequence = __see_below__;
#else
using is_const_buffer_sequence = mp11::mp_all<
    net::is_const_buffer_sequence<
        typename std::decay<BufferSequence>::type>...>;
#endif

/** Determine if a list of types satisfy the <em>MutableBufferSequence</em> requirements.

    This metafunction is used to determine if all of the specified types
    meet the requirements for mutable buffer sequences. This type alias
    will be `std::true_type` if each specified type meets the requirements,
    otherwise, this type alias will be `std::false_type`.

    @tparam BufferSequence A list of zero or more types to check. If this
    list is empty, the resulting type alias will be `std::true_type`.
*/
template<class... BufferSequence>
#if BOOST_BEAST_DOXYGEN
using is_mutable_buffer_sequence = __see_below__;
#else
using is_mutable_buffer_sequence = mp11::mp_all<
    net::is_mutable_buffer_sequence<
        typename std::decay<BufferSequence>::type>...>;
#endif

/** Type alias for the underlying buffer type of a list of buffer sequence types.

    This metafunction is used to determine the underlying buffer type for
    a list of buffer sequence. The equivalent type of the alias will vary
    depending on the template type argument:

    @li If every type in the list is a <em>MutableBufferSequence</em>,
        the resulting type alias will be `net::mutable_buffer`, otherwise

    @li The resulting type alias will be `net::const_buffer`.

    @par Example
    The following code returns the first buffer in a buffer sequence,
    or generates a compilation error if the argument is not a buffer
    sequence:
    @code
    template <class BufferSequence>
    buffers_type <BufferSequence>
    buffers_front (BufferSequence const& buffers)
    {
        static_assert(
            net::is_const_buffer_sequence<BufferSequence>::value,
            "BufferSequence type requirements not met");
        auto const first = net::buffer_sequence_begin (buffers);
        if (first == net::buffer_sequence_end (buffers))
            return {};
        return *first;
    }
    @endcode

    @tparam BufferSequence A list of zero or more types to check. If this
    list is empty, the resulting type alias will be `net::mutable_buffer`.
*/
template<class... BufferSequence>
#if BOOST_BEAST_DOXYGEN
using buffers_type = __see_below__;
#else
using buffers_type = typename std::conditional<
    is_mutable_buffer_sequence<BufferSequence...>::value,
    net::mutable_buffer, net::const_buffer>::type;
#endif

/** Type alias for the iterator type of a buffer sequence type.

    This metafunction is used to determine the type of iterator
    used by a particular buffer sequence.

    @tparam T The buffer sequence type to use. The resulting
    type alias will be equal to the iterator type used by
    the buffer sequence.
*/
template <class BufferSequence>
#if BOOST_BEAST_DOXYGEN
using buffers_iterator_type = __see_below__;
#elif BOOST_WORKAROUND(BOOST_MSVC, < 1910)
using buffers_iterator_type = typename
    detail::buffers_iterator_type_helper<
        typename std::decay<BufferSequence>::type>::type;
#else
using buffers_iterator_type =
    decltype(net::buffer_sequence_begin(
        std::declval<BufferSequence const&>()));
#endif

/** Return the total number of bytes in a buffer or buffer sequence

    This function returns the total number of bytes in a buffer,
    buffer sequence, or object convertible to a buffer. Specifically
    it may be passed:

    @li A <em>ConstBufferSequence</em> or <em>MutableBufferSequence</em>

    @li A `net::const_buffer` or `net::mutable_buffer`

    @li An object convertible to `net::const_buffer`

    This function is designed as an easier-to-use replacement for
    `net::buffer_size`. It recognizes customization points found through
    argument-dependent lookup. The call `beast::buffer_bytes(b)` is
    equivalent to performing:
    @code
    using net::buffer_size;
    return buffer_size(b);
    @endcode
    In addition this handles types which are convertible to
    `net::const_buffer`; these are not handled by `net::buffer_size`.

    @param buffers The buffer or buffer sequence to calculate the size of.

    @return The total number of bytes in the buffer or sequence.
*/
#if BOOST_BEAST_DOXYGEN
template<class BufferSequence>
std::size_t
buffer_bytes(BufferSequence const& buffers);
#else
BOOST_BEAST_INLINE_VARIABLE(buffer_bytes, detail::buffer_bytes_impl)
#endif

} // beast
} // boost

#endif

/* buffer_traits.hpp
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
*/