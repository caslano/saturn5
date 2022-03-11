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
B3KEWFEydgeHO8qMFKBSEIQBfDIXbCeWYDsH+O+6kKQcILaDVwAU96FqHkubHKHICb7c2kNspI6HuxDJjiKedyFCAfXdyuRmwPCwNSpvRUxr/ASXvx5DL5A+78CMbRQK+Qke20KcgZe/f9KjC2Y3GhuiU7vyXvvWQ0WQZMGkzQkOBTudvi6Uwa1AobBy6/nudAA3t4Au22QvP3UxcbUQLcMPLl7U2z4nnfy9bj2NNp+dmqTNV38g1n0nQMp1DoUCtZLggjQdY152gPa0+UVSbvbysZ8ZTPj7QBHC5hIBXrTuNX6ORKACCPZuSZByHiToViQI9rbeizre5grKGsb/duHiEMG4jh4bfUEePowXZNfD03J6aoGn8TdcSNDnTGxwxXMSfvsBr7U4j9Q7BrkxfOXn8bYKt3eHYtYArjB8b4W7sFMZA7KLro7BYBfvTvpIkaDMFfF7MUcJ4Np7d/Lzp5JUeeT7yWCM2bD6Dp9wJCuDxK4UJHknMwUEQYa2IHMwM9MnmJAas+I9zLs7fZMA5zinXGOg0zWZqP7VmlVH2Aw8dl8v2uR2IBWKlD4nKcLYfwAX2CDAvR8BAfbutZc/hiuMGDsC7wE4EJqQrlVxT2ZK0xaHcNgZcR45yE++C3sS5MGa8++eOwSU4R3kR/vWkqOXb/2GBI6p9PIkvawROY/RS0jkPEgv08XLcnqZIV7839Dm2kgK4HBftEDxoQd4JSiObY9ijNpGEtYXMDpIjM7g8VADcHbzUqSz20n2n0DB05PTgqefOt1D5xuosSugMSAbH7ThsVc+qb6bztRcgG3UNgpSkNwNRXKH3qmJJ3Tj5DB/sAEQiE5MQ7fVGxPKEY/BAKI0LMSe/6E3nDSJqPgmotx/8Q1dhmccMaJz1j4DLlE6b41vK8X0zcqE5NQf6oQRbETY+zBAgD+M0eJ/kxKgsJf9lnih1ejmatENsAMvJCY+8LWcnC+s0U/z70y4Uwz7y3B68y3HK5nwwRK3GQeueFcPIIrXqu4TgTjSussvCde5/pSALLCrVw7jxFIjndyh63G6heT33ahFaQQzYwXXUJEq9NmIRfuBIM0rDYXNWLiT/yD7CctagnovqmyRN0WYyPdIhe5nbTK058QRWtAqJiSOQOFtYbDmv43nGriVTf0H2vBiPgWFnw0JN7QgbTmT+ytRxmfNYvfX4YUmhyLLLRJeCVktZb8LCdUm+iNugoCReG2RdgdsnI5oaQdabJaVRLpfUkZGur+vzHqiG290USY+0T0UozhG42kwqNFF10r04ZEOb4dWaKPQIHzHTyzEv6JEfKQCUNiGmdZ4Y/JEbOKiqJ814A0pGDEC4hpZdeO5oQ5bNmjjDaQj2gT1QZnO+HRR4sSEbrTC720wHGdDjO95ocYTN2M+tTSnIUnY5onWQgLwk9M/KYeOt9DCx+j62PaTPakPZYkqqL8c4pmRFlP6mYy7LjnZ7WrCI75a6QGteK9WHHMvsSo2FPeEHS0OAg4wFFZgAXUAqSKGNMbw5Je6N3mOACSz7/oWkIPiuegULcZvxofSFz/8iY/6eHoVC7MDhI7h9esBa3SO1XOazcWwyvUD8w77zYd8Af00W3TAc1KxslutGG1t1oormdzJhrLGvOJKz/G1Q/MO5cmVgIqiaPl7WBTvbY9bUCXBk0ILLP0L+8JSsnAGu8MiRtDBArZortVzsnRQ3mHoWhRKxJKNrUuPJcQbNRbijRo57+IWujztRo2FbMHCfjdq8C2jHHyhuf+NGnc0d/+HGzVuuvRGjYXpN2o0vo1CjeP/uFTjOjPJmv//rgrBkzx0kgk3Gx7pUX9zyZEewhj2fvk58lmPQTvyymXo2OQr3yX8GxzdiFS/DSMdSHDB+5KSWXehRwTvAA5tW0RZs5JZ27AWhmKEeBFljU1mPYdZeNyepEnIkpJZqGm34WWRwVCthfJa6zFPXRGqOZCN7w3ifVGo4Z+Uf5TeFWt0YzbuzyVv4n6kL82JjIJAkB+ER7YBY8pwj6oz08jWD5xoeDjO0Z4Qz2Wrndz6ON47SBTR06FmVc+jC3SNbxV9150Fgn4Bp1hjwVA1jldLvUSHienm9D/jSt7MVlndxQ5lKAys7Uy34TZ5LLTjLE1CrxMkSF3u5+PPdtPh3xP8R2qv/p2n2Sko18vpMqzG19Ah0ZHn7WKZ/vDI8P3h+4vo6r5O4VuZgZwZrWDHvu4G7gItczu0CyMrR7d48tj5wFrcETaJ31bTnTysmN3/vBd+T+28OKnvnpvzz9EOdaC71GZEsmxEPMDgLKTWabfUYxmHvWx7soyfjUOhKRgMD+4XdIpfshIX2rcmWhDRxxRwuhkTU19YyKcT2UFe/nW33r9EIipV5K/AfGowSEF/2Il4pzi/YDAZ55c8kqS/LSAhmNPtFrr4qYg/0Jhw353r1fU0VLgtHRVAuz6q+1mxE+DlCNKt+DlIJyqBHkzwnFduTcO9T8cB7gl/3k/68KpXZZJx1Vq1Msa9xqqMdK+xKA62gW74ldFchZcwpkfwQot2ci4kbFDxUe7SGnvZ48JgKPwOSKwDJGBrpTXAGPhf3xHcCGrnC9aywySOk9F3V2pYJih0WmmtVopfHdBKG/ut0xa8ZVHAHIRld2muvewKir+pVG7ET2VUK5MLlTGFir3QXn4Whlxtxm8KxEfBXyf8HQp/8zEqBf466AuobXVk8M5meOe8jc29i1xJ1rwq+pRcC6vJO4FBOd5WcZLBfMKneTvpy0RDY9hkuTxJsWjm+F7RAN0DDyq/1VxlHH2gsoNi2B2UVRuMjrytqV64Jnckyqd1AJU2iEovMDzLZhNDMup1JBuHgeRTOXv5w/RlsySnebkGsWkSgWcwgCfCLW1NGNb+f8zXLMOUYTT/L5O2l2chS6FWzFXigzYwk/7THpqYtr38/YuJ0nlVRryuzPE43wFz1f8F4g1G/eepfmteVdtZfEoqO9n0sTzbUbzs1Bq5SmKZwcQlubpvJewFzQxkQME7dtRcdgL0spmxEjwnRozPF3Id07Lcg9UstijXPUjJ9BxSMuMFnkPqGFGjSBTH9owK8SlFdMmpruYUGbm0jYxz//yHfeQUGDA+axmIa/lAt3MxxGs+Wmt2nrfSPbJNoCLOw09cIuMjjwt9S5OOdK8H0NEBp3L0DIJwHl5Pfi3WgQRQuQ+vJRwc6tXDpmB4fBjtvt52vOW7aWWvHsDM7Xsw9qCDX9+QoBm/e0WEGIwCigMZlyUz/nQeY0KFfamdb32wF+PdLoehsbkY8oCxDzQWdRBacr724xur4q/CNFIk6P7+vl1WbAPy4wxqXsDDHBT35FwgQsUHNO8OICD0mcniw926NruoWt6N+KGV7tFKK7SbhL83PAzEHwDGA+jtl8ngXEmGVnmPD03XIPdmE6j38nMXdIpevAJ1zZvsZaMHJG5gPc6nHuvR/XizoJCRZx9L+ZLIESJE4/HHyBI7FOiOp075IaoWFBQKCXgeZMsW4yXGTEEhJrPG801jm843AaVTpjNvTaKKR96pWD0fw6qReTWZXi7HVEwve4yc70Cy9qgZ7tIK5cfMexQkq5vsz1ZqJmRdS6gvrLdJiOezYeZ+fuwsXRCZB23CECcxE7vcGOQIdhxGZsTtFx/wQE+pD7weFY1aqFGoKCdngJ+IoZZfPSvA14Qs9SZlIt0xieJItRE9AIPxC10Li4krMEGazPzO7326L7eX/UJKLcBu0cowNsu4MGqSiGVd9Z33tqTIvetcQsbA+c5PLol3d/kh1Qqs//3RDmU6HsoOBkDY2ItmNjQVJVzdfN0bGRIr3SGugtoVz0B77uwkSdx+BElirnFl5BBrjx55QJEiD6yRQDQ9ktTPIuumSOrQsJW33NWjVxdM6csC0BQ46fOniv2JBdPQ4zdZ19frWoETgJ76ck83b8kzPnOLX6m8d3UPXrU+GK8KhNeFq/GE2rKStlVX9+jhxbG2fw9z8HNngSycgc27jeftRTsxxWICT9xGts0ycuEl3p4zJSzC23gRlOaeTqt0hA2jY+oCGcQ0jONGWD51bqjUil9eUBz87Xm0PBj939fWLe4SxztqNsDfSI1+OBuDEnZQhErifP5wUBi0Agt9fmUT3k2KXxHcdBs+DEXfPj2ickf3IxuSfuRRi6SMZrdY2DBtCxWAx9uhcCEN9BYLBW+n5RVZtS2YF/mBRUpeOsi3ZPfQveqWwZXxMSj0itMsdP7Kih7uB3imZKjHYVssjNR21tdWigfNTmo5/FcvdCcV2xsi6xRJuQ7AznkOOq+BKS5QkHmYoDRdBAt6kc8G+ayDz0BuJy7r3wftHnZgfCx98Jiuf0yIbOdkm5UATIJbODt5pQtkWDB+08rXVsASC+s+ro3xOWLjNhiY6q4R6Njvwy+eLIl0WZSFeIHbU1ONG5duRTdzloJxvMadrheXqRPxBuMaJddXlPyQMqjtgYA4pIIfGo8PwtM1x3nDw2im7ltakhQyhcmQuGjVgW6Kz525mz5V7OOVI7DX0P3vEl04daQncfHoFPoKqzM+hAJ+jC+gfI4vUOvnWKsLWvwnO9LvI6swuR9/CrxnkfX8B2Pfew20EGniu+Z3yw/TYSRfEAOJQ7oRMn0Tge4AnibeJI3W9Se6UQ185Cq6zHVQpMWeIX0B8xqSgZmHuCXD8YUwyy1qBV3DOC7X/w6yDN76erceloo4fgUJ5YtIDHFeStFNWpfhxiXyRRy/gtTfsAIFk61iiRiJU3g1vJM5XMeeWGcp+kSSyKIPNbaZUpfYXdK8ca9rEV8t+hhD1Uut6dV3iA6TxcVFJhOYlf0CPYsB17GDOkDllgfcP728RM1yF2YrA/DuVkcKo4Af5+ARJvGFu2D5MXTZ2BDFrYkg7j5+LV640BEI9eWMcPAhh4U5Sc3ij66E1erQX6kVB6WkBDaxCKaALLXKBri54SE8f4qnpD67EohdByiaWaBg4ckgUdowWKadmQpLIVML8Ir7zGm3HiWvUKUjT9lSbAOa6ULZFkmK/RY3tOXfuKG1V1t7hUuLognXvtWNJ5z2I/1Qh7CnkXbwnVAiHoftXH5MfPwnwMOtmULx53e+g/6MKIcy/MnjXXi9NTzi/CiOIxpt701Ec5th/+O1eNFyTPOFbw5VvjfCESrUASvLsYHQNB21Kcf7XXrkaE7c+R0lsqnEV41YIpu9wemixrAU5C/s78Z7wMlPZa/u0g0A+SyxLZuzHEeYmKe4mLJiIlD65V8hpSfG9eG2bmBcTqk6c+VJ2JzAumKOH41O3dIq0vlHUCxxpco3my6xvyAZ9eWcf+/cYZM6An1NAD6JOQjzcolr0OdabvsvvGax3SqFJ/FHNhmnsTowFKEPaE4G/y80Gb34JQwtxqHPIzFLQ8K6miK8utanJz9XEeD/wnOjhvrZ8SXoLO95Diu2e+Af0vJBP76g43fqurt7k1cL8/Vr+pJTuTptKjDC9xE5CtutiQ/K3Ns4Am9s04es+RA/2dan5rHNk4ZK+G0jBxvmg3VGUqI/Q9832DxF5GSFJf6KH7+bd6+J7giVuA26NOAfa8uU+BvQBd4Y24f9NcaN/viPzgDr0UU9kMRF//y6n/bp1RsxbRLAA1iqtnH2ULq0lX5n0G8h/d6Gvwcn0e8U+p1Gv/n0O2cofmJntsk4r1jFZ7Vb0zgjmuwScBn+5LdMbEEUA87wf5zDMboPTsddYmXb8Z6neCbbjh9NYBuxU9D717upY3Uy2+TIwv0dMv0L9os0yQLycpcC8vKZN8hxuBGLsc3466mzl+G3RqLz6M7qSGWG+wmOJvN1Gv2NrfoAZt9rUjJi+f/EbwNR1WFBn35PtvECQgrGJMTvEiAEqe9W96NOZa6+DwHGbz2LV5tAEzBuAhuMm4BonAc6QKQoUr0wqO9bi6YHYsj9LWbT+38lOxjdjj2BQvWx+Fqf+3GnvawFwWsGtm7CEwPocrkXAw75LDw2ihHFl8i9+FkOcSkA6KVyMwq0coP4zt9aQoXkTaVCnq0nm9nOl4BabsbzVOGFxsfYjCPMs1qAkpmDlIyhrA1B0NfIhsY20vkrb6O2CWfLShtZcUPQH92MmMMLSahRJ2nbBSIhUuHn2tLobZK0JuXgX8WsUvJWuf4GRT9dzRcIXnKJA3tf3HBK164+/Mj/ee2q4HhGlJ79m0wp2e/l2G8aYfkFt0qhu3AaY8u+TVueBmWaF7Qhbcn9IEFViooCAqmv/DSTDhRnDa5sG4nOowzc8MEAL8MzGF2sjlQLa7VlEkUOjHqdRN5BwKjWOil4EqRWfygT0JQ7m4EnhDa1If97HS+ARiynbXFEGRuZi+2a7OUPCs9cDf/53ZLUtsyU+HptOOMCYX8INos0ee6twNnEl1Rw2aIHiTAAaClk1GkW6tRyspJBot8fNvn9ofxb6fTtlulGfj4J004/7UGYysYKZGwvftWLsQCClvCrOnp1/CJCBsvHb1Xkz/CHbr5VlMYNwhWjtNzH+/59SVHoW1AhMSz8DCqiPozEQh3yG0RlfsvP+nQxRElkXG5kTIEMXe0SVPxqrut+vx+vArjtvgu6e9xtwI7U2e5xK6tQX2Mbu2xI6qxDEJv76NlGz3gkVtvooGcLPWcPobOGt/TRtWkhE67Phg9wfWr/C2jQg68JGjSp/+qow9ED6CfSjhwM4bwUpcBjaR4zB+oDxJA2gziAFyP3Gt9RiimIX6A6XDUbsLL3UyTu6NteDFCnM5AgPb70crce4FedRdyBHQIysGkJ5LEu3nWUQiTa+Q1HgI9TJZafS2rcoCCpprz3SDdp2/i9aV4jynfwLChPoTWkplijMpICELzrUVqwxccK+370LqteREdO5A4f/wNlOiLEMSQllxEokp+iSGNu8VGYIvOwIWmlztLhJ8j4bw5iwFc7Pj4Nj/xDmDV+B8LWRFsNucvZwXjXNJoAQNSY0SREjWoTPrXdbpUSH8nLNE4RNuojW/AEDbEr2Gvrg+Gc6ME5JPEF+f/C3gdmgwWt+F0iIPBoitGLJqGhRrzpIzvxZtaXZgvHR3wOHn1EYuJC7Az6RSl+9JVu3aivbSRv8MjYseEgQQOInz2kbVyInRxaRp+iQBfbQWpPuT8xUuhwMdTfQP2LJisq0FqPoxMJzAojm5Y+KkbNGmND9cGnj9x7DEe7kMI4BJyWlRxJELe9/wLihjo0v2n9t4nbb/A7Kj9uReI2pWlEuuyG4OVfZErJy//c6791Hd5dl3yQ2xwUfl3XObx+UVNj7gqkO2qWceVVWiRQWwZi8N6wKQai2810zpmLSzdqfcD0JeCIIdQrMFrcuLcldTML/9SGKmRt9BXEcuOQw1S6n2Wq3EEtolm3IU9uNHk7TXIXtQds4I1T3ToNzouXdBq18eAHsNZdQuy8J4TXukUwi258acmL3EvPHchiI8vpGc3MeZH76bnLdQ4DeczoPkAlIxSNIAx8iQuG+l/go9CdMweQjQX4Da0YTbWX9mbRC8Ylscd5Bjzih5zbfYFAP0jwLwen3QcSfNmauuKaHaJPZDg+HOHQCi3iSkd8+Q72mrgll3o709+zRqddFlhQHqIz/AssPloYGODvuUlyF3Ogowss/OZT5MPLl5Tx+DoKXieb4HUupqlD/OFu4ScXdwq1m7KY3GGab2Fyp2m+lcldpvm25DyerkibB9ks9IcsgqmZentSnqakNxfnhRj5x7XfwshLrlIPsm52N81GaMGqzS/m2IaWRMgKcPUfsAZ3WybjwPGqdJOIM5gs7aBTg+fYfIs/aWD8jlul5lsol2Swuy0EqY2/69HPf1SiOCOlXFLwesVCzRyfgFEBd1oLPTWlA9ghbZ417kAv/Z22ZIoNLRrKYGjGz03QRnw4m2c53+hj5vN4LaEApuGu/P7fhAM/hB/xid2DDMPVAqTtff1hS9S7gZ8GHILarnNRb0WRplZo6l7Yj4CLKDSqfcaA50HZlqLkrUia2p5yO95pIdf+mm241VqZt0WEMsBQzr9fRNfqnSabOHT2zbNQ5k4Ln9oAaCAA+Rz/0T408S/H80QU8+XjH+zAPb8NT0WRCIm91xcldzXs85QlV31OWU1BfvI2fZUluYHoq8O1lYhUjXlyJcM9XgPj8dGtvKc19blqeeu0mSMc+E4R+iPXVtKHlLbyn+wQ22orjXnCNjz/uhWVLKMK3/ckwHwyfmjbW49gl7dBy9C7PrIG2kDWtg1r8t8mIJKARQt0zVtXojiK8BRLQMRkNmZipcsARPwQFNFeXYWncF9V6HcN/WK0KagP9FU5ygZB1rFrlxBtoTG1hUgUNrlLv2cGgDqJpqlNh5eEavIOTd6p4f2HeygG/Tj/F4owaRUSeH3+I349DAeaZ46A8UG7Hend3IbW3w38y+d7jEM6G/gpQEp+90dCA/0Z4lzgw4QG6vkZXcpKYb4nqjNvQ0K0Ee8n47b1kFPFzR8ZHhvihaiXScaHpjc7iKXZ4Pds9UbMIS3TZHATkG0+f9r4FuIfd8ODrtwu6rgLJ6k3eV4mhTIbL4LRXybOXgdURJh9aASeiv+Ht6+Pb6q6/0+btA0QSIACVVGrgqDViRaULKBlmIJKMSXQ4LAtOsSaqWNbLsLWFOptK9dLquIT2xzTKZvb1LGhUIaW1jJaBiJT1DKY4EQ9NXUWZdDSyv193p9zb5KCfp/++PF6kd57zrnn4XOePs+fibLEKErfcJlVYs1qbpZ7Ul4m6QEeVPXBBBnvOEToRj0aYIPSFL3KetSZmmDhG1kBeVPH+B4PiMGX9hqxusv4Oe3SXoua/4LgJT4/aJHRaudok6L4AQeVX55B5Hp8PLg00t5pjxj69x4jbG8AFhWAwBu2qkRRsdMmE8NkPCgBNkQtIBx53FuZJoJdw9CeIDueIWZXgQycaL1eR6/l4HnUVFtRmNJKjadftfjvelpJKPYIqo79CdfjnBIzABkCKkQcuIMJ1y1I9RCWHcRVg8Aee29JqnNV0KFZMhWT/KPvTkUMhPuCUr0QzE04gfF1RUYFQoFAiTFiPgJq098XdjJ/d2w44xbGUely2Qj4xjZmSxTgy/XGiA2ykMXqLCtfkES8ZUeOitIlJgW2JyQO0HP82wmIDAuJ62SuU6bFDybAQ3kXJfKQFm/qx94tTkFB6fLpj4O6a1azAkYKHnrVS/97PPQGaEE=
*/