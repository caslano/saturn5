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
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
*/