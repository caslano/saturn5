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
RphDO2jqb9isp/8V+YwN2hu4v4k8nfMdPt907BTo45tp8CQ28rus9aF3oHd8nbZFxMzb4Se8iNzubkDXyEZ09dQ34d2pVjxR5NWz0XvYy/0uBdbYkHeshh8C4PIUbJcOyO+6+M6Xos/9+LC9iZFa50eh0T/YF9iBTzESO6yUOX+OrDhwBvY8eqnVIGjpFOQ9/Jk+DlOzMTER9mqOPYF3z2ROXeCny5EvVyM7af8iMJJprL3YkK8a4sNN5vwvNGvh57072NeLwY+cj0w6AJw6wmfsvWyzzgO8Bd1/QMydsR7+ENunlL6ICcdNRWYgf04GF1ugk/P+imy9GBzM5flTeADa+HABPvyL0EUWtPgE8Yst6PJ3wMXzyBT85WbIkdAsbK12xAxZ803HYZcgF/O8xIbQO0XA+THOJzfDJ70V2bSBNQyBli4rQM9shY+/gRbRB9a+Q3IZNv0ZwLwnfjI4uQib6eqbkQ1PAhds3BmXYZMPxvfAVvgZo8m3HTx+Bm8d4IxKHvtyXZE132G/oGOX4tNfxTlGQCvtoOOCF5ER8NKq1zgnBY/+MhQ6wc8LQXsN/hY+B9ge2k5kX3DkNOTc+8BjJ7JkNbz3FDyI/5gJ3Be/jW8Aja2w9lbroJ/B6Y2b0bvroKfz0KHokG+Z22Jk8o/EsgajJ89/C5l2E/HsJGy8a6GXztic0GYGtPSKdT71Fvw2YlyBO7Bn8SdexhcrQkbcjZ01Dv23jjhgPWjqvo/ZR4I/xtdhDvTX0kB2XQa+/OieYcjzduxbdkTn/kE8MAGZC+2cGmDfZDzvbAJmKdgGxJ+tO7Ky70Je5zHPVGTlBs7/QDfLkDtPQZPWWdBzc9nD/Ig5WOdoWmJnQI+vrsWmm48NVh9cnwZ8Y9h7morssmL5ucypPvuK6KaKs6FnYrihq6HHuHDukgQQ0XAesGC/bQR49JvIqCnwPfHzvuDkaebcoxi9DI8tzMWXxBd8xOTZmmcQ2yyIjf8XbK8gfIh8M334qdDMF9jmKciIeWMM29a81A++W+IfpeN7YMN70SWZsciRCvyFo7FRtiJHb2De+FNzNmI7DwCO2NKJydju+9Bj0F8v7J6xyPUWXZjnanTZC/2MweFEEJICr/8AzU2QP/4ADfw/nF2h76nhnwX8vZ7fHfl9jvN9eXpphS9o5yvjc14rzaD6rtwpTy0tU1VO3gOnLrkkhy9U5/jUt/xOufqQmL5UudOe5Mf+fCt/Zz37fpoyNXcrOUKGN45sTRP4WNObnpGYmZgan6g+PI9eaeXguM9ZR1a6N55ECiNJwkCL5LQMq2lS8ugk9c1/1PrUtIxxcSnOuqK2SUmbqNYRvT45dUJcSnLCIdvEp2WnZtn5OLV1m9a6ozVXq45WxZrtPAEBqcqrUifmUHn0cv2l3lA4BXP4z6qcUOq9JuTdsCBYj+ej+CkTPXcSsR2Vu6lBlPaBuge3P1q1b6Taq3xOqn+9LefOVdvjVNsWtK2j2lptmtg5qPT8H3WksXqnSfgdJ29IPb1vypupds1VO5Xbyun7KG0MfrR8JHWlpXq3lXvN6p3WMfqc8GVU+7Yx1XMT0lbdh2N/v22PWd+6KUU9N+Q5RnIr+GDb+Sb9GMpaSW6QFJdiPcfEWDybS7akkETqe0juDJ96bspzX8krCxaF+2zB82DJ433VpyobIfk+rt0qrZRwWTvKkoQUBEW5pEP0Wh3YuX4agpj2MeL8S7dpiEw4haX5DinpJVDUJsWHRDHSRnrTRo7ha3FSZ2R5SeWWaH2RnZWRlkL+DiulhpOT4pBtx8VN8o6MS02YmJyQFebhOodsn5AZn+7Nihsd5sN6h2xrM6x3VErc6EwrRxA=
*/