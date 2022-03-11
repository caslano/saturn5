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