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
SB1bl9BfXn30qrOBJT6Z1TXhVpfC1FTCQ173dXVx0t2kG94anQxplBD+LV8tb0WbMm+vk/opPmJCSlh/rpw5ioPR1mXOhC5QHHy8/eFl+ns9fNqA8ObscADwnU6z8bCx6MqjS12WoixLtsBqM3txhchpSwDpMLurNku64lS/jJlCwKeS0WnN4avXt1stZ8VJK+caLC7bX6TRNWHi8kez1uIfoNbvsg/wHqYJPbx2666avy0kM07xv+jtTGOtDBYaAfpaF9hfpNM2080aCtmLnAyVp973CBY1YF5Sb8be7IHXr8CkhlE17MuEAswNijIdlsBalibh6d9oetrfpwKEGpAn0rfOc/1K4vokycZwc7BB2rTRQvraj2b4JfNUbbNcIq3IGwizGSH2ZqO6zg5iIko2S9ov8NkIWKbaJLgFvw7/bvRs3kxmHXk2NF5TuK1TjlRLfNO2679X5Tbro2CuJjAn7ZaJFUY3QWZqkdWtK8qx+zKAlopN7koh8fI2mevoP2JD37NKKClB/n+HeE7TSica3Uwy/RdNJsl9xJyCvMqd4Pa7jR63cZqmblQEAdCzg46KeuFKz1Wvnaf1l8NIaWRl1uXZnrtTglXsF0R2oW9EDXm2CvU9QdlkMVdolY/3N97mzY9r2258WhUZfT2NggKm6q7cqhR1rSbPblet1J+V8gZXKHf//PXgrpbWhxSmxcPYAP/FL/W7v9pg
*/