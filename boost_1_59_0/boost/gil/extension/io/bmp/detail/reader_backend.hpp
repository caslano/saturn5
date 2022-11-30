//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

/// Color channel mask
struct bit_field
{
    unsigned int mask;  // Bit mask at corresponding position
    unsigned int width; // Bit width of the mask
    unsigned int shift; // Bit position from right to left
};

/// BMP color masks
struct color_mask
{
    bit_field red;   // Red bits
    bit_field green; // Green bits
    bit_field blue;  // Blue bits
};


///
/// BMP Backend
///
template< typename Device >
struct reader_backend< Device
                     , bmp_tag
                     >
{
public:

    using format_tag_t = bmp_tag;

public:

    reader_backend( const Device&                         io_dev
                  , const image_read_settings< bmp_tag >& settings
                  )
    : _io_dev  ( io_dev   )
    , _settings( settings )
    , _info()
    , _scanline_length( 0 )
    , _palette()
    {
        read_header();

        if( _settings._dim.x == 0 )
        {
            _settings._dim.x = _info._width;
        }

        if( _settings._dim.y == 0 )
        {
            _settings._dim.y = _info._height;
        }
    }

    void read_header()
    {
        // the magic number used to identify the BMP file:
        // 0x42 0x4D (ASCII code points for B and M)
        if( _io_dev.read_uint16() == 0x424D )
        {
            io_error( "Wrong magic number for bmp file." );
        }

        // the size of the BMP file in bytes
        _io_dev.read_uint32();

        // reserved; actual value depends on the application that creates the image
        _io_dev.read_uint16();
        // reserved; actual value depends on the application that creates the image
        _io_dev.read_uint16();

        _info._offset = _io_dev.read_uint32();


        // bitmap information

        // the size of this header ( 40 bytes )
        _info._header_size = _io_dev.read_uint32();

        if( _info._header_size == bmp_header_size::_win32_info_size )
        {
            _info._width  = _io_dev.read_uint32();
            _info._height = _io_dev.read_uint32();

            if (_info._height < 0)
            {
                _info._height = -_info._height;
                _info._top_down = true;
            }

            // the number of color planes being used. Must be set to 1.
            _io_dev.read_uint16();

            _info._bits_per_pixel = _io_dev.read_uint16();

            _info._compression = _io_dev.read_uint32();

            _info._image_size = _io_dev.read_uint32();

            _info._horizontal_resolution = _io_dev.read_uint32();
            _info._vertical_resolution   = _io_dev.read_uint32();

            _info._num_colors           = _io_dev.read_uint32();
            _info._num_important_colors = _io_dev.read_uint32();

        }
        else if( _info._header_size == bmp_header_size::_os2_info_size )
        {
            _info._width  = static_cast< bmp_image_width::type  >( _io_dev.read_uint16() );
            _info._height = static_cast< bmp_image_height::type >( _io_dev.read_uint16() );

            // the number of color planes being used. Must be set to 1.
            _io_dev.read_uint16();

            _info._bits_per_pixel = _io_dev.read_uint16();

            _info._compression = bmp_compression::_rgb;

            // not used
            _info._image_size            = 0;
            _info._horizontal_resolution = 0;
            _info._vertical_resolution   = 0;
            _info._num_colors            = 0;
            _info._num_important_colors  = 0;
        }
        else if (_info._header_size > bmp_header_size::_win32_info_size)
        {
            // could be v4 or v5
            // see MSDN: Bitmap Header Types ( BITMAPV4HEADER or BITMAPV5HEADER )

            _info._width = _io_dev.read_uint32();
            _info._height = _io_dev.read_uint32();

            // the number of color planes being used. Must be set to 1.
            _io_dev.read_uint16();

            _info._bits_per_pixel = _io_dev.read_uint16();

            _info._compression = _io_dev.read_uint32();

            _info._image_size = _io_dev.read_uint32();

            _info._horizontal_resolution = _io_dev.read_uint32();
            _info._vertical_resolution = _io_dev.read_uint32();

            _info._num_colors = _io_dev.read_uint32();
            _info._num_important_colors = _io_dev.read_uint32();
        }
        else
        {
            io_error( "Invalid BMP info header." );
        }

        _info._valid = true;
    }

    void read_palette()
    {
        int entries = this->_info._num_colors;

        if( entries == 0 )
        {
            entries = 1u << this->_info._bits_per_pixel;
        }

        _palette.resize( entries, rgba8_pixel_t(0, 0, 0, 0));

		for( int i = 0; i < entries; ++i )
        {
            get_color( _palette[i], blue_t()  ) = _io_dev.read_uint8();
            get_color( _palette[i], green_t() ) = _io_dev.read_uint8();
            get_color( _palette[i], red_t()   ) = _io_dev.read_uint8();

            // there are 4 entries when windows header
            // but 3 for os2 header
            if( _info._header_size == bmp_header_size::_win32_info_size )
            {
                _io_dev.read_uint8();
            }

        } // for
    }

    /// Check if image is large enough.
    void check_image_size( const point_t& img_dim )
    {
        if( _settings._dim.x > 0 )
        {
            if( img_dim.x < _settings._dim.x ) { io_error( "Supplied image is too small" ); }
        }
        else
        {
            if( img_dim.x < _info._width ) { io_error( "Supplied image is too small" ); }
        }


        if( _settings._dim.y > 0 )
        {
            if( img_dim.y < _settings._dim.y ) { io_error( "Supplied image is too small" ); }
        }
        else
        {
            if( img_dim.y < _info._height ) { io_error( "Supplied image is too small" ); }
        }
    }

public:

    Device _io_dev;

    image_read_settings< bmp_tag > _settings;
    image_read_info< bmp_tag >     _info;

    std::size_t _scanline_length;

    ///@todo make it an image.
    std::vector< rgba8_pixel_t > _palette;

    color_mask _mask;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* reader_backend.hpp
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
*/