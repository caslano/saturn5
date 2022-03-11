//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_READ_HPP

#include <boost/gil/extension/io/png/tags.hpp>
#include <boost/gil/extension/io/png/detail/reader_backend.hpp>
#include <boost/gil/extension/io/png/detail/is_allowed.hpp>

#include <boost/gil.hpp> // FIXME: Include what you use!
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/error.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <type_traits>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNG Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , png_tag
            , ConversionPolicy
            >
    : public reader_base< png_tag
                        , ConversionPolicy >
    , public reader_backend< Device
                           , png_tag
                           >
{
private:

    using this_t = reader<Device, png_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, png_tag>;

public:

    reader( const Device&                         io_dev
          , const image_read_settings< png_tag >& settings
          )
    : reader_base< png_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                                          io_dev
          , const typename ConversionPolicy::color_converter_type& cc
          , const image_read_settings< png_tag >&                  settings
          )
    : reader_base< png_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template< typename View >
    void apply( const View& view )
    {
        // guard from errors in the following functions
        if (setjmp( png_jmpbuf( this->get_struct() )))
        {
            io_error("png is invalid");
        }

        // The info structures are filled at this point.

        // Now it's time for some transformations.

        if( little_endian() )
        {
            if( this->_info._bit_depth == 16 )
            {
                // Swap bytes of 16 bit files to least significant byte first.
                png_set_swap( this->get_struct() );
            }

            if( this->_info._bit_depth < 8 )
            {
                // swap bits of 1, 2, 4 bit packed pixel formats
                png_set_packswap( this->get_struct() );
            }
        }

        if( this->_info._color_type == PNG_COLOR_TYPE_PALETTE )
        {
            png_set_palette_to_rgb( this->get_struct() );
        }

        if( png_get_valid( this->get_struct(), this->get_info(), PNG_INFO_tRNS ) )
        {
            png_set_tRNS_to_alpha( this->get_struct() );
        }

        // Tell libpng to handle the gamma conversion for you.  The final call
        // is a good guess for PC generated images, but it should be configurable
        // by the user at run time by the user.  It is strongly suggested that
        // your application support gamma correction.
        if( this->_settings._apply_screen_gamma )
        {
            // png_set_gamma will change the image data!

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        png_set_gamma( this->get_struct()
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#else
        png_set_gamma( this->get_struct()
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        }

        // Turn on interlace handling.  REQUIRED if you are not using
        // png_read_image().  To see how to handle interlacing passes,
        // see the png_read_row() method below:
        this->_number_passes = png_set_interlace_handling( this->get_struct() );


        // The above transformation might have changed the bit_depth and color type.
        png_read_update_info( this->get_struct()
                            , this->get_info()
                            );

        this->_info._bit_depth = png_get_bit_depth( this->get_struct()
                                                  , this->get_info()
                                                  );

        this->_info._num_channels = png_get_channels( this->get_struct()
                                                    , this->get_info()
                                                    );

        this->_info._color_type = png_get_color_type( this->get_struct()
                                                    , this->get_info()
                                                    );

        this->_scanline_length = png_get_rowbytes( this->get_struct()
                                                 , this->get_info()
                                                 );

        switch( this->_info._color_type )
        {
            case PNG_COLOR_TYPE_GRAY:
            {
                switch( this->_info._bit_depth )
                {
                    case  1: read_rows< gray1_image_t::view_t::reference >( view ); break;
                    case  2: read_rows< gray2_image_t::view_t::reference >( view ); break;
                    case  4: read_rows< gray4_image_t::view_t::reference >( view ); break;
                    case  8: read_rows< gray8_pixel_t  >( view ); break;
                    case 16: read_rows< gray16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            case PNG_COLOR_TYPE_GA:
            {
                #ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
                switch( this->_info._bit_depth )
                {
                    case  8: read_rows< gray_alpha8_pixel_t > ( view ); break;
                    case 16: read_rows< gray_alpha16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }
                #else
                    io_error( "gray_alpha isn't enabled. Define BOOST_GIL_IO_ENABLE_GRAY_ALPHA when building application." );
                #endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA


                break;
            }
            case PNG_COLOR_TYPE_RGB:
            {
                switch( this->_info._bit_depth )
                {
                    case 8:  read_rows< rgb8_pixel_t > ( view ); break;
                    case 16: read_rows< rgb16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            case PNG_COLOR_TYPE_RGBA:
            {
                switch( this->_info._bit_depth )
                {
                    case  8: read_rows< rgba8_pixel_t > ( view ); break;
                    case 16: read_rows< rgba16_pixel_t >( view ); break;
                    default: io_error( "png_reader_color_convert::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            default: io_error( "png_reader_color_convert::read_data(): unknown color type" );
        }

        // read rest of file, and get additional chunks in info_ptr
        png_read_end( this->get_struct()
                    , nullptr
                    );
    }

private:

    template< typename ImagePixel
            , typename View
            >
    void read_rows( const View& view )
    {
        // guard from errors in the following functions
        if (setjmp( png_jmpbuf( this->get_struct() )))
        {
            io_error("png is invalid");
        }

        using row_buffer_helper_t = detail::row_buffer_helper_view<ImagePixel>;

        using it_t = typename row_buffer_helper_t::iterator_t;

        using is_read_and_convert_t = typename std::is_same
            <
                ConversionPolicy,
                detail::read_and_no_convert
            >::type;

        io_error_if( !detail::is_allowed< View >( this->_info
                                                , is_read_and_convert_t()
                                                )
                   , "Image types aren't compatible."
                   );

        std::size_t rowbytes = png_get_rowbytes( this->get_struct()
                                               , this->get_info()
                                               );

        row_buffer_helper_t buffer( rowbytes
                                  , true
                                  );

        png_bytep row_ptr = (png_bytep)( &( buffer.data()[0]));

        for( std::size_t pass = 0; pass < this->_number_passes; pass++ )
        {
            if( pass == this->_number_passes - 1 )
            {
                // skip lines if necessary
                for( std::ptrdiff_t y = 0; y < this->_settings._top_left.y; ++y )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }

                for( std::ptrdiff_t y = 0
                   ; y < this->_settings._dim.y
                   ; ++y
                   )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );

                    it_t first = buffer.begin() + this->_settings._top_left.x;
                    it_t last  = first + this->_settings._dim.x; // one after last element

                    this->_cc_policy.read( first
                                         , last
                                         , view.row_begin( y ));
                }

                // Read the rest of the image. libpng needs that.
                std::ptrdiff_t remaining_rows = static_cast< std::ptrdiff_t >( this->_info._height )
                                              - this->_settings._top_left.y
                                              - this->_settings._dim.y;
                for( std::ptrdiff_t y = 0
                   ; y < remaining_rows
                   ; ++y
                   )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }
            }
            else
            {
                for( int y = 0; y < view.height(); ++y )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }
            }
        }
    }
};

namespace detail {

struct png_type_format_checker
{
    png_type_format_checker( png_bitdepth::type   bit_depth
                           , png_color_type::type color_type
                           )
    : _bit_depth ( bit_depth  )
    , _color_type( color_type )
    {}

    template< typename Image >
    bool apply()
    {
        using is_supported_t = is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                png_tag
            >;

        return is_supported_t::_bit_depth  == _bit_depth
            && is_supported_t::_color_type == _color_type;
    }

private:

    png_bitdepth::type   _bit_depth;
    png_color_type::type _color_type;
};

struct png_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , png_tag
                                           >
    {};
};

} // namespace detail


///
/// PNG Dynamic Image Reader
///
template< typename Device
        >
class dynamic_image_reader< Device
                          , png_tag
                          >
    : public reader< Device
                   , png_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader
        <
            Device,
            png_tag,
            detail::read_and_no_convert
        >;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< png_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename Images >
    void apply( any_image< Images >& images )
    {
        detail::png_type_format_checker format_checker( this->_info._bit_depth
                                                      , this->_info._color_type
                                                      );

        if( !construct_matched( images
                              , format_checker
                              ))
        {
            io_error( "No matching image type between those of the given any_image and that of the file" );
        }
        else
        {
            this->init_image( images
                            , this->_settings
                            );

            detail::dynamic_io_fnobj< detail::png_read_is_supported
                                    , parent_t
                                    > op( this );

            apply_operation( view( images )
                           , op
                           );
        }
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* read.hpp
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
*/