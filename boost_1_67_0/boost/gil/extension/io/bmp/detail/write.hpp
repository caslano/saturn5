//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>
#include <boost/gil/extension/io/bmp/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

struct bmp_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , bmp_tag
                                   >
    {};
};

template < int N > struct get_bgr_cs {};
template <> struct get_bgr_cs< 1 > { using type = gray8_view_t; };
template <> struct get_bgr_cs< 3 > { using type = bgr8_view_t;  };
template <> struct get_bgr_cs< 4 > { using type = bgra8_view_t; };

} // namespace detail

///
/// BMP Writer
///
template< typename Device >
class writer< Device
            , bmp_tag
            >
    : public writer_backend< Device
                           , bmp_tag
                           >
{
public:

    writer( const Device&                      io_dev
          , const image_write_info< bmp_tag >& info
          )
    : backend_t( io_dev
                    , info
                    )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write( view );
    }

private:

    using backend_t = writer_backend<Device, bmp_tag>;

    template< typename View >
    void write( const View& view )
    {
        // using channel_t = typename channel_type<
        //             typename get_pixel_type<View>::type>::type;

        // using color_space_t = typename color_space_type<View>::type;

        // check if supported
/*
        /// todo
        if( bmp_read_write_support_private<channel_t, color_space_t>::channel != 8)
        {
            io_error("Input view type is incompatible with the image type");
        }
*/

        // compute the file size
        int bpp = num_channels< View >::value * 8;
        int entries = 0;

/*
        /// @todo: Not supported for now. bit_aligned_images refer to indexed images
        ///        in this context.
        if( bpp <= 8 )
        {
            entries = 1u << bpp;
        }
*/

        std::size_t spn = ( view.width() * num_channels< View >::value + 3 ) & ~3;
        std::size_t ofs = bmp_header_size::_size
                        + bmp_header_size::_win32_info_size
                        + entries * 4;

        std::size_t siz = ofs + spn * view.height();

        // write the BMP file header
        this->_io_dev.write_uint16( bmp_signature );
        this->_io_dev.write_uint32( (uint32_t) siz );
        this->_io_dev.write_uint16( 0 );
        this->_io_dev.write_uint16( 0 );
        this->_io_dev.write_uint32( (uint32_t) ofs );

        // writes Windows information header
        this->_io_dev.write_uint32( bmp_header_size::_win32_info_size );
        this->_io_dev.write_uint32( static_cast< uint32_t >( view.width()  ));
        this->_io_dev.write_uint32( static_cast< uint32_t >( view.height() ));
        this->_io_dev.write_uint16( 1 );
        this->_io_dev.write_uint16( static_cast< uint16_t >( bpp ));
        this->_io_dev.write_uint32( bmp_compression::_rgb );
        this->_io_dev.write_uint32( 0 );
        this->_io_dev.write_uint32( 0 );
        this->_io_dev.write_uint32( 0 );
        this->_io_dev.write_uint32( entries );
        this->_io_dev.write_uint32( 0 );

        write_image< View
                   , typename detail::get_bgr_cs< num_channels< View >::value >::type
                   >( view, spn );
    }


    template< typename View
            , typename BMP_View
            >
    void write_image( const View&       view
                    , const std::size_t spn
                    )
    {
        byte_vector_t buffer( spn );
        std::fill( buffer.begin(), buffer.end(), 0 );


        BMP_View row = interleaved_view( view.width()
                                       , 1
                                       , (typename BMP_View::value_type*) &buffer.front()
                                       , spn
                                       );

        for( typename View::y_coord_t y = view.height() - 1; y > -1; --y  )
        {
            copy_pixels( subimage_view( view
                                      , 0
                                      , (int) y
                                      , (int) view.width()
                                      , 1
                                      )
                       , row
                       );

            this->_io_dev.write( &buffer.front(), spn );
        }

    }
};

///
/// BMP Dynamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , bmp_tag
                          >
    : public writer< Device
                   , bmp_tag
                   >
{
    using parent_t = writer<Device, bmp_tag>;

public:

    dynamic_image_writer( const Device&                      io_dev
                        , const image_write_info< bmp_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename Views >
    void apply( const any_image_view< Views >& views )
    {
        detail::dynamic_io_fnobj< detail::bmp_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views
                       , op
                       );
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // gil
} // boost

#endif

/* write.hpp
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
*/