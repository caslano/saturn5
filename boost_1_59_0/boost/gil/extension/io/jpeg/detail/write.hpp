//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/supported_types.hpp>
#include <boost/gil/extension/io/jpeg/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

namespace detail {

struct jpeg_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , jpeg_tag
                                   >
    {};
};

} // detail

///
/// JPEG Writer
///
template< typename Device >
class writer< Device
            , jpeg_tag
            >
    : public writer_backend< Device
                           , jpeg_tag
                           >
{
public:

    using backend_t = writer_backend<Device, jpeg_tag>;

public:

    writer( const Device&                       io_dev
          , const image_write_info< jpeg_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write_rows( view );
    }

private:

    template<typename View>
    void write_rows( const View& view )
    {
        std::vector< pixel< typename channel_type< View >::type
                          , layout<typename color_space_type< View >::type >
                          >
                   > row_buffer( view.width() );

        // In case of an error we'll jump back to here and fire an exception.
        // @todo Is the buffer above cleaned up when the exception is thrown?
        //       The strategy right now is to allocate necessary memory before
        //       the setjmp.
        if( setjmp( this->_mark )) { this->raise_error(); }

        using channel_t = typename channel_type<typename View::value_type>::type;

        this->get()->image_width      = JDIMENSION( view.width()  );
        this->get()->image_height     = JDIMENSION( view.height() );
        this->get()->input_components = num_channels<View>::value;
        this->get()->in_color_space   = detail::jpeg_write_support< channel_t
                                                                  , typename color_space_type< View >::type
                                                                  >::_color_space;

        jpeg_set_defaults( this->get() );

        jpeg_set_quality( this->get()
                        , this->_info._quality
                        , TRUE
                        );

        // Needs to be done after jpeg_set_defaults() since it's overridding this value back to slow.
        this->get()->dct_method = this->_info._dct_method;


        // set the pixel dimensions
        this->get()->density_unit = this->_info._density_unit;
        this->get()->X_density    = this->_info._x_density;
        this->get()->Y_density    = this->_info._y_density;

        // done reading header information

        jpeg_start_compress( this->get()
                           , TRUE
                           );

        JSAMPLE* row_addr = reinterpret_cast< JSAMPLE* >( &row_buffer[0] );

        for( int y =0; y != view.height(); ++ y )
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            jpeg_write_scanlines( this->get()
                                , &row_addr
                                , 1
                                );
        }

        jpeg_finish_compress ( this->get() );
    }
};

///
/// JPEG Dyamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , jpeg_tag
                          >
    : public writer< Device
                   , jpeg_tag
                   >
{
    using parent_t = writer<Device, jpeg_tag>;

public:

    dynamic_image_writer( const Device&                       io_dev
                        , const image_write_info< jpeg_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename ...Views >
    void apply( const any_image_view< Views... >& views )
    {
        detail::dynamic_io_fnobj< detail::jpeg_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views, op );
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