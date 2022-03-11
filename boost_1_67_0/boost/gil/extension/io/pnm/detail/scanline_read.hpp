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
+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
*/