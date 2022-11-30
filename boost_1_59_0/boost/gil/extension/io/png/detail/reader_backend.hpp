//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_DETAIL_READER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_DETAIL_READER_BACKEND_HPP

#include <boost/gil/extension/io/png/tags.hpp>
#include <boost/gil/extension/io/png/detail/base.hpp>
#include <boost/gil/extension/io/png/detail/supported_types.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

///
/// PNG Backend
///
template<typename Device >
struct reader_backend< Device
                     , png_tag
                     >
    : public detail::png_struct_info_wrapper
{
public:

    using format_tag_t = png_tag;
    using this_t = reader_backend<Device, png_tag>;

public:

    reader_backend( const Device&                         io_dev
                  , const image_read_settings< png_tag >& settings
                  )
    : _io_dev( io_dev )

    , _settings( settings )
    , _info()
    , _scanline_length( 0 )

    , _number_passes( 0 )
    {
        read_header();

        if( _settings._dim.x == 0 )
        {
            _settings._dim.x = _info._width;
        }

        if( _settings._dim.y == 0 )
        {
            _settings._dim.y = _info._height;
        }
    }

    void read_header()
    {
        using boost::gil::detail::PNG_BYTES_TO_CHECK;

        // check the file's first few bytes
        byte_t buf[PNG_BYTES_TO_CHECK];

        io_error_if( _io_dev.read( buf
                                , PNG_BYTES_TO_CHECK
                                ) != PNG_BYTES_TO_CHECK
                   , "png_check_validity: failed to read image"
                   );

        io_error_if( png_sig_cmp( png_bytep(buf)
                                , png_size_t(0)
                                , PNG_BYTES_TO_CHECK
                                ) != 0
                   , "png_check_validity: invalid png image"
                   );

        // Create and initialize the png_struct with the desired error handler
        // functions.  If you want to use the default stderr and longjump method,
        // you can supply NULL for the last three parameters.  We also supply the
        // the compiler header file version, so that we know if the application
        // was compiled with a compatible version of the library.  REQUIRED
        get()->_struct = png_create_read_struct( PNG_LIBPNG_VER_STRING
                                             , nullptr  // user_error_ptr
                                             , nullptr  // user_error_fn
                                             , nullptr  // user_warning_fn
                                             );

        io_error_if( get()->_struct == nullptr
                   , "png_reader: fail to call png_create_write_struct()"
                   );

        png_uint_32 user_chunk_data[4];
        user_chunk_data[0] = 0;
        user_chunk_data[1] = 0;
        user_chunk_data[2] = 0;
        user_chunk_data[3] = 0;
        png_set_read_user_chunk_fn( get_struct()
                                  , user_chunk_data
                                  , this_t::read_user_chunk_callback
                                  );

        // Allocate/initialize the memory for image information.  REQUIRED.
        get()->_info = png_create_info_struct( get_struct() );

        if( get_info() == nullptr )
        {
            png_destroy_read_struct( &get()->_struct
                                   , nullptr
                                   , nullptr
                                   );

            io_error( "png_reader: fail to call png_create_info_struct()" );
        }

        // Set error handling if you are using the setjmp/longjmp method (this is
        // the normal method of doing things with libpng).  REQUIRED unless you
        // set up your own error handlers in the png_create_read_struct() earlier.
        if( setjmp( png_jmpbuf( get_struct() )))
        {
            //free all of the memory associated with the png_ptr and info_ptr
            png_destroy_read_struct( &get()->_struct
                                   , &get()->_info
                                   , nullptr
                                   );

            io_error( "png is invalid" );
        }

        png_set_read_fn( get_struct()
                       , static_cast< png_voidp >( &this->_io_dev )
                       , this_t::read_data
                       );

        // Set up a callback function that will be
        // called after each row has been read, which you can use to control
        // a progress meter or the like.
        png_set_read_status_fn( get_struct()
                              , this_t::read_row_callback
                              );

        // Set up a callback which implements user defined transformation.
        // @todo
        png_set_read_user_transform_fn( get_struct()
                                      , png_user_transform_ptr( nullptr )
                                      );

        png_set_keep_unknown_chunks( get_struct()
                                   , PNG_HANDLE_CHUNK_ALWAYS
                                   , nullptr
                                   , 0
                                   );


        // Make sure we read the signature.
        // @todo make it an option
        png_set_sig_bytes( get_struct()
                         , PNG_BYTES_TO_CHECK
                         );

        // The call to png_read_info() gives us all of the information from the
        // PNG file before the first IDAT (image data chunk).  REQUIRED
        png_read_info( get_struct()
                     , get_info()
                     );

        ///
        /// Start reading the image information
        ///

        // get PNG_IHDR chunk information from png_info structure
        png_get_IHDR( get_struct()
                    , get_info()
                    , &this->_info._width
                    , &this->_info._height
                    , &this->_info._bit_depth
                    , &this->_info._color_type
                    , &this->_info._interlace_method
                    , &this->_info._compression_method
                    , &this->_info._filter_method
                    );

        // get number of color channels in image
        this->_info._num_channels = png_get_channels( get_struct()
                                              , get_info()
                                              );

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

        // Get CIE chromacities and referenced white point
        if( this->_settings._read_cie_chromacities )
        {
            this->_info._valid_cie_colors = png_get_cHRM( get_struct()
                                                        , get_info()
                                                        , &this->_info._white_x, &this->_info._white_y
                                                        ,   &this->_info._red_x,   &this->_info._red_y
                                                        , &this->_info._green_x, &this->_info._green_y
                                                        ,  &this->_info._blue_x,  &this->_info._blue_y
                                                        );
        }

        // get the gamma value
        if( this->_settings._read_file_gamma )
        {
            this->_info._valid_file_gamma = png_get_gAMA( get_struct()
                                                        , get_info()
                                                        , &this->_info._file_gamma
                                                        );

            if( this->_info._valid_file_gamma == false )
            {
                this->_info._file_gamma = 1.0;
            }
        }
#else

        // Get CIE chromacities and referenced white point
        if( this->_settings._read_cie_chromacities )
        {
            this->_info._valid_cie_colors = png_get_cHRM_fixed( get_struct()
                                                              , get_info()
                                                              , &this->_info._white_x, &this->_info._white_y
                                                              ,   &this->_info._red_x,   &this->_info._red_y
                                                              , &this->_info._green_x, &this->_info._green_y
                                                              ,  &this->_info._blue_x,  &this->_info._blue_y
                                                              );
        }

        // get the gamma value
        if( this->_settings._read_file_gamma )
        {
            this->_info._valid_file_gamma = png_get_gAMA_fixed( get_struct()
                                                              , get_info()
                                                              , &this->_info._file_gamma
                                                              );

            if( this->_info._valid_file_gamma == false )
            {
                this->_info._file_gamma = 1;
            }
        }
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

        // get the embedded ICC profile data
        if( this->_settings._read_icc_profile )
        {
#if PNG_LIBPNG_VER_MINOR >= 5
            png_charp icc_name = png_charp( nullptr );
            png_bytep profile  = png_bytep( nullptr );

            this->_info._valid_icc_profile = png_get_iCCP( get_struct()
                                                         , get_info()
                                                         , &icc_name
                                                         , &this->_info._iccp_compression_type
                                                         , &profile
                                                         , &this->_info._profile_length
                                                         );
#else
            png_charp icc_name = png_charp( NULL );
            png_charp profile  = png_charp( NULL );

            this->_info._valid_icc_profile = png_get_iCCP( get_struct()
                                                         , get_info()
                                                         , &icc_name
                                                         , &this->_info._iccp_compression_type
                                                         , &profile
                                                         , &this->_info._profile_length
                                                         );
#endif
            if( icc_name )
            {
                this->_info._icc_name.append( icc_name
                                            , std::strlen( icc_name )
                                            );
            }

            if( this->_info._profile_length != 0 )
            {
                std:: copy_n (profile, this->_info._profile_length, std:: back_inserter (this->_info._profile));
            }
        }

        // get the rendering intent
        if( this->_settings._read_intent )
        {
            this->_info._valid_intent = png_get_sRGB( get_struct()
                                                    , get_info()
                                                    , &this->_info._intent
                                                    );
        }

        // get image palette information from png_info structure
        if( this->_settings._read_palette )
        {
            png_colorp palette = png_colorp( nullptr );

            this->_info._valid_palette = png_get_PLTE( get_struct()
                                                     , get_info()
                                                     , &palette
                                                     , &this->_info._num_palette
                                                     );

            if( this->_info._num_palette > 0 )
            {
                this->_info._palette.resize( this->_info._num_palette );
                std::copy( palette
                         , palette + this->_info._num_palette
                         , &this->_info._palette.front()
                         );
            }
        }

        // get background color
        if( this->_settings._read_background )
        {
            png_color_16p background = png_color_16p( nullptr );

            this->_info._valid_background = png_get_bKGD( get_struct()
                                                        , get_info()
                                                        , &background
                                                        );
            if( background )
            {
                this->_info._background = *background;
            }
        }

        // get the histogram
        if( this->_settings._read_histogram )
        {
            png_uint_16p histogram = png_uint_16p( nullptr );

            this->_info._valid_histogram = png_get_hIST( get_struct()
                                                       , get_info()
                                                       , &histogram
                                                       );

            if( histogram )
            {
                // the number of values is set by the number of colors inside
                // the palette.
                if( this->_settings._read_palette == false )
                {
                    png_colorp palette = png_colorp( nullptr );
                    png_get_PLTE( get_struct()
                                , get_info()
                                , &palette
                                , &this->_info._num_palette
                                );
                }

                std::copy( histogram
                         , histogram + this->_info._num_palette
                         , &this->_info._histogram.front()
                         );
            }
        }

        // get screen offsets for the given image
        if( this->_settings._read_screen_offsets )
        {
            this->_info._valid_offset = png_get_oFFs( get_struct()
                                                    , get_info()
                                                    , &this->_info._offset_x
                                                    , &this->_info._offset_y
                                                    , &this->_info._off_unit_type
                                                    );
        }


        // get pixel calibration settings
        if( this->_settings._read_pixel_calibration )
        {
            png_charp purpose = png_charp ( nullptr );
            png_charp units   = png_charp ( nullptr );
            png_charpp params = png_charpp( nullptr );

            this->_info._valid_pixel_calibration = png_get_pCAL( get_struct()
                                                               , get_info()
                                                               , &purpose
                                                               , &this->_info._X0
                                                               , &this->_info._X1
                                                               , &this->_info._cal_type
                                                               , &this->_info._num_params
                                                               , &units
                                                               , &params
                                                               );
            if( purpose )
            {
                this->_info._purpose.append( purpose
                                           , std::strlen( purpose )
                                           );
            }

            if( units )
            {
                this->_info._units.append( units
                                         , std::strlen( units )
                                         );
            }

            if( this->_info._num_params > 0 )
            {
                this->_info._params.resize( this->_info._num_params );

                for( png_CAL_nparam::type i = 0
                   ; i < this->_info._num_params
                   ; ++i
                   )
                {
                    this->_info._params[i].append( params[i]
                                                 , std::strlen( params[i] )
                                                 );
                }
            }
        }

        // get the physical resolution
        if( this->_settings._read_physical_resolution )
        {
            this->_info._valid_resolution = png_get_pHYs( get_struct()
                                                        , get_info()
                                                        , &this->_info._res_x
                                                        , &this->_info._res_y
                                                        , &this->_info._phy_unit_type
                                                        );
        }

        // get the image resolution in pixels per meter.
        if( this->_settings._read_pixels_per_meter )
        {
            this->_info._pixels_per_meter = png_get_pixels_per_meter( get_struct()
                                                                    , get_info()
                                                                    );
        }


        // get number of significant bits for each color channel
        if( this->_settings._read_number_of_significant_bits )
        {
            png_color_8p sig_bits = png_color_8p( nullptr );

            this->_info._valid_significant_bits = png_get_sBIT( get_struct()
                                                              , get_info()
                                                              , &sig_bits
                                                              );

            // @todo Is there one or more colors?
            if( sig_bits )
            {
                this->_info._sig_bits = *sig_bits;
            }
        }

#ifndef BOOST_GIL_IO_PNG_1_4_OR_LOWER

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

        // get physical scale settings
        if( this->_settings._read_scale_factors )
        {
            this->_info._valid_scale_factors = png_get_sCAL( get_struct()
                                                           , get_info()
                                                           , &this->_info._scale_unit
                                                           , &this->_info._scale_width
                                                           , &this->_info._scale_height
                                                           );
        }
#else
#ifdef BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
        if( this->_settings._read_scale_factors )
        {
            this->_info._valid_scale_factors = png_get_sCAL_fixed( get_struct()
                                                                 , get_info()
                                                                 , &this->_info._scale_unit
                                                                 , &this->_info._scale_width
                                                                 , &this->_info._scale_height
                                                                 );
        }
#else
        if( this->_settings._read_scale_factors )
        {
            png_charp scale_width  = nullptr;
            png_charp scale_height = nullptr;

            this->_info._valid_scale_factors = png_get_sCAL_s(
                get_struct(), get_info(), &this->_info._scale_unit, &scale_width, &scale_height);

            if (this->_info._valid_scale_factors)
            {
                if( scale_width )
                {
                    this->_info._scale_width.append( scale_width
                                                   , std::strlen( scale_width )
                                                   );
                }

                if( scale_height )
                {
                    this->_info._scale_height.append( scale_height
                                                    , std::strlen( scale_height )
                                                    );
                }
            }
        }
#endif // BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_1_4_OR_LOWER

        // get comments information from png_info structure
        if( this->_settings._read_comments )
        {
            png_textp text = png_textp( nullptr );

            this->_info._valid_text = png_get_text( get_struct()
                                                  , get_info()
                                                  , &text
                                                  , &this->_info._num_text
                                                  );

            if( this->_info._num_text > 0 )
            {
                this->_info._text.resize( this->_info._num_text );

                for( png_num_text::type i = 0
                   ; i < this->_info._num_text
                   ; ++i
                   )
                {
                    this->_info._text[i]._compression = text[i].compression;
                    this->_info._text[i]._key.append( text[i].key
                                                    , std::strlen( text[i].key )
                                                    );

                    this->_info._text[i]._text.append( text[i].text
                                                     , std::strlen( text[i].text )
                                                     );
                }
            }
        }

        // get last modification time
        if( this->_settings._read_last_modification_time )
        {
            png_timep mod_time = png_timep( nullptr );
            this->_info._valid_modification_time = png_get_tIME( get_struct()
                                                               , get_info()
                                                               , &mod_time
                                                               );
            if( mod_time )
            {
                this->_info._mod_time = *mod_time;
            }
        }

        // get transparency data
        if( this->_settings._read_transparency_data )
        {
            png_bytep     trans        = png_bytep    ( nullptr );
            png_color_16p trans_values = png_color_16p( nullptr );

            this->_info._valid_transparency_factors = png_get_tRNS( get_struct()
                                                                  , get_info()
                                                                  , &trans
                                                                  , &this->_info._num_trans
                                                                  , &trans_values
                                                                  );

            if( trans )
            {
                //@todo What to do, here? How do I know the length of the "trans" array?
            }

            if( this->_info._num_trans )
            {
                this->_info._trans_values.resize( this->_info._num_trans );
                std::copy( trans_values
                         , trans_values + this->_info._num_trans
                         , &this->_info._trans_values.front()
                         );
            }
        }

        // @todo One day!
/*
        if( false )
        {
            png_unknown_chunkp unknowns = png_unknown_chunkp( NULL );
            int num_unknowns = static_cast< int >( png_get_unknown_chunks( get_struct()
                                                                         , get_info()
                                                                         , &unknowns
                                                                         )
                                                 );
        }
*/
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
            if( img_dim.x < _info._width ) { io_error( "Supplied image is too small" ); }
        }


        if( _settings._dim.y > 0 )
        {
            if( img_dim.y < _settings._dim.y ) { io_error( "Supplied image is too small" ); }
        }
        else
        {
            if( img_dim.y < _info._height ) { io_error( "Supplied image is too small" ); }
        }
    }

protected:

    static void read_data( png_structp png_ptr
                         , png_bytep   data
                         , png_size_t length
                         )
    {
        static_cast<Device*>(png_get_io_ptr(png_ptr) )->read( data
                                                            , length );
    }

    static void flush( png_structp png_ptr )
    {
        static_cast<Device*>(png_get_io_ptr(png_ptr) )->flush();
    }


    static int read_user_chunk_callback( png_struct*        /* png_ptr */
                                       , png_unknown_chunkp /* chunk */
                                       )
    {
        // @todo
        return 0;
    }

    static void read_row_callback( png_structp /* png_ptr    */
                                 , png_uint_32 /* row_number */
                                 , int         /* pass       */
                                 )
    {
        // @todo
    }

public:

    Device _io_dev;

    image_read_settings< png_tag > _settings;
    image_read_info    < png_tag > _info;

    std::size_t _scanline_length;

    std::size_t _number_passes;
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