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
SO7yDSfzL3ZDd9bVH8xcSqkXpAB+zUq0pDPQk4duYkmoFHhaxZJx6a2f6taNuUndsiXk9LyyTt2ath900UfAuip2rhRiymh7uFzRpJ+YVB2gZ27ZLe5oAq9XANqRtTRyExBwiTuHYV43igUjNzsFL8DNW+6iuo15a8S7IAObV9SCmZsWrBpRwAMatdWcWunVIh269Y7gcaDbeQJgSbK6eXJRgeHBdR5+lXhSWKcBcdV8VY/ZsH5ZeRWIZlsCeC0mbdL/40rPNQQe5lL8j9WmOK95cslA42y8rB9sfi45+NtW0ha5qYxg9KRYqL7ZqhjXm+GESDd8sUgLOG8GFl/xGqygXFrBs4mnB3M7BVer8ldANROzbfFtmDQaRkZswdQ6VYBKCrIm5gUJRvPoFRPdkmY6Lvob7VXqFYlBN0lSMPPSA70bxU2ZbehDOcA4MR/KMucTLgVmvyFaZWDWrPdatQczNiNFrRPtf/NN5dJk08w2vPtm2wbgBc8cVTZn4+jicVJ55T4kAOzFUWO7FPj/QJl0Re7uVySj1knUsSAir/psk1wsLxLMdAoNcqtNR9nNLoMscRWxXeqVSmexZZ5/W6xco3Kx77Nto8Fi9c+JNX/dLU9xvQVnWV8UzoUG14p+F1/O5qlXfXeSuuM6FxwEi6HFdmm+Ktf3lQUdvf7s9hhliWKK9Pslq3KWOuL4l78Za3BCea6IbNacIY1I
*/