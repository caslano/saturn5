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
gy9mUAepIacir/5ZF57jt9G2fXGjNl/GptHKYP3QbNp0fCeDOCzULW6EWcG6f++6ILDu2qeOg7yfhD/JNu/b22cO91lqMoMWWGK/w+06197aDLbXHINZcbXBxFdanTVW26YvMV7SmKXL9wP0OfJDB60VMNWa0u338OI957BFdqi4CXBlVroxF2aSfz8xCFuFoJbdP4Cpmm6tpgMwlSUwVZlNmOJ8eyZhyoKY4klMZfOx51OYsiCmOGCqHzG12nQRppAGX21E+u1eCNSEqkGpVauS+QtFhk6EsUKO47GsBLBCZ5UldJ3foTur5NoCwmMB4fFqAFsWbrS6ag2yrgSQC1EF+OZjGDko627POK/Hbfwh+BMk1eNHoONCBtT380B/Uuan4gEeSQsyOr9vQPiCUvA+Ls7RE1LxItY1I+1sznLajLcvLj7C6ySciofh6VF6CsDTcnpaCk/L6GkJPC2ip0XwNI+eFsBTOT3dA0+3wlN0Tgn/zCDE6JyJ/PgFtJ4mpB1R4Q+ldfSefV/XEmpwLwH4TrTM4onOsfAzYLU8USYDv1n89ZKgJ/0gk0sn+3VEbm4Q1CWThz/UL6T7ESAfM4B4zlCRSJifRmwMvQajZQscDY7jrlMYk4oa+O9OEKdy6OG+HNuGJ4FV6OMjv1+QaUfufwkepFi/CbXmeQVdyzFTzYu6C/iPC6EW5YICPa+IuQtQivbxG/RzetddVM4uNo0ndzkzjKOKnjytytJ1Xep1StflZNMk29lI7YzpklMlrF10NLY0DwMgZqClDhBewlD00N0v4ZIL2fW30AGqr1wdeAje4zfZ3i6ttr09J7S3w567F8g/8G0LOtY+BGWKSgaCqXeoExAvbE65BpLuYGgubpHaIwdrSx3HgUNs/Aim0lVabou2oq4wZ9bpWZfKJnUsJe2FJFhee/UpBYHl6E1QZTzRYS8BqgcgLsW6+h02Z4oAvCYJeKUAXEeAp9iijxHgySnAkBRIA/y9NMCUOXugfEZIlJ+G5U2i/Ipv7simcK1VUrPQTAitYlnhB+yS4zg7PFP3lABXeSBSZQ1dnTxejXbrP5FnZQUlkeIZ6Eakyj645G5R0pQsOdCBLPNxXaHd4BKnYl/9X2JK7fGJAzNO1yzNK4xfKvImxu2ojDsr7bZn9laQ45X1sRifOB4YT570oi/TXgf/i+D/rfB/GfxX4f8W+P/f8P9xoNpn4P+zSL3GygPGimtGK7MDFWll1l2TQ9Zw7RTERccReGelS8LVvZJXHRmuLZJCQwMe4BPROUv4P9FEKC3Qyhax0jFa2URWWqiVTcOLEcryWOkCrWwMK71HKwAALP/TKwQAWpmHlQa0shJW+rBWNouVLtfKyk+X5mWw0vFaGTDFInixaGV3s9KljoP3Oct7Qe8vmx7PWfegVYe50+ZOd84pD+VFSym823IGksqmsNJyrWwy9hVzJlJ8+GnMKQKlUisbr61aECu75+T8THsse4mEQfIpNhHuXko2oUXyhzL5h/8CrTVdkw11pyuxmpKApGO45xtcFFV2oOTp+yoHwzJx83C/FV3j0PjLeGaWZswTpaXqie5BzuDHfH1+gmJYqWR3rxGxbGHZcXO4CdgQBe1b6y8dA2xo/TjyCzSIM74/F6HxN/2L2BCT2Z29jqMYMr/P9WGIAzHUWmxb97qOhNqdNUgWzpo829Z9F/609pOMnD/Z3jpYQTFtIPemA3KA+4ImK2NQZ/M5VO4xwoT/9Nw5nXNodZ89ZVOYsBNnQbl0NLhUq+1Z5InIDl/uBq56avUZZ6V19UlHg3MxtA6MMvQpT+j9wpxxXTgH0skbnTsRmB/v/QoMrCIff/8CVGwMjfVRmexMerN5xXlBtCLPA/5Koa3a9w1Tx4zdqhgnfCaW+l8gboKFhsBiyhiHroFWoBRqpXlCfJG1hyawVlug1Y7RagvrUQJrpRO12sla7XStdppWOwUGr5WWaLWztFqPVnu3VluOcbMg9O4rbvSQVvcoDMDcqJXeQ1quSM3gS43UBbg8jVQzn2OkLmLK+GSqhU+jVFAvtdIlu+/+eATuDi2l8Mfay/oBNXMCFD/0iHh5mBSQpeJlOYZVcj+8OA7efqY0TxJRHUO02lCstHopWuBzVmt71lJ4bB39bqTfTRRLOl6rLQplaZvFBW14P4KaxycgTzzAMwF5+wqlAGqe9U2IztFX4E1k46PRpeROL9TVMVAJqqROHvPHL4gdXj2/CM/ciKL8zURypwRfwTx8+Qw18QsA2FgfWpL0+NjeVuTA2FMmWDN335orfbshL1eSvn30l7dL0sLiloVs3w8yMwHAmgGbai8eYz4ak7rrRtpdf1pjDuYs1DyWWIk8HMfnsWoeuwaCUniLYiYs1rXru2BQ64abJ93LE4r8b16eUjuTdVDf5tgdB8eVW5Zp5XJVmgbmB93EgSN02zWT4+iZlTKqe3Yw7SOnQ8OZ5UdxeZmzOhlr3osRmSnTrIJi3ZUELkD+Eu3chHJZiQW0cIDVUJI6xVhBTWFJOjsLTT5GpdVJzlKLag2acL/7MF/6nfN4m8pI6o68TKuWmc/C8p6A7vgsmuWJxeEGS9XBNOPXxyZjhPvp0HcwZPUKNhcQC6L2EgyCnBw5rQ69A2q4/vz9k7yVA+2xyyPH1etAP5A9/DakGCx/5sQdrj+vyIMqUcsWVgAl5GQtXDYwlIJlIEOWaSbUbRFL9wkUBMfwivp0R97YC2mOPPIP4dzx7ofPpzS/e+sv0vz+XWSn80zCiOxcYUR2PpQW2UlDQB+1Fah0pQWe1tlN4rTyoMjOW/iVZxJGZGex7qYZwOCyoQlULw7xz+y4m5tgR4C+0T9lBHX+xQjqrLdGRiKZo/666j9lvORsPd6AIG4f09bPot+76Rdjx2NZE6FCbH15Ms6ILgBD0QRDbozeHkJYOMwN08Ru9NVM9ugVcviX08gv+zbdITa0+V+j7Py6AFiv4uzYYoNe13XvB9Ui7bZLYN4BjDCPRnpABwFpVrePpFsROfy2NgzFjQlPAK9CjEam95OfPFW2GyQfHSqr4is+zxm4uM9rqNjhF6nxiB6azLIB6HUMTzuDgNA+BUFljz47jXao+jbm24MSyKB5eeEXERVSfFSUsARttEEbMUIQRaO3RY5XFwDAPH2VxRjm6WWygc7FyWMMhgC3o+5COXi6tT6zRFobfww9m+EHeuF/nxR191YIKB7+6wdlKFZ9zI9300XdPag6bcFDQKwvPpVWKPWF9UX06quZAqIa5EsvFNSUPpaVVhryxJzoaq/RxR3QRXQwHmw0embFUz+UB/gwevZdEveZ/OF/ooNNdBCZapI7rFtGHSzzIwMY3BlQMnqhWRgOdsZMm2rJzsjJzvQZnRkpOiOO/Zgw0g2Lpi5YocMuvBMmiIr72PIitDw/AhsaWYyAcQQt6iz0ahnkd43k0/PtjdAlxYoXrabOsa/rxnuxBigO8rEFUGjik3yBIQ1gTBBxRcuBpsBi15dbwod1QVsAP4u9eTcqxwfE6UWey3PEye51s8S0mho9/BEXbgQ9vBU4xep4Ql+4MOWaC58r/v6E8LmJK+V150ZBBfWy51bTGbXQcDSuACvWedB/MOfiViHO5nHvpQk9xZ/Z7RZQ/dcMW53NTC5FXpGJofu0aSGnF1g9bI0osPLrBYh1mIGnwyxaA2Y7rNJHjC1TD5+06bwuzEuwsq5Kz0smShclDrBG5BT8F5Vy6saC216/iDWGux/2+oLT8QrfrT4PO8aXxkknBYVUU7ZhPI0vMNtOUQAxZasFGYi4QQRskjDSj/IGUJbrgK1OxTfZddjYWGyQkaVOttVVimMQrsNg0qbWCNpmOD3xLGaqwJhRJYEwbjShoju/bx5Q87vQVmHQpNX0EQGNj9T0hUbggjEnabeLLhSeWQjzzoZHQcr6AhwYBdQNmjwVYC9jK63UZdzhYn14D+VuiuMBkg9mBvQ1khQ0+fwAHn1kG38OeT6fX8+f/kdU2GlYeHFeuE+31T0uERbEDWwxpWU8KhJqK16s8dm0hO46oGZqaptxzqwNFn65prRDS9H5LfM0tUNTO2MK7QCKW5JpUICH6kkYYAFAfjENz2uELjdefwivPrxOd2oLLKfUFnpqtaZ4SPJ4Hk160BTU2YmAFWdspVEFAxNzyRLUn6YwuK+tv/ahg9cfHmmrsTpOa38oOqnTyPjZDtC0L4TOsPmg4RR/oL25Fc2nN7fR73b63UG/O+l3F/02nMXf/fTbRL/N9NtCv63wa6vToEd3eUPD7rLV/Q2Qc5ct8gz2cWwrUEk0CmaCXgELXn8fCQ4PNvmiEWzaE41gnoevOJWgUIbpJKJ6SeysMspfJcpjNzxGHp9plM824TVztzvddlsEWIx0OvIGgIWXU/TScZZehmBfnnkVtdLIK/DreqYde73hBBSyPY6ngFyRNkx5HO82FrnfH2Hb8OeBnA1/lLClrj1IeDOQaQVkWEe7kad5o9EOsOIqfDjED5OhJZTvjUYmnsSAgwjOQbJA6AfRSEmvGM5pkrBFyOSb4vfrhNtoFOdCJ2zzSkBQXYN69Tdk3Q9ZjoN1DWDpxYsADfGrwgf1+OV4Zhm3z9lwH6yfMa4DNbjNkWN7tyluZofvQ61a3ML74ifIZK2pu5JQjGb59S14fkt4kARnGiGiP6DntZcAaVHiGIM4P9TdCfVfMaV75wOgzyg9fevxT283/elrgz8O0M7CugmUDH9wKTvs0UN/6Pbzpx4/r5eFdcvqT9LFpQ+v/DrhnIHCh241CaPRHCzx8+rshO7H+0j4aCQc3r7+PDk9155Dfw7GcJkpfb+RHkCTNnW5oJOuo1Kn4mkdv1+r6QWGBLafnt9MbKx6DKoCvSnhPiBED1ehLleS6uO6bjSmBpbZc1jKuGJrgQXvf/moX3eOReFjiywz49VYqOKpOfwTR0LvuodSptEWf7kZD/kTmr3ewE1JfIIazVpAbGrz92tKi6tJ/ZZTsauLXO/b6vLpKtOVo7T5zcEMT4o/wBQ0sya124vbERXoZhy4l4pvX02xW2CoduMGiNJXoil2Ot2GnGVa0wh7fDoYsXQTbycmau5OPX8THlaEd29ghGgEJpj0zg9PK93DgJ+SLxJUohY2fz/hAG0Zee8nGShmrcb131+ir216lEJZvB5+pBOF0na89UJpAdEUowwLhTesnqApa0VJaHR2cmQUna5sZ+5mrFUia6awuwm1/coW288aNKU1vgCjSpoGcIHXjigtoWn/DtyVAhyb36op9QjR8pSzEg/YKfXQRNysu1t1uqvapez//vNQ0nmpmpcaoZ201y66O5s0VwaS4Z15XkNkNeMdDSsLAQUkte4hPv0OkwNIDwFZy7d79OGYgyJSyDOcY0BVLiSQygIizWKINK+utiSFWpw2VQq9Hq9QXwIZRKYtMFVNCKQVgRyggx37TWo5XivZIiQgXv09TXQ2Or9pHpvfEN4nzwuaYgoyvkIhls+Il5BNVxvEqsFlEK+mmW8jIVnZnrxpY8+NaCh1AI7K6R7Hd/A+dYpC6U7GBRDtpYTjjWmXQa670RCQA0nfhSTob+uAkPyQUEF3GZJ01GhBESrxNTkdeFcDJuQtBo5GFwK1fpTkaGiIvfsV2dmW8JLVeG/Cy8CC2eGqriFKQjcYzpjBAhP4n7jmBhZDNywECqcpeqIfGHAI9J5un4c3JPpFABXyVNxhhqbR9XQAGer8j9KsIx9unJ/gd/hlVD1US25DfBj0YjgwbbEXXm4ocNjV8z5Z4n8EbTxcnSfhhntVFwcOVtUYXFT/BXpnaoZScAHeD4WHAaNuXqG/hTYjnrL3IAUgmTCiOE6hzjjhNT1+kAvRmm5/hebuYUB+86x4KSOQSQ+wIC/Wnx5VtqEfc/LfczDGcr/VG1O22XCxeyxBa7BEz1+C+n4fcpAyGY+4EWvEgIkLC4TyqpVZtCsCFrHMtJr6mPIKOroMZecSP2kteFkNnnvCi6dAI1TeYGZoqVNqsEFLQIGdkpQhhUaE3dvkde5dEvRgnXsnWoOYtRbvjcassHuXJezeacHwdhBD7nQdCYgSqO0/B4TWW1tTqi7uDYJGByLsDpRx6AZt19UOYvl4H7o+mRxbiHpI5vdV442k7ejWQvdj3T/P6Ya3QGlbvQdQjOYlLv6eedH53fPwQllaqHXPG5eGGupdK99uTQZ6Hb0C5vHNXJxHfvzzfrGZfFnXOYxYEQZgN5oOfEMAr7DpRtpblEkOPxP/lSjfwz8HssDdyh5PQN6A5y46ySG5PJO8BHipLrroQ4VYdu1vLuiBkv/AUj38qU/PiXsmNHI6MHcPDuxXned0AUPiP8e7rIQXeCskOxp4R27S4fqSB/p+NkcEqZEdC3axcywSgq0uCyVspRy6jJcZh4kP8+Nf6kaw2qbPpKQ6AXJuSJIXCzEYeoQ/+xnYoOUWXvn7ft3rDeYiCVUmQKq9RT6OLP0tYrSHxZcu8LKyHn6z3q/vMoFsyPKK3RSKAYdnqq5/GMjEVy9RxnLgsiJiLZfPAMDOyp7V92B35+I9yCd09D3nO59Fr4w61Gi0ib9xtUFYxv2/E4ltjUlLwtMk0MTUtccMpgW457/JoYia+gUbMCSmJ0uS6vPG4kULiDolD33oOjvmOOiK4c3If7CAGuc6AmrD4r/gOTt78RFb3VjowJ2hWXeGLr0zdGsA1xH002uhiJv7c8gxT7qlYU/LAKLCj5pl0pY+FI2MQa06HotG+XlD9c5vFZm/8Ucj7/ST7ol5Hu0P+Kb9oYF+99NvE/02028L/PLWz4S6/V109xZyJMUodp0vAqIK19jBvkuoRacj7VC4QL0Fg34xu0J/sw0PlB/S32zFDVc6URQvSGVHo9geeTEwBpRFMDXc0OPhls/OgYUbFe92PPmaxaVPzuldfbC8Arjn+e9Gb6s7iHsvkTzI6DqLpfFIff08nIRfyBiij4fOWmE9w2LOVazq8EDRRjrvVngK4CPdOI579+B+qc/wen/4zxywhE0j35/nCWw7O8Lu51OhKMsO77cHdAwqjrYjlr0evE5vrU/PX7sPtKcIJmL4VtPJc3gKQGn3BIdB5tbG5HcO7kalv8d1yrb5SXE8oqS3+EC5FmmDitVrfIC88ziSVgPOkidEQBYwrgog0L2ADhbFTNZ25vhlx5Os6ljHOf1Co5qjR7H6D+rjU5OA2gxAZaxfTzulVH8CAbUZIQ8I4kcAIlAosPLE2XM6784GsqMwnkk/BDyeyEJilo99weSPKjtAYKJEoot4QGh202ni7X2AeUSicfELJH3Y108RZBhTxmdio2Jrpwha4yuz00JIyZMyIszlddM++ghWZbaH//L9HGlhZWPMVMKgWyIQ6cuPz6UuUuGfpAUNXPGLi/wjhrurHheTJ7zXwqdA80bsQwQp44qsVOwDNsCn/xNpfI6FP/aPFHuGVUgxmAf4wSwRNje5vgErf5KZK0V/YKEJdJwOvDKVGK6mcpA3/KcSxmDLlJDg0/uAFm5Fdnw0gnt4PWxBrw9vdqxs5T11/Tpqgwdsm0ajqJxSENhBoLo1EEjzknAocpefOiMAdXONAHVD28zdVtykKe3R20G5o9uINGW/q8cW3YvO2dO2jceIzFzLe21PHobHZeHpy6eLL9vgdWmNrp6aCT66zO0IXwHExqSwm6MWCguy9NZcPDZ+QMk1oe4Df6XTCqc4p2aYfYpzWvy3c/ramlw8V6x0RkHFi98O4JoQ3PgnsPftDE/Ie/jZGbn0IZ42gEikC5Wv/BuSbciquztDtzIYRChLZ5WtpS51v23TbXpqf/LcR0g4JLu+/IiElCuTiDPgl7LX8vhPgCFd0EN/dqoda5rZgWLQU4+AVO1AKuRjN2Aoq9Ujotv5ni+SREg4/TmCPsQfwRPhh/iJjf16sdrCjpjVduAELXyyvx95HahNb4tjDuW94bOm2psjB6vDy8LTrlQnRm+/4BF7mFD/tfW4yigenc8f3NDN0FBgO8xtYOtUOhL61bR+ENQOSNgkEjoxYSOWWCsS3seE1ZgQEgn7MAFJLfCwSHgNE3ZhwlKRsAMTlmDCApHw5LT+JBbfaE9h8aV2xGJJ1xuouJAumvl70A9fxE+DwB/0iEixrHtw2R2oggWIT10vQxGhQv+OyqlZlV3XvCFJ5I4y6Vsa0KnPn7mahGY2cKtXzvbracFI5GagC0z6cFcQrFk9fwcYK2vxJMPbDeroiF49KtxXGMpeFq6RH8G7SOnW7E0msXePOsmCVBg4fTENYAqQp9ejLWMKDUet2yqsGQzwj9tAOUy60BBQ1WDfLUjhY+/1677ocmvkdOjU6awMMD/wRnqUWlrpmIs9bslKO99DrX2MrI5kngKHJ+/0voyQTN9USrnpBur8m6D35k2poPf/sVz7N5azJIuKQt1QKLlHmlYWL1+VAysH+6VPXpUQjBB15oLBeR9AXiPTkAIiB0Pj2F5m9zHIfhovDBq4PzkbHl8BHasqbTcPiYRHgDSSLHnT9otd1oJwgDgUOVxeYOL7rkwMXMgFkz4Et7/U6exJbB/RuRzNlj6Tei3bgEnh+mYCcBlT7Bi/pFhhoQeHBtBi4AdAP4xnA+N5GKAae5AP12evAm79MwnvxXCcdv3NVvc9VFxXFNrqluFUmZN0+9GVdBYcHcduOkXRgRdNCvcvsnW127hVdTfduqriTX/eqHvjC/w/303oDl18JA9v3z5jq8ObfzAuo47uLMXjKkv3JTAePAhEC0bVjuDklF8YLyzR1S2gQezFm69DQ/xYfgqWV3bu7cgImn+y8MxZcY0cBVA2sTDdsPfYavNe5uZaGG/NYuEO/D1R3DMHYNzF5uIBeNzttT2zDw+9/gmexN1HDIsXMwQRNIW7MiqYe7uHKZ0lHh//vBe4BUEq7ono6u/w0xk/pMaokWJ3BztZ3FOsdgZNZrW7eJ9Z6fRBfTyv2sF/jZVTR+yF9r2Rb9uT0PkOPUdqTLu3c/k4urfzyh/109XYtrozyIhKLXjj8SDkEO6K9uJXUhwNEZ1OKdgiqO3xcX/qN+6Koyimar9Dj4/A78Yg4RayOwtdbmtobBks18+RJRxGrY7NSBghf/yTg/2Gr9CY/8IU3+rFgQjeg35E3PT5U3QdTq+x2TNw+/CS9KvmxcYo/9cVeL60jS8=
*/