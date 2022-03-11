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