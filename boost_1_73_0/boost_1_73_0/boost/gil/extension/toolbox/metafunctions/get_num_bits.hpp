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
pjMDxy4oYZUsS4iu5ejUwaUvIBRyaxbY0ZPcDtZx6QMecjdC2lFg+w4ooNoLfY/cjwe3EseJIYEdRrgBYLX0wRNTCmkn8GBvRsZeiSXc3dbkAIiRabuIiEoNIr6NJqriKrcnhAFmcLNV+xJ8mgvIkA6aWEUPfdRhLH1rBNOE9rYTaWboSKuHyeJvsEGpI7wcqXgfGAfyDGzIb23XVRJRG2a8OeOhiohGyCFixdywQ1HtD2c+Ht+AA58XkHBcQJgg2JOgi15CYRWEG6wLi5DZiAdX1208mCR8+C5CjRH6F8ce0kEj7ctDz3MWMkmbCO1j0jKQcmwV+gTlbk74YkuX8lgWeYEtmA5uGk+MuyLaKYi5xEmqFoDRmUsAIY0KkWh1TCbOmtBEcX1An1GbA/MhbcGou9aEW3d8RKeYoEQgdntEpoKnaiIiNH0/8CB0xeUg/4iAFjBL5mAKHvdiquJI9AEMDpRaqdYthIluLqQC51EidFweOZKop+FtFlSKQUm0IH6Mo7+fHfzFUV8ZZXl2AIgfPYtRAlqRxIKITgaz2iByCmZwB1vUV9ha/mSNx0azjl8b+lf2jXaZnY0iFU8049WaxmzHHfFHxk6pT8HHg1ydzxPhQFOTa+AXeXzF+vFJGH26M8fZwmN52yUn
*/