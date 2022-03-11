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