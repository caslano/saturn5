//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_TAGS_HPP

// taken from jpegxx - https://bitbucket.org/edd/jpegxx/src/ea2492a1a4a6/src/ijg_headers.hpp
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#else
    // DONT_USE_EXTERN_C introduced in v7 of the IJG library.
    // By default the v7 IJG headers check for __cplusplus being defined and
    // wrap the content in an 'extern "C"' block if it's present.
    // When DONT_USE_EXTERN_C is defined, this wrapping is not performed.
    #ifndef DONT_USE_EXTERN_C
        #define DONT_USE_EXTERN_C 1
    #endif
#endif

#include <cstdio> // jpeglib doesn't know about FILE

#include <jerror.h>
#include <jpeglib.h>

#ifndef BOOST_GIL_EXTENSION_IO_JPEG_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

#include <boost/gil/io/base.hpp>

namespace boost { namespace gil {

/// Defines jpeg tag.
struct jpeg_tag : format_tag {};

/// see http://en.wikipedia.org/wiki/JPEG for reference

/// Defines type for image width property.
struct jpeg_image_width : property_base< JDIMENSION > {};

/// Defines type for image height property.
struct jpeg_image_height : property_base< JDIMENSION > {};

/// Defines type for number of components property.
struct jpeg_num_components : property_base< int > {};

/// Defines type for color space property.
struct jpeg_color_space : property_base< J_COLOR_SPACE > {};

/// Defines type for jpeg quality property.
struct jpeg_quality : property_base< int >
{
    static const type default_value = 100;
};

/// Defines type for data precision property.
struct jpeg_data_precision : property_base< int > {};

/// JFIF code for pixel size units
struct jpeg_density_unit : property_base< UINT8 >
{
    static const type default_value = 0;
};

/// pixel density
struct jpeg_pixel_density : property_base< UINT16 >
{
    static const type default_value = 0;
};

/// Defines type for dct ( discrete cosine transformation ) method property.
struct jpeg_dct_method : property_base< J_DCT_METHOD >
{
    static const type slow        = JDCT_ISLOW;
    static const type fast        = JDCT_IFAST;
    static const type floating_pt = JDCT_FLOAT;
    static const type fastest     = JDCT_FASTEST;

    static const type default_value = slow;
};

/// Read information for jpeg images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< jpeg_tag >
{
    image_read_info()
    : _width ( 0 )
    , _height( 0 )

    , _num_components( 0 )

    , _color_space( J_COLOR_SPACE( 0 ))

    , _data_precision( 0 )

    , _density_unit ( 0 )
    , _x_density    ( 0 )
    , _y_density    ( 0 )

    , _pixel_width_mm ( 0.0 )
    , _pixel_height_mm( 0.0 )
    {}

    /// The image width.
    jpeg_image_width::type _width;

    /// The image height.
    jpeg_image_height::type _height;

    /// The number of channels.
    jpeg_num_components::type _num_components;

    /// The color space.
    jpeg_color_space::type _color_space;

    /// The width of channel.
    /// I believe this number is always 8 in the case libjpeg is built with 8.
    /// see: http://www.asmail.be/msg0055405033.html
    jpeg_data_precision::type _data_precision;

    /// Density conversion unit.
    jpeg_density_unit::type  _density_unit;
    jpeg_pixel_density::type _x_density;
    jpeg_pixel_density::type _y_density;

    /// Real-world dimensions
    double _pixel_width_mm;
    double _pixel_height_mm;
};

/// Read settings for jpeg images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< jpeg_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings<jpeg_tag>()
    : image_read_settings_base()
    , _dct_method( jpeg_dct_method::default_value )
    {}

    /// Constructor
    /// \param top_left   Top left coordinate for reading partial image.
    /// \param dim        Dimensions for reading partial image.
    /// \param dct_method Specifies dct method.
    image_read_settings( const point_t&        top_left
                       , const point_t&        dim
                       , jpeg_dct_method::type dct_method = jpeg_dct_method::default_value
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    , _dct_method( dct_method )
    {}

    /// The dct ( discrete cosine transformation ) method.
    jpeg_dct_method::type _dct_method;
};

/// Write information for jpeg images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< jpeg_tag >
{
    /// Constructor
    /// \param quality      Defines the jpeg quality.
    /// \param dct_method   Defines the DCT method.
    /// \param density_unit Defines the density unit.
    /// \param x_density    Defines the x density.
    /// \param y_density    Defines the y density.
    image_write_info( const jpeg_quality::type    quality        = jpeg_quality::default_value
                    , const jpeg_dct_method::type dct_method     = jpeg_dct_method::default_value
                    , const jpeg_density_unit::type density_unit = jpeg_density_unit::default_value
                    , const jpeg_pixel_density::type x_density   = jpeg_pixel_density::default_value
                    , const jpeg_pixel_density::type y_density   = jpeg_pixel_density::default_value
                    )
    : _quality   ( quality    )
    , _dct_method( dct_method )

    , _density_unit( density_unit )
    , _x_density   ( x_density    )
    , _y_density   ( y_density    )
    {}

    /// The jpeg quality.
    jpeg_quality::type _quality;

    /// The dct ( discrete cosine transformation ) method.
    jpeg_dct_method::type _dct_method;

    /// Density conversion unit.
    jpeg_density_unit::type _density_unit;

    /// Pixel density dimensions.
    jpeg_pixel_density::type _x_density;
    jpeg_pixel_density::type _y_density;

    /// Sets the pixel dimensions.
    void set_pixel_dimensions( int    image_width   // in pixels
                             , int    image_height  // in pixels
                             , double pixel_width   // in mm
                             , double pixel_height  // in mm
                             )
    {
        _density_unit = 2; // dots per cm

        _x_density = round( image_width  / ( pixel_width  / 10 ));
        _y_density = round( image_height / ( pixel_height / 10 ));
    }

private:

    UINT16 round( double d )
    {
        return static_cast< UINT16 >( d + 0.5 );
    }

};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
r5GegejRVpylIrleh1UfnLBlHi6kUsVxcKuFZRPYbYebFBfuzY1GypwbLSsxN0ra9MW8bnDvxWfoTIp9kx4n9DXstHf1D2At1tUz4Jv6aDDp7wTt1e7pI01kbUS8eqdjPF9tgWNWOrs1PkrvUrrl2GbL5e7LjaZz7F9l1Nfu3F2/aKTDK4EE+M5R6lU/mSE9OaFhnLWIkFOAiLhd5ZRO5lVeBcprO+GxzajwDbZT6OtK8XuVon0i0d5Nbeskon2ySHM7r3lIZ2xeyVHsIyS9vapTbfq429snvP6++ObpnjL1stSc/TSas3u+ak/31RuPM20jaVSwJ1wFHv+9/vH3vYwczpRzY+pj3oWvOuS32z2LZHh2UdYYZ8WdFFUH51EdrKA6OJ/SX1DG3LCc/V2T/0Ui/4vFuLZXjWvvbjCfuq9C/FxKuMH7NZ53A+xHeYewHlPBUaX3E8vYc7FnZkqOl6l2cjnxfYWoh5yQw5Uq/Qe8clM9fJDSXyXaQr+Q3dVKdh9uMJ/yB0Y0Psr9gtyzFOcyBKtV650Q+YPy3oG9Rva7E6xPpJ7yeRKfU8HfFPF2nShfNf32+e4W79Ea2PW2LZp7+JZ5vsf/SdkmX+acYoGQ76eUfG9swKfk+2kqw02Eu8DHt/WM5dv/1P61Pit5LmMfO3D+O8n+x/qZEvog/L3JoxXHwL9gZZ3M+AgZPoj/myX/kzyzEWeofL4s+7FbSba3ifbzbmGPdgfgcg7ag/AXSdfkHFTemfgS4leqOa/iPXgFIWbA8oxUn2nfSTzfFdhXcxvgMt5N+Pc0iLNt0WamBpyHf53S3Etp/uobs0znBp9Ucu/Dwmi/g2x6UKdsF7HL7n8AR/jIvNvaSgAm/GHeDrx5zlBLknC+ivBCJ9ni5bUZ4WaEcxQ+B+HlTo7xP4HwasRv984HEO50tnP8fQj3IT4r0m9yshxv5LFZ7LeYNrQfhP4NUY8jZe63Hira+f2qnX+rAZ9q598mmX9nvHXoJOehht4DRG8j1eGDtixDOHnJpKXdTq31C5Ae9WSbsHWGN5Pd7X7e1wpjrhwjVHumQOfn3xMymlfGPDBwzJ9EGzFle4jK1hLUx/RlE8PJnZbvH9DcjWmI9cQP/8N524/UvO1h2eYnv29gx+nr1Tj/COnGT8Q49g2xT/4zpV8/b8Cn9OsXROPR8ebvZa0P4ItdjaGPmzLT2gNSFzqF9zyssVrx7OlXUj5l2SZUhN4n5jS/Ee3qt6rcTzTgU+X+HZX7STUXuk+dS/yB8P6o8N5J9J6qp3MSwvuzqItzBU/PKJ6ebcCnePoL0XhO5dWk6v1vhPe8yKtDpfkHpUnQnO4FSvOit39GdXS9jd8Sz8nzELNnk9zm3ZUBjN7OcmG8Fv6XnJNN+szN5XOTKpszy+WzYlaxbHOFHKcALuVYNcv9pByriUYN4Xp57VZ51RLePrNK+F7jeaVy7KXh1O80CD6nKT73nYVP8bkf5b9/kU9jS8I6PR1wj16dojdjFj5FbybRq1flTqhyzyK8sJDxRUp/GhEn08yhNE0izTSVZj/K54BZtL9OaeaJNNMVb/Mpn7upHR1IaQ4SdcL90STrxPO1tgC0tK+111mY9rWm7eEC4FTXF6uyv57K0UhlP4TKcago+5VCP96o6vNNs/Cp+nwz0WhWMouq+mwhvMUir31FXktVXstm4VN5HUY0lgsaNXqPnNKgz3D3yCnN4Yq/A5TurCS8VYL2bxTtVkpzGdFeQ2naKI2876zvW0SA49E5k+Jmk5+PtYiTaQH32RZ2ifgFobG0j+B4N221il9PfL6XyiPvp2MC/LTFVXtUR3plQtx8xx/XL2VJecrybEC8DJ8=
*/