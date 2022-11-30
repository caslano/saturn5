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
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
*/