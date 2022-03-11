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