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