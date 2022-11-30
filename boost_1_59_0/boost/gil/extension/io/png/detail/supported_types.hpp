//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
#include <boost/gil/extension/toolbox/color_spaces/gray_alpha.hpp>
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil { namespace detail {

static const size_t PNG_BYTES_TO_CHECK = 4;

// Read support
template< png_bitdepth::type   BitDepth
        , png_color_type::type ColorType
        >
struct png_rw_support_base
{
    static const png_bitdepth::type   _bit_depth  = BitDepth;
    static const png_color_type::type _color_type = ColorType;
};

template< typename Channel
        , typename ColorSpace
        >
struct png_read_support : read_support_false
                        , png_rw_support_base< 1
                                             , PNG_COLOR_TYPE_GRAY
                                             > {};

template< typename BitField
        , bool     Mutable
        >
struct png_read_support< packed_dynamic_channel_reference< BitField
                                                         , 1
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
                         , png_rw_support_base< 1
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

template< typename BitField
        , bool     Mutable
        >
struct png_read_support< packed_dynamic_channel_reference< BitField
                                                         , 2
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
                         , png_rw_support_base< 2
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

template< typename BitField
        , bool     Mutable
        >
struct png_read_support< packed_dynamic_channel_reference< BitField
                                                         , 4
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
                         , png_rw_support_base< 4
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

template<>
struct png_read_support<uint8_t
                       , gray_t
                       > : read_support_true
                         , png_rw_support_base< 8
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
template<>
struct png_read_support<uint8_t
                       , gray_alpha_t
                       > : read_support_true
                         , png_rw_support_base< 8
                                              , PNG_COLOR_TYPE_GA
                                              > {};
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

template<>
struct png_read_support<uint8_t
                       , rgb_t
                       > : read_support_true
                         , png_rw_support_base< 8
                                              , PNG_COLOR_TYPE_RGB
                                              > {};

template<>
struct png_read_support<uint8_t
                       , rgba_t
                       > : read_support_true
                         , png_rw_support_base< 8
                                              , PNG_COLOR_TYPE_RGBA
                                              > {};

template<>
struct png_read_support<uint16_t
                       , gray_t
                       > : read_support_true
                         , png_rw_support_base< 16
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

template<>
struct png_read_support<uint16_t
                       , rgb_t
                       > : read_support_true
                         , png_rw_support_base< 16
                                              , PNG_COLOR_TYPE_RGB
                                              > {};

template<>
struct png_read_support<uint16_t
                       , rgba_t
                       > : read_support_true
                         , png_rw_support_base< 16
                                              , PNG_COLOR_TYPE_RGBA
                                              > {};

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
template<>
struct png_read_support<uint16_t
                       , gray_alpha_t
                       > : read_support_true
                         , png_rw_support_base< 16
                                              , PNG_COLOR_TYPE_GA
                                              > {};
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

// Write support

template< typename Channel
        , typename ColorSpace
        >
struct png_write_support : write_support_false
                         , png_rw_support_base< 1
                                              , PNG_COLOR_TYPE_GRAY
                                              > {};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 1
                                                          , Mutable
                                                          >
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 1
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 1
                                                          , Mutable
                                                          > const
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 1
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 2
                                                          , Mutable
                                                          >
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 2
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 2
                                                          , Mutable
                                                          > const
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 2
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 4
                                                          , Mutable
                                                          >
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 4
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template< typename BitField
        , bool     Mutable
        >
struct png_write_support< packed_dynamic_channel_reference< BitField
                                                          , 4
                                                          , Mutable
                                                          > const
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 4
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template<>
struct png_write_support<uint8_t
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 8
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
template<>
struct png_write_support<uint8_t
                        , gray_alpha_t
                        > : write_support_true
                          , png_rw_support_base< 8
                                               , PNG_COLOR_TYPE_GA
                                               >
{};
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

template<>
struct png_write_support<uint8_t
                        , rgb_t
                        > : write_support_true
                          , png_rw_support_base< 8
                                               , PNG_COLOR_TYPE_RGB
                                               >
{};

template<>
struct png_write_support<uint8_t
                        , rgba_t
                        > : write_support_true
                          , png_rw_support_base< 8
                                               , PNG_COLOR_TYPE_RGBA
                                               >
{};

template<>
struct png_write_support<uint16_t
                        , gray_t
                        > : write_support_true
                          , png_rw_support_base< 16
                                               , PNG_COLOR_TYPE_GRAY
                                               >
{};

template<>
struct png_write_support<uint16_t
                        , rgb_t
                        > : write_support_true
                          , png_rw_support_base< 16
                                               , PNG_COLOR_TYPE_RGB
                                               >
{};

template<>
struct png_write_support<uint16_t
                        , rgba_t
                        > : write_support_true
                          , png_rw_support_base< 16
                                               , PNG_COLOR_TYPE_RGBA
                                               >
{};

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
template<>
struct png_write_support<uint16_t
                        , gray_alpha_t
                        > : write_support_true
                          , png_rw_support_base< 16
                                               , PNG_COLOR_TYPE_GA
                                               >
{};
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA


} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, png_tag>
    : std::integral_constant
    <
        bool,
        detail::png_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::png_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const png_bitdepth::type   _bit_depth  = parent_t::_bit_depth;
    static const png_color_type::type _color_type = parent_t::_color_type;
};

template<typename Pixel>
struct is_write_supported<Pixel, png_tag>
    : std::integral_constant
    <
        bool,
        detail::png_write_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::png_write_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const png_bitdepth::type   _bit_depth  = parent_t::_bit_depth;
    static const png_color_type::type _color_type = parent_t::_color_type;
};

} // namespace gil
} // namespace boost

#endif

/* supported_types.hpp
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
*/