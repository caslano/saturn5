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