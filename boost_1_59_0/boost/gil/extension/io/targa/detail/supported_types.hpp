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
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
*/