//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read Support

template< pnm_image_type::type ASCII_Type
        , pnm_image_type::type Binary_Type
        >
struct pnm_rw_support_base
{
    static const pnm_image_type::type _asc_type = ASCII_Type;
    static const pnm_image_type::type _bin_type = Binary_Type;
};

template< typename Channel
        , typename ColorSpace
        >
struct pnm_read_support : read_support_false
                        , pnm_rw_support_base< 0
                                             , 0
                                             > {};

template< typename BitField, bool Mutable >
struct pnm_read_support< packed_dynamic_channel_reference< BitField
                                                         , 1
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::mono_asc_t::value
                                              , pnm_image_type::mono_bin_t::value
                                              > {};

template<>
struct pnm_read_support<uint8_t
                       , gray_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::gray_asc_t::value
                                              , pnm_image_type::gray_bin_t::value
                                              > {};


template<>
struct pnm_read_support<uint8_t
                       , rgb_t
                       > : read_support_true
                         , pnm_rw_support_base< pnm_image_type::color_asc_t::value
                                              , pnm_image_type::color_bin_t::value
                                              > {};

// Write support

template< typename Channel
        , typename ColorSpace
        >
struct pnm_write_support : write_support_false
{};

template< typename BitField, bool Mutable >
struct pnm_write_support< packed_dynamic_channel_reference< BitField
                                                          , 1
                                                          , Mutable
                                                          >
                        , gray_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::mono_asc_t::value
                                               , pnm_image_type::mono_bin_t::value
                                               > {};


template<>
struct pnm_write_support<uint8_t
                        , gray_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::gray_asc_t::value
                                               , pnm_image_type::gray_bin_t::value
                                               > {};


template<>
struct pnm_write_support<uint8_t
                        , rgb_t
                        > : write_support_true
                          , pnm_rw_support_base< pnm_image_type::color_asc_t::value
                                               , pnm_image_type::color_bin_t::value
                                               > {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, pnm_tag>
    : std::integral_constant
    <
        bool,
        detail::pnm_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::pnm_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const pnm_image_type::type _asc_type = parent_t::_asc_type;
    static const pnm_image_type::type _bin_type = parent_t::_bin_type;
};

template<typename Pixel>
struct is_write_supported<Pixel, pnm_tag>
    : std::integral_constant
    <
        bool,
        detail::pnm_write_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{};

} // namespace gil
} // namespace boost

#endif

/* supported_types.hpp
LeaJ/bqCMU+/fanoExCN2zku2EcjuM1z1Fl+avP+cwTvfbsWXjGd8IDhqc6DuXdvuzeFwHGxF1xsX/81uE1DFm74cOXWgK6X5emPreJWtl1w2wwPGbzI/J/cp2Xu2SklMDDCb5Qhg6gTdsyX21iU81vq3U5hkqGA2thgcYXbLxBMxbOlWoVEfDpRhRGZHYIjo87uq466D+NiLBDxMY4u2dUo1Bvx7H31ep7dvebSunM3cte56J3+MePA3EvrTkwxBnv3BimjOVoa9Q8bXjbBzIfwwwZsZwXglCg/s9HZaRZbiv+YFukY6RgVR4Ucw/o35t8EpwBKciT6X//UiCjdfaWLCkIVuWaI+hoFJyL+z3jqKS4jg4GyiYiycj3+h011JkTxN9Z+1+N79+at0Gb64XJ35qaOzUpWg8VlDsRdBleCULEymeKZ8khpJLF1BClMKeANqSR6tuLGPzHEme1MJeprTJH0B5se/4SsQEHKLy/TfxGdZCp+zqOkON1iKc6etEvmSP8Z6xyoTO+998ViRDZL6CzL3zug3hCUr3gd/7VyREMIewAw2Jnrn3KoKBWXf/vudanY5njZyDc8TE2Nc+ku0T4TjZKkR3F6nbjHayXC8oQs3ZmqXbs5VzVH6Tw/Odl90q2NeUaWsAmfdTqE09zj1kPg9AJqQxDitrY8WjjMEzHwWDm3TRb1dveCiHmEGbNexhO4czcYOCAL
*/