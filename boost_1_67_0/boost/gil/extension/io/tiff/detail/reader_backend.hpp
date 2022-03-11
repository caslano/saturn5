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