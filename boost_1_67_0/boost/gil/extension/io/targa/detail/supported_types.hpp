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