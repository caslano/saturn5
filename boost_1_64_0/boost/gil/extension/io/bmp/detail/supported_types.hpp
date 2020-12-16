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
up++NXaL0HfbAe61LSirv4C6AmNPqx178pmMEv6pTHwsmhjXzcx9x/BjAdvo69BfvjRc7U/D8/jA3nA8nRoedb5A8LxEnUO8PiF5uXukgq5uD2hlNn337OBdup+ydcz+ePktp09bnP0dpjYVkuP9QH8fx0hwDA19n1a7EPkbEzKMhr/vE9bpXTyTCU2SNOCl7cbQjCQ2xzUzjqmQAXW8f9GiMImk7yLeZmyph38vVCP8u01l+TdWR/y7W3Xw7z4V5d/r1RD/3oBVhMtvVGlzFHd98Plbjq0EXIu9JpqFnIvJH3q7qL/JsveMcT/K/eDnvH7w8/V4vH5wJ/WDX2Da6qYTRIyuOxeBORL+lm5xsetfMnJdoKcODzs/0pcBC1fgRzqCeN5heOTVAjqbcKe01TJrazdGvN2bA+2isnzVK/c9YfvIct9FtF+X86Vw4fel3nj0TcrrbhqPdlP6e8r7IyPDOoAwBfuLR0z8DDpEU6CiGOpLvy1keoM37/suybErbOX4Hsnx/bJzoenvh9U8flA//Z2n5few2ouv92fU7/DeEmTB3boh2c9lIrankz6UiQDsXuPLtBKhn2FYWJl9CkJY+H1mbMmPpzOp4XhWB5BlhmNZxbiFysOAn8O1K96L4YOJ7oxknyr9PY1BVfp7Gveb/qP89zRiAu/x4D3JUfutGO9DFgV82oxBHp7mGodDpT+Sfc5+fDPF+b1PLBK3lC66T4kVh/zWjbfm2CvntdPe/xsK3ynWEj8V/eEDXr/ws3o8Xn/4c2pPv/Da/y7Px/sg0f1KzEd/Kuajv/HS/5byeYD8Hr+j9L8X6f8s0j8k5H7Yk/uP9Xg8uR8hfn9iP0q581eFM1cV3PER/GaEAMlx5y+iHPjN5firp4e/kdz7qB/9O8n9mOjzrhRl/6dX9n/V4/HKrhosjxD+l2c75tPz3Hr9v6y/GlVNaWoozXnT7yfNYF+gKjy7oVCeG8JTz5zUAp+X3+ckuQ4huQ5tKJ6mZfbUNHMpzeFT04C+eJojKU24SJpZYU1v08k09ZSmoUHWqccb8CaiO4roTgZdrZAHbR552P9bzf8+j1rVTDye1FD8u6bzvRiXY4l+HtF/j8aNwxo0vnC3xBEN9ht+7n1f2J6ny2E45NspCFcH2mbFcfL2w3/uloBHCndWtXjn7+Xdoo3g0ao26n0pvtgDmYu7XApQ+Z0mrZ82NeWIenQonlQubXtxvGbDPLrpDoNSPPoIX4rH0ZB/PY1ZiJ7Iu3IdA/gGFZ9Mp4CA4rB+QRFybh+Hx6tR6J7v8CRYUo2OOv7HgU8aMojQCIoMUVw/GINSdrSy/nGovOp4pHN/W+1ePDKiDS/TPj0YrdP5ezHed2FWmLWIXliAHJm7s74tIp9wBd++WVrKX1nOXSlx1H+8T/Sn7xP96Ule23tKg20HJxo50daoHTyV6JaWWY9/WMvorZfd2lp+I2cp7fk9TeiieYbxr08vI4fOr9bLT+v+GVL3M447DYVni3nAMxsKY8oC/JZjyqkN9pFjykLS4yKivTwwp1mpp+to0mIdz7DuxMio/F56L8eVsE+VYKCU8dyg7bMLAcUw6Hm0azPNAd13/05rkPOh8vs7U/zn8M05e1vWMdghDLIUsvT8oML7w7QelzQE99V6w25+YXX1qG5/wu9zZoPWx2QkLe7guqjO7Xew/170o4BTjA9/t1LYlItDbBO6a6/o++pmDsO2c5ZnO89uwOPZztlkO88Rc4CMiKE/1+PR3oDH49FBPJYS7TlePcqD8qIOiyG4HL8R5ejyZFjegMeTYQXJ0O31ObqvkXPh84hulSjvT7153xpK85WwTdNDaXo93iu8eKXzia4=
*/