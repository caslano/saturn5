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
NVBgKPBPqlTg1Xm6AvN9JGfuCVyKirtaROtQb5S1MNgsL465xno9fKRU6/ZRulKf88Q1KeJtjbyo4HTMDFDr0PtTGk3dRsVfn187uFw/78KnvPk+2GgOdlKIKQoSpFPn1P+wfkdjVoZ+mzRvaqav2kL6Heu4xgbv8BmK/8zHP7YFNOk2PMBF6vwvNWQqHfR+IEIx3rvQ+f8axvTZGWJJiRgEZMg9gVzROu+3cMJyJrrV2E2AkEvZ8Bms/P4m8QqaQ3GgmtF6gJYC4+hiQ2gxEZCFmiadsJdV+WkWtD1OUvQw9a34BSZnEJGzYL600n3U3yKLSu5SGbqjRJDCXfKLecAhAX/9iQm51HxgGQsFEkg+gUa9L/KkMTqCP7ZSczWKz0KNf5GRn7nKyKeSw/KEzNonsxRyu/rJrM0y6xxN244X9TO2Kb95vltXjE1/l5s96gU7R4Loa0EJ80P7sCMQDqd95Bi6Sz6PKtzIhTup3xGUpDMKPErZvmmeP9pJJ0modsy8F15g/vbDK31XQTCVtaBSjHlesvWfLxhs7V/vWHqqPLxl/9IsZYjIRa1YCWAyohYn/hkoXnghRMu0FyQtHzIthWCTbnA9iY78BzXau31S0tIWaboneBoOA90cDLUgHAAQrzNdgeAzKGpwP+Rvb+vysp0t0TS+ZVED6Ab2drIORYf5Yl89DZRnwvx80Mlf3Mk5zWpP8j2JQhR0lAVTUSAVVpTLgrj6n9GgkgKU1DOnoftbl5eGYsntudFSfWRt49tULu1o/ft6m8PwF16Q8C1+Bd+gf4tCdfSrdBpqronwZBFpb+hiyKAhfxQvWikih9M7U9msF6jTCgUa21OMwtNaD5tvRkHD6UI8ptPzEp4SLlwKun5/vqt6qwF9oyR9dr6397ykrwvRlxGirwOVHWbJx1AsyEafh4v/FU3bn5c0/ev5/0LTJkX5NX11jmS58ickHyhYTuTa3zKuVJU4S+igh1MV7jwnVsBVeHzjVKvxiMbvqp2TmpML9uFnxe8GR57zNH7H8avAbzp+2/A7Ah/3lGZRSpy7TdTMsI4m/lhAK19o96odnX+5zAbj87O8QhE75lGo8kqwK4W3Ot5m4p3E1kCg0drh+WWa5quOn37StURdMM8xFswxb9WOidmJJp6e850lPPDEuURZ8ww5XOvFSCoH5ZUfigFI4nh75coS52l2x94ocR7nxCJxH6Oprnxe3ImUcasSfgqC2OhUcDxGpGguizTbPzj3SHAQckucFRr+gpkEUdVOh3iBISqCaZT7PefupC2jDuhksB1lbqFMcDcYT2/r5dvVYASjnE5k6TIJnq+llVjs4lqLIu5GACnPCz+/NtiYjsa8dAf11kPsTL7E7MytlOycM9esENhxszwYfxcu6gHbp1NI+/ZjAxXNreedx6/M8uTrnFyqkbVe7JhLknCWEGyWJj6oC7wQwHTwpb381Nin02lpkichvmGIMYzOud6heqfTpuEjCO/M0b+dkrVPyuoGxNWs4qZcju1bc/rIM2OPX+QeHKdZ0J/N5vohZInnuSve9S511jfBG2jKWZKDTsqjPqcKlXhJ/0s5cnztQevY3xl0lU/HfMZLn13yi1FzZzFLvWmEgSsdytZxQ+2p8lv6MalULh9x3pU3AmXe85WReFvPnzhw5D07h7072R68Gcisjv82ZtAcewEBZpqHcCA7J5u+zsd3H5xzzEWom+ecYwEEXe8X+33SFS8JdbELSrKkhU5EbwGMqMqN9P2fC+DGjOw63GhEzfB1f+c+0q/35hBjvPvUWXOIMvo2L7LhuC6cIx3XZchRvyPQeXP0y5kHP0JiTCntKcuScVwSu7uKxTEhKH0=
*/