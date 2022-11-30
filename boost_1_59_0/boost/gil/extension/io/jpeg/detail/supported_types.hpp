//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< jpeg_color_space::type ColorSpace >
struct jpeg_rw_support_base
{
    static const jpeg_color_space::type _color_space = ColorSpace;
};

template< typename Channel
        , typename ColorSpace
        >
struct jpeg_read_support : read_support_false
                         , jpeg_rw_support_base< JCS_UNKNOWN > {};

template<>
struct jpeg_read_support<uint8_t
                        , rgb_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_RGB > {};

template<>
struct jpeg_read_support<uint8_t
                        , cmyk_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_CMYK > {};

template<>
struct jpeg_read_support<uint8_t
                        , gray_t
                        > : read_support_true
                          , jpeg_rw_support_base< JCS_GRAYSCALE > {};

// Write support

template< typename Channel
        , typename ColorSpace
        >
struct jpeg_write_support : write_support_false
                          , jpeg_rw_support_base< JCS_UNKNOWN > {};

template<>
struct jpeg_write_support<uint8_t
                         , gray_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_GRAYSCALE > {};

template<>
struct jpeg_write_support<uint8_t
                         , rgb_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_RGB > {};

template<>
struct jpeg_write_support<uint8_t
                         , cmyk_t
                         > : write_support_true
                          , jpeg_rw_support_base< JCS_CMYK > {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, jpeg_tag>
    : std::integral_constant
    <
        bool,
        detail::jpeg_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::jpeg_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const typename jpeg_color_space::type _color_space = parent_t::_color_space;
};

template<typename Pixel>
struct is_write_supported<Pixel, jpeg_tag>
    : std::integral_constant
    <
        bool,
        detail::jpeg_write_support
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