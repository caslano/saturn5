//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_NUM_BITS_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_NUM_BITS_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/detail/is_channel_integral.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// get_num_bits metafunctions
/// \brief Determines the numbers of bits for the given channel type.

template <typename T, class = void>
struct get_num_bits;

template<typename B, int I, int S, bool M>
struct get_num_bits<packed_channel_reference<B, I, S, M>>
    : std::integral_constant<int, S>
{};

template<typename B, int I, int S, bool M>
struct get_num_bits<packed_channel_reference<B, I, S, M> const>
    : std::integral_constant<int, S>
{};

template<typename B, int I, bool M>
struct get_num_bits<packed_dynamic_channel_reference<B, I, M>>
    : std::integral_constant<int, I>
{};

template<typename B, int I, bool M>
struct get_num_bits<packed_dynamic_channel_reference<B, I, M> const>
    : std::integral_constant<int, I>
{};

template<int N>
struct get_num_bits<packed_channel_value<N>> : std::integral_constant<int, N>
{};

template<int N>
struct get_num_bits<packed_channel_value<N> const> : std::integral_constant<int, N>
{};

template <typename T>
struct get_num_bits
    <
        T,
        typename std::enable_if
        <
            mp11::mp_and
            <
                detail::is_channel_integral<T>,
                mp11::mp_not<std::is_class<T>>
           >::value
       >::type
    >
    : std::integral_constant<std::size_t, sizeof(T) * 8>
{};

}} // namespace boost::gil

#endif

/* get_num_bits.hpp
x1WQULpDQFpEQEE6piIgUiIg0lLS3TCYdEuHxAYC0qF0jk7p7mbAgDFyI7a7e+9zn+d+uF/uds6283v/7zn/9z3bwClbLp8yMpdN++II6wo0Iu3FjkpDTaQA3wWbcpjFvfQQRNMbVRi/nofNrazzsm4LAkdI3Vsxx6OavO7as7TRtmKd4+dn9rt0Rh+idmA9yncRbUvMAT7nFc3asI5LpfybMQkus5X1b2oKraGV+9j0jQxUvvLNBNXsomEknJTZ5f69hcLuc5J2dQkUr6EXnjWh/MOVS43kseweV/iXpzamNsQsZDWkwSFf0odl9jVlLe81URH2VF/L6rMiTvz7M+DMFZCKPdk6i0VtXZDRTSwLuNaNVilN3LQb4p5+arNoYCtuQvbyrQmEAvIYcgekzsxwL6xtrHNMQyVao/KJXAct221l2Q8CQ1mzz01phUprTpq7ByQqkDBD/8RhTj75NMvnNolU1KLjkSzywZxB/plK1+i+l+SRUVFVP6nn8uQRgU5g6xlLmA2KpbSA+0EO5Nir4u1xcLbBr978yqTPepD6uXG12aKidPLbSopviB/tw3kTdKfPgjnVGdnY2AAmn8EBc3ybeJvbXUpY3dhRkytfnvNm6jK9BsFKebajjm5OXl+xymp3lc/FXz7//c2oe7T6WfQAWUKnpZRm71dXjRi4AQ/DLHorwcjzmeTthKZeTnGy1OGHQhFs163X
*/