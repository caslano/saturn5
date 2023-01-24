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
pLV2iYfkLG/kcfUjPNaoG0r761xEYTXafLbxQr5gfQb6LuS7FbTfp1zBkNzj8e56XebETv4qPopfavqMW5BTQusbKSzdP/SVIS7LezIF54lWkw2Rjcw338Q31n7Nuc67P9MGbOK9e98/u5/S2IDyI+ErUnOOfU8X3SfTKYVn69joRy026Dz5cai10oYE+j5OnXhhyN5YtR/0iBCSdrOOb8hAXjkCdaOr2i9HSqU+7J7wzd9eJctUV7GLq/1NhZVOvWReDnj57vynTD498z/cU1dbWOFvTtyS4mme0S/o/GnmeQ/25RK9lwpMU36MnbM9fuz2W/oTmE6w+y7mtE2foXtPdR36YrCemMyJc/ji5qrajfU8QcqnnhqL3NcGwFkvyZZM0qcQBie3QvSa8MvDreWrfpgvXMXkF30aeDzNTu+Jjm3oKY4GAeUO4gvezO4ZcwZDjpcnMY/N7tavB1zDkkXOZHGn6v7XXYzG0/fWW5DKWlYLVhU0/t88c9ORc9Xvw54opeDHOOcHkaJGGjKqneRNS3uVytMwASZqCEJXpYxYiiYfkeo9I0lstYzrWK7mr6yTxMApmSnBbqEH0871Dv/nZSjPPl9XYnmxEfJIuOHQiPL2qQ1Ag2xDNAjybCNU2qS3b17UlNVO6hO68mQHP1bv+s1K/xfjrUi2phWXrzwX8ugBCKXU/5/cdSEq3gPK4WpCHXLnI+32ArWg
*/