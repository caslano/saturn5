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
+8vAA8424MfD3EF87pRyc97l0+6itF91Mhxi+50/h4H2YiG2A1ZbYp89rIrvs78YuGYXEwgbcbyu02Vy55bF2cZWB6MuAYspTqP7yoUens7EMb7Nw+eiiWTgzJqH1zu1cp94mcN7ZyTfCnm7ZUyGOId/PXB9KhMfS22OS7TGvRO49WokniuS7l3AbdDtM1foJ68qcsb5RtBtV3p9UnwvXtfpdQIv9zLPNfEX0+9d3KQq27v4APjd4tanulpFeT4E3K1GjpE4ygk/bSLu9PAR4HYKGQWaz1Pv8s5Tp5FmtxqLnSHe9yisURcp3vPfizS5TFSLwvuyHwPdg+a8N9/mwTELDykvZoF8TfuU2PN3vt0ie/s13t5+bZm9/bll9vbD3t6+i/1oNr4i6TubevazyvjKisfULGQ472qz7G1ejIeDn10mvqTd4URMyIYQ2UoJe6wFzWiZeJMHTIwKx/OYck6Gisc1fQK8tobEIKN4vx++sOn3+7eHpt/v1zq4rnx8hHpbmfiIHcD58RF6DLqJ9WTqUEeS87r9UyZ+RbYjOwo6mT4D/K3u7LwIiShWxp1T6XiP+Tbw2SXP4JuNF02iuI73BPBmPARRAb8vgI/GswZt89+pbdaLGwCW2/WLkL7Fi3cAjmVv9XBO7gbwXVhVPj6oDfhS8UFtwLdXBfd/v6R1KvbNkVsMSXOJbDymhWJ9lqZh+b6i9SroyEMSKNvuovhCm/ya7s/sHjljZb3u9XDSZluAf7CC/fWHqqbfX/++ruOqQjzdGbR37scOPFvXdZn9c77rr7ryGJHW6uljRBZWVx4j0laSVuwhVJeOI9J6767WWwh2/ng+FgR3yT3N6vL3Oem51KXefuI3vP3Iu2nO9U2xH3mv2I+8R6yNv+WtN79dh8dbG3+H+H3Xy/cB75zZ94luj1tjCp+Efxdatbj7rIf8Ej+U+94HFDceCn9AlPc+Ud77vfL+qA6PV94fUzn2sl+n/Bl2WH6G9599sDwr5+vPq7efUb4/F2uksme4eXfRg9E645fl5OfzwLDeVNpnxWAp/69cjPq0csHVX4Kxj5fy/qaCcscSI/EsW4EHIz6/q6jc5qS+Lx6DZbn/QPyuJ3tOzzZ8chngXUyEEvf4PWjsWJfUvv/avHOBTV/3W6ZBXlBHhNE2ze8N3pSM+9uHDIxFNHxWGFgqp7dItZ+tFouuhwGrrcDPttH5K2c7X7XidUqtaK8833RnwNmPE4vnsMrRMrtz7M3ifsM/mjVYDHLZ+14ekXtqZe5kXFy6vQ1nki4Jv3O9/9lrX4967esv1L72sX2UPbeZGF8Ct+mmbHqRya8InPL9m+VX/LxaCR+l9iU8hnTu/pfLqS4A02nGsjgViJldwvlQHa7G4viEJnB8HrPW4jbympPv8wGcT2Va+D/0GGzhWTemL6azmf8U9dSoEljlZMXRTPGOcpS5LzSXyRdaqoBwfWlDk36YEN57p5wxwXqk3tZbNdG786oWb5iyTdaIvdeaeq0T850/m7W4iyzs4mjYp4jJz6LC3KpFv2ufOdnurHphuxWVz9rgLBojkaexwTlUlloqC4/HbLfAA6fT3Be2aQ6jNHPry95xit3/PPu8zBufo5Tne8eibs/xxrDWl113XKLNA/CzaCw+ksur85QfcXU5eDDZn5hUeR3RocT+h5lmpjJyD2SMYyD8u1BPtP0LOiEZY5ZNb0qoh8+hOqkTMrbM4Oy/9ONBMNPHH1Ff5jxRBXf7FvWNzuDe5KJ9R4k7wK8l332DKb91dIg5OcpkYf49RTUO7o4xyLuTQ4X9eb5BSOAPDZm1RjEippkreLjbiVz+jZA1HLJRARjxKOAnqxyuOaQ=
*/