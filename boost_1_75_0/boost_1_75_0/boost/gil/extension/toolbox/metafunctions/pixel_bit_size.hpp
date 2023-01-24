//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_PIXEL_BIT_SIZE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_PIXEL_BIT_SIZE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/packed_pixel.hpp>

namespace boost{ namespace gil {

/// pixel_bit_size metafunctions
/// \brief Accumulates the all channel size.
///
/// \code
/// using image_t = bit_aligned_image5_type<16, 16, 16, 8, 8, devicen_layout_t<5>>::type;
/// const int size = pixel_bit_size<image_t::view_t::reference>::value;
/// \endcode
template< typename PixelRef>
struct pixel_bit_size : std::integral_constant<int, 0> {};

template <typename B, typename C, typename L, bool M>
struct pixel_bit_size<bit_aligned_pixel_reference<B, C, L, M>>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

template <typename B, typename C, typename L, bool M>
struct pixel_bit_size<bit_aligned_pixel_reference<B, C, L, M> const>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

template <typename B, typename C, typename L>
struct pixel_bit_size<packed_pixel<B, C, L>>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >

{};

template <typename B, typename C, typename L>
struct pixel_bit_size<const packed_pixel<B,C,L> >
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

}} // namespace boost::gil

#endif

/* pixel_bit_size.hpp
sw3W+WmK6QiuUaV+B62V83MBDn1BbWZDW04WELJkQez2VCMP+yyUhkitfGVK8IbvZOi7ggaorA5bUc+BrSv1ujxjSz2HsIiN1r7OHohyanvkfpV63bgjvwM0gtnkTZTzEh60pYoVNugo8oJGGxevxFbELzF5eeUmzZPUFdc3C+v2SbYPdk6sjSbxBOhHo1hun57EpQ1V91699Km6SQulrFUUIrP+ol4jx3QFuvNBhZCofjuQiGD7zp1vvPdwazx8mjtEuCd+Irf2nf960OCmmY2j0IvnIiJCFs6WFu4eNoIW9vYHrcSvtJVOABhFKkLVt8pi42p/EtLN3X7cd0vvXp5eSovkSXirFsSQN25No0biHXqXNKdojdFJ87WpdlhEVO9DIe0PjJYtQi1C8a/TGT8cn1buX35NJ5Tp4cpcRmCVRBTUPLx0dL08LuHgisuVa6MNLnLlREfOO1w2BVzhdRPD8lSBXtUmrQWWxtJs+sV29ae531t9QTBmmSrsLF6zP3yx1QAacAu9vP0Tjmh/fQv0uzz1b73ta1u9wJb0iZAyi3m/TfjdCoN+j5sGyfQSQ4D13n8ZAgGPhlB5K8t+LsBwca690n7fiSDxCw+3VKeUjOsVzdHru6+flesWfzZHrua4BRTmX4UwvROm6zDU6J716wr+ED8ysPV22mZ6dnCNX7n4l69oQUM6a4Mm54qZ99c13eW2Qjoiz6fa
*/