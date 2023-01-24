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
mGLpAerOlmFUAC+NiUauVOUXUPdW4si/lW/SxQhM6fdSzgdTJvlm34IXo4pLCo/zfT4UO1PxrDsPF5ke8wAwQKbvout71ScugXn5RFoGHZjFGfrY1NuJ/7Wjuhtyqw9MvZpE78D5+6HqOgiBrrxUthaqG2Xr/upWpwnIvkQWHAK6zUMiaj1UWCBz+M7xFXTqv4+l5CCpEk4y3STJ9Y0kDkYE/HY6roHhKcyczs/3cMAOWbIv4dn6wCvZ2Q9cn1yr80fB6VuDefYpEIPhmobrDcOkKnpocjRLT2g0x3X+COQNkbwV3OT8Z89/4R0bR1dB+Ivv2Ijx8TxUO04wlAjUPIQsEnLTHS+9iKHbgYq1JGONu9Yx5PWViO/l0fMv5shG0hQbzCd0EDMx49TEeEuelWlcoZrhwbjI/kw1R9BeyjP/0TtTAxxiSM/HLgrpv3hILwvQegieJ8n6NbKjufuozsskOLvQOBqXCeVgWTXwODrXBGPiDBCSUwMT7XQMBnIwV4EGYX0okKf8+va41TVnsTqWeBScAY+IpEqIwGHAypDBtTMhOPzOwNiSg5HEq1jDgSVMi+ImtVBIda2LPJZ5JrNf9dbFXH0Exq4i+ihE6eNuqo9vY/q4F/XxwalXBfVxiurjfaiPl6M+bneOALIIfaSjsGCKVD+6JpSDCTkgshJMMN0Ed9EP++il7v4MFTGBDveCAJ6w3Igr5ghv
*/