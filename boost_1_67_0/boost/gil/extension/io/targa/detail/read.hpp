//
// Copyright 2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READ_HPP

#include <boost/gil/extension/io/targa/tags.hpp>
#include <boost/gil/extension/io/targa/detail/reader_backend.hpp>
#include <boost/gil/extension/io/targa/detail/is_allowed.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// Targa Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , targa_tag
            , ConversionPolicy
            >
    : public reader_base< targa_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , targa_tag
                           >
{
private:

    using this_t = reader<Device, targa_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, targa_tag>;

    reader( const Device&                           io_dev
          , const image_read_settings< targa_tag >& settings
          )
    : reader_base< targa_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                         io_dev
          , const cc_t&                           cc
          , const image_read_settings< targa_tag >& settings
          )
    : reader_base< targa_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template< typename View >
    void apply( const View& dst_view )
    {
        using is_read_and_convert_t = typename std::is_same
            <
                ConversionPolicy,
                detail::read_and_no_convert
            >::type;

        io_error_if( !detail::is_allowed< View >( this->_info, is_read_and_convert_t() )
                   , "Image types aren't compatible."
                   );

        switch( this->_info._image_type )
        {
            case targa_image_type::_rgb:
            {
                if( this->_info._color_map_type != targa_color_map_type::_rgb )
                {
                    io_error( "Inconsistent color map type and image type in targa file." );
                }

                if( this->_info._color_map_length != 0 )
                {
                    io_error( "Non-indexed targa files containing a palette are not supported." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        if( this->_info._screen_origin_bit )
                        {
                            read_data< bgr8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_data< bgr8_view_t >( dst_view );
                        }

                        break;
                    }
                    case 32:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        if( this->_info._screen_origin_bit )
                        {
                            read_data< bgra8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_data< bgra8_view_t >( dst_view );
                        }

                        break;
                    }
                    default:
                    {
                        io_error( "Unsupported bit depth in targa file." );
                        break;
                    }
                }

                break;
            }
            case targa_image_type::_rle_rgb:
            {
                if( this->_info._color_map_type != targa_color_map_type::_rgb )
                {
                    io_error( "Inconsistent color map type and image type in targa file." );
                }

                if( this->_info._color_map_length != 0 )
                {
                    io_error( "Non-indexed targa files containing a palette are not supported." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    {
                        if( this->_info._screen_origin_bit )
                        {
                            read_rle_data< bgr8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_rle_data< bgr8_view_t >( dst_view );
                        }
                        break;
                    }
                    case 32:
                    {
                        if( this->_info._screen_origin_bit )
                        {
                            read_rle_data< bgra8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_rle_data< bgra8_view_t >( dst_view );
                        }
                        break;
                    }
                    default:
                    {
                        io_error( "Unsupported bit depth in targa file." );
                        break;
                    }
                }

                break;
            }
            default:
            {
                io_error( "Unsupported image type in targa file." );
                break;
            }
        }
    }

private:

    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src, typename View_Dst >
    void read_data( const View_Dst& view )
    {
        byte_vector_t row( this->_info._width * (this->_info._bits_per_pixel / 8) );

        // jump to first scanline
        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

        View_Src v = interleaved_view( this->_info._width,
                                       1,
                                       reinterpret_cast<typename View_Src::value_type*>( &row.front() ),
                                       this->_info._width * num_channels< View_Src >::value
                                     );

        typename View_Src::x_iterator beg = v.row_begin( 0 ) + this->_settings._top_left.x;
        typename View_Src::x_iterator end = beg + this->_settings._dim.x;

        // read bottom up since targa origin is bottom left
        for( std::ptrdiff_t y = this->_settings._dim.y - 1; y > -1; --y )
        {
            // @todo: For now we're reading the whole scanline which is
            // slightly inefficient. Later versions should try to read
            // only the bytes which are necessary.
            this->_io_dev.read( &row.front(), row.size() );
            this->_cc_policy.read( beg, end, view.row_begin(y) );
        }
    }

    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src, typename View_Dst >
    void read_rle_data( const View_Dst& view )
    {
        targa_depth::type bytes_per_pixel = this->_info._bits_per_pixel / 8;
        size_t image_size = this->_info._width * this->_info._height * bytes_per_pixel;
        byte_vector_t image_data( image_size );

        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

        for( size_t pixel = 0; pixel < image_size; )
        {
            targa_offset::type current_byte = this->_io_dev.read_uint8();

            if( current_byte & 0x80 ) // run length chunk (high bit = 1)
            {
                uint8_t chunk_length = current_byte - 127;
                uint8_t pixel_data[4];
                for( size_t channel = 0; channel < bytes_per_pixel; ++channel )
                {
                    pixel_data[channel] = this->_io_dev.read_uint8();
                }

                // Repeat the next pixel chunk_length times
                for( uint8_t i = 0; i < chunk_length; ++i, pixel += bytes_per_pixel )
                {
                    memcpy( &image_data[pixel], pixel_data, bytes_per_pixel );
                }
            }
            else // raw chunk
            {
                uint8_t chunk_length = current_byte + 1;

                // Write the next chunk_length pixels directly
                size_t pixels_written = chunk_length * bytes_per_pixel;
                this->_io_dev.read( &image_data[pixel], pixels_written );
                pixel += pixels_written;
            }
        }

        View_Src v = flipped_up_down_view( interleaved_view( this->_info._width,
                                                             this->_info._height,
                                                             reinterpret_cast<typename View_Src::value_type*>( &image_data.front() ),
                                                             this->_info._width * num_channels< View_Src >::value ) );

        for( std::ptrdiff_t y = 0; y != this->_settings._dim.y; ++y )
        {
            typename View_Src::x_iterator beg = v.row_begin( y ) + this->_settings._top_left.x;
            typename View_Src::x_iterator end = beg + this->_settings._dim.x;
            this->_cc_policy.read( beg, end, view.row_begin(y) );
        }
    }
};

namespace detail {

class targa_type_format_checker
{
public:

    targa_type_format_checker( const targa_depth::type& bpp )
    : _bpp( bpp )
    {}

    template< typename Image >
    bool apply()
    {
        if( _bpp < 32 )
        {
            return pixels_are_compatible< typename Image::value_type, rgb8_pixel_t >::value
                   ? true
                   : false;
        }
        else
        {
            return pixels_are_compatible< typename Image::value_type, rgba8_pixel_t >::value
                   ? true
                   : false;
        }
    }

private:

    // to avoid C4512
    targa_type_format_checker& operator=( const targa_type_format_checker& ) { return *this; }

private:

    const targa_depth::type _bpp;
};

struct targa_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , targa_tag
                                           >
    {};
};

} // namespace detail

///
/// Targa Dynamic Image Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , targa_tag
                          >
    : public reader< Device
                   , targa_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, targa_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                           io_dev
                        , const image_read_settings< targa_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename Images >
    void apply( any_image< Images >& images )
    {
        detail::targa_type_format_checker format_checker( this->_info._bits_per_pixel );

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

            detail::dynamic_io_fnobj< detail::targa_read_is_supported
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