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