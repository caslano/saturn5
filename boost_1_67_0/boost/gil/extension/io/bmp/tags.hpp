//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_TAGS_HPP

#include <boost/gil/io/base.hpp>

namespace boost { namespace gil {

/// Defines bmp tag.
struct bmp_tag : format_tag {};

    /// See http://en.wikipedia.org/wiki/BMP_file_format#BMP_File_Header for reference.

/// Defines type for offset value.
struct bmp_offset : property_base< uint32_t > {};

/// Defines type for header sizes.
struct bmp_header_size : property_base< uint32_t >
{
    static const type _size            = 14; /// Constant size for bmp file header size.
    static const type _win32_info_size = 40; /// Constant size for win32 bmp info header size.
    static const type _os2_info_size   = 12; /// Constant size for os2 bmp info header size.
};

/// Defines type for image width property.
struct bmp_image_width : property_base< int32_t > {};

/// Defines type for image height property.
struct bmp_image_height : property_base< int32_t > {};

/// Defines type for bits per pixels property.
struct bmp_bits_per_pixel : property_base< uint16_t > {};

/// Defines type for compression property.
struct bmp_compression : property_base< uint32_t >
{
    static const type _rgb      = 0; /// RGB without compression
    static const type _rle8     = 1; /// 8 bit index with RLE compression
    static const type _rle4     = 2; /// 4 bit index with RLE compression
    static const type _bitfield = 3; /// 16 or 32 bit fields without compression
};

/// Defines type for image size property.
struct bmp_image_size : property_base< uint32_t > {};

/// Defines type for horizontal resolution property.
struct bmp_horizontal_resolution : property_base< int32_t > {};

/// Defines type for vertical resolution property.
struct bmp_vertical_resolution : property_base< int32_t > {};

/// Defines type for number of colors property.
struct bmp_num_colors : property_base< uint32_t > {};

/// Defines type for important number of colors property.
struct bmp_num_important_colors : property_base< uint32_t > {};

/// if height is negative then image is stored top-down instead of bottom-up.
struct bmp_top_down : property_base< bool > {};

static const uint32_t bmp_signature = 0x4D42; /// Constant signature for bmp file format.

/// Read information for bmp images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< bmp_tag >
{
    /// Default contructor.
    image_read_info< bmp_tag >()
    : _top_down(false)
    , _valid( false )
    {}

    /// The offset, i.e. starting address, of the byte where the bitmap data can be found.
    bmp_offset::type _offset;

    /// The size of this header:
    /// - 40 bytes for Windows V3 header
    /// - 12 bytes for OS/2 V1 header
    bmp_header_size::type _header_size;

    /// The bitmap width in pixels ( signed integer ).
    bmp_image_width::type  _width;

    /// The bitmap height in pixels ( signed integer ).
    bmp_image_height::type _height;

    /// The number of bits per pixel, which is the color depth of the image.
    /// Typical values are 1, 4, 8, 16, 24 and 32.
    bmp_bits_per_pixel::type _bits_per_pixel;

    /// The compression method being used. See above for a list of possible values.
    bmp_compression::type _compression;

    /// The image size. This is the size of the raw bitmap data (see below),
    /// and should not be confused with the file size.
    bmp_image_size::type _image_size;

    /// The horizontal resolution of the image. (pixel per meter, signed integer)
    bmp_horizontal_resolution::type _horizontal_resolution;

    /// The vertical resolution of the image. (pixel per meter, signed integer)
    bmp_vertical_resolution::type   _vertical_resolution;

    /// The number of colors in the color palette, or 0 to default to 2^n - 1.
    bmp_num_colors::type            _num_colors;

    /// The number of important colors used, or 0 when every color is important;
    /// generally ignored.
    bmp_num_important_colors::type  _num_important_colors;

    bmp_top_down::type _top_down;

    /// Used internaly to identify is the header has been read.
    bool _valid;
};

/// Read settings for bmp images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< bmp_tag > : public image_read_settings_base
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

/// Write information for bmp images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< bmp_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
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
*/