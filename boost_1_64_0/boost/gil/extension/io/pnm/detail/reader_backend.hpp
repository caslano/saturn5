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
UZEPLJ98aowvv6ozq3RBDAFe6bLlIMsWrXNhwf9zjEfdgpzK3aSWE6Ajp92firXbepaLbeJeUgFs0IR93nq3IfwhnUF3APTh0pNOAPv53+hL4+vTiMKEspa8FHD4om1hbAh+/jqSm1n5/lJWV84MjcWa831JsNDVw3Ea883elUuoc4aoBWoIJRFAgz75NhFFuz6j1iDXqMHjbMsl1rJIT9brPancKgmA/rXZjnMRJqiD/55CkimoPK2Ud4LoYRGOQWVI7qCQRL79h7tIRK453fzV3IGKonen0vv/0BAIugpfAajBehndOyQwjOBwPipTNdrUF8xvbBx34x05OjlKZMErLNQxa1jflIkyDlKSnk63+WNfoIEbQVVpaHYxpa4Zr0kWOOWENgmVmHgsqBiChRUippCWZSbwLXGE54BAUsMyJ4cEvD+i+1/vNb93geJQ+oLIHf7uRZD45pjdtf9LjyWnAZ9uqoa4QX8Jx89NsEg94NXD/RqWeEAaUJqZVHjPR60BQgfgHF5cdnyApM53slGz4mrfHJaB8F2UvGTUYgdbSF7m9UHlwwc0BA==
*/