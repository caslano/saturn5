//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/bmp/detail/is_allowed.hpp>
#include <boost/gil/extension/io/bmp/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <functional>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

///
/// BMP Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , bmp_tag
                     >
    : public reader_backend< Device
                           , bmp_tag
                           >
{
public:

    using tag_t = bmp_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

public:

    //
    // Constructor
    //
    scanline_reader( Device&                               device
                   , const image_read_settings< bmp_tag >& settings
                   )
    : backend_t( device
                    , settings
                    )

    , _pitch( 0 )
    {
        initialize();
    }

    /// Read part of image defined by View and return the data.
    void read( byte_t* dst, int pos )
    {
        // jump to scanline
        long offset = 0;

        if( this->_info._height > 0 )
        {
            // the image is upside down
            offset = this->_info._offset
                   + ( this->_info._height - 1 - pos ) * this->_pitch;
        }
        else
        {
            offset = this->_info._offset
                   + pos * _pitch;
        }

        this->_io_dev.seek( offset );


        // read data
        _read_function(this, dst);
    }

    /// Skip over a scanline.
    void skip( byte_t*, int )
    {
        // nothing to do.
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        if( this->_info._bits_per_pixel < 8 )
        {
            _pitch = (( this->_info._width * this->_info._bits_per_pixel ) + 7 ) >> 3;
        }
        else
        {
            _pitch = this->_info._width * (( this->_info._bits_per_pixel + 7 ) >> 3);
        }

        _pitch = (_pitch + 3) & ~3;

        //

        switch( this->_info._bits_per_pixel )
        {
            case 1:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                read_palette();
                _buffer.resize( _pitch );

                _read_function = std::mem_fn(&this_t::read_1_bit_row);

                break;
            }

            case 4:
            {
                switch( this->_info._compression )
                {
                    case bmp_compression::_rle4:
                    {
                        io_error( "Cannot read run-length encoded images in iterator mode. Try to read as whole image." );

                        break;
                    }

                    case bmp_compression::_rgb :
                    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                        read_palette();
                        _buffer.resize( _pitch );

                        _read_function = std::mem_fn(&this_t::read_4_bits_row);

                        break;
                    }

                    default:
                    {
                        io_error( "Unsupported compression mode in BMP file." );
                    }
                }

                break;
            }

            case 8:
            {
                switch( this->_info._compression )
                {
                    case bmp_compression::_rle8:
                    {
                        io_error( "Cannot read run-length encoded images in iterator mode. Try to read as whole image." );

                        break;
                    }
                    case bmp_compression::_rgb:
                    {
                        this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;

                        read_palette();
                        _buffer.resize( _pitch );

                        _read_function = std::mem_fn(&this_t::read_8_bits_row);

                        break;
                    }

                    default: { io_error( "Unsupported compression mode in BMP file." ); break; }
                }

                break;
            }

            case 15:
            case 16:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;

                _buffer.resize( _pitch );

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
                    io_error( "Unsupported BMP compression." );
                }


                _read_function = std::mem_fn(&this_t::read_15_bits_row);

                break;
            }

            case 24:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgb8_view_t >::value + 3 ) & ~3;
                _read_function = std::mem_fn(&this_t::read_row);

                break;
            }

            case 32:
            {
                this->_scanline_length = ( this->_info._width * num_channels< rgba8_view_t >::value + 3 ) & ~3;
                _read_function = std::mem_fn(&this_t::read_row);

                break;
            }

            default:
            {
                io_error( "Unsupported bits per pixel." );
            }
        }
    }

    void read_palette()
    {
        if( this->_palette.size() > 0 )
        {
            // palette has been read already.
            return;
        }

        int entries = this->_info._num_colors;

        if( entries == 0 )
        {
            entries = 1u << this->_info._bits_per_pixel;
        }

		this->_palette.resize( entries, rgba8_pixel_t(0,0,0,0) );

        for( int i = 0; i < entries; ++i )
        {
            get_color( this->_palette[i], blue_t()  ) = this->_io_dev.read_uint8();
            get_color( this->_palette[i], green_t() ) = this->_io_dev.read_uint8();
            get_color( this->_palette[i], red_t()   ) = this->_io_dev.read_uint8();

            // there are 4 entries when windows header
            // but 3 for os2 header
            if( this->_info._header_size == bmp_header_size::_win32_info_size )
            {
                this->_io_dev.read_uint8();
            }

        } // for
    }

    template< typename View >
    void read_bit_row( byte_t* dst )
    {
        using src_view_t = View;
        using dst_view_t = rgba8_image_t::view_t;

        src_view_t src_view = interleaved_view( this->_info._width
                                              , 1
                                              , (typename src_view_t::x_iterator) &_buffer.front()
                                              , this->_pitch
                                              );

        dst_view_t dst_view = interleaved_view( this->_info._width
                                              , 1
                                              , (typename dst_view_t::value_type*) dst
                                              , num_channels< dst_view_t >::value * this->_info._width
                                              );


        typename src_view_t::x_iterator src_it = src_view.row_begin( 0 );
        typename dst_view_t::x_iterator dst_it = dst_view.row_begin( 0 );

        for( dst_view_t::x_coord_t i = 0
           ; i < this->_info._width
           ; ++i, src_it++, dst_it++
           )
        {
            unsigned char c = get_color( *src_it, gray_color_t() );
            *dst_it = this->_palette[c];
        }
    }

    // Read 1 bit image. The colors are encoded by an index.
    void read_1_bit_row( byte_t* dst )
    {
        this->_io_dev.read( &_buffer.front(), _pitch );
        _mirror_bits( _buffer );

        read_bit_row< gray1_image_t::view_t >( dst );
    }

    // Read 4 bits image. The colors are encoded by an index.
    void read_4_bits_row( byte_t* dst )
    {
        this->_io_dev.read( &_buffer.front(), _pitch );
        _swap_half_bytes( _buffer );

        read_bit_row< gray4_image_t::view_t >( dst );
    }

    /// Read 8 bits image. The colors are encoded by an index.
    void read_8_bits_row( byte_t* dst )
    {
        this->_io_dev.read( &_buffer.front(), _pitch );

        read_bit_row< gray8_image_t::view_t >( dst );
    }

    /// Read 15 or 16 bits image.
    void read_15_bits_row( byte_t* dst )
    {
        using dst_view_t = rgb8_view_t;

        dst_view_t dst_view = interleaved_view( this->_info._width
                                              , 1
                                              , (typename dst_view_t::value_type*) dst
                                              , this->_pitch
                                              );

        typename dst_view_t::x_iterator dst_it = dst_view.row_begin( 0 );

        //
        byte_t* src = &_buffer.front();
        this->_io_dev.read( src, _pitch );

        for( dst_view_t::x_coord_t i = 0
           ; i < this->_info._width
           ; ++i, src += 2
           )
        {
            int p = ( src[1] << 8 ) | src[0];

            int r = ((p & this->_mask.red.mask)   >> this->_mask.red.shift)   << (8 - this->_mask.red.width);
            int g = ((p & this->_mask.green.mask) >> this->_mask.green.shift) << (8 - this->_mask.green.width);
            int b = ((p & this->_mask.blue.mask)  >> this->_mask.blue.shift)  << (8 - this->_mask.blue.width);

            get_color( dst_it[i], red_t()   ) = static_cast< byte_t >( r );
            get_color( dst_it[i], green_t() ) = static_cast< byte_t >( g );
            get_color( dst_it[i], blue_t()  ) = static_cast< byte_t >( b );
        }
    }

    void read_row( byte_t* dst )
    {
        this->_io_dev.read( dst, _pitch );
    }

private:

    // the row pitch must be multiple of 4 bytes
    int _pitch;

    std::vector<byte_t> _buffer;
    detail::mirror_bits <std::vector<byte_t>, std::true_type> _mirror_bits;
    detail::swap_half_bytes<std::vector<byte_t>, std::true_type> _swap_half_bytes;

    std::function<void(this_t*, byte_t*)> _read_function;
};

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
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
*/