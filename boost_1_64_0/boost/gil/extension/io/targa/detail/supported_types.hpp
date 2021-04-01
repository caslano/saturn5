//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< typename Channel
        , typename ColorSpace
        >
struct targa_read_support : read_support_false
{
    static const targa_depth::type bpp = 0;
};

template<>
struct targa_read_support<uint8_t
                         , rgb_t
                         > : read_support_true
{
    static const targa_depth::type bpp = 24;
};


template<>
struct targa_read_support<uint8_t
                         , rgba_t
                         > : read_support_true
{
    static const targa_depth::type bpp = 32;
};


// Write support

template< typename Channel
        , typename ColorSpace
        >
struct targa_write_support : write_support_false
{};

template<>
struct targa_write_support<uint8_t
                          , rgb_t
                          > : write_support_true {};

template<>
struct targa_write_support<uint8_t
                          , rgba_t
                          > : write_support_true {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, targa_tag>
    : std::integral_constant
        <
            bool,
            detail::targa_read_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{
    using parent_t = detail::targa_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const typename targa_depth::type bpp = parent_t::bpp;
};

template<typename Pixel>
struct is_write_supported<Pixel, targa_tag>
    : std::integral_constant
        <
            bool,
            detail::targa_write_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{};

}} // namespace boost::gil

#endif

/* supported_types.hpp
kSo69CcxpK5dKI03LNUYuwqM4Fy8rpG3bQb4nPZlP2lNY6rCZysh+kRVEhhEovL5EERUMbv88E5hAx2QxxnXyr/Gq5IJE6ITOCDVM+wW3DDIfq/XFBXPRSmGYY8HJdMnqIP5VjMhksVZzF8UkepSfPUVf4yW9vbjZDURxK7lux8TPlMRmKyQr4yjFIspQz/xMot5yT+0D0G3oC+bC3KFH4rwI5rK1HMq/pzwDc+8j1tb/+qqh7sS20+aqZvcGOEC5AdtrJcJc5e2TOvHb1+pXGxhWN8Op8ng9HK8z8794SV/Yb3usb9yH3FBREQBrvEbTr2Lss8EjjFEhtii1bnHHluWJ6AHfy39vLm2Iwky76JFt6h2PL1Hf4bzCKON/+jFIDA7BHBkQ42gkr/SfWBgtwt+axlfypsEaKiMmCbZV5Qz+SO+hssQ7sH1obcTQnp+ljDORhiJrgNmBZhINxn922NI5MMVJa6bhdoFyH4GGDKjLkUD5J9ipQt2ZVwalB+pkGVvujACyMhbd7OrVD9P0hIUgbG+99zyndPIveQvU6u7A2IsQjX8AK9MKw==
*/