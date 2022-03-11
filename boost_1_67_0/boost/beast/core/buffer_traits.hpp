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