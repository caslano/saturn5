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
uSG3rOzG+hqNLT9ewT1AEQGAia6kQxhHLoxWbrJr04K4aXW9TDRNQU6uNkKvmPP4OBKboMfU2wh4DAAIgc7j+pM/bSKik6K3PramxLdvFp3SuwXrO0M0VA9hH/8xrOVtqiEgTWrZZVgXkqWXhpzrHuf2slQvJfnTxoga2bDjHFqXGzCmrnI/OsVQtsNLxQPrgGAyqFAtDLiltUT3/CNggVkedsDbTZZ+0AmkHefeeihweYuf+eP4PyKzz3H6W2lQ0h0aNPoIR+1hhzcGN3CDj+lCcvYuqf2qrJkBQPC7x/BqXztWfW1WfXXJE07kQwjcF4xCNAtifhbIGfRI1bHuzUhxjNQGtSRTBsyCE1v3tNvEsDJcY5OjcVc5wtTeU8g/uELl/hNa2c+QcRuo2ft0IbK3sggtycM6cwwZ1aoif+T5meUaU9XXnQ1Jk7oNNVZ/xhqHWHLug+ks9KyVL6yUP3okXW3KRPJrTZn96sx+rIaZhgRXsT5q/yyEMJK7gxRW01ntdGHxIJlQRXgWL5A1cskALHXRkmzsPPq3iB/8L37ZZPcHhf89ZSpgiMFznqvgQjHHTXFsQ0FPIelYgUYSGiNQfSUTtgXAK8++ilf24O4nXRu4v0Cg9QLcRLj5cEvgdpVzh+EM3K9wv8NFI04sXA78G+H+dH9U43zEFfsjfeeuhO/4PyOTptH9UbHuj1IxR2a712OKzHen6/S4i0L9AkqqsEWCKzLds3SGvH2qTh077OPcFy9exvQYax3nzq7ktLZGM5+7amv0OwAYMF9x/KeqnM6j5wLjD6HTzI/i+Q9wmGRogemn8dNh8KOnQotCk0xHeHXKvCNNd0XBR2TaG18YzFBPQfAemfdOwb8+2Bd+EyGxSgALdlGkXcFbdNp7x4dpb/JEzIPXMgMGCwFKebMfzdblMC/kx5CHNYWTtdinIhHuSwXTNP0ovKAYZuj2mTY4Vw0bQtpAzGHrMRP407DNAUJRIgxr4lZSGdf3OklgA3ILr/KX6lX+XpVBhG+Nc0B0qiLz5Zl+Ul9DxummJOV7iotdM79ltSaAlWFbltMyyFP0qi9iaDUBbrBTpGyTlit8XndLJwwxzdP4gyizESQ8vc7KF+Yj6rGDiHpZlJrcqdzDBwD89qDgZyip08T7GiB/Wqpse8bJtodbym38aKnPyDdGIqA8GBFbIKK573shcr0S2UoizzKxOfoatnCeda3t8yFhg2K34Mc8zvnhGlSl0WvOu/Adj9qktWzhgO8PqP5vChJpoTldRf8JUo+P4CxeiL1KH7mZZmKRLbI8rikPYPRSeOpB90GnK8JvEdq9AL/7yHwFf7JOadZZnqzcii9l/VAxUD9i7cVI8x6ggb41/SW0t8DSrK0h7XYL0ua8AZDsrorN3AOIr9xlk/mq/wScJP8W3SE+kijMZxGCK2vwqeRywXdq8D4En50nwYXlg9tIcOyXgHHfAAzTVNKLXaagnwlyKehFBVWUvG1H9sy5/RIwXgPalQV8rwEjNCCtLGC9BvTVgHEs+UcAJeaUqFBnv5QBdkABxFjgRtHXAXulKF9NGNNFq049GiHHGi+BDQvZzTIZQEuHcS0IBNtgdwI5gTxN6EGYpfH/MFfhO4ir27Jv+qKhow7oDvkNEnQzKdFo3Ao1px8Juj4+Fx1M1jr7NqgsLlt/1HiP4hcjUuzvJMeQpS6VvVrRD9LuxgzZrwohY/DLDHVCBJGTHOr53+QkC7Au0zWFyYTx+P0KbiVcAVwI7le4ugj7Hb+V8LvTgv9n/ljsNDQ5HZ7xt0Q5LKspZILRU9JGK6OsLHIj/74yfvh4GYfs0iWhYrZvZ7Y7P9uNU4kvhEfOy3ZPBL8=
*/