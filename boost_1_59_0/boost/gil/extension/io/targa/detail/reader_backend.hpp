//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// Targa Backend
///
template< typename Device >
struct reader_backend< Device
                     , targa_tag
                     >
{
public:

    using format_tag_t = targa_tag;

public:

    reader_backend( const Device&                           io_dev
                  , const image_read_settings< targa_tag >& settings
                  )
    : _io_dev  ( io_dev   )
    , _scanline_length(0)
    , _settings( settings )
    , _info()
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
        _info._header_size = targa_header_size::_size;

        _info._offset = _io_dev.read_uint8() + _info._header_size;

        _info._color_map_type = _io_dev.read_uint8();
        _info._image_type = _io_dev.read_uint8();

        _info._color_map_start  = _io_dev.read_uint16();
        _info._color_map_length = _io_dev.read_uint16();
        _info._color_map_depth  = _io_dev.read_uint8();

        _info._x_origin = _io_dev.read_uint16();
        _info._y_origin = _io_dev.read_uint16();

        _info._width  = _io_dev.read_uint16();
        _info._height = _io_dev.read_uint16();

        if( _info._width < 1 || _info._height < 1 )
        {
            io_error( "Invalid dimension for targa file" );
        }

        _info._bits_per_pixel = _io_dev.read_uint8();
        if( _info._bits_per_pixel != 24 && _info._bits_per_pixel != 32 )
        {
            io_error( "Unsupported bit depth for targa file" );
        }

        _info._descriptor = _io_dev.read_uint8();

        // According to TGA specs, http://www.gamers.org/dEngine/quake3/TGA.txt,
        // the image descriptor byte is:
        //
        // For Data Type 1, This entire byte should be set to 0.
        if (_info._image_type == 1 && _info._descriptor != 0)
        {
            io_error("Unsupported descriptor for targa file");
        }
        else if (_info._bits_per_pixel == 24)
        {
            // Bits 3-0 - For the Targa 24, it should be 0.
            if ((_info._descriptor & 0x0FU) != 0)
            {
                io_error("Unsupported descriptor for targa file");
            }
        }
        else if (_info._bits_per_pixel == 32)
        {
            // Bits 3-0 - For Targa 32, it should be 8.
            if (_info._descriptor != 8 && _info._descriptor != 40)
            {
                io_error("Unsupported descriptor for targa file");
            }
        }
        else
        {
            io_error("Unsupported descriptor for targa file");
        }

        if (_info._descriptor & 32)
        {
            _info._screen_origin_bit = true;
        }

        _info._valid = true;
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

    std::size_t _scanline_length;

    image_read_settings< targa_tag > _settings;
    image_read_info< targa_tag >     _info;
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