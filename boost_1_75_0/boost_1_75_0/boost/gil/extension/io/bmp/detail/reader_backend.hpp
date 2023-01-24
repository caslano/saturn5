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
MwZe+FEzNjEE0dOMoAU6yGs2dL1bLsDvppGkxynpHSrQScJmV+0bbpNBS+hVmkOx8fkiGLKP9XX/tZ+ysX/LNKSp3ugp2fCiL3spKGGZ3U04VxTG2x/qmy5ThJKEMjHDuR+mnVAVWCJTwBAFj8pL9Ffk2btlzqy/cPDgG9Q2oWHyZpVdhLPUR8Pti130G9QRm8w2qqAtq+lYYJtdehF+l5gTfJx14cLA7So0zU0zOlgkFopYGygxvz0vm97GJNbRK6uHJS15B8/PHkVBQn5xnF1Zh1cRT4PlVrhU/gAXXvXnq5SESzBmw53snuyvubn4TGwgl2mgqXX2vuwoJGp8nyJU8fe5pGXUGkmNP0LIVPYQERQkWsuUtXXhL2EJ6RKP9T6cWp1L9hvHp7HxyS49hikSlZ82ZHfk46Ovu0807X4lAT8ywkE4UmloVMwcQ11inT841KPDtXt4vA4GH5gV8lmlGWFeM2z/kZ7MV3uFFjP2nGv14J+erFQnAfVNi4XuLG3gODl0izlCCddtANhL1a8t3hsaHVGYmzl9oaVY2zK4dZLF/p8t3gk+ddJIqzYIF2lbS8YlKpxZJucGcqA7wqkxn9yDoZZlQiyseRWggJhP43/H4o8h8ONWczx3gPlAY10KT427tU8z2uQXBT+2d8Lx8uYEEQzg6V1OfNpYPAQCP2UlpknBmZdMSJU8ynNHdGj1c1fAfeAjWg8i
*/