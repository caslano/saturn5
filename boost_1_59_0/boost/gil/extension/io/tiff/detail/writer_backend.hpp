//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>
#include <boost/gil/extension/io/tiff/detail/device.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// TIFF Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , tiff_tag
                     >
{
public:

    using format_tag_t = tiff_tag;

public:

    writer_backend( const Device&                       io_dev
                  , const image_write_info< tiff_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

protected:

    template< typename View >
    void write_header( const View& view )
    {
        using pixel_t = typename View::value_type;

        // get the type of the first channel (heterogeneous pixels might be broken for now!)
        using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;
				using color_space_t = typename color_space_type<View>::type;

        if(! this->_info._photometric_interpretation_user_defined )
        {
            // write photometric interpretion - Warning: This value is rather
            // subjective. The user should better set this value itself. There
            // is no way to decide if a image is PHOTOMETRIC_MINISWHITE or
            // PHOTOMETRIC_MINISBLACK. If the user has not manually set it, then
            // this writer will assume PHOTOMETRIC_MINISBLACK for gray_t images,
            // PHOTOMETRIC_RGB for rgb_t images, and PHOTOMETRIC_SEPARATED (as
            // is conventional) for cmyk_t images.
            this->_info._photometric_interpretation = detail::photometric_interpretation< color_space_t >::value;
        }

        // write dimensions
        tiff_image_width::type  width  = (tiff_image_width::type)  view.width();
        tiff_image_height::type height = (tiff_image_height::type) view.height();

        this->_io_dev.template set_property< tiff_image_width  >( width  );
        this->_io_dev.template set_property< tiff_image_height >( height );

        // write planar configuration
        this->_io_dev.template set_property<tiff_planar_configuration>( this->_info._planar_configuration );

        // write samples per pixel
        tiff_samples_per_pixel::type samples_per_pixel = num_channels< pixel_t >::value;
        this->_io_dev.template set_property<tiff_samples_per_pixel>( samples_per_pixel );

        if /*constexpr*/ (mp11::mp_contains<color_space_t, alpha_t>::value)
        {
          std:: vector <uint16_t> extra_samples {EXTRASAMPLE_ASSOCALPHA};
          this->_io_dev.template set_property<tiff_extra_samples>( extra_samples );
        }

        // write bits per sample
        // @todo: Settings this value usually requires to write for each sample the bit
        // value seperately in case they are different, like rgb556.
        tiff_bits_per_sample::type bits_per_sample = detail::unsigned_integral_num_bits< channel_t >::value;
        this->_io_dev.template set_property<tiff_bits_per_sample>( bits_per_sample );

        // write sample format
        tiff_sample_format::type sampl_format = detail::sample_format< channel_t >::value;
        this->_io_dev.template set_property<tiff_sample_format>( sampl_format );

        // write photometric format
        this->_io_dev.template set_property<tiff_photometric_interpretation>( this->_info._photometric_interpretation );

        // write compression
        this->_io_dev.template set_property<tiff_compression>( this->_info._compression );

        // write orientation
        this->_io_dev.template set_property<tiff_orientation>( this->_info._orientation );

        // write rows per strip
        this->_io_dev.template set_property<tiff_rows_per_strip>( this->_io_dev.get_default_strip_size() );

        // write x, y resolution and units
        this->_io_dev.template set_property<tiff_resolution_unit>( this->_info._resolution_unit );
        this->_io_dev.template set_property<tiff_x_resolution>( this->_info._x_resolution );
        this->_io_dev.template set_property<tiff_y_resolution>( this->_info._y_resolution );

        /// Optional and / or non-baseline tags below here

        // write ICC colour profile, if it's there
        // http://www.color.org/icc_specs2.xalter
        if ( 0 != this->_info._icc_profile.size())
          this->_io_dev.template set_property<tiff_icc_profile>( this->_info._icc_profile );
    }


public:

    Device _io_dev;

    image_write_info< tiff_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
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
*/