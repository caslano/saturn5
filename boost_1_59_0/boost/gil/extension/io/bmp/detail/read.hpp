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

    template< typename ...Images >
    void apply( any_image< Images... >& images )
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