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
8+gCbGReew8APUoJCzOKhDgrCMp36vmx1ZdFwA89EgRH2Lyx7rRT4MYQFheIxohwFZlE3W5adQ5Q/wXrpL7IxPu26gqXsN/uSJBdQKX9y/VIm7hquFLI+qFAaUU6EQTwpxIdrNnQ4Y4NvuCkF8p6kl3eoLXmyh3hCCZQj9jAEul1ArTyr6/eMzq6X5ty3GJKHxfc6t7k1ciQKDKQfe7VNLipSnIqBaTw6j/GEXLKzLdrC93V/MmMxBR9LamtIwc4Rx/v5tmD8bgxErAb5tKvK32IyweGq83YAaI0Sat/0a3Xtdtu6ZGHQJMeiSm41k6ThuPIqWL3+F0bKWeWCLmGB0N7tt5zbxIkMjvKU8y4Z1EOlZvqOg+9BYvXbW7PtonIdDSBfg5ycrkCkND5cTnJ4vqCve3ZwaKFHAvq/5UKLg+5jM4m5x0/lCzoSnqGStauQG6/23cpsiYVZWC/vbD3/Of6OrZL4Rf+5AbDKimhvlQuOYugM4MwOmSUQhV8ZarGGtvXNAvuHajfsv0l7ES9gQKFRKBQ0STF2Ly44zPotpY1X6dBgvoX6qRbJQ==
*/