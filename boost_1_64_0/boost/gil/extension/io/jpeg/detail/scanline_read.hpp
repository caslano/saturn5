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
mnxZnjvdzndSifhoIbM2my5QHS8EXtgHb4uPDiZSbfFUakt8kMcSlB9liMYHE+2pFOVxCNIudFqNr/S4NxnCtrUt85vrTBk6kqPxFL1dzBRt2mWIX+4UHEsbcjzc8eL7ssk0vOzscnjMXe30J3fDzngd3V14VMip04kN9MXaWru717S2HQFV2NgVhUpsXGwlViLO9C9yH9ztg9fEc27/+4itww749TF8RzC92OVEqQ/7pezDgtuq0Nhx4r1zCOahO72D5DrDzjM6k1tHsF/vvaUm8w2YR/EbgOOOjROP23LuNU/Nxa7GXOysKslz36LOtPuWtgeDzrVoWMjpW6xhYadviYBRfn1LNWyh07dMwubbtkGa1mGPnRi+hOZEXj+13OlPbG3LcXiFCbcXw4ebcKQYXmnCHcXwahNeWwyvMeF+hCm/didiOZD8djrt2WanGO5DeJEIb0K4RYQ3I7xYhEcQXibCGYQPE+GdaIM7RXiPEx2U4XOc6JAM73WiW2T4cieay4jw1YiX4esQnxThm0BPhm91ostlee90om+R4fscLMEE/gMIy/I/jLAs/6MIy/I/gfASEf4zwktF+HknmvT4/a1pExUdqbxZ5hHsCQvrTMTRyfrmwRXdia3xwV0eDDoNfcb8t9nh8E0mvKgYvtOEW4rhB0x4cTH8qAkvKYb/bMJLOYxWi/CyYjhkwocVw/NMeHkx3GzCbymGV5swpOmF+2x4EYc323ALhzM2vJjDe2x4CYf32vBSG/6d4W/KRrvS8JYAsh6vrnLjaHXlsH5UtSe2FLZ64KKeVHXHc/k1WQweIwNp1JHUGRHXASe0Jpb1x8bxethNKvXJH0/J3bO51ZDwk6JffKCq9PxQriEr0K/JMT2kwiMVHGYbgZtpzfmxgDHf0IX3iAR8HlrhbE0MWfgfzFxRzQX+CFitWs99FbCw0z2UJZndiTD6wmx60LxtGjdzLbNA4/nFQk6/hP3FrXZa86mBkcLo8f1mVtGXzzo8bncy/lLuu/oYtoxpbGLYYYy3mWHLGTY0Jq/FLV6dPQX+RjjNWxxaU6LtsMyaPdzLZhid70uDhFvWLlyVjKYL2FHh/j413Zw5c9pFHvxPoHlrEd4ix4c7K/tBDNrSNWTn5cim8s9CT+6rHDsvj5Y/Fy97fDc69Mycoj/rj/jma232XiPvS2D8H4ynOpMCVu2sTaW3EFDsYdQ4tN0kYFOdXkzbHDEOYz5BD8/6xmI7r/AiXPizVv/sPMeuSWohr78IeT38MtYkgb79XuZczcxr/jrevIb5M2/qW2ISwHOj58UaydRBRWVxn6zZ7mVGOrHiTiWo7SyysA0+2D+sXDrjudZUcuvotgRqhufvLwiZVZXhz9bbv3zRpluTzNNcpo70I3180ltk8RvG/wRuVRl+JVcS7X9Z2gWH6CKtZTwxhNkuEee4WocLhfRkyyPKNG0S6yej+9A3tn+9Xuq+3P/E7poHryrC5bzKrr1ri3HRxCDt31G/FSrGeYqNOG+frMdejuZulOIqmkwfy+nMEje7Le7u0a6kM5dK4Hh/l09i/0COHZvV2LJzmn8/8+qpvnjk6g8/INJ7c/InSZZVTWPHou/ZPSXqTyOj25PZtK3QNan04PHemxZIN6LGpRrAHp3mH5emArZn5kAq159Kk25izQtYg3/8qQXeOQxbWhxPZnmwDuyYprhP3wf4mxGnx589s5BXZGcmPmo6bzfTBbTme5Woi3NmxQa8/nvA7b95r2OK+F09xd2b4P6ijL0JI+v9mlxZV0LWV5GspwGm19j7WphVVeHzGmtVNCzUQCq91eH+udLt73uHjcbnHN5zmeLupfAUzN13Ybhvn3k=
*/