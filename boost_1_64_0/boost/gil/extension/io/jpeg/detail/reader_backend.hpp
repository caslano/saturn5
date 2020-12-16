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
Oe3bACOdUvYeFc4qovWi2FNoncNxRIfD2q4Oe8J+W9h2gQP+7Xoio86zOpgfN17m0Yk4OWfaHWIZ8H85Z1qneAo6Y+xWOL0BOtczh3VI9VMB99cVvaAzyyjjiLam93598jU279JvYDCfR4m2lyedkzSOpvp8Wu6tqPrSZ1fvID6mCBsmSif6YJYr38+Psb7KfRuWBdOPe7IQePpMclDgeLJaoewnE1Q2Yw/NZSNZbSW91+1zRNCtLnHufRyXQ+5Bu2dsklZK6eZCtTYifNbN0Tml7M76o30x845pLLODjzQVjOZ/mTnF8eGEOUVb1Owc/3omh3BO6VOe5FXgsasUL1t7JBcI8di1ozgmmd/Myy41Vu2mvHdS33Ei5X0S41WiLOpe7Rx1r5bS7CG8FePxa4+kmWsJY95PF7yfLng/U/HxLuLjDOL9LOLjbMKLCtsW+e7rHXV2XuV4v0POdvvbrL3Dzlb+Pc/pcbz0Cx0zgXPXBQhWnivmYM1l6wV0QZXhfCrDKVSGC6gMFyq8nUrmFxPeXsaDfISeXaL07NI5+JSevYdovJdwDwmSF8miVsgl5GCDntYWlwk5hCfQyV2CvysUf++fYz7lF5X4+wDhLvDxt2XZktiWUX+dIix8XV0l5+dl6x/5ylXyvtrrw4gXyae+93e7siv+2Bx/fEb1/ddSPKfHJ+OvU/Enq3nd9cQrZOCfdyGfgLtNqEP3A779Mmo/40bVr1aLT/arN5FMlk/3688Ot73HtyeGoouanac9WK0HW+Q8fYCpI6T5nK+O2nIdWfet/LP4vCqyczBhvVO1pUfhkKWQiOxMDBYMgP2njMXpT8SzgyN8rsfxPTDsSwxx0LHxU2T6FFx6JIY2jO5Ijg65eyl8VvUF8ArHK20R910pPKvS19vfhd90XhUYR2dW3jvur7Ul7U6Mbs2PGLgHw9ma+/YDRRn4Cdb+dE1heNi9y+6t52/xyQx7Q11tve0R6zKjZ63VawUraX8aW7+oZXmrTeL+5LX/bTQu73EcX9ih/Zt5TnHv/LgKWTZTBdl06ijyNcLl67ceUgxYrq2rnIH4VheXYdVONIGOE6qyyKH00MpINpvO9mYG00MJwp1vdIrgw8Pw1yPym+bC+xMpPIOWzjKd/Zh2i1P0y9cOO08iIepkpoUzCYY3MI3FTCPsrN/ZlstyuMkNx9bDW69H83bIcJ7TAcPPfDSxNQlNzOa4/0Lc1c6mbds4xs3viwZe4eW3xJ4xhCDOLxV1AKHYpv7WjThM7o2ubx1wq1NCUKsbg+s/OtAdM8++8DlrX2sU7ukHsKVoyYyHwDYMX5kz3rs28LCyJtbdHo3B4QqpmoTQ2HAX0TC65d3V6yu1D1emznt+he8wayalU3cjv5DShXsA2+x0bYtvTfTF8yPmaTaGZ6DX27bFR4e6Xf+CG2kP6GuiHva8AvJsCS5vN55wEk+9ijDJ79456l1gy1cHvCEe73hh9CU27L0L/A3Zj4yfR4k5qD3cj2wilaMA68X9c8Z5Y1L2pNFIW2+03SWioVS+b6s9qe8gbPTkW/Y/+ame445L38X/BSV1kVWQ+XyQaHeU0rWjuowlBsTRGz06NtC6ptu9WRAYQ/x+n+dl1XW2n0Ne/Lvqmac93ZxHfeZQwt///MDOe91hqJfsy39oYb2ZLsxEZT/lOHbUJAKuzxPIqOZHwK9k/tE2LNsDEmBlUKJv6FrfuhZWGxtgvoF3zYyHKVMtQkPGxSA5/Hh8HVjbby1cuiOie9BArqef6D6CfE31kCyvDY1t5z8zeq/a+b22H+4aXZ/Yls7u6jUOv9fbx8u70fMKf1g/l3P8Mvqxp3x+WTf6zo0PtvPTvnQ=
*/