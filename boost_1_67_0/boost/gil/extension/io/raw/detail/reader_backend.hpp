//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/raw/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// RAW Backend
///
template< typename Device >
struct reader_backend< Device
                     , raw_tag
                     >
{
public:

    using format_tag_t = raw_tag;

public:

    reader_backend( const Device&                         io_dev
                  , const image_read_settings< raw_tag >& settings
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
        _io_dev.get_mem_image_format( &_info._width
                                    , &_info._height
                                    , &_info._samples_per_pixel
                                    , &_info._bits_per_pixel
                                    );

        // iparams
        _info._camera_manufacturer = _io_dev.get_camera_manufacturer();
        _info._camera_model        = _io_dev.get_camera_model();
        _info._raw_images_count    = _io_dev.get_raw_count();
        _info._dng_version         = _io_dev.get_dng_version();
        _info._number_colors       = _io_dev.get_colors();
        //_io_dev.get_filters();
        _info._colors_description  = _io_dev.get_cdesc();

        // image_sizes
        _info._raw_width      = _io_dev.get_raw_width();
        _info._raw_height     = _io_dev.get_raw_height();
        _info._visible_width  = _io_dev.get_image_width();
        _info._visible_height = _io_dev.get_image_height();
        _info._top_margin     = _io_dev.get_top_margin();
        _info._left_margin    = _io_dev.get_left_margin();
        _info._output_width   = _io_dev.get_iwidth();
        _info._output_height  = _io_dev.get_iheight();
        _info._pixel_aspect   = _io_dev.get_pixel_aspect();
        _info._flip           = _io_dev.get_flip();

        // imgother
        _info._iso_speed         = _io_dev.get_iso_speed();
        _info._shutter           = _io_dev.get_shutter();
        _info._aperture          = _io_dev.get_aperture();
        _info._focal_length      = _io_dev.get_focal_len();
        _info._timestamp         = _io_dev.get_timestamp();
        _info._shot_order        = static_cast< uint16_t >( _io_dev.get_shot_order() );
        //_io_dev.get_gpsdata();
        _info._image_description = _io_dev.get_desc();
        _info._artist            = _io_dev.get_artist();

        _info._libraw_version = _io_dev.get_version();

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

    image_read_settings< raw_tag > _settings;
    image_read_info< raw_tag >     _info;

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