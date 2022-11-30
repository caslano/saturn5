//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/packed_pixel.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< typename Channel
        , typename ColorSpace
        >
struct bmp_read_support : read_support_false
{
    static const bmp_bits_per_pixel::type bpp = 0;
};

template< typename BitField
        , bool     Mutable
        >
struct bmp_read_support< packed_dynamic_channel_reference< BitField
                                                         , 1
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
{
    static const bmp_bits_per_pixel::type bpp = 1;
};

template< typename BitField
        , bool     Mutable
        >
struct bmp_read_support< packed_dynamic_channel_reference< BitField
                                                         , 4
                                                         , Mutable
                                                         >
                       , gray_t
                       > : read_support_true
{
    static const bmp_bits_per_pixel::type bpp = 4;
};


template<>
struct bmp_read_support<uint8_t
                       , gray_t
                       > : read_support_true
{
    static const bmp_bits_per_pixel::type bpp = 8;
};



template<>
struct bmp_read_support<uint8_t
                       , rgb_t
                       > : read_support_true
{
    static const bmp_bits_per_pixel::type bpp = 24;
};


template<>
struct bmp_read_support<uint8_t
                       , rgba_t
                       > : read_support_true
{
    static const bmp_bits_per_pixel::type bpp = 32;
};


// Write support

template< typename Channel
        , typename ColorSpace
        >
struct bmp_write_support : write_support_false
{};

template<>
struct bmp_write_support<uint8_t
                        , rgb_t
                        > : write_support_true {};

template<>
struct bmp_write_support<uint8_t
                        , rgba_t
                        > : write_support_true {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, bmp_tag>
    : std::integral_constant
    <
        bool,
        detail::bmp_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >::is_supported
    >
{
    using parent_t = detail::bmp_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const typename bmp_bits_per_pixel::type bpp = parent_t::bpp;
};

template<typename Pixel>
struct is_write_supported<Pixel, bmp_tag>
    : std::integral_constant
    <
        bool,
        detail::bmp_write_support
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