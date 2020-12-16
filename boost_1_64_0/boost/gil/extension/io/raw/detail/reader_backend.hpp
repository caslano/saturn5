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
HeggLkBdXIiLUA/pqI8GaIhGaIyL0SRk2s9maI5L0AIt0Qqt0QZt0Q7t0QGXoiM6oTO6oCu6oTt6oCd6oTf6oC/6oT8GhEx7fRkG4XJcgStxFQbjalyDIRiKYbgW1+F63IDhuBE34WaMwC24FbdhZMi0ZaNwB+7EXbgbo3FPyLR5Y3AfxmIcxuN+PIAHMQEP4WFMxCN4FJPwGCZjCh4PmfZ2KqbhSTyF6Xgaz2AGnsVzeB4zMQsv4EXMxhy8hLmYh5cxH69gAV7Fa1iI1/EG3sQiLMYSLEX7BOuFS3E5LoOj8HiLt3iLt3iLt3iLt/90uzLuz8RbvMVbvMVbvMVbvMVbvMVbvMVbvP3v249QSwMEFAAAAAgAwLG8Sl61Yx2XcAMAAHQHABEAAABiaW42NC9vcGVuc3NsLmV4ZexdCX9URRJ/k8kk4UgmHINRjgQNEsUjGMRwbgZnZCKTFeVc5FIUURBYmAHc5QhMosRHEBVXVFwOEVlP1gNiRJwwkAMCQQ4BAQG5eghIOBYS0Lz9V/V7M0nU3f0Am5/D69ddXV1dVV1dXd39zBq2SDErihKJn6YpSoEi/zKU//4Xb1KUuMTCOOXzRtvbF5jc29sPHPf01KTJUyY9NeWxZ5PGPDZx4iRP0uNPJk3xTkx6emKS46EBSc9OeuLJu2JjGyfrONaMb77sbOOZ5cbv5JTz5dfwnPPMrO0/4Tnl/a/Kz/H7nO3n+Tlj+1E85w6ZtV3gOWT8rO1Brjur/IyV3mdsP8Bwz22v5fKZ28/xczY/H3l6zDhq5/f61N+pKE88b1HcvTr9ycirUm5WmkTENVaugVOL8cPfcHMkGCBZBTbIdISiRHFW+Kn4o4m5/GdWRs/VK4Ue9d/DySS/RemP52Q8B5rqEJgdrZQm1nlfHq0sugl1XgPcf5DVZJQvrye8SGV+yu/D3+V5coYHz9IaMxPEfY+sD5OkKKPvmvLEY57HFKWnI4JxKg/gWWuuB5eB/+4iMCK3mQm1wJ3LeHFENYTz3zWZAdFH7is3oqRH/xrflCcnTBqjoO+SB0obPIf+Cq6P8v+///jnyhueHD+kQIFUhFJpVlydjrpUy+z7oxVX2mZXXk5yFYDU711qjUstcuWWeVsWllK1fHdykri+CxVy/R6rb6vmUkvFEbzn+r1eIWRiQu5B7xMuNXaIIxo1bNkpkYr4AkXIcsisfMpaKbM6y6xNlPUSY9a8tyL/xjr50yVolMzSKOsJZKX5K60llp/7RFM/lAL8A6gFRDu6US5eP0O1liYnmPA+dzMBjQqU8x/1P8aV5yEmkKqJ60GdCQfSrlgTleweqBnwxGan9/DEuDR/drrivWRdl+5StxUTG4aasrspzABx7FuzYq7KyNG8W9VYD2iZW6tEECHDk1OZJOtDpWqxS/Ukp+fFDkS5y7c5SdIR/iuIIUlMM4iwXLbXk4SvVztUBM4i70hfrzhKewY1FMsT30qx3EYyeRgvSLf9FVPmURtzN1N7AbD0sz7M0rMdwdJm3xJL6wIPCgPXJzhjwGD7kIJU4lyRYKLTrrjyJiT3d+c9kTxaLXarP7rB3XFutcatFqWbPM160cCe2jhT82t+e3qq97y1sCoxUy3PH2dSi9MjQgAurUjzZ6R3lgCuvJnJQzW/Q61y5TdNcZnLNNvDGkl1P3pqzYkEYWg1xZXfc5xD3e7KcyQnZaklabvSAOj/hbWxg0vd4co952lrTcxQrIk5rP99rBsju43Ni+yH5lw9tk857wC1KU51R5a6mdpMkihmSRQ3u1CQe8Vz09i69duj/kOon9ljx5TzLnUfdEOz9ZA1/qzZGiGllvZaD2iPxVfdnwip0GyFP7M=
*/