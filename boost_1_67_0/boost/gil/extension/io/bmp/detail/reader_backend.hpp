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