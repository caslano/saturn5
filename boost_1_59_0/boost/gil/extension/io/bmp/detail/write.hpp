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

    template< typename ...Views >
    void apply( const any_image_view< Views... >& views )
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