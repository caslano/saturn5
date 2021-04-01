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
/ANatvZSyvnV+vthU+Ixc5Xm2FQDt+kDm60Etd0y4W204Zro0yBnzlcueWMmFdkcqoeOiTkM6hZ4CUxM1Yd2ZsegSGa9+VPHaO/gqmHUbGv+bBd/tniMqd0pGjZ6yu3hi0ZOzZAttDze+GYg5okyOmP+49i8iBlzTTlQXDb63ORMS4Ao4fPO159tkA4vQEeTEKoKJjdgDGu5/uJvjVXhO7hFpCg7PKZ7kV8nFr3fEde8zI6TJmKxkzDOgpFvHiXoUJmgnySY7jNLiSPDUAx0olV44ksaXs1+h13+7MTiKtApiA6z3vEGGGR/B9MKL4XQbioeKXX4zqMG0YpGYhPbZj6MPd3oyqU1eRIGwiUhs27VCTgopZioK0htl8riGdHNoQp0fHNva+lu/Z1z/pK9OYt8KaAgxUdQx2TihAQt5EnV2NWDZfn+vjCxzPUZPTj1z6wRSlRRNQIBC4SntC0g2rut9ujCIZyCoZwS+GSBIoqPIN5F9IYAmSLE9Unf9upQJueYZWKoTU72TmkKqsIK+c/NM3O8UEl5xLFtRGQP6IZw3EXrKQs5pJvoLA==
*/