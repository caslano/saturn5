//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_TAGS_HPP

#include <boost/gil/io/base.hpp>

namespace boost { namespace gil {

/// Defines targa tag.
struct targa_tag : format_tag {};

/// See http://en.wikipedia.org/wiki/Truevision_TGA#Header for reference.
/// http://local.wasp.uwa.edu.au/~pbourke/dataformats/tga/


/// Defines type for header sizes.
struct targa_header_size : property_base< uint8_t >
{
    static const type _size = 18; /// Constant size for targa file header size.
};

/// Defines type for offset value.
struct targa_offset : property_base< uint8_t > {};

/// Defines type for color map type property.
struct targa_color_map_type : property_base< uint8_t >
{
    static const type _rgb = 0;
    static const type _indexed = 1;
};

/// Defines type for image type property.
struct targa_image_type : property_base< uint8_t >
{
    static const type _none          = 0;  /// no image data
    static const type _indexed       = 1;  /// indexed
    static const type _rgb           = 2;  /// RGB
    static const type _greyscale     = 3;  /// greyscale
    static const type _rle_indexed   = 9;  /// indexed with RLE compression
    static const type _rle_rgb       = 10; /// RGB with RLE compression
    static const type _rle_greyscale = 11; /// greyscale with RLE compression
};

/// Defines type for color map start property.
struct targa_color_map_start : property_base< uint16_t > {};

/// Defines type for color map length property.
struct targa_color_map_length : property_base< uint16_t > {};

/// Defines type for color map bit depth property.
struct targa_color_map_depth : property_base< uint8_t > {};

/// Defines type for origin x and y value properties.
struct targa_origin_element : property_base< uint16_t > {};

/// Defines type for image dimension properties.
struct targa_dimension : property_base< uint16_t > {};

/// Defines type for image bit depth property.
struct targa_depth : property_base< uint8_t > {};

/// Defines type for image descriptor property.
struct targa_descriptor : property_base< uint8_t > {};

struct targa_screen_origin_bit : property_base< bool > {};

/// Read information for targa images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< targa_tag >
{
    /// Default contructor.
    image_read_info< targa_tag >()
    : _screen_origin_bit(false)
    , _valid( false )
    {}

    /// The size of this header:
    targa_header_size::type _header_size;

    /// The offset, i.e. starting address, of the byte where the targa data can be found.
    targa_offset::type _offset;

    /// The type of color map used by the image, i.e. RGB or indexed.
    targa_color_map_type::type _color_map_type;

    /// The type of image data, i.e compressed, indexed, uncompressed RGB, etc.
    targa_image_type::type _image_type;

    /// Index of first entry in the color map table.
    targa_color_map_start::type _color_map_start;

    /// Number of entries in the color map table.
    targa_color_map_length::type _color_map_length;

    /// Bit depth for each color map entry.
    targa_color_map_depth::type _color_map_depth;

    /// X coordinate of the image origin.
    targa_origin_element::type _x_origin;

    /// Y coordinate of the image origin.
    targa_origin_element::type _y_origin;

    /// Width of the image in pixels.
    targa_dimension::type _width;

    /// Height of the image in pixels.
    targa_dimension::type _height;

    /// Bit depth of the image.
    targa_depth::type _bits_per_pixel;

    /// The targa image descriptor.
    targa_descriptor::type _descriptor;

    // false: Origin in lower left-hand corner.
    // true: Origin in upper left-hand corner.
    targa_screen_origin_bit::type _screen_origin_bit;

    /// Used internally to identify if the header has been read.
    bool _valid;
};

/// Read settings for targa images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< targa_tag > : public image_read_settings_base
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

/// Write information for targa images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< targa_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
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
*/