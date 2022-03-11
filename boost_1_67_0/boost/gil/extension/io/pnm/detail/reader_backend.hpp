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