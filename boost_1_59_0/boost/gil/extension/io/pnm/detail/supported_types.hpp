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
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
*/