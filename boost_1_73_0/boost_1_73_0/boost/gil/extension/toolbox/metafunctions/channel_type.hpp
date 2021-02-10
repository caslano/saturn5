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
XbQ6XaN/fXl53mmfrqAmacRSg33qXX3sD1qDTu97RizCLqeevZPWuQH/VjCzBKfcOp1/an3ur+ghNKQFgwgPZww+XyqhLxshj1GSfL999Xv7ahXyAqMs+Q8lLDmHUNqSm6ubcnOJH1K7DMaO8Ev/stftL51BIVKJQVonJ+3L1YfJoJUYCBxEdwBL1++jKZUQ2lzEUmsjV7TTfd8rvzoaUrGvhVirrK9t7s8hcVCexMEcEoflSRzOIfFbeRK/zSFxVJ7EUak12wWSpddqtyRRUBij/c+TD63u2Qobuo5VapiDw/LED8SifFubF4hP+GMmDLc8F9Iua2IGbGM4G9chT/qDGxFzuCvCcR3AZ28YAB2vYSaBtGtM0KErisMwgvw2AA4bj2KCDxNI5qpAcWuLvWWN9Hxi6F8bze3mYwXSkDg1wHRkw9/cpDn9wp2Qz8k8RKbr+UYYTaM4vRXFE5r+iFveCOb15POmEZnBLYdUWK84wf+zUNasCJaywIoABUbGXkXl71SNQUpbTTaFlNG85UhGlf9UIevSDMwpj3gQl2ywaiIKnV9s9yv9sEWpbwhUbM+VwkQCKOYxDwpgBXejDAOEg0tXSN92/VmkSCJUHauMDseMe6/JsGgSbitZxRR2vFn0VVIQFSjkP4yC
*/