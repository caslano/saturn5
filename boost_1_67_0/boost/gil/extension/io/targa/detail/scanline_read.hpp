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