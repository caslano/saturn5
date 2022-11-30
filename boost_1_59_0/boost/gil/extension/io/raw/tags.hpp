//
// Copyright 2013 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_TAGS_HPP

#include <boost/gil/io/base.hpp>

// Historically, LibRaw expects WIN32, not _WIN32 (see https://github.com/LibRaw/LibRaw/pull/206)
#ifdef _MSC_VER
#ifndef WIN32
#define WIN32
#endif
#pragma warning(push)
#pragma warning(disable:4251) // 'type' needs to have dll-interface to be used by clients of class
#endif

#include <libraw/libraw.h>

namespace boost { namespace gil {

/// Defines tiff tag.
struct raw_tag : format_tag {};

/// Defines type for image width property.
struct raw_image_width : property_base< int32_t > {};

/// Defines type for image height property.
struct raw_image_height : property_base< int32_t > {};

/// Defines type for samples per pixel property.
struct raw_samples_per_pixel : property_base< int32_t > {};

/// Defines type for bits per pixel property.
struct raw_bits_per_pixel : property_base< int32_t > {};

/// Defines type for camera manufacturer.
struct raw_camera_manufacturer : property_base< std::string > {};

/// Defines type for camera model.
struct raw_camera_model : property_base< std::string > {};

/// Defines type for raw images count.
struct raw_raw_images_count : property_base< unsigned > {};

/// Defines type for dng version.
struct raw_dng_version : property_base< unsigned > {};

/// Defines type for number of colors.
struct raw_number_colors : property_base< int32_t > {};

/// Defines type for colors description.
struct raw_colors_description : property_base< std::string > {};

/// Defines type for raw height.
struct raw_raw_height : property_base< uint16_t > {};

/// Defines type for raw width.
struct raw_raw_width : property_base< uint16_t > {};

/// Defines type for visible height.
struct raw_visible_height : property_base< uint16_t > {};

/// Defines type for visible width.
struct raw_visible_width : property_base< uint16_t > {};

/// Defines type for top margin.
struct raw_top_margin : property_base< uint16_t > {};

/// Defines type for left margin.
struct raw_left_margin : property_base< uint16_t > {};

/// Defines type for output height.
struct raw_output_height : property_base< uint16_t > {};

/// Defines type for output width.
struct raw_output_width : property_base< uint16_t > {};

/// Defines type for pixel aspect.
struct raw_pixel_aspect : property_base< double > {};

/// Defines type for image orientation.
struct raw_flip : property_base< uint32_t > {};

/// Defines type for iso speed.
struct raw_iso_speed : property_base< float > {};

/// Defines type for shutter.
struct raw_shutter : property_base< float > {};

/// Defines type for aperture.
struct raw_aperture : property_base< float > {};

/// Defines type for focal length.
struct raw_focal_length : property_base< float > {};

/// Defines type for timestamp.
struct raw_timestamp : property_base< time_t > {};

/// Defines type for shot order.
struct raw_shot_order : property_base< uint16_t > {};

/// Defines type for image description.
struct raw_image_description : property_base< std::string > {};

/// Defines type for artist.
struct raw_artist : property_base< std::string > {};

/// Defines type for libraw version.
struct raw_libraw_version : property_base< std::string > {};

/// Defines type for unpack function name.
struct raw_unpack_function_name : property_base< std::string > {};

/// Read information for raw images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< raw_tag >
{
    /// Default contructor.
    image_read_info< raw_tag >()
    : _valid( false )
    {}

    // Here, width and height of the image are the ones of the output height (ie after having been processed by dcraw emulator)
    raw_image_width::type       _width;
    raw_image_height::type      _height;
    raw_samples_per_pixel::type _samples_per_pixel;
    raw_bits_per_pixel::type    _bits_per_pixel;

    raw_camera_manufacturer::type _camera_manufacturer;
    raw_camera_model::type        _camera_model;

    raw_raw_images_count::type   _raw_images_count;
    raw_dng_version::type        _dng_version;
    raw_number_colors::type      _number_colors;
    raw_colors_description::type _colors_description;

    raw_raw_width::type      _raw_width;
    raw_raw_height::type     _raw_height;
    raw_visible_width::type  _visible_width;
    raw_visible_height::type _visible_height;
    raw_top_margin::type     _top_margin;
    raw_left_margin::type    _left_margin;
    raw_output_width::type   _output_width;
    raw_output_height::type  _output_height;
    raw_pixel_aspect::type   _pixel_aspect;
    raw_flip::type           _flip;

    raw_iso_speed::type         _iso_speed;
    raw_shutter::type           _shutter;
    raw_aperture::type          _aperture;
    raw_focal_length::type      _focal_length;
    raw_timestamp::type         _timestamp;
    raw_shot_order::type        _shot_order;
    raw_image_description::type _image_description;
    raw_artist::type            _artist;

    raw_libraw_version::type       _libraw_version;
    raw_unpack_function_name::type _unpack_function_name;

    /// Used internaly to identify if the header has been read.
    bool _valid;
};

/// Read settings for raw images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< raw_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left Top left coordinate for reading partial image.
    /// \param dim      Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for raw images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< raw_tag >
{
};

}} // namespace boost::gil

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* tags.hpp
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
*/