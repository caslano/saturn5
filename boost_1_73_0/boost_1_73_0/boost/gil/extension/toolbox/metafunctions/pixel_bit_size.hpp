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
Z2LrNzfrqnnnBV4T9lMMu7Me9xkQqDoyVVONa4osGZsgYUMXQDLSxWubm+KslDEqwWmjSjKSZUFGNvHQsCoMPsNGZGxvNa2J7XIIl2bu1n/NTIfCHa3solp6Rx4P3XUwF/tOdBCNYRt5Enad4On1K9WAc5J5tUpVZNWyLwV/qdUK23N0nBq1OPARHVtHtjvDSAmDeNhUXyQH95klVhKS1JO7UiQ0uOwqWbVsavzerK2V6xtJHreVjGRNXj5q0HjcPZIn5GkI2N4hLH/6UnxXmPbEDCeKAgGl+7Hw1TNSsJJa0g+xrPWqgFz8Hhljemdg7wWMLsmruCue1w8bBacpRkJdrisVr0u1q0vLWSlaU0zWNTGuwjDYEkUagYo0ZG1owURoGghfTYZMVqU88y+15hZw+nW5X63IvYyUVuBfLsQPmIGoXdTFTMTuVFfbWPnOQLqa2gkTcik/Gb+W6LtPSOLTDurBvDg9ME47Z1gWOW93zwYf2O5hvGkztWkLh/uJg3aiA5VPOoi6Bz5x8aDuUDdjhp/Yi5ZyMs/xMdHUn39zOjoIZ9MvxbNe6rJiVeOiiiGSyDiIRNfkTVNPg/1g3wVjFw0Ge5sV92PjyQ7Zj+JBNg6Ki5mRFdVLcyRKSXiQEGqYIY8kpujJpG78
*/