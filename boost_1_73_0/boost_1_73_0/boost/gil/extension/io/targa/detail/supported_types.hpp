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
JAbomK1lZm18rYMKg4zCWSz4WPhAETUKrTi+ccKqRqsxvw0idp7g0bULqn2Gan6MRQvoFU1ovpMEDfgU/w3Bn6IqGSskOBjSJtGML2c5DhXUsDNnQTeKDZCtvryB+ICyYxYW7nDJQk391yTweDommZ9Q9ARFCpMpMMzyJBVRKaLIN7wkikS1Z6iCcYPJjbzDzG1pIqqgiFI74abSiu/EGkrLkm7UVzuYJgCSo6/or0TsKyAoEVsWAm8/s7hl3uQazzRrlDzbRUYPGQ/rfUj7NLfQ1k5ukzxhk6mB3Kss+pw8nZcIQoXgL49P32cAXvR7w4m8vdwGoSm2EU9Ez2y33agd0jOcWPGkUWvynC73npr9wb5f9rZ/yh9lxrfQEHNfylDq55juylNiWUubsezslPAeBamfXGICrrXFn14rawHKcRI4l6xUoAVmK8D4nRz1L45bJhGqCbWalxfJpywOfZH3MfNshkNf4wjPRhuLwjrlr7OPumzggx+Ux2DcJgAd7Q5+BSAC0Onm0/o1wDIgnXtBMYToa6gwwHR0AtKMg0pREE/2W9DdPpgQ5VXQbqmytnHm4KHXOw3zYYIjB+3WsV2rg2Hb1pIh0a/gb+ukBK+T3L80fU8ioCRklYlnk4Xicf7i3nxAXOJjCuFg
*/