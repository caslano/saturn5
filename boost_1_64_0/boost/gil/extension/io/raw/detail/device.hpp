//
// Copyright 2012 Olivier Tournaire
// Copyright 2007 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_DEVICE_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_DEVICE_HPP

#include <boost/gil/extension/io/raw/tags.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>

#include <memory>
#include <string>
#include <type_traits>

namespace boost { namespace gil { namespace detail {

class raw_device_base
{
public:

    ///
    /// Constructor
    ///
    raw_device_base()
    : _processor_ptr( new LibRaw )
    {}

    // iparams getters
    std::string get_camera_manufacturer() { return std::string(_processor_ptr.get()->imgdata.idata.make);  }
    std::string get_camera_model()        { return std::string(_processor_ptr.get()->imgdata.idata.model); }
    unsigned get_raw_count()              { return _processor_ptr.get()->imgdata.idata.raw_count; }
    unsigned get_dng_version()            { return _processor_ptr.get()->imgdata.idata.dng_version; }
    int get_colors()                      { return _processor_ptr.get()->imgdata.idata.colors; }
    unsigned get_filters()                { return _processor_ptr.get()->imgdata.idata.filters; }
    std::string get_cdesc()               { return std::string(_processor_ptr.get()->imgdata.idata.cdesc); }

    // image_sizes getters
    unsigned short get_raw_width()    { return _processor_ptr.get()->imgdata.sizes.raw_width;  }
    unsigned short get_raw_height()   { return _processor_ptr.get()->imgdata.sizes.raw_height; }
    unsigned short get_image_width()  { return _processor_ptr.get()->imgdata.sizes.width;  }
    unsigned short get_image_height() { return _processor_ptr.get()->imgdata.sizes.height; }
    unsigned short get_top_margin()   { return _processor_ptr.get()->imgdata.sizes.top_margin;  }
    unsigned short get_left_margin()  { return _processor_ptr.get()->imgdata.sizes.left_margin; }
    unsigned short get_iwidth()       { return _processor_ptr.get()->imgdata.sizes.iwidth;  }
    unsigned short get_iheight()      { return _processor_ptr.get()->imgdata.sizes.iheight; }
    double get_pixel_aspect()         { return _processor_ptr.get()->imgdata.sizes.pixel_aspect;  }
    int get_flip()                    { return _processor_ptr.get()->imgdata.sizes.flip; }

    // colordata getters
    // TODO

    // imgother getters
    float get_iso_speed()     { return _processor_ptr.get()->imgdata.other.iso_speed; }
    float get_shutter()       { return _processor_ptr.get()->imgdata.other.shutter; }
    float get_aperture()      { return _processor_ptr.get()->imgdata.other.aperture; }
    float get_focal_len()     { return _processor_ptr.get()->imgdata.other.focal_len; }
    time_t get_timestamp()    { return _processor_ptr.get()->imgdata.other.timestamp; }
    unsigned int get_shot_order() { return _processor_ptr.get()->imgdata.other.shot_order; }
    unsigned* get_gpsdata()   { return _processor_ptr.get()->imgdata.other.gpsdata; }
    std::string get_desc()    { return std::string(_processor_ptr.get()->imgdata.other.desc); }
    std::string get_artist()  { return std::string(_processor_ptr.get()->imgdata.other.artist); }

    std::string get_version()               { return std::string(_processor_ptr.get()->version()); }
    std::string get_unpack_function_name()  { return std::string(_processor_ptr.get()->unpack_function_name()); }

    void get_mem_image_format(int *widthp, int *heightp, int *colorsp, int *bpp) { _processor_ptr.get()->get_mem_image_format(widthp, heightp, colorsp, bpp); }

    int unpack()                                                         { return _processor_ptr.get()->unpack(); }
    int dcraw_process()                                                  { return _processor_ptr.get()->dcraw_process(); }
    libraw_processed_image_t* dcraw_make_mem_image(int* error_code=nullptr) { return _processor_ptr.get()->dcraw_make_mem_image(error_code); }

protected:

    using libraw_ptr_t = std::shared_ptr<LibRaw>;
    libraw_ptr_t _processor_ptr;
};

/*!
 *
 * file_stream_device specialization for raw images
 */
template<>
class file_stream_device< raw_tag > : public raw_device_base
{
public:

    struct read_tag {};

    ///
    /// Constructor
    ///
    file_stream_device( std::string const& file_name
                      , read_tag   = read_tag()
                      )
    {
        io_error_if( _processor_ptr.get()->open_file( file_name.c_str() ) != LIBRAW_SUCCESS
                   , "file_stream_device: failed to open file"
                   );
    }

    ///
    /// Constructor
    ///
    file_stream_device( const char* file_name
                      , read_tag   = read_tag()
                      )
    {
        io_error_if( _processor_ptr.get()->open_file( file_name ) != LIBRAW_SUCCESS
                   , "file_stream_device: failed to open file"
                   );
    }
};

template< typename FormatTag >
struct is_adaptable_input_device<FormatTag, LibRaw, void> : std::true_type
{
    using device_type = file_stream_device<FormatTag>;
};


} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* device.hpp
WezplRDnLSfeNzUu9xOjvS7OXn0T+ygsZr7fyx4gseQVB1E+MbSv00eziIG+/QWe3ZvxPJX4JHudOz5C/Jk+3Zu9xy8RO/0Zcc+TaP8J7CN8kXjwAR+z93V6TKbfyR7kLxLy+DjaSVz1IvZI92LMLv8U628W2/dS1zNOisk+PyLu90mRd+7Bb2Yf9n3OBqSuZP/mZmJoyHThGSLLvh2Txt3ZL2Tf8rm6mBxF7P7bxA/3po9OHUIffoIY3dyY3EmcdTfiaDucSEyNfaSVz4isQT4uJXZ/E3V85NaE7F/IWL1AIn5VciFrNiaBo2j7j8+ijUjgq5uxZ/8O8Wzq+Vn2d7qeFaltZk/nJPrqB/TZj9mXv5vYaA8xXvry2TGszUeIvEIcfxB1Ho78lI1Ebreg7BMZJ/ZMRrzO3trXibsRU53HYrzwA/ZHGafDiZ1duBmxvRnsoRMbvWEW/cd4n/RNYppfpJ3ziFVPjsmaa4hzfz4hP6AO5xD8+O6DItN+yNz1FvHu/ajTrsRpd03Ivn8WWc3e2eJlyPZ26MEbxOzpy4UnMjbHkoivX0ps++eXcebgaOThBOLhxPXfW08/riDeSAz4dmLB3c+yN0Seg+aLtPP39//M/g97lEcuIi5+B+UgD6exx9KSFLmihfL3YZzLWIsid7MeZjyepK/ZmzwH3Zq0LC4dz1HnT8fk14xVH/mV/wH943fBn9mHuJx4+/nEyRcQQ+3FNu7E/EL9rkF3dmeP6mpkY6bEZMwjyD4xxq+cT1yHsd+ihD56mXGpYI/kxrjcwXmU7Veh59iPVur6YXNMbiQQ03oT8TfG/1N/QXZ3YB+untjlHfQT+jT0OmKYHyMnV1D3e3j+QNqBjjYTdx92NfblAPZ+/trenYdZPYUBHD9zb6JMSstU07TMqJAkIiJLSinRtGnRXtr3TZaoLCEkS6RCRIoiQlFKIrRbIi2TUClZUgopn9sMzwjh4Q889zx9nzsz93d/5/zOed/3vO973vvk/o1icsvmdBYYn1g2Iez8zlmHc7yKzp3mkaXH5js/kOecNEzu3TrkJ1e5JIrq0c9QlA0y3lLG9voA51jONCa55vTG1vdFskmGnmvrnJJu3jc2GuZNlBNax0Y1laOmb2c7o9kszzpgaZAzVZug343LnBmrl7i5k3MjQX253pFwwhl03XlPN3q7vaT89BT5/47kT1Kn81FRdUtRtUmRsGCXPHovecqebMrb5HdLJNTIRR97yC271w+vspd3yBMbe9vr5eTYmXNGWx852OqL9ZPGJoy1D5HdRU2c+bJZZ5mjt31hYFhKYD/kRV8hS2fJPVWT22BLWjgDLe+MpRQb+egxbGA5cXdR8Tl9bb5ZvQwbc7ezoqZ3OddZJp8uj38vWzynr/FcGAnr2PfEFOfeGZHQ1Tnu8WzpAvI7bZCc6WR56qLGQW8yCrCXd5EfMtjFWUbu4eZwsTP/K50VWZMxC+nNDvI3ypkNO7PyWHNU2j6j9mfEYSLnndHw+tPGKnc+i17PSbdudHbXXue0zt67VnFmV4hskfPWdCWNniU3sMTPyGef6iwnF7v+DptBFprqt+NgY57vmfX5yYZImNjKedMr+sjn/Cs5EvZ4vmcT2b01IURXs0Gp5s3YR7IDQx7m01ynnqCyPWUQvWf7elrPcjfaG04jK0OC+hmy72zgvIrs7QD72Axn4/SuxGZ+rOd66n71PBvIA9n4kqwN9EzPXEY2nbc+8Izzh85+N++zB5q3JHbHeftYdmX9vKj6FTpD1xq6x4Ly/AByNKWC53jJekxyttZFvVdztoKO17WPJtkP+q9klz9xvvdkQhjtXOpTz/hNffZwtevmOHOmmws=
*/