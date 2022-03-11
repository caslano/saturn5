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