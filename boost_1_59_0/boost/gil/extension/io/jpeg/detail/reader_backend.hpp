//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/base.hpp>

#include <csetjmp>
#include <memory>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

namespace detail {

///
/// Wrapper for libjpeg's decompress object. Implements value semantics.
///
struct jpeg_decompress_wrapper
{
protected:

    using jpeg_decompress_ptr_t = std::shared_ptr<jpeg_decompress_struct> ;

protected:

    ///
    /// Default Constructor
    ///
    jpeg_decompress_wrapper()
    : _jpeg_decompress_ptr( new jpeg_decompress_struct()
                          , jpeg_decompress_deleter
                          )
    {}

    jpeg_decompress_struct*       get()       { return _jpeg_decompress_ptr.get(); }
    const jpeg_decompress_struct* get() const { return _jpeg_decompress_ptr.get(); }

private:

    static void jpeg_decompress_deleter( jpeg_decompress_struct* jpeg_decompress_ptr )
    {
        if( jpeg_decompress_ptr )
        {
            jpeg_destroy_decompress( jpeg_decompress_ptr );

            delete jpeg_decompress_ptr;
            jpeg_decompress_ptr = nullptr;
        }
    }

private:

   jpeg_decompress_ptr_t _jpeg_decompress_ptr;

};

} // namespace detail

///
/// JPEG Backend
///
template< typename Device >
struct reader_backend< Device
                     , jpeg_tag
                     >
    : public jpeg_io_base
    , public detail::jpeg_decompress_wrapper
{
public:

    using format_tag_t = jpeg_tag;

public:
    //
    // Constructor
    //
    reader_backend( const Device&                          io_dev
                  , const image_read_settings< jpeg_tag >& settings
                  )
    : _io_dev( io_dev )
    , _settings( settings )
    , _info()

    , _scanline_length( 0 )
    {
        get()->err         = jpeg_std_error( &_jerr );
        get()->client_data = this;

        // Error exit handler: does not return to caller.
        _jerr.error_exit = &reader_backend::error_exit;

        if( setjmp( _mark ))
        {
            raise_error();
        }

        _src._jsrc.bytes_in_buffer   = 0;
        _src._jsrc.next_input_byte   = buffer_;
        _src._jsrc.init_source       = reinterpret_cast< void(*)   ( j_decompress_ptr )>( &reader_backend< Device, jpeg_tag >::init_device );
        _src._jsrc.fill_input_buffer = reinterpret_cast< boolean(*)( j_decompress_ptr )>( &reader_backend< Device, jpeg_tag >::fill_buffer );
        _src._jsrc.skip_input_data   = reinterpret_cast< void(*)   ( j_decompress_ptr
                                                                   , long num_bytes
                                                                   ) >( &reader_backend< Device, jpeg_tag >::skip_input_data );
        _src._jsrc.term_source       = reinterpret_cast< void(*)   ( j_decompress_ptr ) >( &reader_backend< Device, jpeg_tag >::close_device );
        _src._jsrc.resync_to_restart = jpeg_resync_to_restart;
        _src._this = this;

        jpeg_create_decompress( get() );

        get()->src = &_src._jsrc;

        jpeg_read_header( get()
                        , TRUE
                        );

        io_error_if( get()->data_precision != 8
                   , "Image file is not supported."
                   );

        //
        read_header();

        //
        if( _settings._dim.x == 0 )
        {
            _settings._dim.x = _info._width;
        }

        if( _settings._dim.y == 0 )
        {
            _settings._dim.y = _info._height;
        }
    }

    /// Read image header.
    void read_header()
    {
        _info._width          = get()->image_width;
        _info._height         = get()->image_height;
        _info._num_components = get()->num_components;
        _info._color_space    = get()->jpeg_color_space;
        _info._data_precision = get()->data_precision;

        _info._density_unit = get()->density_unit;
        _info._x_density    = get()->X_density;
        _info._y_density    = get()->Y_density;

        // obtain real world dimensions
        // taken from https://bitbucket.org/edd/jpegxx/src/ea2492a1a4a6/src/read.cpp#cl-62

        jpeg_calc_output_dimensions( get() );

        double units_conversion = 0;
        if (get()->density_unit == 1) // dots per inch
        {
            units_conversion = 25.4; // millimeters in an inch
        }
        else if (get()->density_unit == 2) // dots per cm
        {
            units_conversion = 10; // millimeters in a centimeter
        }

        _info._pixel_width_mm  = get()->X_density ? (get()->output_width  / double(get()->X_density)) * units_conversion : 0;
        _info._pixel_height_mm = get()->Y_density ? (get()->output_height / double(get()->Y_density)) * units_conversion : 0;
    }

    /// Return image read settings.
    const image_read_settings< jpeg_tag >& get_settings()
    {
        return _settings;
    }

    /// Return image header info.
    const image_read_info< jpeg_tag >& get_info()
    {
        return _info;
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
            if( (jpeg_image_width::type) img_dim.x < _info._width ) { io_error( "Supplied image is too small" ); }
        }


        if( _settings._dim.y > 0 )
        {
            if( img_dim.y < _settings._dim.y ) { io_error( "Supplied image is too small" ); }
        }
        else
        {
            if( (jpeg_image_height::type) img_dim.y < _info._height ) { io_error( "Supplied image is too small" ); }
        }
    }

protected:

    // Taken from jerror.c
    /*
     * Error exit handler: must not return to caller.
     *
     * Applications may override this if they want to get control back after
     * an error.  Typically one would longjmp somewhere instead of exiting.
     * The setjmp buffer can be made a private field within an expanded error
     * handler object.  Note that the info needed to generate an error message
     * is stored in the error object, so you can generate the message now or
     * later, at your convenience.
     * You should make sure that the JPEG object is cleaned up (with jpeg_abort
     * or jpeg_destroy) at some point.
     */
    static void error_exit( j_common_ptr cinfo )
    {
        reader_backend< Device, jpeg_tag >* mgr = reinterpret_cast< reader_backend< Device, jpeg_tag >* >( cinfo->client_data );

        longjmp( mgr->_mark, 1 );
    }

    void raise_error()
    {
        // we clean up in the destructor

        io_error( "jpeg is invalid." );
    }

private:

    // See jdatasrc.c for default implementation for the following static member functions.

    static void init_device( jpeg_decompress_struct* cinfo )
    {
        gil_jpeg_source_mgr* src = reinterpret_cast< gil_jpeg_source_mgr* >( cinfo->src );
        src->_jsrc.bytes_in_buffer = 0;
        src->_jsrc.next_input_byte = src->_this->buffer_;
    }

    static boolean fill_buffer( jpeg_decompress_struct* cinfo )
    {
        gil_jpeg_source_mgr* src = reinterpret_cast< gil_jpeg_source_mgr* >( cinfo->src );
        size_t count = src->_this->_io_dev.read(src->_this->buffer_, sizeof(src->_this->buffer_) );

        if( count <= 0 )
        {
            // libjpeg does that: adding an EOF marker
            src->_this->buffer_[0] = (JOCTET) 0xFF;
            src->_this->buffer_[1] = (JOCTET) JPEG_EOI;
            count = 2;
        }

        src->_jsrc.next_input_byte = src->_this->buffer_;
        src->_jsrc.bytes_in_buffer = count;

        return TRUE;
    }

    static void skip_input_data( jpeg_decompress_struct * cinfo, long num_bytes  )
    {
        gil_jpeg_source_mgr* src = reinterpret_cast< gil_jpeg_source_mgr* >( cinfo->src );

        if( num_bytes > 0 )
        {
            while( num_bytes > long( src->_jsrc.bytes_in_buffer ))
            {
                num_bytes -= (long) src->_jsrc.bytes_in_buffer;
                fill_buffer( cinfo );
            }

            src->_jsrc.next_input_byte += num_bytes;
            src->_jsrc.bytes_in_buffer -= num_bytes;
        }
    }

    static void close_device( jpeg_decompress_struct* ) {}

public:

    Device _io_dev;

    image_read_settings< jpeg_tag > _settings;
    image_read_info< jpeg_tag >     _info;

    std::size_t _scanline_length;

    struct gil_jpeg_source_mgr
    {
        jpeg_source_mgr _jsrc;
        reader_backend* _this;
    };

    gil_jpeg_source_mgr _src;

    // libjpeg default is 4096 - see jdatasrc.c
    JOCTET buffer_[4096];
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