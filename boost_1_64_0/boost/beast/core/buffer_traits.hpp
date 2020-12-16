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
jDuSnkd9lKf55m9rFmL7y1/DugYZWJnHQt88Mp5T1oYXq7Vhr3Vlr3KUnEQ5CrVyONkfF4ufuo9H/eek+5bvNvDn+S0flo0Dl41xnH6fd3O0cLUue4rl4vM58DNwkG+ZLgBvub8ybaioW18dUKYYxxmoT6tw1f9PokyazHntkZB7KPsqrbZAdk4C2eUIZP8kkL2OQHY2AtnlCGRH5fTZPwlk7yVG/PukD7rm4opxxV9MWv1E9mU/+DCQ3ZJA9k8C2SEJbLfkU9qKwCXfhiNMPS4QnhFic8MOCtd+x2m/47XfUdrvWP52gHpqv0O133203zHa7wjtd7T6DdJ+27XfkdrvXumu/MeAPoZ7t7WPi3vHECZzx1tZXtMGSAJtfoyi7vU04A+oW/U8dawPAtcDfwhsBf4Y+A36Xw/8CfBm4CHgXurOvUxduV8BfwP8PdP/DPgr2hb5NbA/8B2lU8Z9PPwd4aVTVo5Obrorgf2AK4EZ1DnMos7hGLrH0X0WdRCLgHXARcA1wKV0lwPXAluom3gJdRO3ARtttNkBvJluM5+l1r4UwDjJJwhYYK27gi8KmMD8JgMTgInAfnSnA5OAQ+keBezH9HeAiph+GNstGr+3M/1c8CUBJwH7AycDB9F/GN3nAKdS5386yzcNeAHdW+n+Ot3XmkWiTn8+8ADwbKDY2AF+CjyH+Ttofb/nnoEIL9sqt1GubgcOoI5SOnWUBgP3A8dQV2kOcBd1+h4ELqONhOW0kbCWNhLOY/gG4EOUw3agmf+9wGuAjwKvJ98ddN9D9wOM105bOY8zHy8AH6P8NRj8Bg4sZ7nswCpr0kXdrGnUsZtOHbuzqWM3AyhbnICTqLs4je7ZdM+lLuNSiUddQfV9GN+92d5mPU0EmlchdcHmAzOAC4DZwGLqCi4E5tI9he6ZwEXA+dRFLQZewHpdyvpbRptA57JelgOfBJYBDwLLqfNZAfwtdUD/Qt1TUy5XA+1A0x1FdyywDugEmukOATYCxwCbgBOAzcBJwPXAacANwFnA84GyZwhYBNwIRB+VfG8ArgXeAKwHPgBcB3wYuII2gypZn23qWyOel2zHXny3NK/f0+bGUbbfB8D+wGDIdxptRwwHfsR6/pj1fAyYS/dU4J+po/op6/Vz4PnALyiPhg35ZbpKJ5vfoIYwX7pOqIPjRhTQCezJft4L2J/uVLotXboGpjeU6em6dNngM0w34402y0d3Bt2Wjmw703EyHV1HdjDTGQoMM/2B8cAsoNK11OIf89K1dBhuvmNd5Is+R8+PJ1+Mdt/sc7qWXlEX+Rq6yNfWRb72LvId7CLfsS7yRRd2zjcOlE2+ND/tvpTyuIxyeC7lcJkmf+WMn+1H/uZTbhYAY4ElwBTgIj6nSoFq3GU6V/sZdy+iTnYr/vejbvMATZd5C8fXrwOL6S6lbncz/S+mewvd1MXlugLKxPvqurjfoA77NcChwG8CJwBvoO70Do63NwNn0X8+/Uvoz/bAe3bg9rBrfEZR1/hSusiX10W+8o74aJvt+BzoJBaEG8NBBaBAurG6XqyuE3sURD1Y6r366rwWU9f1BFDXZ90Natf1VuFumeJfPzUPRJ1U0UWtou5pFfJ8HKjpmlLH1Ee/VOmUFoGU/qh/vVGlJ1oALHoupEP90G3Iw7J83Ae4H3QYdAKUcg50OEGloE2gW0H7QIdAx0EJhdDhBFWBtoB2gV4BHQNFz4UeKagU1AraCXoOdAT0OSi9CDqkoDpQW1G3fmf31X11X91X99V9dV/dV/fVfXVfX/0VAlr5Fer/l0GFv1rU/r+c3r+ph/+XNEPpTBziOmwe9zTkgv4cizWLifLdcW7RjMIFCwo=
*/