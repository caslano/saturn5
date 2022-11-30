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
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
*/