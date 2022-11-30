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
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
*/