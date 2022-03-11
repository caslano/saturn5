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