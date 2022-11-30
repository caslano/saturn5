//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// TIFF Backend
///
template< typename Device >
struct reader_backend< Device
                     , tiff_tag
                     >
{
public:

    using format_tag_t = tiff_tag;

public:

    reader_backend( const Device&                          io_dev
                  , const image_read_settings< tiff_tag >& settings
                  )
    : _io_dev  ( io_dev   )
    , _settings( settings )
    , _info()

    , _scanline_length( 0 )

    , _red  ( nullptr )
    , _green( nullptr )
    , _blue ( nullptr )
    {
        init_multipage_read( settings );

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
        io_error_if( _io_dev.template get_property<tiff_image_width>               ( _info._width ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_image_height>              ( _info._height ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_compression>               ( _info._compression ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_samples_per_pixel>         ( _info._samples_per_pixel ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_bits_per_sample>           ( _info._bits_per_sample ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_sample_format>             ( _info._sample_format ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_planar_configuration>      ( _info._planar_configuration ) == false
                    , "cannot read tiff tag." );
        io_error_if( _io_dev.template get_property<tiff_photometric_interpretation>( _info._photometric_interpretation  ) == false
                    , "cannot read tiff tag." );

        _info._is_tiled = false;

        // Tile tags
        if( _io_dev.is_tiled() )
        {
            _info._is_tiled = true;

            io_error_if( !_io_dev.template get_property< tiff_tile_width  >( _info._tile_width )
                        , "cannot read tiff_tile_width tag." );
            io_error_if( !_io_dev.template get_property< tiff_tile_length >( _info._tile_length )
                        , "cannot read tiff_tile_length tag." );
        }

        io_error_if( _io_dev.template get_property<tiff_resolution_unit>( _info._resolution_unit) == false
          , "cannot read tiff tag");
        io_error_if( _io_dev. template get_property<tiff_x_resolution>( _info._x_resolution ) == false
          , "cannot read tiff tag" );
        io_error_if( _io_dev. template get_property<tiff_y_resolution>( _info._y_resolution ) == false
          , "cannot read tiff tag" );

        /// optional and non-baseline properties below here
        _io_dev. template get_property <tiff_icc_profile> ( _info._icc_profile );
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
            if( (tiff_image_width::type) img_dim.x < _info._width ) { io_error( "Supplied image is too small" ); }
        }


        if( _settings._dim.y > 0 )
        {
            if( img_dim.y < _settings._dim.y ) { io_error( "Supplied image is too small" ); }
        }
        else
        {
            if( (tiff_image_height::type) img_dim.y < _info._height ) { io_error( "Supplied image is too small" ); }
        }
    }

private:

    void init_multipage_read( const image_read_settings< tiff_tag >& settings )
    {
        if( settings._directory > 0 )
        {
            _io_dev.set_directory( settings._directory );
        }
    }

public:

    Device _io_dev;

    image_read_settings< tiff_tag > _settings;
    image_read_info< tiff_tag >     _info;

    std::size_t _scanline_length;

    // palette
    tiff_color_map::red_t   _red;
    tiff_color_map::green_t _green;
    tiff_color_map::blue_t  _blue;

    rgb16_planar_view_t _palette;
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