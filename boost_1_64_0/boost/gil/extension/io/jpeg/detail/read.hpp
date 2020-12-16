//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READ_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/base.hpp>
#include <boost/gil/extension/io/jpeg/detail/is_allowed.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <csetjmp>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

///
/// JPEG Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , jpeg_tag
            , ConversionPolicy
            >
    : public reader_base< jpeg_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , jpeg_tag
                           >
{
private:

    using this_t = reader<Device, jpeg_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, jpeg_tag>;

public:

    //
    // Constructor
    //
    reader( const Device&                          io_dev
          , const image_read_settings< jpeg_tag >& settings
          )
    : reader_base< jpeg_tag
                 , ConversionPolicy
                 >()

    , backend_t( io_dev
               , settings
               )
    {}

    //
    // Constructor
    //
    reader( const Device&                                          io_dev
          , const typename ConversionPolicy::color_converter_type& cc
          , const image_read_settings< jpeg_tag >&                 settings
          )
    : reader_base< jpeg_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark ))
        {
            this->raise_error();
        }

        this->get()->dct_method = this->_settings._dct_method;

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

        if( jpeg_start_decompress( this->get() ) == false )
        {
            io_error( "Cannot start decompression." );
        }

        switch( this->_info._color_space )
        {
            case JCS_GRAYSCALE:
            {
                this->_scanline_length = this->_info._width;
                read_rows< gray8_pixel_t >( view );

                break;
            }

            case JCS_RGB:
            //!\todo add Y'CbCr? We loose image quality when reading JCS_YCbCr as JCS_RGB
            case JCS_YCbCr:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                read_rows< rgb8_pixel_t  >( view );
                break;
            }

            case JCS_CMYK:
            //!\todo add Y'CbCrK? We loose image quality when reading JCS_YCCK as JCS_CMYK
            case JCS_YCCK:
            {
                this->get()->out_color_space = JCS_CMYK;
                this->_scanline_length = this->_info._width * num_channels< cmyk8_view_t >::value;

                read_rows< cmyk8_pixel_t >( view );

                break;
            }
            default: { io_error( "Unsupported jpeg color space." ); }
        }

        jpeg_finish_decompress ( this->get() );
    }

private:

    template< typename ImagePixel
            , typename View
            >
    void read_rows( const View& view )
    {
        using buffer_t = std::vector<ImagePixel>;
        buffer_t buffer( this->_info._width );

        // In case of an error we'll jump back to here and fire an exception.
        // @todo Is the buffer above cleaned up when the exception is thrown?
        //       The strategy right now is to allocate necessary memory before
        //       the setjmp.
        if( setjmp( this->_mark ))
        {
            this->raise_error();
        }


        JSAMPLE *row_adr = reinterpret_cast< JSAMPLE* >( &buffer[0] );

        //Skip scanlines if necessary.
        for( int y = 0; y <  this->_settings._top_left.y; ++y )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) !=1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );
        }

        // Read data.
        for( int y = 0; y < view.height(); ++y )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) != 1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );

            typename buffer_t::iterator beg = buffer.begin() + this->_settings._top_left.x;
            typename buffer_t::iterator end = beg + this->_settings._dim.x;

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }

        //@todo: There might be a better way to do that.
        while( this->get()->output_scanline < this->get()->image_height )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) !=1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );
        }

    }
};

namespace detail {

struct jpeg_type_format_checker
{
    jpeg_type_format_checker( jpeg_color_space::type color_space )
    : _color_space( color_space )
    {}

    template< typename Image >
    bool apply()
    {
        return is_read_supported< typename get_pixel_type< typename Image::view_t >::type
                                , jpeg_tag
                                >::_color_space == _color_space;
    }

private:

    jpeg_color_space::type _color_space;
};

struct jpeg_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , jpeg_tag
                                           >
    {};
};

} // namespace detail

///
/// JPEG Dynamic Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , jpeg_tag
                          >
    : public reader< Device
                   , jpeg_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, jpeg_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                          io_dev
                        , const image_read_settings< jpeg_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename Images >
    void apply( any_image< Images >& images )
    {
        detail::jpeg_type_format_checker format_checker( this->_info._color_space != JCS_YCbCr
                                                       ? this->_info._color_space
                                                       : JCS_RGB
                                                       );

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

            detail::dynamic_io_fnobj< detail::jpeg_read_is_supported
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
vhz1a0cTLvFm+/hjAGN84u3tQmbAAU3/fss7Vfx81TfE5FhE6fV4G1cy6pzpfhJnEDjyXc1qthkWNAVfw6qP03tQI6qP1PHHARZluzNraxcbiLb2xGA72hslWzMJx4pwoKtnQ4RsDitlXEdXT1d/Z6QdcW8StnmpRknZNTErhl2byY3MAxyyWGPDCLHA9p4M52yeJR5kmp72WGdrTzueUT3C8LhC8DHaKKlHIwMbosSNghJPRTvU9f1rY33RXuMmj7iyPEk4cxUztoXwA+4QbwKHhecBgMa2m4F4TGulsEPNNPo5kiWRcFkWU+drRXuW49Zf1bj4KJ19/D1UnM+nGwWumDOuIf09odFNu4Pa3c5G5UtCnDfupjhJ5yji4SjS65OIzsmCzjbmgeaIkg7NWa5V7y2cJsaQx5TPijMQp99Dnaf6rHcRH2fR3rh8MxTnP3w3Tc6PznHzDN0m7r2dR7zq9AcGpL8AuNJfx2mOY2k0SR5Y/u78TtPYSzzUi/ukl8i+kM+idV+GO/1UZqQV8nVl8z7Vz14m+pfXSvt3ir9CyH9Q2edcKdJKm3jg2bQf5HjDK+fNtD+k6u9ShPXdhw8rHMOjxvmoykffBb4G8fIceB7xO1Z21c7HG+kcQuG+NhC/xvkElcnI1n1Hl/llXrR/iRsUv3WK3xtLri3oQgU2VobTdoyVAL5TdVNj0T75M418X9AX3kw6ecVM/55InvMR79s12n0Ru0nohbH3acK8J/IFuc4qg09Z/lzIb09xC+l+n2h/t6m+IoE2c7vSpztI7z9DuFQ+ZRsR1Obx9ptXJ4Sjz/HuEnqYp0/TuJvbil5nVzhfU3U+X9X5vYiXtPabTvlRv/hgwF7DNxslDvdHPpxvCZ7WqPb7HU93iYcXKX4exV/E80ZhG0I8FIj+91TbMnlMCwv5iHuzD6m50RTSyfNJJ+cpnxYhhNeA9v5EGzIA3Yn/L6T/Y98939/5cSPdp6Z5ninHG8x8l87QW+i/vKP8E1F3Z6o5vbUrk3VHcpMyyQtbg7zaU3mUdP1Uoeu/VLr+OMJenm00vv5K1Gt1o79ef8NlNHHllfEJ1e8ZeEHs8+SVLdCTnkwoj8dVW/wDwse58y+EXEecmBXRtRP8XN8XxRwn4t19qRqLs6FHYBmcmrE4nUevidr7M/IuyVPI23obNbuwXs9j3ozz7rGUiETHVOK8Jp/KxQYL2e2JYo8mQLLv/bPoe58mvX5HhavXrwsJvRfhWhWuUuGD5B1bzdeiFjKP97hiAPP0N8HT843Cn4wINzvjlB0k7YESF17ByB7/BZHPi0R3r+OU8A+PV//deqDlogiPeU9B+/+Fn+8tyTzfxRXvH62g8eglMR5NK7P+qO/h+4fkbxRh4mGweJ5RMQd5GhiOXrNmvUTng5WA860GGz+4xSshh5Db/HHLh6B4P69K0Kwto86jk5Bd3tLEEUdyiO9Uz/NkBu8ytpLpHNOsX2oEL6EydcPnp6hSyxUvIcVTW41oDazWyJVgOSHXfUS+yysRL+TKIeQl++GumTx+8dhwoN7HBV3r13DO2Pl9L+3f94f8c/P953D/Cjwe6/ibR5/sX6fPYV4Yr1rZdc0Ajlw3gH2UP6DtjKNXdq+WyhKcNlB2nDZMae1em/Il9zphdz9njvIli7CU/VyEpX3LKWrf4jUiHml5nAaeu3cImKwLkimPQ/ht6+JAQWd2gA+0gzme92x865/XzXHLBnnbssl+dz7kr+0h9J7QoV651d5bRsyxJD87eL4kfMKVuHvcrGQAPWRcqY8tAk/S1HhLhA4Walh3fTq4TNCC7QefGx2p2sDygPqR52EHEt4Kal/Py7UrlfVwxOk=
*/