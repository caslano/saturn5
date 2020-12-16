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
PtgLKaMkJYhSRrWS+88AqT8S1lkxTyWzabtYTC/glmVzaapBjhonxQcJmaOvg0xQK1Ovn27GsDQYKcQ/fzAUshJMsqLtINXf+20Zvh1wOm8iAtvDAcKhygJKWIOE3BjS3lDSa0iSC8/TsHty45oIamKj/XJboJQQSgFQ3LEwSGTQUgLdG24Y/xbQ27Ywuf8vJS4hUIZBNlFFgCx/slraVsSqIkx+xyaPpWMSDyNOw0tbijG2jYs1xrZf6ZygVYktQMYaWjvj9gmPDVIuupPcNgWk5XCHYcIRxj2rv28/xePdQM5YT5W5NxJRHuiuCOMh4AuCPsgIIMOj3mW0Yy77ffIzlVHAUi90N40sY+ebVx1p18AGlr+kFc8tQqjUPsPfCvUQeMEH+tjBJa4MgfDbyZ7R8buvxUPIYTwmaXuAC1fAF/EoR8izMZ0yhFJCH0d/BtKfLPozg/7kQC2QQisJPO3GM814DqGPIaR4+pNBf7LpTyb9maOyXhfjycw3ZYP2mflz5u/3JMuMLsbPmb/8tWk19PaLxsExiuRr6epKWDnqjxI3nnqRlwrud1SxD8suWOcA0ScR1lzEyNDBvVTd5UNLE7R6QruR0EYIWp5OdwtUoryVsy2RulbeSuU26zACdRZQmYD6A4SPd/JLLF5smznaEVEya/TUkEYFYZIeIKhzOP3nS5elj9NPXA4aqO+7HJSlf3A5aIa++nJQjr7yclC2/iiB7ABVFeMv6R31eZe4RhlcI7YlWh+gfv+CHMiXUP/6/EF02/bq/neNs2e68z8ILUmO9vV4OWY99GQI5PMVanyYrOpDQ8DTwLcZhxTFT7u44zbNFeXrT0EYqSKBQ1e2NtIPl5G7AkfB11Y7/xw4oCp4nMdjzmRfYfChnUIjSRcZqjrISHV8qRMqcfUGjEpZKW06oQayuhTsdcXwHaKcsIoSXK3F1gFi6NUPySLf+O2hLCBQwjZDY5rXmurMHvB56hqBdymK3Tmnr8GnDAJlKqo90ojGYH7y9up8BF/GYdxUwo0I9jpTC2C0PVhInMNoQPYJ54N4Y5ydC9PQwXTfCDnUzkBCM04Gq7kai/LoePc6oA7NZc4OIsShxNb3RMMXDYB7JyLLVgO4EkBiMVXuDQi1+fXFAk+D9qYjMrDeJqER/OALJGAK32DCsZnxxZHEgS5gKDvpY70kdor4HEKnT5oiEzwt8s4GyczblUY6ar1qg6OfB/HNo3zsEDBNUCEl4/MooStnTs9T4XbDIJiVbrMDsbLlgSXZY102OZBkYAaGJg1D06xSe/Jp11WU+3CrIBaORPKbulrsnu8PpbZT2ThxSsJWw7VImhro7A25Via4H+9jHo5CJmqycQEMPQIoLSmuxeepcYGGV0083TQJ75I8p14D33cF0AFWIPO9HYio9ULhGcHZNxkgjyUI9f/OdTVVtT+XW8urBbr3JnjHXpMzxE+BitpOElyLgRsluA7BfdfAXS24Wa6hSLtG0l6kOi1HAmXfEM7Z2iKJpu7MEH713MuYA6lmM4XEDNdUJHwrCfOIRJpBYgFIsAsaepkt9LYAj+iFh9AxE537SsabKWMHC+P8RUB1kwCySCHZ4vWb/YbQ2mQgGeAR2QsQEtPeRhYLxyBl+OxdwUzrVqHleVXsRt7xBNLYMTDhCObe4c4SV5VtawS7HidL6VBgfvMq5+t0L61dBiPJsyO5wWG11ymXkddZ8kAAZuM6u4yRNgjX42+TxSES7XRGk75abU0StSV9fhYEdo4l15oqS+DHwrhXFgGaA3duNPmhFJw3onDnqyQlSLEHC7YrTMWFsUn7vBBWl9WTvEkVH87B2u34pUCKz6P4q6gg22Q8iAg=
*/