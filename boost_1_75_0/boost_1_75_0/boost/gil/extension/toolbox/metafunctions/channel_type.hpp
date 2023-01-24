//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_CHANNEL_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_CHANNEL_TYPE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>
#include <boost/gil/extension/toolbox/metafunctions/get_num_bits.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_homogeneous.hpp>

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/channel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/utility/enable_if.hpp> // boost::lazy_enable_if

namespace boost{ namespace gil {

/// channel_type metafunction
/// \brief Generates the channel type for

template <typename B, typename C, typename L, bool M>
struct gen_chan_ref
{
    using type = packed_dynamic_channel_reference
        <
            B,
            mp11::mp_at_c<C, 0>::value,
            M
        >;
};

//! This implementation works for bit_algined_pixel_reference
//! with a homogeneous channel layout.
//! The result type will be a packed_dynamic_channel_reference, since the
//! offset info will be missing.

// bit_aligned_pixel_reference
template <typename B, typename C, typename L, bool M>
struct channel_type< bit_aligned_pixel_reference<B,C,L,M> >
    : lazy_enable_if< is_homogeneous< bit_aligned_pixel_reference< B, C, L, M > >
                    , gen_chan_ref< B, C, L, M >
                    > {};

template <typename B, typename C, typename L, bool M>
struct channel_type<const bit_aligned_pixel_reference<B,C,L,M> >
    : lazy_enable_if< is_homogeneous< bit_aligned_pixel_reference< B, C, L, M > >
                    , gen_chan_ref< B, C, L, M >
                    > {};

template <typename B, typename C, typename L>
struct gen_chan_ref_p
{
    using type = packed_dynamic_channel_reference
        <
            B,
            get_num_bits<mp11::mp_at_c<C, 0>>::value,
            true
        >;
};

// packed_pixel
template < typename BitField
         , typename ChannelRefs
         , typename Layout
         >
struct channel_type< packed_pixel< BitField
                                 , ChannelRefs
                                 , Layout
                                 >
                   > : lazy_enable_if< is_homogeneous< packed_pixel< BitField
                                                                   , ChannelRefs
                                                                   , Layout
                                                                   >
                                                     >
                                     , gen_chan_ref_p< BitField
                                                     , ChannelRefs
                                                     , Layout
                                                     >
                                     > {};

template <typename B, typename C, typename L>
struct channel_type< const packed_pixel< B, C, L > >
    : lazy_enable_if< is_homogeneous<packed_pixel< B, C, L > >
                    , gen_chan_ref_p< B, C, L >
                    >
{};

template<>
struct channel_type< any_image_pixel_t >
{
    using type = any_image_channel_t;
};

} // namespace gil
} // namespace boost

#endif

/* channel_type.hpp
Pp29cWdMadbcs9e/GzdJbhWJD0Ak3uOUYikvCavS+Ok2OxlYqTCqYStQhRE6ecrwbeBUsA4jODkq6SJEaMZwLjbeL+IEcHEQc8bmoYzP1Mivqog63vil7FufM/XG+3O9iJgDScR1Ko0vbT8mjpdCIK3el0JYxuWRD2ZiSQTrFlYtLFabJErh/FJ8fbGw+8RO2HXhEriOdsKuzceEXbmk+wh+M1e8BDVeIyyewxXP5Iqn2YikFXDFI7nW1uoYuprfX8nWtFy9CXqWma0zFurzTNoMczYXbkPAcP6evhoPO8dKCnaUZGEXRCHEyC104tAgriutxqMy6dvv8ZiVc68nFdbUnrto7ld3gXy26oZ++rw2s4edLXSaus+Qom3W6sUB45nskW93t/5ZdrTFntjVy59kXtbvqRuwck4fw6ipwybGJHS96DR96Nma7d2fhLWZ2OX0xjcDbrWSaBsvuNOy1srzWz0KZobcvJd2JKrl4KJ6T9yGrZpqHjn56bGGTEyT/ROUX69YLXJa8CDjzwztrNImrZsM6BGnry3NzOk1d/ZPI5/unfIkpunV1y1O7wp4mNNg/e0NjR6cvvJEsWGe15y58YqW8sfs+O9qH/BV33x0sPnJ3ou3xIXIDsn2H/p8/e0vfrhcdVzn6B7BvgMb1Ryx6WmjF1ebhWoy537Rc3xGTm7ZdvOBcJF4Fd3Eq1VJa7f4dPnezfHPbkwZ
*/