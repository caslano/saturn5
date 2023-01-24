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
ACEjdJS10zHzm4TRFCgLfLpsyCb7J1lig5GgvP2JEpmod7Jkfr8ba+0yFgmtlZtBVManRVdNTudBR8TRF1yi6kebHDklM/exXrG8Jirw2OXC0cNXuATyym/ydsxlFq9pXjVND7xxfwcKLPXTaukcPrfwJw56X9Q1zwmlUzxLIddRCfiRXYnkzp3E5FKVZls9h86WDviw3Pl9gtVzgAE1TzXJ16+NNfY03mZ0Hhl7GtNKugn2kd75dw3IZK9uX48ftl7kYiCbzwtrnueEcgKEidyfWeaFklxCu4WWK9XDCSDHsXcI5RX2DcjsDH/slTHuHsGOQWnyXT28ZRNcSniWnqQw/QQk/1ger64x+SdX54QnCTyCCvj8CAUcIoD9IcDVedEDFunL+F+k0CsIdKENenW/5JeQbDFGxoW7sOnjx14PRcDWk4499lwwspoPRB4ORj4ejHwjGBGEQGRjMPKKYOTTwcg/ByPrxUBk3o9seVZCu4QXEpy+i340Ge0I3t11LY5pAwd4a+DQnC6Tz1GRu2b6IW8r5NlSjLzaf84Eaxgjt2idvhtRTKY54AfMEmXkyBqI2QqGXpXmbDWGNwML5/qghgGzhN/t0CDpEYzmSlVS0tZj9B4DicOzW9vI/af4wVY7jjUq5khNPq5AgYywmIjh1FTICOT2ZXicxlGaSnRdXUoi7iGCW76vBs/VWbGcEwxRUdlNcAEIllTJ
*/