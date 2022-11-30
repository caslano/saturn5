//
// Copyright 2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/targa/detail/is_allowed.hpp>
#include <boost/gil/extension/io/targa/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <vector>

namespace boost { namespace gil {

///
/// Targa Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , targa_tag
                     >
    : public reader_backend< Device
                           , targa_tag
                           >
{
public:

    using tag_t = targa_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

    //
    // Constructor
    //
    scanline_reader( Device&                                 device
                   , const image_read_settings< targa_tag >& settings
                   )
    : backend_t( device
                    , settings
                    )
    {
        initialize();
    }

    /// Read part of image defined by View and return the data.
    void read( byte_t* dst, int pos )
    {
        // jump to scanline
        long offset = this->_info._offset
                    + ( this->_info._height - 1 - pos ) * static_cast< long >( this->_scanline_length );

        this->_io_dev.seek( offset );


        read_row( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t*, int )
    {
        this->_io_dev.seek( static_cast<long>( this->_scanline_length )
                          , SEEK_CUR
                          );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        if( this->_info._color_map_type != targa_color_map_type::_rgb )
        {
            io_error( "scanline reader cannot read indexed targa files." );
        }

        if( this->_info._image_type != targa_image_type::_rgb )
        {
            io_error( "scanline reader cannot read this targa image type." );
        }

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

                if( this->_info._screen_origin_bit )
                {
                    io_error( "scanline reader cannot read targa files which have screen origin bit set." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    case 32:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        // jump to first scanline
                        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

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

    void read_row( byte_t* dst )
    {
        this->_io_dev.read( dst, this->_scanline_length );
    }
};

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
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
*/