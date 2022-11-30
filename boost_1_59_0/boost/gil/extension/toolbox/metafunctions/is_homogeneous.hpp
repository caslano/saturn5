//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_HOMOGENEOUS_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_HOMOGENEOUS_HPP

#include <boost/gil/pixel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_homogeneous metafunctions
/// \brief Determines if a pixel types are homogeneous.

template<typename C,typename CMP, int Next, int Last>
struct is_homogeneous_impl;

template<typename C, typename CMP, int Last>
struct is_homogeneous_impl<C, CMP, Last, Last> : std::true_type {};

template<typename C, typename CMP, int Next, int Last>
struct is_homogeneous_impl
    : mp11::mp_and
        <
            is_homogeneous_impl<C, CMP, Next + 1, Last>,
            std::is_same<CMP, mp11::mp_at_c<C, Next>>
        >
{};

template <typename P>
struct is_homogeneous : std::false_type {};

// pixel
template <typename C, typename L>
struct is_homogeneous<pixel<C, L>> : std::true_type {};

template <typename C, typename L >
struct is_homogeneous<pixel<C, L> const> : std::true_type {};

template <typename C, typename L>
struct is_homogeneous<pixel<C, L>&> : std::true_type {};

template <typename C, typename L>
struct is_homogeneous<pixel<C, L> const&> : std::true_type {};

// planar pixel reference
template <typename Channel, typename ColorSpace>
struct is_homogeneous<planar_pixel_reference<Channel, ColorSpace>> : std::true_type {};

template <typename Channel, typename ColorSpace>
struct is_homogeneous<planar_pixel_reference<Channel, ColorSpace> const> : std::true_type {};

template<typename C, typename CMP, int I, int Last>
struct is_homogeneous_impl_p {};

// for packed_pixel
template <typename B, typename C, typename L>
struct is_homogeneous<packed_pixel<B, C, L>>
    : is_homogeneous_impl_p
    <
        C,
        mp11::mp_at_c<C, 0>,
        1,
        mp11::mp_size<C>::value
    > {};

template< typename B
        , typename C
        , typename L
        >
struct is_homogeneous<packed_pixel<B, C, L> const>
    : is_homogeneous_impl_p
    <
        C,
        mp11::mp_at_c<C, 0>,
        1,
        mp11::mp_size<C>::value
    > {};

// for bit_aligned_pixel_reference
template <typename B, typename C, typename L, bool M>
struct is_homogeneous<bit_aligned_pixel_reference<B, C, L, M>>
    : is_homogeneous_impl<C, mp11::mp_at_c<C, 0>, 1, mp11::mp_size<C>::value>
{};

template <typename B, typename C, typename L, bool M>
struct is_homogeneous<const bit_aligned_pixel_reference<B, C, L, M> >
    : is_homogeneous_impl<C, mp11::mp_at_c<C, 0>, 1, mp11::mp_size<C>::value>
{};

}} // namespace boost::gil

#endif

/* is_homogeneous.hpp
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
*/