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