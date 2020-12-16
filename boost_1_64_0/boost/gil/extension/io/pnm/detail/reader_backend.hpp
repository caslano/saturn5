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
Z+jm+9Z2X8rg7oVVerwONHlTctRQRKoYidU8rA0sTydkwxfyuHVwv69xcDp/xCkqIPsbh4doOlMFi4WQIU0/1NDNfftGqmi769vr79Zp3CyqlKzasvez3/ZvpD1pBvJw2mRfNommDixXRp+bRlke075U5kxkLi0dX7HPL9c89G9gK3zrFmO/bS19PK5a2nN9qgyfzq7KpZuK0lfuGtCUETZH6WlHlIc7n7s+hdv3RuaMkVDldZn8WljKretOnyen353YCe/0GNrA1srhuaics4U7bG99bdWmrw/z+2X6PiOaJj5+3QMuf7Gyg8rvyF8CdfI+018pA1x79PY0t+aeDx29vXvW8njG44KtorOWuxnsdIPto7DvGKwgwAZUBwaRYExuHXZSdXDugqqtSZY1tjcnS41pV7Ks73aFj19zz/0GeNx4/Lmjst81oYqsHYIv6WT84vN9POZ80pqW3Lt1LvTwh/cYcf2BXg9wD67LZz9UZfjy5Yc+mBvgVJzz4n74bC2VjF3q4bf3SdPf+hn3ji63z1267m9tBy8zZa4w5VVJfpr2Fy/XNNOu0Gla7+Nx+0h9n8LwmPYazUrLl7orvx8+Rl203wJfLs8aDoHZGmTHguG1oSwjSE5E6638/KYQl1/vy6lxzGpeoLcx8nsCvd1vqsjEdBzEYL9bmMGupv2bb836WzLYLoZvz9IMdi18e8E3V/HdOCrim7RlBrvD8H1b8d1t+Io3yWCPgx0K3yDF97R59ssKe9Y8u+miDPa8wW7ZNoO9aLBdVF1eM9heiu9NU8ZFqox3DN8dik9Gixzl1C8xOuL74bgMtvXoKL8bFd/g0VHbxihsBb7HNWC/iGWwoSa/gv0y2HCDvbGtym9Y9Ox95tl9jA1ePquhpaVhdXNvV1d7qqG5p5e/w7si+robwm8ZN6ztaGnoSK2GlFyFhLa2TykOzzDo58OnbS7lrauLShqa2job1k4pbmjsaJlW0lC2cHLFsgoZULmpnuaGFanoQf6IHPye6AxEU+Z5CiCA0JpqqOxEvDtaW4JpLp2lqfJkPmTFxUg4fIclpxVOLymZXjilsKGr6bCWKHvD1jI5iClxtGZyd0uTbBaLypjUPG5SpSpocvgIOtSwJNpZhvw39Z/3OdIaumtlf8RUb8vK7u4NcDT3z1HW1dlcW5/D0U4Yv7G7raGts7m9ryW0g3HTD3l5OcoQWKw83dDT1xksLoIcN8wRDccGOhS+DXNEOQ2gxLYpM6blsC2kaaU1lbYb/mjkLZ8kIHs9jTUUHm7N8mRGDcjin/lUw+q//cEGVlgdy4N481b5xlz3fQVrWuaq9jCnqtbeucsaVpdMnpqfZ3FneH92WW39xvHkNiU/ybQhPXJwadvU0rq6pW11/tKXEpXpWpNqKCpsSLWsCvjE9sVAnyBF9I1+oCFc0HRt8Lml5rlVHX7WJXVlXR0dXZ26nYy+4ehuQw3CS13y9YOmR2Y8WTejMFlbJm8ZPaghFtkwpweTXIXmp8jkH2SJbXW6+5oInTR0Na5qqPy7dOHA6eMmdXbxjhn9urSEtGzcpOoW0rpJ4yaVJxfNSS4qrUmWV9ZWlNUHAJI3Z2F5RCqrQxes7gPV1pcFP+ULF/IDJ3+YZ5LzFlbPKcWLrS+tr0hW1lUvLK3nLbeArSwI79fXVpYFQLKupqJsdlGEl+PxLlsW/iu5JMhkaWXVlOLg/1X1s9U/QsKyGtjIf+EAuEoXLqxemlxUV5ZcwvePF1XWLSqtL5ufodQurgreRk0urJxTW1p7gOWQ9aq9lruyvqK2tL66NlleMWfxvOTCiiUVC3WmYRWAS6uSpVX0G3+AVlXXVdQuqSyriDjKmfA=
*/