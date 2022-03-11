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