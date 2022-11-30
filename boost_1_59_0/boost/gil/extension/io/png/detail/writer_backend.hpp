//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/png/tags.hpp>
#include <boost/gil/extension/io/png/detail/base.hpp>
#include <boost/gil/extension/io/png/detail/supported_types.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/typedefs.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

///
/// PNG Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , png_tag
                     >
    : public detail::png_struct_info_wrapper
{

private:

    using this_t = writer_backend<Device, png_tag>;

public:

    using format_tag_t = png_tag;

    ///
    /// Constructor
    ///
    writer_backend( const Device&                      io_dev
                  , const image_write_info< png_tag >& info
                  )
    : png_struct_info_wrapper( false )
    , _io_dev( io_dev )
    , _info( info )
    {
        // Create and initialize the png_struct with the desired error handler
        // functions.  If you want to use the default stderr and longjump method,
        // you can supply NULL for the last three parameters.  We also check that
        // the library version is compatible with the one used at compile time,
        // in case we are using dynamically linked libraries.  REQUIRED.
        get()->_struct = png_create_write_struct( PNG_LIBPNG_VER_STRING
                                                , nullptr  // user_error_ptr
                                                , nullptr  // user_error_fn
                                                , nullptr  // user_warning_fn
                                                );

        io_error_if( get_struct() == nullptr
                   , "png_writer: fail to call png_create_write_struct()"
                   );

        // Allocate/initialize the image information data.  REQUIRED
        get()->_info = png_create_info_struct( get_struct() );

        if( get_info() == nullptr )
        {
            png_destroy_write_struct( &get()->_struct
                                    , nullptr
                                    );

            io_error( "png_writer: fail to call png_create_info_struct()" );
        }

        // Set error handling.  REQUIRED if you aren't supplying your own
        // error handling functions in the png_create_write_struct() call.
        if( setjmp( png_jmpbuf( get_struct() )))
        {
            //free all of the memory associated with the png_ptr and info_ptr
            png_destroy_write_struct( &get()->_struct
                                    , &get()->_info
                                    );

            io_error( "png_writer: fail to call setjmp()" );
        }

        init_io( get_struct() );
    }

protected:

    template< typename View >
    void write_header( const View& view )
    {
        using png_rw_info_t = detail::png_write_support
            <
                typename channel_type<typename get_pixel_type<View>::type>::type,
                typename color_space_type<View>::type
            >;

        // Set the image information here.  Width and height are up to 2^31,
        // bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
        // the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
        // PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
        // or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
        // PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
        // currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
        png_set_IHDR( get_struct()
                    , get_info()
                    , static_cast< png_image_width::type  >( view.width()  )
                    , static_cast< png_image_height::type >( view.height() )
                    , static_cast< png_bitdepth::type     >( png_rw_info_t::_bit_depth )
                    , static_cast< png_color_type::type   >( png_rw_info_t::_color_type )
                    , _info._interlace_method
                    , _info._compression_type
                    , _info._filter_method
                    );

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        if( _info._valid_cie_colors )
        {
            png_set_cHRM( get_struct()
                        , get_info()
                        , _info._white_x
                        , _info._white_y
                        , _info._red_x
                        , _info._red_y
                        , _info._green_x
                        , _info._green_y
                        , _info._blue_x
                        , _info._blue_y
                        );
        }

        if( _info._valid_file_gamma )
        {
            png_set_gAMA( get_struct()
                        , get_info()
                        , _info._file_gamma
                        );
        }
#else
        if( _info._valid_cie_colors )
        {
            png_set_cHRM_fixed( get_struct()
                              , get_info()
                              , _info._white_x
                              , _info._white_y
                              , _info._red_x
                              , _info._red_y
                              , _info._green_x
                              , _info._green_y
                              , _info._blue_x
                              , _info._blue_y
                              );
        }

        if( _info._valid_file_gamma )
        {
            png_set_gAMA_fixed( get_struct()
                              , get_info()
                              , _info._file_gamma
                              );
        }
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

        if( _info._valid_icc_profile )
        {
#if PNG_LIBPNG_VER_MINOR >= 5
            png_set_iCCP( get_struct()
                        , get_info()
                        , const_cast< png_charp >( _info._icc_name.c_str() )
                        , _info._iccp_compression_type
                        , reinterpret_cast< png_const_bytep >( & (_info._profile.front ()) )
                        , _info._profile_length
                        );
#else
            png_set_iCCP( get_struct()
                        , get_info()
                        , const_cast< png_charp >( _info._icc_name.c_str() )
                        , _info._iccp_compression_type
                        , const_cast< png_charp >( & (_info._profile.front()) )
                        , _info._profile_length
                        );
#endif
        }

        if( _info._valid_intent )
        {
            png_set_sRGB( get_struct()
                        , get_info()
                        , _info._intent
                        );
        }

        if( _info._valid_palette )
        {
            png_set_PLTE( get_struct()
                        , get_info()
                        , const_cast< png_colorp >( &_info._palette.front() )
                        , _info._num_palette
                        );
        }

        if( _info._valid_background )
        {
            png_set_bKGD( get_struct()
                        , get_info()
                        , const_cast< png_color_16p >( &_info._background )
                        );
        }

        if( _info._valid_histogram )
        {
            png_set_hIST( get_struct()
                        , get_info()
                        , const_cast< png_uint_16p >( &_info._histogram.front() )
                        );
        }

        if( _info._valid_offset )
        {
            png_set_oFFs( get_struct()
                        , get_info()
                        , _info._offset_x
                        , _info._offset_y
                        , _info._off_unit_type
                        );
        }

        if( _info._valid_pixel_calibration )
        {
            std::vector< const char* > params( _info._num_params );
            for( std::size_t i = 0; i < params.size(); ++i )
            {
                params[i] = _info._params[ i ].c_str();
            }

            png_set_pCAL( get_struct()
                        , get_info()
                        , const_cast< png_charp >( _info._purpose.c_str() )
                        , _info._X0
                        , _info._X1
                        , _info._cal_type
                        , _info._num_params
                        , const_cast< png_charp  >( _info._units.c_str() )
                        , const_cast< png_charpp >( &params.front()     )
                        );
        }

        if( _info._valid_resolution )
        {
            png_set_pHYs( get_struct()
                        , get_info()
                        , _info._res_x
                        , _info._res_y
                        , _info._phy_unit_type
                        );
        }

        if( _info._valid_significant_bits )
        {
            png_set_sBIT( get_struct()
                        , get_info()
                        , const_cast< png_color_8p >( &_info._sig_bits )
                        );
        }

#ifndef BOOST_GIL_IO_PNG_1_4_OR_LOWER

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        if( _info._valid_scale_factors )
        {
            png_set_sCAL( get_struct()
                        , get_info()
                        , this->_info._scale_unit
                        , this->_info._scale_width
                        , this->_info._scale_height
                        );
        }
#else
#ifdef BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
        if( _info._valid_scale_factors )
        {
            png_set_sCAL_fixed( get_struct()
                              , get_info()
                              , this->_info._scale_unit
                              , this->_info._scale_width
                              , this->_info._scale_height
                              );
        }
#else
        if( _info._valid_scale_factors )
        {
            png_set_sCAL_s( get_struct()
                          , get_info()
                          , this->_info._scale_unit
                          , const_cast< png_charp >( this->_info._scale_width.c_str()  )
                          , const_cast< png_charp >( this->_info._scale_height.c_str() )
                          );
        }

#endif // BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_1_4_OR_LOWER

        if( _info._valid_text )
        {
            std::vector< png_text > texts( _info._num_text );
            for( std::size_t i = 0; i < texts.size(); ++i )
            {
                png_text pt;
                pt.compression = _info._text[i]._compression;
                pt.key         = const_cast< png_charp >( this->_info._text[i]._key.c_str()  );
                pt.text        = const_cast< png_charp >( this->_info._text[i]._text.c_str() );
                pt.text_length = _info._text[i]._text.length();

                texts[i] = pt;
            }

            png_set_text( get_struct()
                        , get_info()
                        , &texts.front()
                        , _info._num_text
                        );
        }

        if( _info._valid_modification_time )
        {
            png_set_tIME( get_struct()
                        , get_info()
                        , const_cast< png_timep >( &_info._mod_time )
                        );
        }

        if( _info._valid_transparency_factors )
        {
            int sample_max = ( 1u << _info._bit_depth );

            /* libpng doesn't reject a tRNS chunk with out-of-range samples */
            if( !(  (  _info._color_type == PNG_COLOR_TYPE_GRAY
                    && (int) _info._trans_values[0].gray > sample_max
                    )
                 || (  _info._color_type == PNG_COLOR_TYPE_RGB
                    &&(  (int) _info._trans_values[0].red   > sample_max
                      || (int) _info._trans_values[0].green > sample_max
                      || (int) _info._trans_values[0].blue  > sample_max
                      )
                    )
                 )
              )
            {
                //@todo Fix that once reading transparency values works
/*
                png_set_tRNS( get_struct()
                            , get_info()
                            , trans
                            , num_trans
                            , trans_values
                            );
*/
            }
        }

        // Compression Levels - valid values are [0,9]
        png_set_compression_level( get_struct()
                                 , _info._compression_level
                                 );

        png_set_compression_mem_level( get_struct()
                                     , _info._compression_mem_level
                                     );

        png_set_compression_strategy( get_struct()
                                    , _info._compression_strategy
                                    );

        png_set_compression_window_bits( get_struct()
                                       , _info._compression_window_bits
                                       );

        png_set_compression_method( get_struct()
                                  , _info._compression_method
                                  );

        png_set_compression_buffer_size( get_struct()
                                       , _info._compression_buffer_size
                                       );

#ifdef BOOST_GIL_IO_PNG_DITHERING_SUPPORTED
        // Dithering
        if( _info._set_dithering )
        {
            png_set_dither( get_struct()
                          , &_info._dithering_palette.front()
                          , _info._dithering_num_palette
                          , _info._dithering_maximum_colors
                          , &_info._dithering_histogram.front()
                          , _info._full_dither
                          );
        }
#endif // BOOST_GIL_IO_PNG_DITHERING_SUPPORTED

        // Filter
        if( _info._set_filter )
        {
            png_set_filter( get_struct()
                          , 0
                          , _info._filter
                          );
        }

        // Invert Mono
        if( _info._invert_mono )
        {
            png_set_invert_mono( get_struct() );
        }

        // True Bits
        if( _info._set_true_bits )
        {
            png_set_sBIT( get_struct()
                        , get_info()
                        , &_info._true_bits.front()
                        );
        }

        // sRGB Intent
        if( _info._set_srgb_intent )
        {
            png_set_sRGB( get_struct()
                        , get_info()
                        , _info._srgb_intent
                        );
        }

        // Strip Alpha
        if( _info._strip_alpha )
        {
            png_set_strip_alpha( get_struct() );
        }

        // Swap Alpha
        if( _info._swap_alpha )
        {
            png_set_swap_alpha( get_struct() );
        }


        png_write_info( get_struct()
                      , get_info()
                      );
    }

protected:

    static void write_data( png_structp png_ptr
                          , png_bytep   data
                          , png_size_t  length
                          )
    {
        static_cast< Device* >( png_get_io_ptr( png_ptr ))->write( data
                                                                 , length );
    }

    static void flush( png_structp png_ptr )
    {
        static_cast< Device* >(png_get_io_ptr(png_ptr) )->flush();
    }

private:

    void init_io( png_structp png_ptr )
    {
        png_set_write_fn( png_ptr
                        , static_cast< void* >        ( &this->_io_dev      )
                        , static_cast< png_rw_ptr >   ( &this_t::write_data )
                        , static_cast< png_flush_ptr >( &this_t::flush      )
                        );
    }

public:

    Device _io_dev;

    image_write_info< png_tag > _info;
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