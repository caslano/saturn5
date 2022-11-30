//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNM Backend
///
template< typename Device >
struct reader_backend< Device
                     , pnm_tag
                     >
{
public:

    using format_tag_t = pnm_tag;

public:

    reader_backend( const Device&                         io_dev
                  , const image_read_settings< pnm_tag >& settings
                  )
    : _io_dev  ( io_dev   )
    , _settings( settings )
    , _info()

    , _scanline_length( 0 )
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
        // read signature
        io_error_if( read_char() != 'P', "Invalid PNM signature" );

        _info._type = read_char() - '0';

        io_error_if( _info._type < pnm_image_type::mono_asc_t::value || _info._type > pnm_image_type::color_bin_t::value
                   , "Invalid PNM file (supports P1 to P6)"
                   );

        _info._width  = read_int();
        _info._height = read_int();

        if( _info._type == pnm_image_type::mono_asc_t::value || _info._type == pnm_image_type::mono_bin_t::value )
        {
            _info._max_value = 1;
        }
        else
        {
            _info._max_value = read_int();

            io_error_if( _info._max_value > 255
                       , "Unsupported PNM format (supports maximum value 255)"
                       );
        }
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

private:

    // Read a character and skip a comment if necessary.
    char read_char()
    {
        char ch;

        if(( ch = _io_dev.getc() ) == '#' )
        {
            // skip comment to EOL
            do
            {
                ch = _io_dev.getc();
            }
            while (ch != '\n' && ch != '\r');
        }

        return ch;
    }

    unsigned int read_int()
    {
        char ch;

        // skip whitespaces, tabs, and new lines
        do
        {
            ch = read_char();
        }
        while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

        if( ch < '0' || ch > '9' )
        {
            io_error( "Unexpected characters reading decimal digits" );
        }

        unsigned val = 0;

        do
        {
            unsigned dig = ch - '0';

            if( val > INT_MAX / 10 - dig )
            {
                io_error( "Integer too large" );
            }

            val = val * 10 + dig;

            ch = read_char();
        }
        while( '0' <= ch && ch <= '9' );

        return val;
    }


public:

    Device _io_dev;

    image_read_settings< pnm_tag > _settings;
    image_read_info< pnm_tag >     _info;

    std::size_t _scanline_length;
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