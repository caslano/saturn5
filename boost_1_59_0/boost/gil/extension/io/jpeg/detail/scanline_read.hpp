//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_SCANLINE_READ_HPP


#include <boost/gil/extension/io/jpeg/detail/base.hpp>
#include <boost/gil/extension/io/jpeg/detail/is_allowed.hpp>
#include <boost/gil/extension/io/jpeg/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <csetjmp>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

///
/// JPEG Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , jpeg_tag
                     >
    : public reader_backend< Device
                           , jpeg_tag
                           >
{
public:

    using tag_t = jpeg_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

public:
    scanline_reader( Device&                                device
                   , const image_read_settings< jpeg_tag >& settings
                   )
    : reader_backend< Device
                    , jpeg_tag
                     >( device
                      , settings
                      )
    {
        initialize();
    }

    void read( byte_t* dst
             , int
             )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark )) { this->raise_error(); }

        // read data
        read_scanline( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t* dst, int )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark )) { this->raise_error(); }

        // read data
        read_scanline( dst );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        this->get()->dct_method = this->_settings._dct_method;

        io_error_if( jpeg_start_decompress( this->get() ) == false
                    , "Cannot start decompression." );

        switch( this->_info._color_space )
        {
            case JCS_GRAYSCALE:
            {
                this->_scanline_length = this->_info._width;

                break;
            }

            case JCS_RGB:
            //!\todo add Y'CbCr? We loose image quality when reading JCS_YCbCr as JCS_RGB
            case JCS_YCbCr:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                break;
            }


            case JCS_CMYK:
            //!\todo add Y'CbCrK? We loose image quality when reading JCS_YCCK as JCS_CMYK
            case JCS_YCCK:
            {
                this->get()->out_color_space = JCS_CMYK;
                this->_scanline_length = this->_info._width * num_channels< cmyk8_view_t >::value;

                break;
            }

            default: { io_error( "Unsupported jpeg color space." ); }
        }
    }

    void read_scanline( byte_t* dst )
    {
        JSAMPLE *row_adr = reinterpret_cast< JSAMPLE* >( dst );

        // Read data.
        io_error_if( jpeg_read_scanlines( this->get()
                                        , &row_adr
                                        , 1
                                        ) != 1
                    , "jpeg_read_scanlines: fail to read JPEG file"
                    );

    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
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
*/