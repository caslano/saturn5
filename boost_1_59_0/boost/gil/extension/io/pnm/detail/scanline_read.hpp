//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/pnm/detail/is_allowed.hpp>
#include <boost/gil/extension/io/pnm/detail/reader_backend.hpp>

#include <boost/gil.hpp> // FIXME: Include what you use!
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
/// PNM Reader
///
template< typename Device >
class scanline_reader< Device
                     , pnm_tag
                     >
    : public reader_backend< Device
                           , pnm_tag
                           >
{
public:

    using tag_t = pnm_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

public:
    scanline_reader( Device&                                device
                   , const image_read_settings< pnm_tag >& settings
                   )
    : backend_t( device
               , settings
               )
    {
        initialize();
    }

    /// Read part of image defined by View and return the data.
    void read( byte_t* dst
             , int
             )
    {
        _read_function( this, dst );
    }

    /// Skip over a scanline.
    void skip( byte_t*, int )
    {
        _skip_function( this );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        switch( this->_info._type )
        {
            // reading mono text is reading grayscale but with only two values
            case pnm_image_type::mono_asc_t::value:
            case pnm_image_type::gray_asc_t::value:
            {
                this->_scanline_length = this->_info._width;

                _read_function = std::mem_fn(&this_t::read_text_row);
                _skip_function = std::mem_fn(&this_t::skip_text_row);

                break;
            }

            case pnm_image_type::color_asc_t::value:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                _read_function = std::mem_fn(&this_t::read_text_row);
                _skip_function = std::mem_fn(&this_t::skip_text_row);

                break;
            }


            case pnm_image_type::mono_bin_t::value:
            {
                //gray1_image_t
                this->_scanline_length = ( this->_info._width + 7 ) >> 3;

                _read_function = std::mem_fn(&this_t::read_binary_bit_row);
                _skip_function = std::mem_fn(&this_t::skip_binary_row);

                break;
            }

            case pnm_image_type::gray_bin_t::value:
            {
                // gray8_image_t
                this->_scanline_length = this->_info._width;

                _read_function = std::mem_fn(&this_t::read_binary_byte_row);
                _skip_function = std::mem_fn(&this_t::skip_binary_row);

                break;
            }

            case pnm_image_type::color_bin_t::value:
            {
                // rgb8_image_t
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                _read_function = std::mem_fn(&this_t::read_binary_byte_row);
                _skip_function = std::mem_fn(&this_t::skip_binary_row);

                break;
            }

            default: { io_error( "Unsupported pnm file." ); break; }
        }
    }

    void read_text_row( byte_t* dst )
    {
        for( std::size_t x = 0; x < this->_scanline_length; ++x )
        {
            for( uint32_t k = 0; ; )
            {
                int ch = this->_io_dev.getc_unchecked();

                if( isdigit( ch ))
                {
                    _text_buffer[ k++ ] = static_cast< char >( ch );
                }
                else if( k )
                {
                    _text_buffer[ k ] = 0;
                    break;
                }
                else if( ch == EOF || !isspace( ch ))
                {
                    return;
                }
            }

            int value = atoi( _text_buffer );

            if( this->_info._max_value == 1 )
            {
                // for pnm format 0 is white
                dst[x] = ( value != 0 )
                            ? 0
                            : 255;
            }
            else
            {
                dst[x] = static_cast< byte_t >( value );
            }
        }
    }

    void skip_text_row()
    {
        for( std::size_t x = 0; x < this->_scanline_length; ++x )
        {
            for( uint32_t k = 0; ; )
            {
                int ch = this->_io_dev.getc_unchecked();

                if( isdigit( ch ))
                {
                    k++;
                }
                else if( k )
                {
                    break;
                }
                else if( ch == EOF || !isspace( ch ))
                {
                    return;
                }
            }
        }
    }


    void read_binary_bit_row( byte_t* dst )
    {
        this->_io_dev.read( dst
                    , this->_scanline_length
                    );

        _negate_bits    ( dst, this->_scanline_length );
        _swap_half_bytes( dst, this->_scanline_length );

    }

    void read_binary_byte_row( byte_t* dst )
    {
        this->_io_dev.read( dst
                    , this->_scanline_length
                    );
    }

    void skip_binary_row()
    {
        this->_io_dev.seek( static_cast<long>( this->_scanline_length ), SEEK_CUR );
    }

private:

    char _text_buffer[16];

    // For bit_aligned images we need to negate all bytes in the row_buffer
    // to make sure that 0 is black and 255 is white.
    detail::negate_bits<std::vector<byte_t>, std::true_type> _negate_bits;
    detail::swap_half_bytes<std::vector<byte_t>, std::true_type> _swap_half_bytes;

    std::function<void(this_t*, byte_t*)> _read_function;
    std::function<void(this_t*)> _skip_function;
};


} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
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
*/