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