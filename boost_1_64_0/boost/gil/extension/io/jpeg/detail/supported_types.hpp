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
f+RXRXs0hoxnpzYV5ENCPjVl9IfDvva4BtnLtsPtcXSIxxCxB048mEbjRes4s5ONNLxvWSf4m/YK7PUE++Sw5yCtA23wcu6bCgbAaVyZ2eSOCf8Sa3E+U+gbdHg8DdgjCPn3CBgXY2nOvHSXzMEpsHvAJNa4A3Bqksh3ZSzM7icu9Naz1LMZ+G8Ab3a68WB8AdnSECT6vOUOwYygCf6QWTM4nVAkbDMNgIFEsS47nf7BdCbRBTfWO2VddmOPJpVqtvJ8NeqpQdRT3yTlGbRXWt/k3ysNN7GdBXDc+J8qu5JGwI6p8M7jTFbdrUcjm46utbH+ttae7q6eSAxdbcTsu0Oz+/siba77fTqfmzANNsPXRiOuS3g6s5swTReKGe1ubTN35yafJrahD57fwWR3e0dXtH/AozFlMjS6e48KouHseWkiIh299h0I0MJUfaN4d6CpaUIJu4eNEyCh+tHXenU2Gqf3E6k+BtPbWM441IBGDyGctXbjtZaPA8BHLLYd3pTy+WxySyGfyK1YkdieGPUeiGj14CtWGM/XsYTLlvt7dSDmakXQ8NjIPOYyCXDh8pez+4u7wU8l8TNvEvyYx4y2gYLHE4UnxddxAf1ZuRzYJlluTs+6c+H5TWQbQfYHr0G40dnHtkETdyA+p7LCOYj6g7FxxjbVjatzamx7Phhwa8eG/6dAzqF6ly7V19Mm/FqEWT6A7Q+Jvw6wQPapXzM0HOHv3NCo8qgQrNn20UOmA40joZXnVKeucqEcd/5L8lzDOpVYk06brXSH9B79bT6xFR036X7CHsYW236iPV3YkjLlvMSc+5PuHRKkeyOJVCaR9YG2L4rFU3nIZYLGEYC3egy5gKKdV55OlseZFerL5cTV2TconT1U6KyJeyPp7JuozleSDgKPdXC6OZtAOIhD6JHBZV0z5Z8CHWoWOlT1Pyr/M5WsY62juzbk0IU6pGNt6bZUPJdzYaRnuL1jVC87jAMbN4J0rsZJqAgXXusk1ifMQskFWlgIMOs8RcDmifQy0sStFnFEjOP2MJ8yhsavCo5jihw3JeFugogoHveqKM7MgQSPTm2CJcJ0QkXeeC0o0zRTcVSkjVud6Grvdo/sJM3KPc4e1EZ6dNe2dEHIv2qPY+plANU8lBj2w1E3G0YxY2Q6BK9yEhG48fLKx3DUS3tiGBtiMFvRaVA//flsYTDvRjAcdWQ3kzQ+6gfLEihbfteYfPYgf9Pj6TSom4HEtkwqnmc9knFSKEV4ZaIrlUps9ThgeFWi1XhMHMGalAXG9F46dZXVbYia6J2HPvEA6hNbyuwTCyYpNy43zP0hBVab/5Nsgae87L6QMpPdwMvI3/R/S9z+j/s8E15Kfd5FNBavoD5vMeBe2U2ftwxhxQnf33LcNypRRre/O2zS/d0rU8Z1NI5WOHH4LcmbbQvqz9znhIrj5nA24embM5oo5LPxFOlstbMlbfwpbofuVJPuvCVId/Ij5n0X0GUeBcxTGAFYzb/HncdtKU9PBDEptPLysL5P1Vi4QoyFJu5w0ou3UV2quMD520qav63C/zWkR4auFIuZr62WMKVPwGd9MrKogj61Sn16hWUh1hyYsWUd0p9UKr0jMeT10wjviO/CHoZ/zdEWpBfxrVuz6LrM+n2CaZXAfEXm9oqeEEW5OdHcPqJ0o13ohonrIN1Yy7oh4kroRifpRhfrhksXsuB5/DqEJat6Ht8u5lbHkW4cIXXjvyST7eWtM7OJwUQSOlTOSpNxx6v30fLqXVOUpSw/N6r7nib/mxnrEW4WdWzie20d42Y4yZ70BLhBeLjXQHgqjvSE4khPjiQ96af/A/h/LOnLeqkvqJENCOsCyrk=
*/