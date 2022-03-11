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