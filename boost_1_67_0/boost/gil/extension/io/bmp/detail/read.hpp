//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_READ_HPP

#include <boost/gil/extension/io/bmp/detail/is_allowed.hpp>
#include <boost/gil/extension/io/bmp/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <boost/assert.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// BMP Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , bmp_tag
            , ConversionPolicy
            >
    : public reader_base< bmp_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , bmp_tag
                           >
{
private:

    using this_t = reader<Device, bmp_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend< Device, bmp_tag>;

public:

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const image_read_settings< bmp_tag >& settings
          )
    : backend_t( io_dev
               , settings
               )
    , _pitch( 0 )
    {}

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const ConversionPolicy&               cc
          , const image_read_settings< bmp_tag >& settings
          )
    : reader_base< bmp_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    , _pitch( 0 )
    {}


    /// Read image.
    template< typename View >
    void apply( const View& dst_view )
    {
        if( this->_info._valid == false )
        {
            io_error( "Image header was not read." );
        }

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

        // the row pitch must be multiple 4 bytes
        if( this->_info._bits_per_pixel < 8 )
        {
            _pitch = static_cast<long>((( this->_info._width * this->_info._bits_per_pixel ) + 7 ) >> 3 );
        }
        else
        {
            _pitch = static_cast<long>( this->_info._width * (( this->_info._bits_per_pixel + 7 ) >> 3 ));
        }

        _pitch = (_pitch + 3) & ~3;

        switch( this->_info._bits_per_pixel )
        {
            case 1:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                read_palette_image
                    <
                        gray1_image_t::view_t,
                        detail::mirror_bits<byte_vector_t, std::true_type>
                    >(dst_view);
                break;
            }

            case 4:
            {
                switch ( this->_info._compression )
                {
                    case bmp_compression::_rle4:
                    {
                        ///@todo How can we determine that?
                        this->_scanline_length = 0;

                        read_palette_image_rle( dst_view );

                        break;
                    }

                    case bmp_compression::_rgb:
                    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                        read_palette_image
                            <
                                gray4_image_t::view_t,
                                detail::swap_half_bytes<byte_vector_t, std::true_type>
                            >(dst_view);
                        break;
                    }

                    default:
                    {
                        io_error( "Unsupported compression mode in BMP file." );
                        break;
                    }
                }
                break;
            }

            case 8:
            {
                switch ( this->_info._compression )
                {
                    case bmp_compression::_rle8:
                    {
                        ///@todo How can we determine that?
                        this->_scanline_length = 0;

                        read_palette_image_rle( dst_view );
                        break;
                    }

                    case bmp_compression::_rgb:
                    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                        read_palette_image< gray8_image_t::view_t
                                          , detail::do_nothing< std::vector< gray8_pixel_t > >
                                          > ( dst_view );
                        break;
                    }

                    default:
                    {
                        io_error( "Unsupported compression mode in BMP file." );
                        break;
                    }
                }

                break;
            }

            case 15: case 16:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;

                read_data_15( dst_view );

                break;
            }

            case 24:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;

                read_data< bgr8_view_t  >( dst_view );

                break;
            }

            case 32:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                read_data< bgra8_view_t >( dst_view );

                break;
            }
        }
    }

private:

    long get_offset( std::ptrdiff_t pos )
    {
        if( this->_info._height > 0 )
        {
            // the image is upside down
            return static_cast<long>( ( this->_info._offset
                                      + ( this->_info._height - 1 - pos ) * _pitch
                                    ));
        }
        else
        {
            return static_cast<long>( ( this->_info._offset
                                      + pos * _pitch
                                    ));
        }
    }

    template< typename View_Src
            , typename Byte_Manipulator
            , typename View_Dst
            >
    void read_palette_image( const View_Dst& view )
    {
        this->read_palette();

        using rh_t = detail::row_buffer_helper_view<View_Src>;
        using it_t = typename rh_t::iterator_t;

        rh_t rh( _pitch, true );

        // we have to swap bits
        Byte_Manipulator byte_manipulator;

        for( std::ptrdiff_t y = 0
           ; y < this->_settings._dim.y
           ; ++y
           )
        {
            this->_io_dev.seek( get_offset( y + this->_settings._top_left.y ));

            this->_io_dev.read( reinterpret_cast< byte_t* >( rh.data() )
                        , _pitch
                        );

            byte_manipulator( rh.buffer() );

            typename View_Dst::x_iterator dst_it = view.row_begin( y );

            it_t it  = rh.begin() + this->_settings._top_left.x;
            it_t end = it + this->_settings._dim.x;

            for( ; it != end; ++it, ++dst_it )
            {
                unsigned char c = get_color( *it, gray_color_t() );
                *dst_it = this->_palette[ c ];
            }
        }
    }

    template< typename View >
    void read_data_15( const View& view )
    {
        byte_vector_t row( _pitch );

        // read the color masks
        if( this->_info._compression == bmp_compression::_bitfield )
        {
            this->_mask.red.mask    = this->_io_dev.read_uint32();
            this->_mask.green.mask  = this->_io_dev.read_uint32();
            this->_mask.blue.mask   = this->_io_dev.read_uint32();

            this->_mask.red.width   = detail::count_ones( this->_mask.red.mask   );
            this->_mask.green.width = detail::count_ones( this->_mask.green.mask );
            this->_mask.blue.width  = detail::count_ones( this->_mask.blue.mask  );

            this->_mask.red.shift   = detail::trailing_zeros( this->_mask.red.mask   );
            this->_mask.green.shift = detail::trailing_zeros( this->_mask.green.mask );
            this->_mask.blue.shift  = detail::trailing_zeros( this->_mask.blue.mask  );
        }
        else if( this->_info._compression == bmp_compression::_rgb )
        {
            switch( this->_info._bits_per_pixel )
            {
                case 15:
                case 16:
                {
                    this->_mask.red.mask   = 0x007C00; this->_mask.red.width   = 5; this->_mask.red.shift   = 10;
                    this->_mask.green.mask = 0x0003E0; this->_mask.green.width = 5; this->_mask.green.shift =  5;
                    this->_mask.blue.mask  = 0x00001F; this->_mask.blue.width  = 5; this->_mask.blue.shift  =  0;

                    break;
                }

                case 24:
                case 32:
                {
                    this->_mask.red.mask   = 0xFF0000; this->_mask.red.width   = 8; this->_mask.red.shift   = 16;
                    this->_mask.green.mask = 0x00FF00; this->_mask.green.width = 8; this->_mask.green.shift =  8;
                    this->_mask.blue.mask  = 0x0000FF; this->_mask.blue.width  = 8; this->_mask.blue.shift  =  0;

                    break;
                }
            }
        }
        else
        {
            io_error( "bmp_reader::apply(): unsupported BMP compression" );
        }

        using image_t = rgb8_image_t;
        using it_t = typename image_t::view_t::x_iterator;

        for( std::ptrdiff_t y = 0
           ; y < this->_settings._dim.y
           ; ++y
           )
        {
            this->_io_dev.seek( get_offset( y + this->_settings._top_left.y ));

            this->_io_dev.read( &row.front()
                        , row.size()
                        );

            image_t img_row( this->_info._width, 1 );
            image_t::view_t v = gil::view( img_row );
            it_t it = v.row_begin( 0 );

            it_t beg = v.row_begin( 0 ) + this->_settings._top_left.x;
            it_t end = beg + this->_settings._dim.x;

            byte_t* src = &row.front();
            for( int32_t i = 0 ; i < this->_info._width; ++i, src += 2 )
            {
                int p = ( src[1] << 8 ) | src[0];

                int r = ((p & this->_mask.red.mask)   >> this->_mask.red.shift)   << (8 - this->_mask.red.width);
                int g = ((p & this->_mask.green.mask) >> this->_mask.green.shift) << (8 - this->_mask.green.width);
                int b = ((p & this->_mask.blue.mask)  >> this->_mask.blue.shift)  << (8 - this->_mask.blue.width);

                get_color( it[i], red_t()   ) = static_cast< byte_t >( r );
                get_color( it[i], green_t() ) = static_cast< byte_t >( g );
                get_color( it[i], blue_t()  ) = static_cast< byte_t >( b );
            }

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }
    }


    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src
            , typename View_Dst
            >
    void read_data( const View_Dst& view )
    {
        byte_vector_t row( _pitch );

        View_Src v = interleaved_view( this->_info._width
                                     , 1
                                     , (typename View_Src::value_type*) &row.front()
                                     , this->_info._width * num_channels< View_Src >::value
                                     );

        typename View_Src::x_iterator beg = v.row_begin( 0 ) + this->_settings._top_left.x;
        typename View_Src::x_iterator end = beg + this->_settings._dim.x;

        for( std::ptrdiff_t y = 0
           ; y < this->_settings._dim.y
           ; ++y
           )
        {
            this->_io_dev.seek( get_offset( y + this->_settings._top_left.y ));

            this->_io_dev.read( &row.front()
                        , row.size()
                        );

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }
    }

    template< typename Buffer
            , typename View
            >
    void copy_row_if_needed( const Buffer&  buf
                           , const View&    view
                           , std::ptrdiff_t y
                           )
    {
        if(  y >= this->_settings._top_left.y
          && y <  this->_settings._dim.y
          )
        {
            typename Buffer::const_iterator beg = buf.begin() + this->_settings._top_left.x;
            typename Buffer::const_iterator end = beg + this->_settings._dim.x;

            std::copy( beg
                     , end
                     , view.row_begin( y )
                     );
        }
    }

    template< typename View_Dst >
    void read_palette_image_rle( const View_Dst& view )
    {
        BOOST_ASSERT(
            this->_info._compression == bmp_compression::_rle4 ||
            this->_info._compression == bmp_compression::_rle8);

        this->read_palette();

        // jump to start of rle4 data
        this->_io_dev.seek( this->_info._offset );

        // we need to know the stream position for padding purposes
        std::size_t stream_pos = this->_info._offset;

        using Buf_type = std::vector<rgba8_pixel_t>;
        Buf_type buf( this->_settings._dim.x );
        Buf_type::iterator dst_it  = buf.begin();
        Buf_type::iterator dst_end = buf.end();

        // If height is positive, the bitmap is a bottom-up DIB.
        // If height is negative, the bitmap is a top-down DIB.
        // The origin of a bottom-up DIB is the bottom left corner of the bitmap image,
        // which is the first pixel of the first row of bitmap data.
        // The origin of a top-down DIB is also the bottom left corner of the bitmap image,
        // but in this case the bottom left corner is the first pixel of the last row of bitmap data.
        // - "Programming Windows", 5th Ed. by Charles Petzold explains Windows docs ambiguities.
        std::ptrdiff_t ybeg = 0;
        std::ptrdiff_t yend = this->_settings._dim.y;
        std::ptrdiff_t yinc = 1;
        if( this->_info._height > 0 )
        {
            ybeg = this->_settings._dim.y - 1;
            yend = -1;
            yinc = -1;
        }

        std::ptrdiff_t y = ybeg;
        bool finished = false;

        while ( !finished )
        {
            std::ptrdiff_t count  = this->_io_dev.read_uint8();
            std::ptrdiff_t second = this->_io_dev.read_uint8();
            stream_pos += 2;

            if ( count )
            {
                // encoded mode

                // clamp to boundary
                if( count > dst_end - dst_it )
                {
                    count = dst_end - dst_it;
                }

                if( this->_info._compression == bmp_compression::_rle4 )
                {
                    std::ptrdiff_t cs[2] = { second >> 4, second & 0x0f };

                    for( int i = 0; i < count; ++i )
                    {
                        *dst_it++ = this->_palette[ cs[i & 1] ];
                    }
                }
                else
                {
                    for( int i = 0; i < count; ++i )
                    {
                        *dst_it++ = this->_palette[ second ];
                    }
                }
            }
            else
            {
                switch( second )
                {
                    case 0:  // end of row
                    {
                        copy_row_if_needed( buf, view, y );

                        y += yinc;
                        if( y == yend )
                        {
                            finished = true;
                        }
                        else
                        {
                            dst_it = buf.begin();
                            dst_end = buf.end();
                        }

                        break;
                    }

                    case 1:  // end of bitmap
                    {
                        copy_row_if_needed( buf, view, y );
                        finished = true;

                        break;
                    }

                    case 2:  // offset coordinates
                    {
                        std::ptrdiff_t dx = this->_io_dev.read_uint8();
                        std::ptrdiff_t dy = this->_io_dev.read_uint8() * yinc;
                        stream_pos += 2;

                        if( dy )
                        {
                            copy_row_if_needed( buf, view, y );
                        }

                        std::ptrdiff_t x = dst_it - buf.begin();
                        x += dx;

                        if( x > this->_info._width )
                        {
                            io_error( "Mangled BMP file." );
                        }

                        y += dy;
                        if( yinc > 0 ? y > yend : y < yend )
                        {
                            io_error( "Mangled BMP file." );
                        }

                        dst_it = buf.begin() + x;
                        dst_end = buf.end();

                        break;
                    }

                    default:  // absolute mode
                    {
                        count = second;

                        // clamp to boundary
                        if( count > dst_end - dst_it )
                        {
                            count = dst_end - dst_it;
                        }

                        if ( this->_info._compression == bmp_compression::_rle4 )
                        {
                            for( int i = 0; i < count; ++i )
                            {
                                uint8_t packed_indices = this->_io_dev.read_uint8();
                                ++stream_pos;

                                *dst_it++ = this->_palette[ packed_indices >> 4 ];
                                if( ++i == second )
                                    break;

                                *dst_it++ = this->_palette[ packed_indices & 0x0f ];
                            }
                        }
                        else
                        {
                            for( int i = 0; i < count; ++i )
                            {
                                uint8_t c = this->_io_dev.read_uint8();
                                ++stream_pos;
                                *dst_it++ = this->_palette[ c ];
                             }
                        }

                        // pad to word boundary
                        if( ( stream_pos - get_offset( 0 )) & 1 )
                        {
                            this->_io_dev.seek( 1, SEEK_CUR );
                            ++stream_pos;
                        }

                        break;
                    }
                }
            }
        }
    }

private:

    std::size_t _pitch;
};

namespace detail {

class bmp_type_format_checker
{
public:

    bmp_type_format_checker( const bmp_bits_per_pixel::type& bpp )
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
    bmp_type_format_checker& operator=( const bmp_type_format_checker& ) { return *this; }

private:

    const bmp_bits_per_pixel::type _bpp;
};

struct bmp_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , bmp_tag
                                           >
    {};
};

} // namespace detail

///
/// BMP Dynamic Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , bmp_tag
                          >
    : public reader< Device
                   , bmp_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, bmp_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< bmp_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename Images >
    void apply( any_image< Images >& images )
    {
        detail::bmp_type_format_checker format_checker( this->_info._bits_per_pixel );

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

            detail::dynamic_io_fnobj< detail::bmp_read_is_supported
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

} // gil
} // boost

#endif

/* read.hpp
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
*/